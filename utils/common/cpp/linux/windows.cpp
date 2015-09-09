//////////
//
// /libsf/utils/common/cpp/linux/windows.cpp
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
// Version 0.55
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//    Jan.17.2014
//////
// Change log:
//    Jan.17.2014 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//    http://www.libsf.org/
//    http://www.libsf.org/licenses/
//    http://www.visual-freepro.org/vjr/indexmain.html
//    http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//  _       _         ___             _
// | |     (_)       |__ \           (_)
// | |      _  _ __     ) |__      __ _  _ __
// | |     | || '_ \   / / \ \ /\ / /| || '_ \
// | |____ | || | | | / /_  \ V  V / | || | | |
// |______||_||_| |_||____|  \_/\_/  |_||_| |_|
//     Linux to Windows -- Emulation Layer
//
//////////




//////////
//
// Called to create a window
//
//////
	WINUSERAPI HWND WINAPI CreateWindowEx(	__in DWORD		dwExStyle,
											__in_opt cs8*	lpClassName, __in_opt cs8* lpWindowName,
											__in DWORD		dwStyle,
											__in int		X, __in int Y, __in int nWidth, __in int nHeight,
											__in_opt		HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance,
											__in_opt LPVOID	lpParam)
	{
		SClassX*		cls;
		union {
			uptr		_win;
			SHwndX*		win;
		};


		// Make sure our environment is sane
		if (lpClassName && nWidth > 0 && nHeight > 0 && (cls = iHwndX_findClass_byName(lpClassName)))
		{
			// Allocate a new window
			win = (SHwndX*)iBuilder_appendData(gsWindows, (cs8*)NULL, sizeof(SHwndX));
			if (win)
			{
				//////////
				// Populate
				//////
					win->hwnd		= (uptr)_win;
					win->isValid	= true;
					win->isVisible	= false;
					win->isEnabled	= true;
					win->nThreadId	= pthread_self();
					win->clsx		= cls;

					SetRect(&win->rc, X, Y, X + nWidth, Y + nHeight);
					CopyRect(&win->rcClient, &win->rc);
					iBuilder_createAndInitialize(&win->msgQueue, -1);

					iDatum_duplicate(&win->cClass, (cu8*)lpClassName,	strlen(lpClassName)		+ 1);
					iDatum_duplicate(&win->cTitle, (cu8*)lpWindowName,	strlen(lpWindowName)	+ 1);

					// Createstruct used for callback
					win->data.lpCreateParams	= lpParam;
					win->data.style				= dwStyle;
					win->data.dwExStyle			= dwExStyle;
					win->data.x					= X;
					win->data.y					= Y;
					win->data.cx				= nWidth;
					win->data.cy				= nHeight;
					win->data.hwndParent		= hWndParent;
					win->data.hMenu				= hMenu;
					win->data.hInstance			= hInstance;
					win->data.lpszClass			= win->cClass.data_cs8;
					win->data.lpszName			= win->cTitle.data_cs8;


				//////////
				// Ask HwndX to send out the CreateWindow() messages into the msgQueue
				//////
					iHwndX_createWindow(win);


				//////////
				// If it's initially visible, go ahead and show it
				//////
					if ((dwStyle & WS_VISIBLE) != 0)
						ShowWindow(win->hwnd, SW_SHOW);


				//////////
				// Indicate success
				//////
					return(win->hwnd);
			}
		}

		// If we get here, the window could not be created
		return(0);
	}




//////////
//
// Sets a callback timer for a window, or for an indicated function
//
//////
	WINUSERAPI UINT_PTR WINAPI SetTimer(__in_opt HWND hWnd, __in s32 nIDEvent, __in UINT uElapse, sptr lpTimerFunc)
	{
		bool		llSuccess;
		SHwndX*		win;
		union {
			s32			_eventId;
			UINT_PTR	eventId;
		};


		//////////
		// Either window timer, or general timer
		//////
			llSuccess = false;
			if (hWnd)
			{
				// They are applying the timer directly to the hWnd as a message in queue
				// Locate the window
				win = iHwndX_findWindow_byHwnd(hWnd);
				if (win && win->isValid)
					llSuccess = iHwndX_addTimer(win, nIDEvent, uElapse, 0);

			} else {
				// It is a general timer that goes to a specific function address
				llSuccess = iHwndX_addTimer(NULL, nIDEvent, uElapse, lpTimerFunc);
			}


		//////////
		// Indicate success or failure
		//////
			if (llSuccess)
			{
				// Indicate success
				_eventId = nIDEvent;
				return(eventId);

			} else {
				// Failure
				return(NULL);
			}
	}




//////////
//
// Called to display a message box
//
//////
	const SDL_MessageBoxButtonData mb_buttons_ok[] =
	{
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "ok" }
	};
	const int mb_buttons_ok_choice[] = { IDOK };

	const SDL_MessageBoxButtonData mb_buttons_ok_cancel[] =
	{
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "ok" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "cancel" }
	};
	const int mb_buttons_ok_cancel_choice[] = { IDOK, IDCANCEL };

	const SDL_MessageBoxButtonData mb_buttons_yes_no_cancel[] =
	{
		{ /* .flags, .buttonid, .text */		0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" }
	};
	const int mb_buttons_yes_no_cancel_choice[] = { IDNO, IDYES, IDCANCEL };

	const SDL_MessageBoxButtonData mb_buttons_abort_retry_ignore[] =
	{
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "abort" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "retry" },
		{ /* .flags, .buttonid, .text */		0, 2, "ignore" }
	};
	const int mb_buttons_abort_retry_ignore_choice[] = { IDABORT, IDRETRY, IDIGNORE };

	const SDL_MessageBoxButtonData mb_buttons_yes_no[] =
	{
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "yes" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "no" }
	};
	const int mb_buttons_yes_no_choice[] = { IDYES, IDNO };

	const SDL_MessageBoxButtonData mb_buttons_retry_cancel[] =
	{
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "retry" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "cancel" }
	};
	const int mb_buttons_retry_cancel_choice[] = { IDRETRY, IDCANCEL };

	const SDL_MessageBoxButtonData mb_buttons_cancel_retry_continue[] =
	{
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "cancel" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "retry" },
		{ /* .flags, .buttonid, .text */		0, 2, "continue" }
	};
	const int mb_buttons_cancel_retry_continue_choice[] = { IDCANCEL, IDRETRY, IDCONTINUE };

	const SDL_MessageBoxColorScheme mb_colorScheme_information =
	{
		{ /* .colors (.r, .g, .b) */
			{ 255, 255, 255 },		// [SDL_MESSAGEBOX_COLOR_BACKGROUND]
			{   0,   0,   0 },		// [SDL_MESSAGEBOX_COLOR_TEXT]
			{   0,   0, 255 },		// [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
			{ 112, 164, 255 },		// [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
			{ 255, 255, 128 }		// [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
		}
	};

	const SDL_MessageBoxColorScheme mb_colorScheme_warning =
	{
		{ /* .colors (.r, .g, .b) */
			{ 255, 255, 192 },		// [SDL_MESSAGEBOX_COLOR_BACKGROUND]
			{   0,   0,   0 },		// [SDL_MESSAGEBOX_COLOR_TEXT]
			{   0,   0, 255 },		// [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
			{ 112, 164, 255 },		// [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
			{ 128, 255, 255 }		// [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
		}
	};

	const SDL_MessageBoxColorScheme mb_colorScheme_error =
	{
		{ /* .colors (.r, .g, .b) */
			{ 255, 128, 128 },		// [SDL_MESSAGEBOX_COLOR_BACKGROUND]
			{   0,   0,   0 },		// [SDL_MESSAGEBOX_COLOR_TEXT]
			{   0,   0, 255 },		// [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]
			{ 112, 164, 255 },		// [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]
			{ 255, 255, 255 }		// [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]
		}
	};

	WINUSERAPI int WINAPI MessageBox(__in_opt HWND hWnd, __in_opt cs8* lpText, __in_opt cs8* lpCaption, __in UINT uType)
	{
		int					lnChoice;
		const int*			buttonChoiceTranslation;
		SDL_MessageBoxData	messageboxdata;


		// Initialize
		memset(&messageboxdata, 0, sizeof(messageboxdata));
		messageboxdata.title		= lpCaption;
		messageboxdata.message		= lpText;


		//////////
		// Establish the expected values
		//////
			switch (uType)
			{
				default:
				case MB_OK:
					messageboxdata.buttons		= &mb_buttons_ok[0];
					messageboxdata.numbuttons	= 1;
					buttonChoiceTranslation		= &mb_buttons_ok_choice[0];
					break;
				case MB_OKCANCEL:
					messageboxdata.buttons		= &mb_buttons_ok_cancel[0];
					messageboxdata.numbuttons	= 2;
					buttonChoiceTranslation		= &mb_buttons_ok_cancel_choice[0];
					break;
				case MB_ABORTRETRYIGNORE:
					messageboxdata.buttons		= &mb_buttons_abort_retry_ignore[0];
					messageboxdata.numbuttons	= 3;
					buttonChoiceTranslation		= &mb_buttons_abort_retry_ignore_choice[0];
					break;
				case MB_YESNOCANCEL:
					messageboxdata.buttons		= &mb_buttons_yes_no_cancel[0];
					messageboxdata.numbuttons	= 3;
					buttonChoiceTranslation		= &mb_buttons_yes_no_cancel_choice[0];
					break;
				case MB_YESNO:
					messageboxdata.buttons		= &mb_buttons_yes_no[0];
					messageboxdata.numbuttons	= 2;
					buttonChoiceTranslation		= &mb_buttons_yes_no_choice[0];
					break;
				case MB_RETRYCANCEL:
					messageboxdata.buttons		= &mb_buttons_retry_cancel[0];
					messageboxdata.numbuttons	= 2;
					buttonChoiceTranslation		= &mb_buttons_retry_cancel_choice[0];
					break;
				case MB_CANCELTRYCONTINUE:
					messageboxdata.buttons		= &mb_buttons_cancel_retry_continue[0];
					messageboxdata.numbuttons	= 3;
					buttonChoiceTranslation		= &mb_buttons_cancel_retry_continue_choice[0];
					break;
			}


		//////////
		// Establish the message box type
		//////
			switch (uType & 0x70)
			{
				default:
					messageboxdata.flags		= SDL_MESSAGEBOX_INFORMATION;
					messageboxdata.colorScheme	= &mb_colorScheme_information;
					break;
				case MB_ICONWARNING:
					messageboxdata.flags		= SDL_MESSAGEBOX_WARNING;
					messageboxdata.colorScheme	= &mb_colorScheme_warning;
					break;
				case MB_ICONERROR:
					messageboxdata.flags		= SDL_MESSAGEBOX_ERROR;
					messageboxdata.colorScheme	= &mb_colorScheme_error;
					break;
			}


		//////////
		// Display the message box
		//////
			lnChoice = -2;	// Default to an error code
			if (SDL_ShowMessageBox(&messageboxdata, &lnChoice) < 0)
			{
				// Error
				return(lnChoice);
			}


		//////////
		// Indicate their choice
		//////
			return(buttonChoiceTranslation[lnChoice]);
	}




//////////
//
// Called to create a new thread
//
//////
	WINBASEAPI HANDLE WINAPI CreateThread(	__in_opt LPSECURITY_ATTRIBUTES				lpThreadAttributes,
											__in SIZE_T									dwStackSize,
											__in LPTHREAD_START_ROUTINE					lpStartAddress,
											__in_opt __deref __drv_aliasesMem LPVOID	lpParameter,
											__in DWORD									dwCreationFlags,
											__out_opt LPDWORD							lpThreadId)
	{
		pthread_t			lnThreadId;
		pthread_attr_t		attr;
		void*				stackptr;
		union {
			LPTHREAD_START_ROUTINE	_startRoutine;
			void*					(*startRoutine)(void*);
		};


		// Make sure we have a target for the thread id
		if (!lpThreadId)
			lpThreadId = (DWORD*)&lnThreadId;

// TODO:  Honor dwCreationFlags

		// Iterate through the pthread process to verify we can create the thread successfully
		if (pthread_attr_init(&attr) == 0)
		{
			if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) == 0)
			{
				if (pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) == 0)
				{
					if (posix_memalign(&stackptr, sysconf(_SC_PAGESIZE), _CREATE_THREAD_DEFAULT_STACK_SIZE) == 0)
					{
						if (pthread_attr_setstack(&attr, stackptr, _CREATE_THREAD_DEFAULT_STACK_SIZE) == 0)
						{
							_startRoutine = lpStartAddress;
							if (pthread_create((pthread_t*)lpThreadId, &attr, startRoutine, lpParameter) == 0)
							{
								// If we get here, the thread was created successfully
								return(*lpThreadId);
							}
						}
					}
				}
			}
		}

		// If we get here, failure
		pthread_attr_destroy(&attr);
		return(-1);
	}




//////////
//
// Exits the thread
//
//////
	WINBASEAPI VOID WINAPI ExitThread(__in DWORD dwExitCode)
	{
		pthread_exit((void*)(uptr)dwExitCode);
	}




//////////
//
// Retrieves the class indicated by the name.
// Note:  The instance is ignored because in this context there's only one instance you see. :-)
//
//////
	WINUSERAPI BOOL WINAPI GetClassInfoExA(__in_opt HINSTANCE hInstance, __in cs8* lpszClass, __out WNDCLASSEX* lpwcx)
	{
		SClassX* cls;


		// Make sure the environment is sane
		if (lpszClass && lpwcx && gsClasses)
		{
			// Iterate through all of the defined classes and report
			cls = iHwndX_findClass_byName(lpszClass);
			if (cls)
			{
				// Indicate success
				memcpy(lpwcx, &cls->wcx, sizeof(WNDCLASSEX));
				return(TRUE);
			}
			// If we get here, the class wasn't found
		}

		// If we get here, failure
		return(FALSE);
	}




//////////
//
// Registers a class if it doesn't already exist
//
//////
	WINUSERAPI ATOM WINAPI RegisterClassExA(__in CONST WNDCLASSEX* lpwcx)
	{
		union {
			uptr		_cls;
			SClassX*	cls;
		};
		WNDCLASSEX	wcx;


		// Make sure there is a class builder
		if (!gsClasses)
			iBuilder_createAndInitialize(&gsClasses, -1);

		// make sure our environment is sane
		if (gsClasses && lpwcx)
		{
			// See if the class already exists
			if (!GetClassInfoExA(lpwcx->hInstance, lpwcx->lpszClassName, &wcx))
			{
				// Does not exist, add it
				cls = (SClassX*)iBuilder_appendData(gsClasses, NULL, sizeof(SClassX));
				if (cls)
				{
					// Initialize
					cls->isValid = true;
					iDatum_duplicate(&cls->cClass, (cu8*)lpwcx->lpszClassName, -1);

					// Copy over the WNDCLASSEX structure
					memcpy(&cls->wcx, lpwcx, sizeof(WNDCLASSEX));

					// Indicate our "atom" return value
					return(_cls & 0xffff);
				}
			}
			// If we get here, it already exists
		}

		// If we get here, failure
		return(0);
	}




//////////
//
// Peek or grab the next message from the queue.
// Note:  This function is not fully implemented.  It only honors PM_NOREMOVE, and !PM_NOREMOVE.
//		It does not honor other PM_* settings, and will simply remove or not remove based on
//		the value PM_NOREMOVE.
//
//////
	WINUSERAPI BOOL WINAPI PeekMessage(__out MSG* lpMsg, __in_opt HWND hWnd, __in UINT wMsgFilterMin, __in UINT wMsgFilterMax, __in UINT wRemoveMsg)
	{
		u32			lnI;
		SHwndX*		win;
		SMessageX*	msg;
		pthread_t	lnThreadId;


		// Make sure our environment is sane
		if (lpMsg)
		{
			// Grab the current thread (because Windows only allows hwnd messages to be read
			// for those windows created in the current thread)
			lnThreadId = pthread_self();

			// Iterate through every window to see which one of them has a message to dispatch
			for (lnI = 0, win = (SHwndX*)gsWindows->buffer; lnI < gsWindows->populatedLength; lnI += sizeof(SHwndX), win++)
			{
				// Is this entry valid?
				if (win->isValid)
				{
					// Is it our hwnd?
					if (hWnd == null0 || hWnd == win->hwnd)
					{
						// Is this window valid?
						if (win->msgQueue && win->nThreadId == lnThreadId && win->msgQueue->populatedLength > 0)
						{
							// This one is for our thread, it has a message queue, and it matches the hWnd filter
							// If no filter, it's always the top message
							if (wMsgFilterMin == 0 && wMsgFilterMax == 0)
							{
								// Dispatch the top message
								memcpy(lpMsg, &((SMessageX*)win->msgQueue->buffer)->msg, sizeof(*lpMsg));

								// Delete if need be
								if (wRemoveMsg != PM_NOREMOVE)
									iBuilder_delete(win->msgQueue, 0, sizeof(SMessageX));

								// Indicate success
								return(TRUE);

							} else {
								// Only filtered messages
								for (lnI = 0, msg = (SMessageX*)win->msgQueue->buffer; lnI < win->msgQueue->populatedLength; lnI += sizeof(SMessageX), msg++)
								{
									// Is this within the range?
									if (msg->msg.message >= wMsgFilterMin && msg->msg.message <= wMsgFilterMax)
									{
										// Yes, dispatch this message
										memcpy(lpMsg, &msg->msg, sizeof(*lpMsg));

										// Delete if need be
										if (wRemoveMsg != PM_NOREMOVE)
											iBuilder_delete(win->msgQueue, lnI, sizeof(SMessageX));

										// Indicate success
										return(TRUE);
									}
								}
							}
						}
						// When we get here, the message has no mesages waiting
						if (hWnd == win->hwnd)
							break;	// We were only searching for this one window, and now we're done
					}
				}
				// If we get here, no messages are waiting for this window
			}
		}

		// If we get here, not valid
		return(FALSE);
	}




//////////
//
// Grab the next message from the queue
//
//////
	WINUSERAPI BOOL WINAPI GetMessage(__out LPMSG lpMsg, __in_opt HWND hWnd, __in UINT wMsgFilterMin, __in UINT wMsgFilterMax)
	{
		// Call PeekMessage() with a consume setting
		return(PeekMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, PM_NOREMOVE));
	}




//////////
//
// Called to translate the raw message into possibly other messages based on ... who knows? :-)
// Note:  This is not supported because all messages are untranslated, but go through raw
//		(because we handle the signaled messages anyway you see)
//
//////
	WINUSERAPI BOOL WINAPI TranslateMessage(__in CONST MSG *lpMsg)
	{
		// No translations are currently processed, so we pass through exactly as is
		return(TRUE);
	}




//////////
//
// Called to call the wndProc() for the indicated message context
//
//////
	WINUSERAPI LRESULT WINAPI DispatchMessage(__in CONST MSG *lpMsg)
	{
		SHwndX* win;


		// Make sure our environment is sane
		if (lpMsg)
		{
			// They are retrieving from a particular window for the current thread
			win = iHwndX_findWindow_byHwnd(lpMsg->hwnd);

			// If valid, call the associated wndProc()
			if (win)
				return(win->clsx->wcx.lpfnWndProc(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam));

			// If we get here, we didn't find the indicated message, so ignore it
		}
		return(0);
	}




//////////
//
// Basic default wndProc() which quits, and then draws basic stuff.  It also updates
// the win->pt position as the mouse moves.
//////
	LRESULT CALLBACK DefWindowProc(__in HWND hWnd, __in UINT Msg, __in WPARAM wParam, __in LPARAM lParam)
	{
		SHwndX*			win;
		HDC				hdc;
		PAINTSTRUCT		ps;


		// Try to find the window
		win = iHwndX_findWindow_byHwnd(hWnd);
		if (win && win->isValid)
		{
			// Process the message
			switch (Msg)
			{
				case WM_QUIT:
					// They are wanting to quit the app
					exit(wParam);
					break;

				case WM_ERASEBKGND:
				case WM_PAINT:
					if (win->isVisible)
					{
						// By default, we simply paint it white
						hdc = BeginPaint(hWnd, &ps);
						FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));
						EndPaint(hWnd, &ps);
					}
					break;
			}
		}

		// If we get here, the window is invalid ... ignore it
		return(0);
	}




//////////
//
// Posts the message to the indicated window if it's valid
//
//////
	WINUSERAPI BOOL WINAPI PostMessage(__in_opt HWND hWnd, __in UINT Msg, __in WPARAM wParam, __in LPARAM lParam)
	{
		// If possible, post the associated message
		return(iHwndX_postMessage_byHwnd(hWnd, Msg, wParam, lParam));
	}




//////////
//
// Returns the "pseudo desktop window" which is always the first window
//
//////
	WINUSERAPI HWND WINAPI GetDesktopWindow(VOID)
	{
		return(ghWndDesktop);
	}




//////////
//
// Called to obtain the client rectangle for the specified window
//
//////
	WINUSERAPI BOOL WINAPI GetClientRect(__in HWND hWnd, __out LPRECT lpRect)
	{
		SHwndX* win;


		// Locate the window
		win = iHwndX_findWindow_byHwnd(hWnd);

		// Is it valid?
		if (win && win->isValid)
		{
			// Yes, indicate success
			CopyRect(lpRect, &win->rcClient);
			return(TRUE);
		}

		// If we get here, failure
		return(FALSE);
	}




//////////
//
// Called to obtain the window rectangle for the specified window
//
//////
	WINUSERAPI BOOL WINAPI GetWindowRect(__in HWND hWnd, __out LPRECT lpRect)
	{
		SHwndX* win;


		// Locate the window
		win = iHwndX_findWindow_byHwnd(hWnd);

		// Is it valid?
		if (win && win->isValid)
		{
			// Yes, indicate success
			CopyRect(lpRect, &win->rc);
			return(TRUE);
		}

		// If we get here, failure
		return(FALSE);
	}




//////////
//
// Defines a Windows rectangle
//
//////
	WINUSERAPI BOOL WINAPI SetRect(__out LPRECT lprc, __in int xLeft, __in int yTop, __in int xRight, __in int yBottom)
	{
		// Make sure our environment is sane
		if (lprc)
		{
			// Set the coordinates
			lprc->left		= xLeft;
			lprc->top		= yTop;
			lprc->right		= xRight;
			lprc->bottom	= yBottom;

			// If we get here, success
			return(TRUE);
		}
		// If we get here, failure
		return(FALSE);
	}




WINGDIAPI HGDIOBJ WINAPI SelectObject(__in HDC hdc, __in HGDIOBJ h)
{
	SHdcX*			hdcx;
	union {
		HGDIOBJ		_hOld;
		SFont*		fontOld;
	};
	union {
		HGDIOBJ		_h;
		SFont*		font;
	};



	// Locate the HDC
	hdcx = iHwndX_findHdc_byHdc(hdc);
	if (hdcx)
	{
		// See what type of object it is
		_h = h;


		//////////
		// Font?
		//////
			if (iBuilder_isPointer(gsHfonts, _h))
			{
				// They're selecting a font into this hdc
				fontOld		= hdcx->font;
				hdcx->font	= font;
				return(_hOld);
			}
	}


	//////////
	// If we get here, it wasn't a valid object
	//////
		return(-1);
}




WINGDIAPI COLORREF WINAPI SetTextColor(__in HDC hdc, __in COLORREF color)
{
	SHdcX*	hdcx;
	u32		lnColor;


	//////////
	// Get the HDC
	//////
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx && hdcx->isValid)
		{
			// Set the color
			lnColor					= hdcx->colorFore.color;
			hdcx->colorFore.color	= color;

			// Make sure the alpha channel is fully saturated
			hdcx->colorFore.alp		= 255;

		} else {
			// Set to black
			lnColor					= 0;
		}


	//////////
	// Return
	//////
		return(lnColor);
}




WINGDIAPI int WINAPI SetBkMode(__in HDC hdc, __in int mode)
{
	SHdcX* hdcx;


	//////////
	// Find the HDC
	//////
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx)
		{
			// We're good, set the mode
			hdcx->isOpaque = (mode == OPAQUE);

			// Indicate success
			return(1);
		}


	//////////
	// Could not find HDC
	//////
		// Indicate failure
		return(0);
}




//////////
//
// For DT_CALCRECT:
//
//		XTextExtents()
//		XQueryTextExtents()
//
//////////
WINUSERAPI int WINAPI DrawText(__in HDC hdc, cs8* lpchText, __in int cchText, __inout LPRECT lprc, __in UINT format)
{
	int				direction, ascent, descent;
	XCharStruct		cs;
	SHdcX*			hdcx;
	SHwndX*			hwndx;
	RECT			lrc;


	// Make sure our environment is sane
	if (lpchText && cchText > 0 && lprc)
	{
		// Locate the associated hdcx
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx)
		{
			// Locate the associated window to this hdcx
			hwndx = iHwndX_findWindow_byHdcx(hdcx);
			if (hwndx && hwndx->x11)
			{
				//////////
				// Compute the size of the rectangle
				//////
					if ((format & DT_CALCRECT) != 0 || (format & DT_CENTER) != 0 || (format & DT_RIGHT) != 0)
					{
						// Query the extents
						XQueryTextExtents(hwndx->x11->display, hwndx->x11->gc->gid, lpchText, cchText, &direction, &ascent, &descent, &cs);

						// Populate the rectangle
						SetRect(&lrc, 0, 0, cs.width, cs.ascent + cs.descent);
					}


				//////////
				// Are we computing the rectangle for this text?
				//////
					if (format & DT_CALCRECT)
					{
						// Copy the extents
						CopyRect(lprc, &lrc);

					} else {
// TODO:  honor the other flags
						if (format & DT_CENTER)
						{
							// Draw centered within the area
							if (cs.width <= lprc->right - lprc->left)
							{
								// The entire string will fit inside the rectangle
								if (format & DT_VCENTER)
								{
									// Center vertically
									XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
													(lprc->left + lprc->right - cs.width) / 2,
													((lprc->top + lprc->bottom) / 2) - ((cs.ascent + cs.descent) / 2),
													lpchText, cchText);

								} else if (format & DT_BOTTOM) {
									// Draw at the bottom
									XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
													(lprc->left + lprc->right - cs.width) / 2,
													lprc->bottom - cs.ascent - cs.descent,
													lpchText, cchText);

								} else {
									// Draw at top
									XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
													(lprc->left + lprc->right - cs.width) / 2,
													lprc->top,
													lpchText, cchText);
								}

							} else {
								// It's too wide, so we draw from the lefft
								if (format & DT_VCENTER)
								{
									// Center vertically
									XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
													lprc->left,
													((lprc->top + lprc->bottom) / 2) - ((cs.ascent + cs.descent) / 2),
													lpchText, cchText);

								} else if (format & DT_BOTTOM) {
									// Draw at the bottom
									XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
													lprc->left,
													lprc->bottom - cs.ascent - cs.descent,
													lpchText, cchText);

								} else {
									// Draw at top
									XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
													lprc->left,
													lprc->top,
													lpchText, cchText);
								}
							}

						} else if (format & DT_RIGHT) {
							// Draw right-justified
							if (format & DT_VCENTER)
							{
								// Center vertically
								XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
												max(lprc->left, lprc->right - cs.width),
												((lprc->top + lprc->bottom) / 2) - ((cs.ascent + cs.descent) / 2),
												lpchText, cchText);

							} else if (format & DT_BOTTOM) {
								// Draw at the bottom
								XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
												max(lprc->left, lprc->right - cs.width),
												lprc->bottom - cs.ascent - cs.descent,
												lpchText, cchText);

							} else {
								// Draw at top
								XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
												max(lprc->left, lprc->right - cs.width),
												lprc->top,
												lpchText, cchText);
							}

						} else {
							// Draw left-justified
							if (format & DT_VCENTER)
							{
								// Center vertically
								XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
												lprc->left,
												((lprc->top + lprc->bottom) / 2) - ((cs.ascent + cs.descent) / 2),
												lpchText, cchText);

							} else if (format & DT_BOTTOM) {
								// Draw at the bottom
								XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
												lprc->left,
												lprc->bottom - cs.ascent - cs.descent,
												lpchText, cchText);

							} else {
								// Draw at top
								XDrawString(hwndx->x11->display, hwndx->x11->drawable, hwndx->x11->gc,
												lprc->left,
												lprc->top,
												lpchText, cchText);
							}
						}
					}


				//////////
				// Indicate success
				//////
					return(cchText);

			}
		}
	}


	//////////
	// If we get here, failure
	//////
		return(0);
}




WINBASEAPI DWORD WINAPI GetTickCount(VOID)
{
	timespec	lts;
	DWORD		lnTickCount;


	//////////
	// Grab the current time
	//////
		clock_gettime(CLOCK_REALTIME, &lts);


	//////////
	// Compute the tick count
	//////
		lnTickCount  = lts.tv_nsec / 1000000;
		lnTickCount += lts.tv_sec * 1000;


	//////////
	// Return the count
	//////
		return(lnTickCount);
}




WINBASEAPI VOID WINAPI InitializeCriticalSection(__out LPCRITICAL_SECTION lpCriticalSection)
{
	pthread_mutexattr_t attr;


	//////////
	// Create (initialize)
	//////
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL/*PTHREAD_MUTEX_RECURSIVE_NP*/);
		pthread_mutex_init(lpCriticalSection, &attr);
		pthread_mutexattr_destroy(&attr);
}




WINBASEAPI VOID WINAPI EnterCriticalSection(__inout LPCRITICAL_SECTION lpCriticalSection)
{
	pthread_mutex_lock(lpCriticalSection);
}




WINBASEAPI BOOL WINAPI TryEnterCriticalSection(__inout LPCRITICAL_SECTION lpCriticalSection)
{
	return(pthread_mutex_trylock(lpCriticalSection) == 0);
}




WINBASEAPI VOID WINAPI LeaveCriticalSection(__inout LPCRITICAL_SECTION lpCriticalSection)
{
	pthread_mutex_unlock(lpCriticalSection);
}




WINBASEAPI VOID WINAPI DeleteCriticalSection(__inout LPCRITICAL_SECTION lpCriticalSection)
{
	pthread_mutex_destroy(lpCriticalSection);
}




WINUSERAPI VOID WINAPI PostQuitMessage(__in int nExitCode)
{
	u32		lnI;
	SHwndX*	win;


	//////////
	// Iterate through every window and send the WM_QUIT message
	//////
		for (lnI = 0, win = (SHwndX*)gsWindows->buffer; lnI < gsWindows->populatedLength; lnI += sizeof(SHwndX), win++)
		{
			// If the window's valid, send it
			if (win->isValid)
				PostMessage(win->hwnd, WM_QUIT, nExitCode, 0);
		}
}




WINUSERAPI HCURSOR WINAPI LoadCursor(__in_opt HINSTANCE hInstance, __in uptr lpCursorName)
{
	switch (lpCursorName)
	{
		default:
		case IDC_ARROW:			return(XCreateFontCursor(gsDesktop.display, XC_arrow));
		case IDC_IBEAM:			return(XCreateFontCursor(gsDesktop.display, XC_xterm));
		case IDC_WAIT:			return(XCreateFontCursor(gsDesktop.display, XC_watch));
		case IDC_CROSS:			return(XCreateFontCursor(gsDesktop.display, XC_cross));
		case IDC_UPARROW:		return(XCreateFontCursor(gsDesktop.display, XC_center_ptr));
		case IDC_SIZENWSE:		return(XCreateFontCursor(gsDesktop.display, XC_fleur));
		case IDC_SIZENESW:		return(XCreateFontCursor(gsDesktop.display, XC_fleur));
		case IDC_SIZEWE:		return(XCreateFontCursor(gsDesktop.display, XC_fleur));
		case IDC_SIZENS:		return(XCreateFontCursor(gsDesktop.display, XC_fleur));
		case IDC_SIZEALL:		return(XCreateFontCursor(gsDesktop.display, XC_fleur));
		case IDC_NO:			return(XCreateFontCursor(gsDesktop.display, XC_circle));
		case IDC_HAND:			return(XCreateFontCursor(gsDesktop.display, XC_hand2));
		case IDC_APPSTARTING:	return(XCreateFontCursor(gsDesktop.display, XC_left_ptr));
		case IDC_HELP:			return(XCreateFontCursor(gsDesktop.display, XC_question_arrow));
	}
	// Control will never reach here
}




WINBASEAPI HMODULE WINAPI GetModuleHandle(__in_opt cs8* lpModuleName)
{
	// Always return 0 because we don't use modules
	return(0);
}




// The HRGN is an SBitmap with a binary pattern (black = no draw, non-black = draw)
WINUSERAPI int WINAPI SetWindowRgn(__in HWND hWnd, __in_opt HRGN hRgn, __in BOOL bRedraw)
{
	u32				lnI;
	s32				lnWidth, lnHeight;
	RECT			lrc;
	SBitmap*		bmpTemp;
	SHwndX*			hwndx;
	SRegionRectX*	regionRect;
	union {
		HRGN		_rgn;
		SRegionX*	region;
		uptr		_ptr;
	};


	//////////
	// Locate the window
	//////
		hwndx = iHwndX_findWindow_byHwnd(hWnd);
		if (hwndx && hwndx->isValid && hwndx->x11 && hwndx->x11->drawable)
		{
			//////////
			// Delete any existing region
			//////
				if (hwndx->regionx)
					iHwndX_deleteRegion(hwndx);


			//////////
			// Create the new region (if any)
			//////
				_rgn = hRgn;
				if (iBuilder_isPointer(gsRegions, _ptr))
				{
					//////////
					// Create the physical pixmap for the window
					//////
						lnWidth				= (hwndx->rc.right - hwndx->rc.left);
						lnHeight			= (hwndx->rc.bottom - hwndx->rc.top);


					//////////
					// Create a temporary bitmap to accumulate the region ops
					//////
						bmpTemp = iBmp_allocate();
						if (bmpTemp)
						{
							//////////
							// Create the bitmap initially white (region is enabled)
							//////
								iBmp_createBySize(bmpTemp, lnWidth, lnHeight, hwndx->x11->depth);
								iBmp_fillRect(bmpTemp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


							/////////
							// Iterate through each region, applying it logically to the pixmap
							//////
								SetRect(&lrc, 0, 0, lnWidth, lnHeight);
								for (lnI = 0, regionRect = (SRegionRectX*)hwndx->regionx->regionArray->buffer; lnI < hwndx->regionx->regionArray->populatedLength; lnI += sizeof(SRegionRectX), regionRect++)
								{
									//////////
									// If this rectangle overlaps the pixmap, apply its logic to the pixmap
									//////
										if (iMath_isRectInRect(&lrc, &regionRect->rc, false))
										{
											// Apply this region's logic to the accumulation bitmap
											switch (regionRect->op)
											{
												case RGN_AND:
													// Where the two intersect, make that
//////////
//
// We are only ANDing or XORing the indicated (///)
// rectangle, and the other portions need to also be processed:
//
//		+---+---+---+
//		|   |   |   |
//		+---+---+---+
//		|   |///|   |
//		+---+---+---+
//		|   |   |   |
//		+---+---+---+
//
//////////

// TODO:  This is only ANDing the 1-in-9 part, and the remaining portions will need to be blacked out
													iBmp_fillRect_op(bmpTemp, &regionRect->rc, whiteColor, blackColor, _FILL_RECT_OP_AND);
													break;

												case RGN_OR:
													// Turn on everything in this rectangle
													iBmp_fillRect_op(bmpTemp, &regionRect->rc, whiteColor, blackColor, _FILL_RECT_OP_OR);
													break;

												case RGN_XOR:
// TODO:  Same as with ANDing, except the XOR in the other 8 areas will be processed against black
													iBmp_fillRect_op(bmpTemp, &regionRect->rc, whiteColor, blackColor, _FILL_RECT_OP_XOR);
													break;
											}
										}

								}


							//////////
							// Convert temporary bitmap into pixmap, and delete
							//////
								hwndx->regionPixmap = XCreatePixmapFromBitmapData(hwndx->x11->display, hwndx->x11->drawable, bmpTemp->bd, lnWidth, lnHeight, blackColor.color, whiteColor.color, hwndx->x11->depth);
								iBmp_delete(&bmpTemp, true, true);


							/////////
							// Indicate success
							//////
								return(hwndx->regionPixmap);
					}
				}
		}


	//////////
	// If we get here, the window wasn't found, or isn't active
	//////
		return(-1);
}




WINUSERAPI BOOL WINAPI KillTimer(__in_opt HWND hWnd, __in sptr uIDEvent)
{
//	s32			lnI;
	SHwndX*		win;
//	STimerX*	timer;


	//////////
	// Locate the window
	//////
		if (hWnd)		win = iHwndX_findWindow_byHwnd(hWnd);
		else			win = NULL;


	//////////
	// Delete the indicated timer
	//////
		iHwndX_deleteTimer(win, uIDEvent);


	//////////
	// Indicate success
	//////
		return(TRUE);
}




WINGDIAPI BOOL WINAPI DeleteDC( __in HDC hdc)
{
	SHdcX* hdcx;


	//////////
	// Locate the HDC
	//////
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx && hdcx->isValid)
		{
			//////////
			// Mark it unused, delete the bitmap
			//////
				hdcx->isValid = false;
				if (hdcx->bmp)
					iBmp_delete(&hdcx->bmp, true, true);


			//////////
			// Indicate success
			//////
				return(TRUE);
		}


	//////////
	// If we get here, not found
	//////
		return(FALSE);
}




WINGDIAPI BOOL WINAPI DeleteObject( __in HGDIOBJ ho)
{
	union {
		uptr		_ho;
		SBrushX*	brush;
		SFontX*		font;
	};


	//////////
	// Brushes
	//////
		_ho = ho;
		if (iBuilder_isPointer(gsBrushes, _ho))
		{
			// It's a brush
			brush->isValid = false;
			return(TRUE);
		}


	//////////
	// Fonts
	//////
		if (iBuilder_isPointer(gsHfonts, _ho))
		{
			// It's a font
			font->isValid = false;
// Possibly actually delete the fonts?
debug_break;
			return(TRUE);
		}


	//////////
	// If we get here, it was an unknown object, indicate failure
	//////
		return(FALSE);
}




WINUSERAPI BOOL WINAPI DestroyWindow(__in HWND hWnd)
{
	SHwndX* win;


	//////////
	// Find the window
	//////
		win = iHwndX_findWindow_byHwnd(hWnd);
		if (win && win->isValid)
		{
			//////////
			// Delete the associated x-window if any
			//////
				if (win->x11)
					iHwndX_deleteXWindow(win);


			//////////
			// Delete the associated HDC
			//////
				if (win->hdcx)
				{
					DeleteDC(win->hdcx->hdc);
					win->hdcx = NULL;
				}


			//////////
			// Delete the class and title allocation associated with this window
			//////
				iDatum_delete(&win->cClass, false);
				iDatum_delete(&win->cTitle, false);


			//////////
			// Delete the message queue
			//////
				if (win->msgQueue)
					iBuilder_freeAndRelease(&win->msgQueue);


			//////////
			// Mark the window as invalid
			//////
				win->isValid	= false;
				win->hwnd		= null0;


			//////////
			// Indicate success
			//////
				return(TRUE);
		}


	//////////
	// If we get here, not found
	//////
		return(FALSE);
}




WINUSERAPI BOOL WINAPI ShowWindow(__in HWND hWnd, __in int nCmdShow)
{
	SHwndX* win;


	// Try to find the window
	win = iHwndX_findWindow_byHwnd(hWnd);
	if (win)
	{
		switch (nCmdShow)
		{
			case SW_HIDE:
//				XMapWindow(win->x11->display, win->x11->window);
				return(TRUE);

			case SW_SHOW:
//				XMapWindow(win->x11->display, win->x11->window);
				return(TRUE);

			default:
				// We don't support any other values
				// Let it fall through and fail
				break;
		}
	}

	// If we get here, failure
	return(FALSE);
}




WINBASEAPI VOID WINAPI Sleep(__in DWORD dwMilliseconds)
{
	// Call the microsecond sleep function
	usleep(dwMilliseconds * 1000);
}




WINUSERAPI BOOL WINAPI SetWindowPos(__in HWND hWnd, __in_opt HWND hWndInsertAfter, __in int X, __in int Y, __in int cx, __in int cy, __in UINT uFlags)
{
	SHwndX*					hwndx;
	SHwndX*					hwndxAfter;
	XClientMessageEvent		msge;
	Atom					state;
	Window					wndRoot, wndParent;
	Window*					wndChildList;
	unsigned int			lnChildCount;


	// Locate the window
	hwndx = iHwndX_findWindow_byHwnd(hWnd);
	if (hwndx && hwndx->x11)
	{
		//////////
		// Reposition?
		//////
			if ((uFlags & SWP_NOMOVE) == 0)
				XMoveWindow(hwndx->x11->display, hwndx->x11->window, X, Y);


		//////////
		// Resize?
		//////
			// Note:  Any draw buffers will need to be resized
			if ((uFlags & SWP_NOSIZE) == 0)
				XResizeWindow(hwndx->x11->display, hwndx->x11->window, cx, cy);


		//////////
		// Z-order
		//////
			if ((uFlags & SWP_NOZORDER) == 0)
			{
				switch (hWndInsertAfter)
				{
					case HWND_BOTTOM:
						XLowerWindow(hwndx->x11->display, hwndx->x11->window);
						break;

					case HWND_TOP:
						XMapRaised(hwndx->x11->display, hwndx->x11->window);
						break;

					case HWND_NOTOPMOST:
					case HWND_TOPMOST:
						//////////
						// Reset our message struture
						//////
							memset(&msge, 0, sizeof(msge));


						//////////
						// Grab our atom
						//////
							state = XInternAtom(hwndx->x11->display, "_NET_WM_STATE_ABOVE", 1);
							if (state == None)
							{
								// This version of x11 does not support always-on-top
								// Simply raise it
								XMapRaised(hwndx->x11->display, hwndx->x11->window);
								return(FALSE);
							}


						//////////
						// Populate
						//////
							msge.type		= ClientMessage;
							msge.window		= hwndx->x11->window;
							msge.format		= 32;
							msge.data.l[0]	= ((hWndInsertAfter == HWND_TOPMOST) ? 1/*add*/ : 0/*remove*/);
							msge.data.l[1]	= state;


						//////////
						// Dispatch
						//////
							XSendEvent(hwndx->x11->display, DefaultRootWindow(hwndx->x11->window), FALSE, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent*)&msge);


						//////////
						// Indicate success
						//////
							return(TRUE);

					default:
						// It must be an existing window, which will now be below it in the z order
						hwndxAfter = iHwndX_findWindow_byHwnd(hWndInsertAfter);
						if (hwndxAfter)
						{
							//////////
							// Query the existing tree/z-order
							//////
								XQueryTree(hwndx->x11->display, hwndx->x11->window, &wndRoot, &wndParent, &wndChildList, &lnChildCount);


							//////////
							// Restack with our window on top
							//////
								XRestackWindows(hwndx->x11->display, wndChildList, hwndx->x11->window);


							//////////
							// Free temporarily allocated resources by XQueryTree()
							//////
								XFree(wndChildList);

							// Indicate success
							return(TRUE);
						}
						break;
				}
			}
	}
	return(FALSE);
}




WINUSERAPI BOOL WINAPI GetCursorPos(__out LPPOINT lpPoint)
{
	//////////
	// Return current mouse position in desktop
	//////
		if (lpPoint)
		{
			lpPoint->x = gnMouseDesktop.x;
			lpPoint->y = gnMouseDesktop.y;
			return(TRUE);
		}


	// Invalid data
	return(FALSE);
}




WINGDIAPI HRGN WINAPI CreateRectRgn(__in int x1, __in int y1, __in int x2, __in int y2)
{
	s32				t;
	SRegionRectX*	rectx;
	union {
		HRGN		_rgn;
		SRegionX*	regionx;
	};


	//////////
	// Make sure the parameters are in appropriate order
	// (x1,y1) should be upper-left, (x2,y2) should be lower-right
	//////
		if (x2 < x1)
		{
			t = x2;
			x2 = x1;
			x1 = t;
		}

		if (y2 < y1)
		{
			t = y2;
			y2 = y1;
			y1 = t;
		}


	//////////
	// Create a region
	//////
		regionx = iHwndX_createRegion();
		if (regionx)
		{
			// Mark it active
			regionx->isValid = true;

			// Set the coordinates
			iBuilder_createAndInitialize(&regionx->regionArray, 1024);
			rectx = (SRegionRectX*)iBuilder_appendData(regionx->regionArray, NULL, sizeof(SRegionRectX));
			if (rectx)
			{
				// Set the rectangle
				SetRect(&rectx->rc, x1, y1, x2, y2);
				rectx->op = _REGION_RECT_OP_DRAW;
			}
		}


	//////////
	// Indicate our success or failure
	//////
		return(_rgn);
}




WINUSERAPI int WINAPI GetWindowRgn(__in HWND hWnd, __in HRGN hRgn)
{
	SHwndX*			hwndx;
	union {
		HRGN		_rgn;
		SRegionX*	regionx;
	};


	//////////
	// Locate the window
	//////
		hwndx = iHwndX_findWindow_byHwnd(hWnd);
		if (hwndx)
		{
			// We found the window, indicate the region
			regionx = hwndx->regionx;

		} else {
			// Indicate failure
			_rgn = 0;
		}


	//////////
	// Indicate success or failure
	//////
		return(_rgn);
}




WINGDIAPI BOOL WINAPI PtInRegion(__in HRGN hrgn, __in int x, __in int y)
{
	u32				lnI;
	bool			lIsInRect;
	BOOL			lIsInRegion;
	SRegionRectX*	regionRect;
	POINT			pt;
	union {
		SRegionX*	regionx;
		HRGN		_rgn;
		uptr		_ptr;
	};


	//////////
	// Make sure the region exists
	//////
		if (iBuilder_isPointer(gsRegions, _ptr))
		{
			// Is it currently valid?
			if (regionx->isValid)
			{
				// Iterate through the array to determine if the point is in the array or not
				pt.x = x;
				pt.y = y;
				for (lnI = 0, regionRect = (SRegionRectX*)regionx->regionArray->buffer; lnI < regionx->regionArray->populatedLength; lnI += sizeof(SRegionRectX), regionRect++)
				{
					// Are we in this region?
					lIsInRect = PtInRect(&regionRect->rc, pt);

					// Based on the operation, continue to propagate the condition
					switch (regionRect->op)
					{
						case RGN_AND:
							// Must be in the current one, and this one
							lIsInRegion = (lIsInRegion & lIsInRect);
							break;

						case RGN_OR:
							// Must be in either current one, or this one
							lIsInRegion = (lIsInRegion | lIsInRect);
							break;

						case RGN_XOR:
							// Must be in only one of them, but not both
							lIsInRegion = (lIsInRegion ^ lIsInRect);
							break;
					}
				}
			}
		}
		// If we get here, failure


	//////////
	// Indicate failure
	//////
		return(FALSE);
}




WINUSERAPI HDC WINAPI BeginPaint(__in HWND hWnd, __out LPPAINTSTRUCT lpPaint)
{
	SHwndX* win;


	// Make sure our environment is sane
	if (lpPaint)
	{
		// Locate the window
		win = iHwndX_findWindow_byHwnd(hWnd);
		if (win)
		{
			//////////
			// Initialize the paint stucture
			//////
				lpPaint->hdc		= win->hdcx->hdc;
				lpPaint->fErase		= FALSE;
				memcpy(&lpPaint->rcPaint, &win->rcClient, sizeof(lpPaint->rcPaint));
				lpPaint->fRestore	= FALSE;
				lpPaint->fIncUpdate	= FALSE;
				memset(&lpPaint->rgbReserved[0], 0, sizeof(lpPaint->rgbReserved));


			//////////
			// Return the HDC
			//////
				return(lpPaint->hdc);
		}
	}


	//////////
	// If we get here, failure
	//////
		return(null0);
}




WINUSERAPI BOOL WINAPI EndPaint(__in HWND hWnd, __in CONST PAINTSTRUCT *lpPaint)
{
	// Always indicate success
	return(TRUE);
}




WINGDIAPI BOOL WINAPI BitBlt( __in HDC hdc, __in int x, __in int y, __in int cx, __in int cy, __in_opt HDC hdcSrc, __in int x1, __in int y1, __in DWORD rop)
{
	SHdcX*	hdcx;
	SHdcX*	hdcxSrc;
	RECT	lrc;


	// Find our device contexts
	hdcx	= iHwndX_findHdc_byHdc(hdc);
	hdcxSrc	= iHwndX_findHdc_byHdc(hdcSrc);
	if (hdcx && hdcxSrc && hdcx->bmp && hdcxSrc->bmp)
	{
		//////////
		// Our rectangle
		//////
			SetRect(&lrc,	x,
							y,
							x + cx,
							y + cy);


		//////////
		// Physically render
		//////
			iBmp_bitBlt(hdcx->bmp, &lrc, hdcxSrc->bmp);


		//////////
		// Indicate success
		//////
			return(TRUE);
	}


	//////////
	// If we get here, failure
	//////
		return(FALSE);
}




WINUSERAPI HICON WINAPI LoadIcon(__in_opt HINSTANCE hInstance, __in uptr lpIconName)
{
	union {
		HICON		_icon;
		SBitmap*	bmp;
	};


	//////////
	// What are they loading?
	//////
		switch (lpIconName)
		{
			case IDI_APPLICATION:
			case IDI_WINLOGO:			// Standard app icon
				bmp = bmpArray[_BMP__app_win];
				break;

			case IDI_ERROR:				// Hand/halt! icon
				bmp = bmpArray[_BMP__halt_win];
				break;

			case IDI_QUESTION:			// Question mark
				bmp = bmpArray[_BMP__question_mark_win];
				break;

			case IDI_EXCLAMATION:		// Exclamation point
				bmp = bmpArray[_BMP__exclamation_point_win];
				break;

			case IDI_ASTERISK:			// Stop sign
				bmp = bmpArray[_BMP__stop_sign_win];
				break;

			case IDI_SHIELD:			// Shield
				bmp = bmpArray[_BMP__shield_win];
				break;

			default:
				// It is a custom icon from a resource
// TODO:  need to figure out what protocol we want to implement this

				// For now, go ahead and use the standard app icon
				bmp = bmpArray[_BMP__app_win];
				break;
		}


	//////////
	// Indicate success
	//////
		return(_icon);
}




//////////
//
// Copies one rectangel to another
//
//////
	WINUSERAPI BOOL WINAPI CopyRect(__out RECT* lprcDst, __in CONST RECT *lprcSrc)
	{
		// Make sure our environment is sane
		if (lprcDst && lprcSrc)
		{
			//
			memcpy(lprcDst, lprcSrc, sizeof(RECT));
			return(TRUE);
		}

		// If we get here, failure
		return(FALSE);
	}




//////////
//
// Makes a Windows rect bigger or smaller
//
//////
	WINUSERAPI BOOL WINAPI InflateRect(__inout RECT* lprc, __in int dx, __in int dy)
	{
		// Make sure our environment is sane
		if (lprc)
		{
			// Adjust horizontally
			lprc->left		-= dx;
			lprc->right		+= dx;

			// Adjust vertically
			lprc->top		-= dy;
			lprc->bottom	+= dy;

			// If we get here, success
			return(TRUE);
		}

		// If we get here, failure
		return(FALSE);
	}




WINUSERAPI LONG WINAPI GetWindowLongA(__in HWND hWnd, __in int nIndex)
{
	// Not currently supported
	return(0);
}




WINUSERAPI LONG WINAPI SetWindowLongA(__in HWND hWnd, __in int nIndex,__in LONG dwNewLong)
{
	// Not currently supported
	return(0);
}




WINUSERAPI BOOL WINAPI InvalidateRect(__in_opt HWND hWnd, __in_opt CONST RECT *lpRect, __in BOOL bErase)
{
	MSG msg;


	//////////
	// Because of the way VJr draws, we don't really support invalidated rects,
	// but instead simply append a WM_PAINT message (if one isn't already present)
	//////
		if (!PeekMessage(&msg, hWnd, WM_PAINT, WM_PAINT, PM_NOREMOVE))
			iHwndX_postMessage_byHwnd(hWnd, WM_PAINT, 0, 0);


	// Indicate success either way
	return(TRUE);
}




WINUSERAPI HMENU WINAPI GetMenu(__in HWND hWnd)
{
	// We do not support menus, except as placeholder functions
	return(null0);
}




WINUSERAPI BOOL WINAPI SetMenu(__in HWND hWnd, __in_opt HMENU hMenu)
{
	// We do not support menus, except as placeholder functions
	return(FALSE);
}




WINGDIAPI HRGN WINAPI CreateRectRgnIndirect( __in CONST RECT *lprect)
{
	union {
		HRGN		_rgn;
		SRegionX*	regionx;
	};
	SRegionRectX*	regionxRect;


	//////////
	// Create the new region
	//////
		regionx = iHwndX_createRegion();
		if (regionx)
		{
			// Activate and create the regionArray
			regionx->isValid = true;
			iBuilder_createAndInitialize(&regionx->regionArray, -1);
			if (regionx->regionArray)
			{
				// Add in this rectangle
				regionxRect = (SRegionRectX*)iBuilder_appendData(regionx->regionArray, NULL, sizeof(SRegionRectX));
				if (regionxRect)
				{
					// The op is AND against however big the full region is
					regionxRect->op = RGN_AND;

					// Set the rectangle
					CopyRect(&regionxRect->rc, lprect);

					// Indicate success
					return(_rgn);
				}
			}
		}


	//////////
	// If we get here, failure
	//////
		return(0);
}




//////////
//
// Returns if the point is within the physical borders of the rectangle, inclusive
//
//////
	WINUSERAPI BOOL WINAPI PtInRect(__in CONST RECT *lprc, __in POINT pt)
	{
		// Make sure our environment is sane
		if (lprc)
		{
			// If the point is in the rectangle, indicate the same
			return((	pt.x >= lprc->left	&&	pt.x <= lprc->right
					&&	pt.y >= lprc->top	&&	pt.y <= lprc->bottom));
		}

		// Invalid rect
		return(FALSE);
	}




WINUSERAPI SHORT WINAPI GetAsyncKeyState(__in int vKey)
{
	return(0);
}




WINUSERAPI SHORT WINAPI GetKeyState(__in int nVirtKey)
{
	return(0);
}




WINUSERAPI BOOL WINAPI AdjustWindowRect(__inout LPRECT lpRect, __in DWORD dwStyle, __in BOOL bMenu)
{
	//////////
	// Not currently supported, because we only allow windows that are basically WS_POPUP
	// windows, which have no border, and allow for no menu
	//////////


	// Indicate success anyway (because there is no adjustment for the window type)
	return(TRUE);
}




WINUSERAPI BOOL WINAPI GetKeyboardState(BYTE lpKeyState[256])
{
	return(FALSE);
}




WINUSERAPI int WINAPI ToAscii(__in UINT uVirtKey, __in UINT uScanCode, CONST BYTE lpKeyState[256], __out LPWORD lpChar, __in UINT uFlags)
{
	return(0);
}




WINGDIAPI int WINAPI CombineRgn(__in_opt HRGN hrgnDst, __in_opt HRGN hrgnSrc1, __in_opt HRGN hrgnSrc2, __in int iMode)
{
	return(0);
}




//////////
//
// For "solid brushes" we don't actually use a brush, but rather the direct color
//
//////
	WINGDIAPI HBRUSH WINAPI CreateSolidBrush(__in COLORREF color)
	{
		union {
			HBRUSH		_brushx;
			SBrushX*	brushx;
		};


		// Create the "solid brush" by color
		brushx = iHwndX_createBrush(true, (uptr)color);
		if (brushx)
		{
			// Mark the brush valid
			brushx->isValid			= true;

			// Store the brush
			brushx->color.color		= color;
			brushx->isSolidBrush	= true;
		}

		// Return the "solid brush"
		return(_brushx);
	}




WINUSERAPI int WINAPI FillRect(__in HDC hDC, __in CONST RECT *lprc, __in HBRUSH hbr)
{
	RECT		lrc;
	SHdcX*		hdcx;
	SBrushX*	brushx;


	//////////
	// Fill the rect using our internal algorithms
	//////
		// Locate the hdx
		hdcx = iHwndX_findHdc_byHdc(hDC);
		if (hdcx)
		{
			// Locate the brushx
			brushx = iHwndX_findBrush_byBrush(hbr);
			if (brushx)
			{
				SetRect(&lrc, 0, 0, hdcx->bmp->bi.biWidth, hdcx->bmp->bi.biHeight);
				iBmp_fillRect(hdcx->bmp, &lrc, brushx->color, brushx->color, brushx->color, brushx->color, false, NULL, false);
				return(1);
			}
		}


	//////////
	// If we get here, something wasn't valid
	//////
		return(0);
}




WINUSERAPI int WINAPI FrameRect(__in HDC hDC, __in CONST RECT *lprc,__in HBRUSH hbr)
{
	RECT		lrc;
	SHdcX*		hdcx;
	SBrushX*	brushx;


	//////////
	// Fill the rect using our internal algorithms
	//////
		// Locate the hdx
		hdcx = iHwndX_findHdc_byHdc(hDC);
		if (hdcx)
		{
			// Locate the brushx
			brushx = iHwndX_findBrush_byBrush(hbr);
			if (brushx)
			{
				SetRect(&lrc, 0, 0, hdcx->bmp->bi.biWidth, hdcx->bmp->bi.biHeight);
				iBmp_frameRect(hdcx->bmp, &lrc, brushx->color, brushx->color, brushx->color, brushx->color, false, NULL, false);
				return(1);
			}
		}


	//////////
	// If we get here, something wasn't valid
	//////
		return(0);
}




WINBASEAPI VOID WINAPI GetSystemTime(__out LPSYSTEMTIME lpSystemTime)
{
	timeb	ltb;
	tm*		lts;


	//////////
	// Grab the current time
	//////
		ftime(&ltb);
		lts = gmtime(&ltb.time);


	//////////
	// Translate to Windows' format
	//////
		lpSystemTime->wYear			= lts->tm_year + 1900;
		lpSystemTime->wMonth		= lts->tm_mon;
		lpSystemTime->wDayOfWeek	= lts->tm_wday;
		lpSystemTime->wDay			= lts->tm_mday;
		lpSystemTime->wHour			= lts->tm_hour;
		lpSystemTime->wMinute		= lts->tm_min;
		lpSystemTime->wSecond		= lts->tm_sec;
		lpSystemTime->wMilliseconds	= ltb.millitm;
}




WINBASEAPI VOID WINAPI GetSystemTimeAsFileTime(__out LPFILETIME lpSystemTimeAsFileTime)
{
	timeval		tv;

	union {
		u64		result;
		struct Sul
		{
			u32	upper;
			u32 lower;
		} ul;
	};


	// Make sure our environment is sane
	if (lpSystemTimeAsFileTime)
	{
		//////////
		// Set the initial value
		//////
			// Epochs:
			// Jan.01.1601 00:00	-- Unix
			// Jan.01.1970 00:00	-- Windows
			result = 11644473600;	// Difference between Unix and Windows


		//////////
		// Get current time
		//////
			gettimeofday(&tv, NULL);


		//////////
		// Convert to FILETIME
		//////
			result	+= tv.tv_sec;
			result	*= 10000000;
			result	+= tv.tv_usec * 10;


		//////////
		// Store the result
		//////
// These need validated ... they could be inverted
debug_break;
			lpSystemTimeAsFileTime->dwHighDateTime	= ul.upper;
			lpSystemTimeAsFileTime->dwLowDateTime	= ul.lower;
	}
}




WINBASEAPI VOID WINAPI GetLocalTime(__out LPSYSTEMTIME lpSystemTime)
{
	timeb	ltb;
	tm*		lts;


	//////////
	// Grab the current time
	//////
		ftime(&ltb);
		lts = localtime(&ltb.time);


	//////////
	// Translate to Windows' format
	//////
		lpSystemTime->wYear			= lts->tm_year + 1900;
		lpSystemTime->wMonth		= lts->tm_mon;
		lpSystemTime->wDayOfWeek	= lts->tm_wday;
		lpSystemTime->wDay			= lts->tm_mday;
		lpSystemTime->wHour			= lts->tm_hour;
		lpSystemTime->wMinute		= lts->tm_min;
		lpSystemTime->wSecond		= lts->tm_sec;
		lpSystemTime->wMilliseconds	= ltb.millitm;
}




WINUSERAPI HWND WINAPI GetActiveWindow(VOID)
{
	u32		lnI;
	SHwndX* hwndx;


	//////////
	// Iterate through every window and find which one is currently active
	//////
		for (lnI = 0, hwndx = (SHwndX*)gsWindows->buffer; lnI < gsWindows->populatedLength; lnI += sizeof(SHwndX), hwndx++)
		{
			// Is this window active?
			if (hwndx->isValid && hwndx->isActive)
				return(hwndx->hwnd);
		}



	//////////
	// If we get here, we didn't find an active window
	//////
		debug_break;	// Shouldn't happen
		return(0);
}




WINGDIAPI COLORREF WINAPI SetBkColor(__in HDC hdc, __in COLORREF color)
{
	SHdcX*	hdcx;
	u32		lnColor;


	//////////
	// Get the HDC
	//////
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx && hdcx->isValid)
		{
			// Set the color
			lnColor					= hdcx->colorBack.color;
			hdcx->colorBack.color	= color;

			// Make sure the alpha channel is fully saturated
			hdcx->colorBack.alp		= 255;

		} else {
			// Set to black
			lnColor					= 0;
		}


	//////////
	// Return
	//////
		return(lnColor);
}




WINUSERAPI HDC WINAPI GetDC(__in_opt HWND hWnd)
{
	SHwndX*	win;
	HDC		_lhdc;


	//////////
	// Try to find it by hWnd
	//////
		win = iHwndX_findWindow_byHwnd(hWnd);
		if (win && win->hdcx)
		{
			// Grab the DC for this window
			_lhdc = win->hdcx->hdc;

		} else {
			// Not found
			_lhdc = -1;
		}


	//////////
	// Indicate our status
	//////
		return(_lhdc);
}




WINGDIAPI HDC WINAPI CreateCompatibleDC( __in_opt HDC hdc)
{
	SHdcX*	lhdcRef;
	SHdcX*	lhdcNew;


	// Try to find it by hdc
	lhdcRef = iHwndX_findHdc_byHdc(hdc);
	if (lhdcRef && lhdcRef->isValid)
	{
		// Create a new entry, and copy everything
		lhdcNew = (SHdcX*)iBuilder_appendData(gsHdcs, NULL, sizeof(SHdcX));
		if (lhdcNew)
		{
			// Populate with the content from the other one
			memcpy(lhdcNew, lhdcRef, sizeof(*lhdcNew));

			// Create copies of the non-copyable things
			lhdcNew->bmp = iBmp_allocate();
			iBmp_createBySize(lhdcNew->bmp, lhdcRef->bmp->bi.biWidth, lhdcRef->bmp->bi.biHeight, lhdcRef->bmp->bi.biBitCount);
		}
	}

	// If we get here, failure
	return(-1);
}




WINGDIAPI HBITMAP WINAPI CreateDIBSection(__in_opt HDC hdc, __in CONST BITMAPINFO* lpbmi, __in UINT usage, VOID **ppvBits, __in_opt HANDLE hSection, __in DWORD offset)
{
	SHdcX*		hdcx;
	union {
		HBITMAP		_bmp;
		SBitmap*	bmp;
	};


	//////////
	// Intercept any unsupported features
	//////
		if (hSection || offset)
		{
			// We do not support mapped files
			debug_break;
			return(null0);
		}


	//////////
	// Locate the HDC
	//////
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx)
		{
			// Allocate the bitmap
			bmp = iBmp_allocate();
			iBmp_createBySize(bmp, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, 24);
			if (ppvBits)
				*ppvBits = bmp->bd;

		} else {
			bmp = NULL;
		}


	//////////
	// Indicate success or failure
	//////
		return(_bmp);
}




s64 _atoi64(cs8* string)
{
	return((s64)strtoll(string, NULL, 10));
}




WINUSERAPI int WINAPI GetSystemMetrics(__in int nIndex)
{
	switch (nIndex)
	{
		case SM_CXFULLSCREEN:
		case SM_CXSCREEN:
		case SM_CXSIZE:
		case SM_CXMAXIMIZED:
		case SM_CXMAXTRACK:
			return gsDesktopWindow->rc.right - gsDesktopWindow->rc.left;

		case SM_CYFULLSCREEN:
		case SM_CYSCREEN:
		case SM_CYSIZE:
		case SM_CYMAXIMIZED:
		case SM_CYMAXTRACK:
			return gsDesktopWindow->rc.bottom - gsDesktopWindow->rc.top;

		case SM_CXHTHUMB:
		case SM_CXCURSOR:
		case SM_CXICON:
		case SM_CXHSCROLL:
			return _BMP__ARRAY_WIDTH;

		case SM_CYVTHUMB:
		case SM_CYICON:
		case SM_CYCURSOR:
		case SM_CYVSCROLL:
			return _BMP__ARRAY_HEIGHT;

		case SM_CXMINTRACK:
		case SM_CXMIN:
		case SM_CXMINIMIZED:
			return bmpClose->bi.biWidth * 10;

		case SM_CYMINTRACK:
		case SM_CYMIN:
		case SM_CYMINIMIZED:
			return bmpClose->bi.biHeight;

		case SM_CXICONSPACING:
		case SM_CXDOUBLECLK:
			return 5;

		case SM_CYICONSPACING:
		case SM_CYDOUBLECLK:
			return 5;

		case SM_CYCAPTION:			return bmpClose->bi.biHeight;
		case SM_MOUSEPRESENT:		return 1;
		case SM_REMOTESESSION:		return 0;
		case SM_MOUSEWHEELPRESENT:	return 1;
		case SM_SHUTTINGDOWN:		return 0;


	//////////
	// The following
	//////
		case SM_CXVSCROLL:
		case SM_CYHSCROLL:
		case SM_CXBORDER:
		case SM_CYBORDER:
		case SM_CXDLGFRAME:
		case SM_CYDLGFRAME:
		case SM_CYMENU:
		case SM_CYKANJIWINDOW:
		case SM_DEBUG:
		case SM_SWAPBUTTON:
		case SM_RESERVED1:
		case SM_RESERVED2:
		case SM_RESERVED3:
		case SM_RESERVED4:
		case SM_CXFRAME:
		case SM_CYFRAME:
		case SM_MENUDROPALIGNMENT:
		case SM_PENWINDOWS:
		case SM_DBCSENABLED:
		case SM_CMOUSEBUTTONS:
		case SM_SECURE:
		case SM_CXEDGE:
		case SM_CYEDGE:
		case SM_CXMINSPACING:
		case SM_CYMINSPACING:
		case SM_CXSMICON:
		case SM_CYSMICON:
		case SM_CYSMCAPTION:
		case SM_CXSMSIZE:
		case SM_CYSMSIZE:
		case SM_CXMENUSIZE:
		case SM_CYMENUSIZE:
		case SM_ARRANGE:
		case SM_NETWORK:
		case SM_CLEANBOOT:
		case SM_CXDRAG:
		case SM_CYDRAG:
		case SM_SHOWSOUNDS:
		case SM_CXMENUCHECK:
		case SM_CYMENUCHECK:
		case SM_SLOWMACHINE:
		case SM_MIDEASTENABLED:
//		case SM_XVIRTUALSCREEN:
		case SM_YVIRTUALSCREEN:
		case SM_CXVIRTUALSCREEN:
		case SM_CYVIRTUALSCREEN:
		case SM_CMONITORS:
		case SM_SAMEDISPLAYFORMAT:
		case SM_IMMENABLED:
		case SM_CXFOCUSBORDER:
		case SM_CYFOCUSBORDER:
		case SM_TABLETPC:
		case SM_MEDIACENTER:
		case SM_STARTER:
		case SM_SERVERR2:
		case SM_MOUSEHORIZONTALWHEELPRESENT:
		case SM_CXPADDEDBORDER:
		case SM_DIGITIZER:
		case SM_MAXIMUMTOUCHES:
//		case SM_CMETRICS:
//		case SM_REMOTECONTROL:
		case SM_CARETBLINKINGENABLED:
			// These constants can have their return values defined if needed
			debug_break;
			return(0);
	}
	// If we get here it wasn't found
	return(-1);
}




WINUSERAPI BOOL WINAPI OffsetRect(__inout LPRECT lprc, __in int dx, __in int dy)
{
	// Make sure the environment is sane
	if (lprc)
	{
		// Delta-X
		lprc->left		+= dx;
		lprc->right		+= dx;

		// Delta-Y
		lprc->top		+= dy;
		lprc->bottom	+= dy;

		// Indicate success
		return(TRUE);
	}

	// If we get here, failure
	return(FALSE);
}




WINBASEAPI DWORD WINAPI GetCurrentDirectory(__in DWORD nBufferLength, s8 lpBuffer[_MAX_PATH])
{
	//////////
	// Reset
	//////
		memset(lpBuffer, 0, _MAX_PATH);


	//////////
	// Grab the
	//////
		getcwd(lpBuffer, nBufferLength);


	//////////
	// Indicate our length
	//////
		return(strlen(lpBuffer));
}




int sopen(cs8* tcPathname, s32 mode, s32 sharing)
{
	int		file;
	u32		lnFlags;
	flock	f;


	//////////
	// Open how?
	//////
		lnFlags	= 0;
		if (mode & _O_CREAT)
		{
			// Creating a new file
			if (mode & _O_WRONLY)
			{
				// Write only
				lnFlags = O_CREAT | O_WRONLY | O_TRUNC;

			} else {
				// Read/write
				lnFlags = O_CREAT | O_RDWR | O_TRUNC;
			}

		} else {
			// Opening an existing
			if (mode & _O_RDONLY)
			{
				// Read-only
				lnFlags = O_RDONLY;

			} else if (mode & _O_WRONLY) {
				// Write-only
				lnFlags = O_WRONLY;

			} else {
				// Read/write
				lnFlags = O_RDWR;
			}
		}


	//////////
	// Perform the open
	//////
		file = open(tcPathname, lnFlags);


	//////////
	// Allow sharing?
	//////
		if (file != -1 && sharing != _SH_DENYNO)
		{
			//////////
			// Populate a lock from 0 to maximum file size
			//////
				f.l_whence	= SEEK_SET;
				f.l_start	= 0;
				f.l_len		= _s64_max;


			//////////
			// Put read/write/both locks on the file
			//////
				if (sharing & _SH_DENYRW/*read/write*/ || (sharing & _SH_DENYWR && sharing & _SH_DENYRD))
				{
					// Read lock
					f.l_type = F_RDLCK;
					fcntl(file, F_RDLCK, &f);

					// Write lock
					f.l_type = F_WRLCK;
					fcntl(file, F_WRLCK, &f);

				} else if (sharing & _SH_DENYWR/*write*/) {
					// Read lock
					f.l_type = F_RDLCK;
					fcntl(file, F_RDLCK, &f);

				} else if (sharing & _SH_DENYRD/*read*/) {
					// Write lock
					f.l_type = F_WRLCK;
					fcntl(file, F_WRLCK, &f);
				}

		}


	//////////
	// Indicate success or failure
	//////
		return(file);
}




s64 telli64(s32 fileno)
{
	return(lseek64(fileno, 0, SEEK_CUR));
}




WINBASEAPI HANDLE WINAPI FindFirstFile(__in cs8* lpFileName, __out LPWIN32_FIND_DATA lpFindFileData)
{
//	BOOL llResult;
//
//
//	// Make sure our environment is sane
//	if (lpFindFileData)
//	{
//		// Try to open the indicated directory
//		if ((lpFindFileData->dp = opendir(lpFileName)) == NULL)
//			return(-1);
//
//		// Get the first file
//		llResult = FindNextFile((HANDLE)&lpFindFileData, lpFindFileData);
//		if (!llResult)
//		{
//			closedir(lpFindFileData->dp);
//			return(-1);
//		}
//
//		// Indicate success
//		return((HANDLE)&lpFindFileData);
//	}
//
//	// If we get here, error
	return(-1);
}




WINBASEAPI BOOL WINAPI FindNextFile(__in HANDLE hFindFile, __out LPWIN32_FIND_DATA lpFindFileData)
{
//	// Make sure our environment is sane
//	if (lpFindFileData)
//	{
//		// Find the next file
//		lpFindFileData->dirp = readdir(lpFindFileData->dp);
//		if (!lpFindFileData->dirp)
//		{
//			// All done!
//			closedir(lpFindFileData->dp));
//			return(FALSE);
//		}
//
//		// Copy attributes
//
//		// Copy the name
//		memcpy(lpFindFileData->cFileName, lpFindFileData->dirp->d_name, strlen(lpFindFileData->dirp->d_name));
//
//		// Indicate success
//		return(TRUE);
//	}
//
//	// If we get here, invalid
	return(FALSE);
}




WINBASEAPI DWORD WINAPI GetFullPathName(__in cs8* lpFileName, __in DWORD nBufferLength, s8 lpBuffer[_MAX_PATH], s8** lpFilePart)
{
// TODO:  Will use VJr's own algorithms for this
	return(0);
}




WINBASEAPI DWORD WINAPI GetTempPath(__in DWORD nBufferLength, s8 lpBuffer[_MAX_PATH])
{
	memcpy(lpBuffer, "\\var\\tmp\\0", 10);
	return(10);
}




WINBASEAPI UINT WINAPI GetTempFileName(__in cs8* lpPathName, __in cs8* lpPrefixString, __in UINT uUnique, s8 lpTempFileName[_MAX_PATH])
{
	//////////
	// Initialize to empty
	//////
		if (lpTempFileName)
			memset(lpTempFileName, 0, _MAX_PATH);


	//////////
	// Prepend the directory
	//////
		if (lpPathName)
		{
			// Copy the path
			memcpy(lpTempFileName, lpPathName, min(strlen(lpPathName), _MAX_PATH - 1));

			// Make sure it ends with a directory symbol
			if (lpTempFileName[strlen(lpTempFileName) - 1] != '\\')
				lpTempFileName[strlen(lpTempFileName) - 1] = '\\';

			// Add the prefix string
// This code could be bad :-)
debug_break;
			memcpy(lpTempFileName + strlen(lpTempFileName), lpPrefixString, min(_MAX_PATH - strlen(lpPrefixString) - strlen(lpTempFileName), strlen(lpPrefixString)));

			// Addin the unique id
			sprintf(lpTempFileName + strlen(lpTempFileName), "%lu", uUnique);

			// Indicate the length
			return(strlen(lpTempFileName));
		}


	//////////
	// If we get here, failure
	//////
		return(-1);
}




WINGDIAPI int WINAPI GetDeviceCaps(__in_opt HDC hdc, __in int index)
{
	switch (index)
	{
		case DRIVERVERSION:
			return 1;

		case TECHNOLOGY:
			return DT_RASDISPLAY;

		case HORZSIZE:
			return gsDesktopWindow->rc.right - gsDesktopWindow->rc.left;

		case VERTSIZE:
			return gsDesktopWindow->rc.bottom - gsDesktopWindow->rc.top;

		case HORZRES:
			return 500;

		case VERTRES:
			return 312;

		case BITSPIXEL:
			return 24;

		case PLANES:
			return 1;

		case NUMBRUSHES:
			return 1000;

		case NUMPENS:
			return 1000;

		case NUMMARKERS:
			return 1000;

		case NUMFONTS:
			return 1000;

		case NUMCOLORS:
			return 1;

		case ASPECTX:
			return (gsDesktopWindow->rc.right - gsDesktopWindow->rc.left) / (gsDesktopWindow->rc.bottom - gsDesktopWindow->rc.top);

		case ASPECTY:
			return (gsDesktopWindow->rc.bottom - gsDesktopWindow->rc.top) / (gsDesktopWindow->rc.right - gsDesktopWindow->rc.left);

		case ASPECTXY:
			return (gsDesktopWindow->rc.right - gsDesktopWindow->rc.left) / (gsDesktopWindow->rc.bottom - gsDesktopWindow->rc.top);

		case LOGPIXELSX:
		case LOGPIXELSY:
			return 96;

		case SIZEPALETTE:
		case NUMRESERVED:
		case COLORRES:
		case PDEVICESIZE:
		case CURVECAPS:
		case LINECAPS:
		case POLYGONALCAPS:
		case TEXTCAPS:
		case CLIPCAPS:
		case RASTERCAPS:
			return 0;
	}
	return(0);
}




WINBASEAPI int WINAPI MulDiv(__in int nNumber, __in int nNumerator, __in int nDenominator)
{
	// (a * b) / c
	return((int)(((s64)nNumber * (s64)nNumerator) / (s64)nDenominator));
}




WINGDIAPI HFONT WINAPI CreateFont(	__in int cHeight, __in int cWidth, __in int cEscapement, __in int cOrientation, __in int cWeight, __in DWORD bItalic,
									__in DWORD bUnderline, __in DWORD bStrikeOut, __in DWORD iCharSet, __in DWORD iOutPrecision, __in DWORD iClipPrecision,
									__in DWORD iQuality, __in DWORD iPitchAndFamily, __in_opt cs8* pszFaceName)
{
	int			lnI, lnNames;
	s8**		fontNameArray;
	SFontX*		fontx;


	// Grab the next font
	fontx = iHwndX_getNextFont();
	if (fontx)
	{
		//////////
		// Copy the attributes
		//////
			fontx->nHeight			= cHeight;
			fontx->nWidth			= cWidth;
			fontx->nEscapement		= cEscapement;
			fontx->nOrientation		= cOrientation;
			fontx->nWeight			= cWeight;
			fontx->lItalic			= bItalic;
			fontx->lUnderline		= bUnderline;
			fontx->lStrikeOut		= bStrikeOut;
			fontx->nCharSet			= iCharSet;
			fontx->nOutPrecision	= iOutPrecision;
			fontx->nClipPrecision	= iClipPrecision;
			fontx->nQuality			= iQuality;
			fontx->nPitchAndFamily	= iPitchAndFamily;
			iDatum_duplicate(&fontx->faceName, (u8*)pszFaceName, (u32)strlen(pszFaceName));


		//////////
		// Grab the list of font names
		//////
			fontNameArray = XListFonts(gsDesktop.display, "*", 999, &lnNames);
			for (lnI = 0; lnI < lnNames; lnI++)
			{
				// Search for the font name that matches
				if (strlen(fontNameArray[lnI]) == fontx->faceName.length && _memicmp(fontNameArray[lnI], fontx->faceName.data, fontx->faceName.length) == 0)
				{
					// Load the font they indicated
					fontx->font = (HFONT)XLoadFont(gsDesktop.display, fontx->faceName.data);
					break;
				}
			}
			// If we get here, _hfont indicates our success
			XFreeFontNames(fontNameArray);


		//////////
		// If we were unsuccessful, load the default font
		//////
			if (!fontx->font)
				fontx->font = (HFONT)XLoadFont(gsDesktop.display, (cs8*)cgcFontName_defaultFixed);


		//////////
		// Query informationa bout the font
		//////
			fontx->fontData = XQueryFont(gsDesktop.display, gsDesktopWindow->x11->gc->gid);


		//////////
		// Populate textmetrics for Windows-related calls
		//////
			// LONG
			fontx->tm.tmHeight				= fontx->fontData->ascent + fontx->fontData->descent;
			fontx->tm.tmAscent				= fontx->fontData->ascent;
			fontx->tm.tmDescent				= fontx->fontData->descent;
			fontx->tm.tmInternalLeading		= 0;
			fontx->tm.tmExternalLeading		= 0;
			fontx->tm.tmAveCharWidth		= fontx->fontData->per_char[fontx->fontData->default_char].width;
			fontx->tm.tmMaxCharWidth		= fontx->fontData->max_bounds.width;
			fontx->tm.tmWeight				= cWeight;
			fontx->tm.tmOverhang			= 0;
			fontx->tm.tmDigitizedAspectX	= 96;
			fontx->tm.tmDigitizedAspectY	= 96;

			// BYTE
			fontx->tm.tmFirstChar			= fontx->fontData->min_char_or_byte2;
			fontx->tm.tmLastChar			= fontx->fontData->max_char_or_byte2;
			fontx->tm.tmDefaultChar			= fontx->fontData->default_char;
			fontx->tm.tmBreakChar			= ' ';
			fontx->tm.tmItalic				= bItalic;
			fontx->tm.tmUnderlined			= bUnderline;
			fontx->tm.tmStruckOut			= bStrikeOut;
			fontx->tm.tmPitchAndFamily		= iPitchAndFamily;
			fontx->tm.tmCharSet				= iCharSet;
	}


	//////////
	// Indicate success or failure
	//////
		return((HFONT)fontx);
}




WINGDIAPI BOOL WINAPI GetTextMetricsA(__in HDC hdc, __out LPTEXTMETRIC lptm)
{
	SHdcX*	hdcx;


	//////////
	// Grab the hdcx
	//////
		hdcx = iHwndX_findHdc_byHdc(hdc);
		if (hdcx)
		{
			// Has a font been assigned?
			if (hdcx->font)
			{
				// Copy the text metrics
				memcpy(lptm, &hdcx->font->tm, sizeof(*lptm));
				return(TRUE);
			}
		}


	//////////
	// If we get here, failure
	//////
		return(FALSE);
}




//////////
//
// Returns default objects for various forms.
// Note:  Not all of them are used in VJr, so not all are implemented.
//
//////
	WINGDIAPI HGDIOBJ WINAPI GetStockObject(__in DWORD obj)
	{
		SBgra color;


		// What object are they requesting?
		switch (obj)
		{
			case NULL_BRUSH:
			case WHITE_BRUSH:
				color.color = rgba(255,255,255,255);
				break;

			case LTGRAY_BRUSH:
				color.color = rgba(235,235,235,255);
				break;

			case GRAY_BRUSH:
				color.color = rgba(192,192,192,255);
				break;

			case DKGRAY_BRUSH:
				color.color = rgba(92,92,92,255);
				break;

			case BLACK_BRUSH:
				color.color = rgba(0,0,0,255);
				break;

			case WHITE_PEN:
			case BLACK_PEN:
			case NULL_PEN:
				color.color = -1;
				break;

			case OEM_FIXED_FONT:
			case ANSI_FIXED_FONT:
			case ANSI_VAR_FONT:
			case SYSTEM_FONT:
			case DEVICE_DEFAULT_FONT:
			case DEFAULT_PALETTE:
			case SYSTEM_FIXED_FONT:
				color.color = -1;
				break;

			default:
				// Default to an invalid value
				color.color = -1;
				break;
		}

		// Return our result
		return(color.color);
	}
