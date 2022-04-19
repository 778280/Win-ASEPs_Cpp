#include <windows.h>
#include <string>

#include "../../../utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
LPCSTR Name = "HKLM_RunOnce-ASEPs";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;


int main(){

    string binaryPath = newBinary(ExePath);

    string strValue = "C:\\Windows\\System32\\rundll32.exe C:\\Windows\\System32\\shell32.dll,ShellExec_RunDLL " + binaryPath;

    set_registry_value(RootKey, SubKey, Name, &strValue, NULL);

    return 0;
}