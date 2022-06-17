#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

HKEY RootKey = HKEY_LOCAL_MACHINE;
LPCSTR SubKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Browser Helper Objects\\{00000000-0000-0000-0000-000000000000}";

int main(){

    string value = "ASEPs-BHO";

    set_registry_value(RootKey, SubKey, NULL, &value, NULL);

    return 0;
}