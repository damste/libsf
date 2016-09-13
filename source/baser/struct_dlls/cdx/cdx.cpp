// cdx.cpp : Defines the exported functions for the DLL application.
//

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "\libsf\utils\common\cpp_vjr\include\common_types.h"
#include "\libsf\utils\common\cpp_vjr\include\datum.h"
#include "\libsf\utils\common\cpp_vjr\include\builder.h"
#include "\libsf\source\baser\source\baser_structs.h"


//////////
//
// DLL entry point
//
//////
	BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
			case DLL_PROCESS_DETACH:
				break;
		}
		return TRUE;
	}




//////////
//
// Decode the indicated data block
//
//////
	void cdx_decode_keyfor(SElement* el, SStructDllCallbacks* cb)
	{
		debug_nop;
	}
