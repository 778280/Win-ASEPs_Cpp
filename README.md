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
