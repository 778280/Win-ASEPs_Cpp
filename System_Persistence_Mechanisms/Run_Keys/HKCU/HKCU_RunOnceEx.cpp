#include <windows.h>
#include <string>

#include "../../../utils.h"

using namespace std;

HKEY RootKey = HKEY_CURRENT_USER;
LPCSTR SubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx";
LPCSTR SubKey_0001 = "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx\\0001";
string Name = "HKCU_RunOnceEx-ASEPs";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;


int main(){

    string binaryPath = newBinary(ExePath);
    DWORD flags = 0x00000002;
    string strValue = "rundll32.exe shell32.dll,ShellExec_RunDLL " + binaryPath;

    set_registry_value(RootKey, SubKey, "Title", &Name, NULL);
    set_registry_value(RootKey, SubKey, "Flags", NULL , &flags);
    set_registry_value(RootKey, SubKey_0001, "RunMyApp", &strValue, NULL);

    return 0;
}