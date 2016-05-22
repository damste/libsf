//////////
//
// /libsf/utils/sdebug/3rd_party/code/code.cpp
//
//////
//    _     _ _     _____ _____ 
//   | |   (_) |__ / ____|  ___|
//   | |   | | '_ \\___ \|  __|
//   | |___| | |_) |___) | |
//   |_____|_|_.__/_____/|_|
//
//   Liberty Software Foundation
// and the Village Freedom Project
//   __     _______     ____  
//   \ \   / /  ___| __|  _ \ 
//    \ \ / /| |_ | '__| |_) |
//     \ V / |  _|| |  |  __/ 
//      \_/  |_|  |_|  |_|
//
//////
// Version 0.01
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     May.22.2016
//////
// Change log:
//     May.22.2016 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//
// This program is a test vehicle for figuring out how to use Microsoft's debug API.
// Baby steps. :-)
//
//////




#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <dbghelp.h>

#include "/libsf/utils/common/cpp/include/common_types.h"
#include "/libsf/utils/common/cpp/include/time.h"
#include "/libsf/utils/common/cpp/base/time.cpp"

#include "/libsf/utils/common/cpp/include/sdebug/sdebug.h"



BOOL CALLBACK EnumSymProc(PSYMBOL_INFO symInfo, ULONG tnSymbolSize, void* param)
{
	// Display information about the DLL
    printf("            %08x, %4u, %s\n", (u32)symInfo->Address, tnSymbolSize, symInfo->Name);
	
	// Continue enumerating
    return(TRUE);
}




int enumDllSymbols(DWORD tnProcess, HANDLE thModule, char* tcDllName)
{
	bool		llInitialized;
	HANDLE		hProcess;
	int			lnResult;
    DWORD64		lnDllBase;


	// Attach as a debugger
if (_memicmp(tcDllName, "bugaboo.exe", 10) == 0)
{
	// Try to attach the debugger
	if (DebugActiveProcess(tnProcess))
		_asm nop;
}

	// Try to load symbols
	llInitialized	= false;
	lnResult		= -1;
	do {
		hProcess = GetCurrentProcess();
		if (!SymInitialize(hProcess, NULL, TRUE))
			break;
	    
		// Get the base address
		llInitialized	= true;
		lnDllBase		= SymLoadModuleEx(hProcess, NULL, tcDllName, NULL, 0, 0, NULL, 0);
		if (lnDllBase == 0)
			break;

		// Enumerate all of the symbols
		lnResult = ((SymEnumSymbols(hProcess, lnDllBase, "*", EnumSymProc, NULL)) ? 1 : -1);

	} while (0);

	// Clean house
	if (llInitialized)
		SymCleanup(hProcess);

	// Indicate our result
	return(lnResult);
}




int main(int argc, char* argv[])
{
	DWORD		lnI, lnJ, lnProcessesCount, lnSize;
	DWORD		lnaProcesses[2048];
	HANDLE		hProcess;
	HMODULE		lhaModules[2048];
	char		buffer[_MAX_PATH];

	// Grab the processes
	EnumProcesses(lnaProcesses, sizeof(lnaProcesses), &lnProcessesCount);
	lnProcessesCount /= sizeof(DWORD);

	// Iterate through each process
	for (lnI = 0; lnI < lnProcessesCount; lnI++)
	{
		// Open a handle to access processes
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, lnaProcesses[lnI]);
		if (!hProcess)
			continue;

		// Get the name
		if (EnumProcessModules(hProcess, lhaModules, sizeof(lhaModules), &lnSize))
		{
			// Display the name
			lnSize /= sizeof(DWORD);
			for (lnJ = 0; lnJ < lnSize; lnJ++)
			{
				GetModuleBaseNameA(hProcess, lhaModules[lnJ], buffer, sizeof(buffer));
				if (lnJ == 0)
				{
					// Process
					printf("%8u -- %s\n", lnaProcesses[lnI], buffer);

					// Enumerate the symbols for this module
					if (_memicmp(buffer, "code.exe", 8) != 0)
						enumDllSymbols(lnaProcesses[lnI], lhaModules[lnJ], buffer);

				} else {
					// Other modules
					printf("            %s\n", buffer);
				}
			}
		}

		// All done with this one
		CloseHandle(hProcess);
	}

	// Indicate success
	return(0);
}
