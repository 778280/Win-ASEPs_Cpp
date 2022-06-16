#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_CLASSES_ROOT;
LPCSTR SubKey = "CLSID\\{00000000-0000-0000-0000-000000000000}\\InprocServer32";

int main(){

    string value = "C:\\Una\\libreria.dll";

    set_registry_value(RootKey, SubKey, NULL, &value, NULL);

    return 0;
}