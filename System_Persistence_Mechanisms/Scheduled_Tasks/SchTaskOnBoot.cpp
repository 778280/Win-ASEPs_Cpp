#include <stdlib.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

string TaskName = "OnBootTask-ASEPs";
string ExePath = string(getenv("WINDIR")) + "\\Notepad.exe";

int main(){

    string binaryPath = newBinary(ExePath);

    string command = "schtasks /create /tn " + TaskName + " /tr " + binaryPath + " /sc onstart";

    return system(command.c_str());
}