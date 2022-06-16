#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR InstalledSDBSubKey   = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\InstalledSDB\\{00000000-0000-0000-0000-000000000000}";
LPCSTR CustomSubKey         = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Custom\\calc.exe";

int main(){

    string InstalledSDBValue    = "C:\\WINDOWS\\AppPatch\\CustomSDB\\{00000000-0000-0000-0000-000000000000}.sdb";

    set_registry_value(RootKey, InstalledSDBSubKey, "DatabasePath", &InstalledSDBValue, NULL);
    set_registry_value(RootKey, CustomSubKey, "{00000000-0000-0000-0000-000000000000}.sdb", NULL, NULL);

    return 0;
}