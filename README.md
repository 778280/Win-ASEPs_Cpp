# Win-ASEPs_Cpp
Proofs of concept for Windows ASEPs in c++

To compile use "g++ *source.cpp* *path_to_**utils.cpp*** -o *prog.exe* -lole32 -luuid -std=c++11"

Many of the generated executables will require the machine administrator privileges to be executed, mainly those compiled from the following source files:  
-HKLM_Run.cpp  
-HKLM_RunOnce.cpp  
-HKLM_RunOnceEx.cpp  
-StartupFolder_AllUsers.cpp  
-SchTaskOnLogon.cpp  
-SchTaskOnBoot.cpp  
-service.cpp  
-ImageFileExecOpts.cpp  
-Winlogon.cpp  
-Appinit-Sys32.cpp  
-Appinit-SysWow64.cpp  
-HKLM-ActiveSetup.cpp   

To ensure the aforementioned programs are executed with administrator privileges, an aplication manifest that changes the privilege level required for them to run can be embeded into the generated executable files. This can be done either during the program compilation process or once it has been compiled, here the steps to perform the latter aproach are listed:  
0. Microsoft [Visual Studio](https://visualstudio.microsoft.com/es/vs/) is needed for this aproach (Visual Studio Code won't work)
1. Open the compiled executable with Visual Studio
2. Right click on it and select add resource
3. Click *Import*
4. Select the manifest file to embed
5. In the *Resource Type* field, enter **RT_MANIFEST**
6. In the property grid, change the resource *ID* from **101** to **1**
7. Save the executable file