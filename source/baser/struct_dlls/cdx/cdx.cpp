// cdx.cpp : Defines the exported functions for the DLL application.
//

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Use VJr processing engine
#define _NONVJR_COMPILE		// Turns off some features in VJr that fail on compilation from here
#define _BMP_LOCALITY 1		// Force definitions to be local
#include "\libsf\source\vjr\source\vjr.h"

// Baser includes
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
				break;
			case DLL_PROCESS_DETACH:
				// Initialize VJr's internal engine
				iVjr_init_minimal();
				break;
		}
		return TRUE;
	}




//////////
//
// Decode the indicated data block
//
//////
	void cdx_decode_keyfor(s32 tnFileOffset, SBuilder* output, SElement* el, SStructDllCallbacks* cb)
	{
		debug_nop;
		// Read the required block from disk

		// Translate

		iBuilder_appendData(output, "cdx_decode_keyfor() was reached\n", -1);
	}
