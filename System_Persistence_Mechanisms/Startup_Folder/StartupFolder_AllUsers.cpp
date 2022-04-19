#include <windows.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;
string Descrip = "StartupFolder_AllUsers";
string LnkPath = "Microsoft\\Windows\\Start Menu\\Programs\\Startup\\" + Descrip + ".lnk";
string WorkDir = getenv("USERPROFILE");

int main(){

    string binaryPath = newBinary(ExePath);
    string shortcutPath = string(getenv("ALLUSERSPROFILE")) + "\\" + LnkPath;

    create_shortcut(shortcutPath, binaryPath, Descrip, &WorkDir, NULL, NULL);

    return 0;
}