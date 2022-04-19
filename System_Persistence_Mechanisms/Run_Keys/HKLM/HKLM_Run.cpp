#include <windows.h>
#include <string>

#include "../../../utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
LPCSTR Name = "HKLM_Run-ASEPs";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;


int main(){

    string binaryPath = newBinary(ExePath);

    set_registry_value(RootKey, SubKey, Name, &binaryPath, NULL);

    return 0;
}