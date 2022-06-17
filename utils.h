#include <iostream>
#include <string>
#include <windows.h>
#include <list>

using namespace std;

void error(string mensaje);

string randName(int len, bool hex);

string newBinary(string exePath);

void createSampleDll(string path);

void set_registry_value(HKEY rootKey, LPCSTR subKey, LPCSTR name, string *strPtr, DWORD *numPtr, bool expand = false);

void create_shortcut(string linkPath, string targetPath, string description, string *workDir, string *arguments, string *iconLocation);

void modify_shortcut(string linkPath, string targetPath);

list<string> ls(string dirPath, string regEx = "*");

string newGuid();