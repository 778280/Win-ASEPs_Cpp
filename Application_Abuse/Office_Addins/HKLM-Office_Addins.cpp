#include <windows.h>
#include <string>
#include <list>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "SOFTWARE\\Microsoft\\Office\\Word\\Addins\\Word.ASEPs_Addin";

int main(){

    string OfficeBasePath = string(getenv("ProgramFiles")) + "\\Microsoft Office\\";

    list<string> dirs = ls(OfficeBasePath, "Office*");

    if(dirs.size() == 1){

        string dllPath = dirs.front() + "\\Addins\\ASEPs-Office_Addins.dll";

        createSampleDll(dllPath);

        DWORD value = 0x3;  //Automatic load at start

        set_registry_value(RootKey, SubKey, "LoadBehavior", NULL, &value);
    }

    return 0;
}