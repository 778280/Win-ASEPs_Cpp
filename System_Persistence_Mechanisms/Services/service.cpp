#include <stdlib.h>
#include <string>

#include "..\..\utils.h"

using namespace std;

string ServiceName = "Service-ASEPs";
string ExeName = "Cmd.exe";
string ExePath = string(getenv("WINDIR")) + "\\System32\\" + ExeName;

int main(){

    string binaryPath = newBinary(ExePath);

    string command = "sc.exe create " + ServiceName + " binPath= " + binaryPath + " start= auto" + " DisplayName= " + ServiceName ;
    
    return system(command.c_str());
}