//////////
//
// /libsf/utils/common/cpp/include/sdebug/sdebug.h
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
// SDebug is short for "Sanitizing Debugger".  It was designed to help find memory bugs.
// This source file contains all references necessary to perform a runtime link to the
// SDebug library.
//
// Within your application, use this general template:
//
// 		(1) Compile with these include files:
//			#include <windows.h>
//			#include "/libsf/utils/common/cpp/include/common_types.h"
// 			#include "/libsf/utils/common/cpp/include/sdebug/sdebug.h"
// 			#include "/libsf/utils/common/cpp/include/time.h"
// 			#include "/libsf/utils/common/cpp/base/time.cpp"
// 
// 		(2) Launch the SDebug.exe application and have it running in the background before
//			launching your application.  Your application cannot be being debugged by
//			another debugger (including Visual Studio) to have this SDebug library work.
//
//		(3) In your top-level main() function, add this code:
//				if ((lnResult = SDebug_wait_forConnect(nSecondsToWait, "earlyOutFunction")) < 0)
//				{
//					// -1 -- SDebug is not running
//					// -2 -- failed to connect / timeout
//					// -3 -- earlyOutFunction() not found
//					// Other negative values, other errors
//
//				} else {
//					// Connection was made, and it's now running in the sanitizing debugger.
//					// The global variable glSDebug will be low
//					// If SDebug terminates via user interaction, it will call earlyOutFunction()
//					// when it shuts down
//				}
//
//		(4) For every function you wish to track, add this:
//				s32 nHandle_myFunction1 = SDebug_trackFunction("my_function1");
//				s32 nHandle_myFunction2 = SDebug_trackFunction("my_function2");
//				s32 nHandle_myFunction3 = SDebug_trackFunction("my_function3");
//
//				// For arbitrary addresses, use:
//				s32 nHandle_myPartialFunction = SDebug_track_byAddress(&my_label1, (&my_label2 - &my_label1));
//
//		(5) To track everything, add this (Note:  This will be very slow as it decodes every instruction):
//				s32 nHandle_trackEverything = SDebug_trackEverything_start();
//
//		(6) To terminate something previously being tracked, such as my_function1():
//				SDebug_trackFunction_stop(nHandle_myFunction1);
//
//		(7) To terminate tracking everything, add this:
//				SDebug_trackEverything_stop();
//
//		(8) Parameters can be setup using:
//				s32 oldValue = SDebug_param_set(s32 index, s32 newValue);
//				// See the _SDEBUG_PARAM_* parameter indexes for settings
//
// SDebug will take control of the application on the indicated functions, or at all points.
// It will live-decode every assembly instruction and track all memory references.  When one
// occurs outside of a runtime boundary by the prescribed margin (settable using the indexes
// _SDEBUG_PARAM_MARGIN_FORE, and _SDEBUG_PARAM_MARGIN_AFT, in SDebug_param_set()), it will
// trap to the SDebug UI.  If _SDEBUG_PARAM_CALL_ON_ERROR has been set, then that function
// will be called.
//
// 
//
//////




//////////
// Index constants used for SDebug_param_get() and SDebug_param_set()
//////
	cu32		_SDEBUG_PARAM_MARGIN_FORE					= 1;			// Number of bytes before malloc() start
	cu32		_SDEBUG_PARAM_MARGIN_AFT					= 2;			// Number of bytes beyond malloc() end
	cu32		_SDEBUG_PARAM_CALL_ON_ERROR					= 3;			// void function(void* ptr, int badRefDelta) to call on error


//////////
// Messages send to SDebug's remote process
//////
	cu32		_SDEBUG_MSG_CONNECT							= WM_USER + 0;	// Tells SDebug to connect to this process
	cu32		_SDEBUG_MSG_TRACK_FUNCTION_BY_NAME			= WM_USER + 1;	// Tracks a function by name (for all IPs within the length of the function)
	cu32		_SDEBUG_MSG_TRACK_BY_ADDRESS_STEP1			= WM_USER + 2;	// Tracks a function by address for a length, or (until the next return)
	cu32		_SDEBUG_MSG_TRACK_BY_ADDRESS_STEP2			= WM_USER + 3;
	cu32		_SDEBUG_MSG_TRACK_FUNCTION_STOP				= WM_USER + 4;	// Stops tracking a previous function handle
	cu32		_SDEBUG_MSG_TRACK_EVERYTHING				= WM_USER + 5;	// Tracks everything (on or off)
	cu32		_SDEBUG_MSG_PARAM_GET						= WM_USER + 6;	// Returns a parameter by index
	cu32		_SDEBUG_MSG_PARAM_SET_STEP1					= WM_USER + 7;	// Sets a parameter by index
	cu32		_SDEBUG_MSG_PARAM_SET_STEP2					= WM_USER + 8;


//////////
// String constants
//////
	cs8			cgc_sdebug_messageWindowClass[]				= "SDebug.message.window";


//////////
// Functions used by SDebug
//////
	s32			iSDebug_timeBetween							(SYSTEMTIME* start, SYSTEMTIME* now);
	s64			iSDebug_getMilliseconds						(SYSTEMTIME* time);
	s32			SDebug_wait_forConnect						(s32 tnSecondsToWait, s8* tcEarlyOutFunctionName);
	s32			SDebug_trackFunction_byName					(s8* tcFunctionName);
	s32			SDebug_track_byAddress						(uptr tnFunctionAddress, s32 tnLength);
	s32			SDebug_trackFunction_stop					(s32 tnFunctionHandle);
	s32			SDebug_trackEverything_start				(void);
	s32			SDebug_trackEverything_stop					(void);
	s32			SDebug_param_get							(s32 index);
	s32			SDebug_param_set							(s32 index, s32 tnNewValue);


//////////
// Global SDebug state used internally
//////
	bool		glSDebug									= false;	// Global flag for when SDebug loads
	bool		glSDebug_earlyOutFunction_found				= false;	// Global flag for when SDebug loads
	HWND		hwnd_sdebug_messageWindow					= NULL;		// Handle for accessing the SDebug message window


//////////
// Sends up a signal flare, and waits for the SDebug to connect.
// Requires:  #include <windows.h>
//////
	s32 SDebug_wait_forConnect(s32 tnSecondsToWait, s8* tcEarlyOutFunctionName)
	{
		size_t		lnLength;
		HWND		lhwnd;
		SYSTEMTIME	start, now;
		HGLOBAL		earlyOutName;
		s8*			lcEarlyOutName;
		

		/////////
		// Locate SDebug's message window
		//////
			glSDebug							= false;
			glSDebug_earlyOutFunction_found		= false;
			tnSecondsToWait						= ((tnSecondsToWait < 1) ? 1 : tnSecondsToWait);

			// Iterate until we find the window (it could be loading right now)
			GetLocalTime(&start);
			for (lhwnd = NULL; !lhwnd && iTime_computeMillisecondsBetween(&start, &now) < tnSecondsToWait; Sleep(100), GetLocalTime(&now))
				lhwnd = FindWindowA(cgc_sdebug_messageWindowClass, NULL);

			// Did we timeout?
			if (!lhwnd || iTime_computeMillisecondsBetween(&start, &now) >= tnSecondsToWait)
				return(-1);	// SDebug is not running


		//////////
		// We found it, indicate our process for connection, and earlyOutFunction()
		//////
			if (tcEarlyOutFunctionName && (lnLength = strlen(tcEarlyOutFunctionName)) != 0)
			{
				// Allocate a global bit of memory for the name
				earlyOutName = GlobalAlloc(GMEM_ZEROINIT, lnLength + 1);
				if (earlyOutName)
				{
					// Lock
					lcEarlyOutName = (s8*)GlobalLock(earlyOutName);
					if (lcEarlyOutName)
					{
						// Copy
						memcpy(lcEarlyOutName, tcEarlyOutFunctionName, lnLength);
						GlobalUnlock(earlyOutName);

					} else {
						// Invalid
						GlobalFree(earlyOutName);
						earlyOutName = 0;
					}
				}

			} else {
				// No function
				earlyOutName = 0;
			}

			// Wait for acknowledgment
			SendMessage(lhwnd, _SDEBUG_MSG_CONNECT, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)earlyOutName);

			// Clean house
			if (earlyOutName)
				GlobalFree(earlyOutName);


		//////////
		// We've found the window, but we have to wait for it to connect to us and load any
		// PDB files.  This typically takes about 10 to 15 seconds max.
		//////
			for (tnSecondsToWait = 20; !glSDebug && iTime_computeMillisecondsBetween(&start, &now) < tnSecondsToWait; GetLocalTime(&now))
				Sleep(10);

			// Did we connect?
			if (!glSDebug || iTime_computeMillisecondsBetween(&start, &now) >= tnSecondsToWait)
				return(-2);

			// Was the connection found?
			if (tcEarlyOutFunctionName && !glSDebug_earlyOutFunction_found)
				return(-3);


		//////////
		// If we get here, we're good
		//////
			hwnd_sdebug_messageWindow = lhwnd;
			return(0);

	}

	s32 SDebug_trackFunction_byName(s8* tcFunctionName)
	{
		s32			lnResult;
		size_t		lnLength;
		HGLOBAL		funcName;
		s8*			lcFunctionName;


		// Make sure the environment is sane
		lnResult = -1;
		if (tcFunctionName && hwnd_sdebug_messageWindow)
		{
			// Grab a copy of the name
			lnLength	= strlen(tcFunctionName);
			funcName	= GlobalAlloc(GMEM_ZEROINIT, lnLength + 1);
			if (funcName)
			{
				// Lock
				if ((lcFunctionName = (s8*)GlobalLock(funcName)))
				{
					// Copy
					memcpy(lcFunctionName, tcFunctionName, lnLength);
					GlobalUnlock(funcName);

					// Send the message
					lnResult = (s32)SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_TRACK_FUNCTION_BY_NAME, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)funcName);

				} else {
					// Failure
					lnResult = -2;
				}

				// Clean house
				GlobalFree(funcName);
			}
		}

		// Indicate the status
		return(lnResult);
	}

	s32 SDebug_track_byAddress(uptr tnFunctionAddress, s32 tnLength)
	{
		s32 lnResult;


		// Make sure our environment is sane
		if (hwnd_sdebug_messageWindow && tnFunctionAddress && tnLength > 0)
		{
			// Two-part message
			lnResult = SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_TRACK_BY_ADDRESS_STEP1, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)tnFunctionAddress);
			lnResult = SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_TRACK_BY_ADDRESS_STEP2, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)tnLength);

			// Indicate our status
			return(lnResult);

		} else {
			// Invalid
			return(-1);
		}
	}

	s32 SDebug_trackFunction_stop(s32 tnFunctionHandle)
	{
		// Make sure our environment is sane
		if (hwnd_sdebug_messageWindow)		return(SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_TRACK_FUNCTION_STOP, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)tnFunctionHandle));
		else								return(-1);
	}

	s32 SDebug_trackEverything_start(void)
	{
		// Make sure our environment is sane
		if (hwnd_sdebug_messageWindow)		return(SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_TRACK_EVERYTHING, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)1));
		else								return(-1);
	}

	s32 SDebug_trackEverything_stop(void)
	{
		// Make sure our environment is sane
		if (hwnd_sdebug_messageWindow)		return(SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_TRACK_EVERYTHING, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)0));
		else								return(-1);
	}

	s32 SDebug_param_get(s32 index)
	{
		// Make sure our environment is sane
		if (hwnd_sdebug_messageWindow)		return(SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_PARAM_GET, (WPARAM)GetProcessId(GetCurrentProcess()), (LPARAM)index));
		else								return(-1);
	}

	s32 SDebug_param_set(s32 index, s32 tnNewValue)
	{
		s32		lnResult;
		DWORD	processId;


		// Make sure our environment is sane
		lnResult = -1;
		if (hwnd_sdebug_messageWindow)
		{
			// Send the message
			processId = GetProcessId(GetCurrentProcess());
			lnResult = (s32)SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_PARAM_SET_STEP1, (WPARAM)processId, (LPARAM)index);
			lnResult = (s32)SendMessage(hwnd_sdebug_messageWindow, _SDEBUG_MSG_PARAM_SET_STEP2, (WPARAM)processId, (LPARAM)tnNewValue);
		}

		// Indicate our success or failure
		return(lnResult);
	}
