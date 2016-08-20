//////////
//
// /libsf/utils/common/cpp/linux/hwndx.cpp
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
//     Jan.17.2014
//////
// Change log:
//     Jan.17.2014 - Initial creation
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
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
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
// Posts a message to the indicated win->msgQueue.
//
//////
	bool iHwndX_postMessage_byWin(SHwndX* win, uptr message, uptr wParam, uptr lParam)
	{
		SMessageX* msg;


		// Make sure our environment is sane
		if (win && win->isValid)
		{
			//////////
			// Make sure there's a message queue
			//////
				if (!win->msgQueue)
					iBuilder_createAndInitialize(&win->msgQueue, -1);


			//////////
			// Append the message
			//////
				msg = (SMessageX*)iBuilder_appendData(win->msgQueue, (s8*)NULL, sizeof(SMessageX));
				if (msg)
				{
					msg->msg.hwnd		= win->hwnd;
					msg->msg.message	= message;
					msg->msg.wParam		= wParam;
					msg->msg.lParam		= lParam;
					msg->msg.time		= iHwndX_getTime();
					memcpy(&msg->msg.pt, &win->mousePt, sizeof(msg->msg.pt));

					// Indicate success
					return(true);
				}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Posts a message to the win->msgQueue derived by the hWnd.
//
//////
	bool iHwndX_postMessage_byHwnd(HWND hWnd, uptr message, uptr wParam, uptr lParam)
	{
		SHwndX* win;


		// Try to find the window
		win = iHwndX_findWindow_byHwnd(hWnd);
		if (win)
			return(iHwndX_postMessage_byWin(win, message, wParam, lParam));

		// If we get here, not found
		return(false);
	}




//////////
//
// Called at startup one time to declare the initial desktop window as a pseudo-window
// which is
//
//////
	SHwndX* iHwndX_declareDesktopHwnd(void)
	{
		s32			lnWidth, lnHeight;
		WNDCLASSEX	wcx;
		SHwndX*		win;


		//////////
		// Allocate our primary SHwndX buffer if need be
		//////
			if (!gsWindows)			iBuilder_createAndInitialize(&gsWindows, -1);
			if (!gsClasses)			iBuilder_createAndInitialize(&gsClasses, -1);
			if (!gsHdcs)			iBuilder_createAndInitialize(&gsHdcs, -1);


		//////////
		// Connect to X11
		//////
			gsDesktop.display		= XOpenDisplay(NULL);
			gsDesktop.screen		= DefaultScreen(gsDesktop.display);
			gsDesktop.depth			= DefaultDepth(gsDesktop.display, gsDesktop.screen);
			gsDesktop.connection	= ConnectionNumber(gsDesktop.display);
			gsDesktop.windowDesktop	= RootWindow(gsDesktop.display, gsDesktop.screen);


		//////////
		// Register our logical desktop class
		//////
			memset(&wcx, 0, sizeof(wcx));
			wcx.cbSize			= sizeof(wcx);
			wcx.style			= CS_OWNDC;
			wcx._lpfnWndProc	= (uptr)&DefWindowProc;
			wcx.lpszClassName	= (cs8*)&cgcDesktop[0];
			wcx.lpszMenuName	= (cs8*)&cgcDesktop[0];
			RegisterClassEx(&wcx);


		//////////
		// Create our logical desktop window
		//////
			lnWidth			= XDisplayWidth(gsDesktop.display, gsDesktop.screen);
			lnHeight		= XDisplayHeight(gsDesktop.display, gsDesktop.screen);
debug_break;
			ghWndDesktop	= CreateWindowEx(	0, cgcDesktop, cgcDesktop, WS_POPUP,
												0, 0, lnWidth, lnHeight,
												null0, null0, null0, null0);


		//////////
		// Create our default device context
		//////
			win = iHwndX_findWindow_byHwnd(ghWndDesktop);
			if (win)
			{
				// Create the actual hdc
				win->hdcx = iHwndX_createHdc(lnWidth, lnHeight, NULL);

				// Populate with default items
				//XQueryFont(gsDesktop.display, "*");
			}


		//////////
		// Return the logical desktop pointer
		//////
			return(win);
	}




//////////
//
// Obtain the current time in milliseconds since startup, or rollover if up for a long, long time.
//
//////
	DWORD iHwndX_getTime(void)
	{
		timespec tp;


		//////////
		// Grab the time
		//////
			clock_gettime(CLOCK_MONOTONIC, &tp);


		//////////
		// Convert to milliseconds
		//////
			tp.tv_nsec	/= 1000000;						// Divide nanoseconds by 1 million to get milliseconds
			tp.tv_nsec	+= ((s32)tp.tv_sec * 1000);		// Add (1000*sec) to milliseconds


		//////////
		// Return our result
		//////
			return((DWORD)tp.tv_nsec);		// (1000*sec) + milliseconds
	}




//////////
//
// Find the indicated window based on its hwnd
//
//////
	SHwndX* iHwndX_findWindow_byHwnd(HWND hWnd)
	{
		u32		lnI;
		SHwndX*	win;


		// Make sure our environment is sane
		if (gsWindows)
		{
			// Iterate through each window until we find the correct one
			for (lnI = 0, win = (SHwndX*)gsWindows->buffer; lnI < gsWindows->populatedLength; lnI += sizeof(SHwndX), win++)
			{
				// Is this our window?
				if (win->isValid && win->hwnd == hWnd)
					return(win);
			}
			// If we get here, not found
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Find the indicated window based on its hdc
//
//////
	SHwndX* iHwndX_findWindow_byHdcx(SHdcX* hdcx)
	{
		u32		lnI;
		SHwndX*	win;


		// Make sure our environment is sane
		if (gsWindows)
		{
			// Iterate through each window until we find the correct one
			for (lnI = 0, win = (SHwndX*)gsWindows->buffer; lnI < gsWindows->populatedLength; lnI += sizeof(SHwndX), win++)
			{
				// Is this our window?
				if (win->isValid && win->hdcx == hdcx)
					return(win);
			}
			// If we get here, not found
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Find the indicated device context based on its hdc
//
//////
	SHdcX* iHwndX_findHdc_byHdc(HDC hdc)
	{
		u32		lnI;
		SHdcX*	lhdc;


		// Make sure our environment is sane
		if (gsHdcs)
		{
			// Iterate through each window until we find the correct one
			for (lnI = 0, lhdc = (SHdcX*)gsHdcs->buffer; lnI < gsHdcs->populatedLength; lnI += sizeof(SHdcX), lhdc++)
			{
				// Is this our window?
				if (lhdc->isValid && lhdc->hdc == hdc)
					return(lhdc);
			}
			// If we get here, not found
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Find the indicated class based on its name
//
//////
	SClassX* iHwndX_findClass_byName(cs8* lpClassName)
	{
		u32			lnI, lnLength;
		SClassX*	cls;


		// Make sure our environment is sane
		if (lpClassName)
		{
			// Iterate through each class until we find the correct one
			lnLength = strlen(lpClassName);
			for (lnI = 0, cls = (SClassX*)gsClasses->buffer; lnI < gsClasses->populatedLength; lnI += sizeof(SClassX), cls++)
			{
				// If it's valid, and the class maches, we're good
				if (cls->isValid && strlen(cls->wcx.lpszClassName) == lnLength && _memicmp(cls->wcx.lpszClassName, lpClassName, lnLength) == 0)
					return(cls);
			}
			// If we get here, the class was not found
		}

		// If we get here, invalid
		return(NULL);
	}




//////////
//
// Called when a new logical Windows window is created to create the associated X-window,
// and also to logically schedule the Windows startup messages
//
//////
	void iHwndX_createWindow(SHwndX* win)
	{
		if (!win->x11)
			win->x11 = iHwndX_createXWindow(win);
	}




//////////
//
// Called to populate the X11 window portion
//
//////
	SXWindow* iHwndX_createXWindow(SHwndX* win)
	{
		SXWindow* xwin;


		// Make sure our environment is sane
		if (win)
		{
			// Allocate the structure
			xwin = (SXWindow*)malloc(sizeof(SXWindow));
			if (xwin)
			{
				// Initialize
				memset(xwin, 0, sizeof(*xwin));

				// Initialize X for this window
				if (iHwndX_initializeXWindow(xwin, win->rc.right - win->rc.left, win->rc.bottom - win->rc.top, win->cTitle.data_s8) == _X11_OK)
					return(xwin);

				// If we get here, failure
				free(xwin);
			}
		}

		// If we get here, invalid
		return(NULL);
	}




//////////
//
// Called to delete the X11 window portion
//
//////
	void iHwndX_deleteXWindow(SHwndX* win)
	{
		SXWindow* xwin;


		// Make sure the window is valid
		if (win && win->isValid && win->x11)
		{
			//////////
			// Delete the region
			//////
				if (win->regionx)
					iHwndX_deleteRegion(win);


			//////////
			// Delete the graphical context
			//////
				xwin = win->x11;
				if (xwin->gc)
					XFreeGC(xwin->display, xwin->gc);


			//////////
			// Primray pixel buffer
			//////
				if (xwin->virtualscreen)
				{
					free(xwin->virtualscreen);
					xwin->virtualscreen = NULL;
				}
				if (xwin->ximage)
				{
					XDestroyImage(xwin->ximage);
					xwin->ximage = NULL;
				}


			//////////
			// Pixel buffer 2
			//////
				if (xwin->virtualscreen2)
				{
					free(xwin->virtualscreen2);
					xwin->virtualscreen2 = NULL;
				}
				if (xwin->ximage2)
				{
					XDestroyImage(xwin->ximage2);
					xwin->ximage = NULL;
				}


			//////////
			// Delete the window on the desktop
			//////
				if (xwin->window)
				{
					XDestroyWindow(xwin->display, xwin->window);
					xwin->window = 0;
				}


			//////////
			// Reset the x11 pointer
			//////
				win->x11 = NULL;
		}
	}




//////////
//
// Called to create a pseudo device context
//
//////
	SHdcX* iHwndX_createHdc(s32 tnWidth, s32 tnHeight, SBitmap* bmp)
	{
		union {
			uptr	_hdc;
			SHdcX*	hdc;
		};


		//////////
		// Make sure we have our HDC buffer allocated
		//////
			if (!gsHdcs)
				iBuilder_createAndInitialize(&gsHdcs, -1);


		//////////
		// Allocate a new one
		//////
			hdc = (SHdcX*)iBuilder_appendData(gsHdcs, (s8*)NULL, sizeof(SHdcX));
			if (hdc)
			{
				// Initialize
				hdc->isValid			= true;
				hdc->hdc				= _hdc;

				// Default settings
				hdc->isOpaque			= false;
				hdc->colorFore.color	= rgba(0,0,0,255);
				hdc->colorBack.color	= rgba(255,255,255,255);;

				// Allocate the default font
				hdc->font				= iFont_create(cgcFontName_default, 10, FW_NORMAL, 0, 0);

				// Allocate a bitmap
				if (!bmp)
				{
					// Create a bitmap
					hdc->bmp = iBmp_allocate();
					iBmp_createBySize(hdc->bmp, tnWidth, tnHeight, 24);

				} else {
					// Use the indicated bitmap
					hdc->bmp = bmp;
				}
			}


		//////////
		// Indicate success or failure
		//////
			return(hdc);
	}




//////////
//
// Called to physically create the X11 window which will be drawn on the desktop.
//
//////
	s32 iHwndX_initializeXWindow(SXWindow* xwin, s32 width, s32 height, s8* title)
	{
		XSizeHints Hints;


		// Make sure our environment is sane
		if (xwin)
		{
			//////////
			// Allocate a display
			//////
				xwin->display = XOpenDisplay(NULL);
				if (!xwin->display)
					return _X11_NO_DISPLAY;


			//////////
			// Populate our local settings
			//////
				xwin->width		= width;
				xwin->height	= height;
				xwin->drawable	= DefaultScreen(xwin->display);
				xwin->screenptr	= DefaultScreenOfDisplay(xwin->display);
				xwin->visual	= DefaultVisualOfScreen(xwin->screenptr);
				xwin->depth		= DefaultDepth(xwin->display, xwin->drawable);
				xwin->pixelsize	= 4;


			//////////
			// Make sure we have a compatible display
			//////
				if (xwin->depth != 24 && xwin->depth != 32)
					return _X11_UNSUPPORTED;


			//////////
			// Physically create the window on the desktop
			//////
				xwin->window	= XCreateWindow(xwin->display,
												RootWindowOfScreen(xwin->screenptr),
												0, 0, xwin->width, xwin->height,
												0, xwin->depth,
												InputOutput,
												xwin->visual, 0, NULL);

				// Are we valid?
				if (!xwin->window)
					return _X11_NO_WINDOW;

				// Raise it to the top
				XMapRaised(xwin->display, xwin->window);


			//////////
			// Provide hints because we do our own resizing internally
			//////
				Hints.flags			= PSize | PMinSize | PMaxSize;
				Hints.min_width		= Hints.max_width	= Hints.base_width	= width;
				Hints.min_height	= Hints.max_height	= Hints.base_height	= height;
				XSetWMNormalHints(xwin->display, xwin->window, &Hints);


			//////////
			// Set window title and specify those events we would like to receive
			//////
				XStoreName(xwin->display, xwin->window, title);
				XSelectInput(xwin->display, xwin->window, 		ExposureMask
															|	KeyPressMask
															|	KeyReleaseMask
															|	ButtonPressMask
															|	EnterWindowMask
															|	LeaveWindowMask
															|	PointerMotionMask
															|	FocusChangeMask);

			//////////
			// Graphical context
			//////
				xwin->gc = XCreateGC(xwin->display, xwin->window, 0, NULL);


			//////////
			// Primray pixel buffer
			//////
				xwin->screensize	= xwin->height * xwin->width * xwin->pixelsize;
				xwin->virtualscreen	= (SBgra*)malloc(xwin->screensize);
				if (!xwin->virtualscreen)
					return _X11_NO_VIRTUAL_SCREEN;

				// Logical image
				xwin->ximage = XCreateImage(xwin->display, xwin->visual, xwin->depth,
											ZPixmap, 0,
											(s8*)xwin->virtualscreen,
											xwin->width, xwin->height,
											(xwin->pixelsize * 8),
											xwin->width * xwin->pixelsize);

				// Did we get the buffer?
				if (!xwin->ximage)
					return _X11_NO_PIXEL_BUFFER;


			//////////
			// Pixel buffer 2
			//////
				xwin->screensize2		= xwin->height * xwin->width * xwin->pixelsize;
				xwin->virtualscreen2	= (SBgra*)malloc(xwin->screensize2);
				if (!xwin->virtualscreen2)
					return _X11_VIRTALLOC;

				// Logical image
				xwin->ximage2 = XCreateImage(xwin->display, xwin->visual, xwin->depth,
											ZPixmap, 0,
											(s8*)xwin->virtualscreen2,
											xwin->width, xwin->height,
											(xwin->pixelsize * 8),
											xwin->width * xwin->pixelsize);
				// Did we get the buffer?
				if (!xwin->ximage2)
					return _X11_NO_PIXEL_BUFFER;


			//////////
			// We're good
			//////
				return _X11_OK;
		}

		// If we get here, invalid
		return _X11_GENERAL_FAILURE;
	}




//////////
//
// Called to add a new timer to a window
//
//////
	bool iHwndX_addTimer(SHwndX* win, sptr nIDEvent, UINT uElapse, sptr lpTimerFunc)
	{
//		sigevent	sev;
//		timer_t		timerid;
//		STimerX*	timer;
//
//
//		//////////
//		// Make sure our builder is created
//		//////
//			if (!gsTimers)
//				iBuilder_createAndInitialize(&gsTimers, -1);
//
//
//		//////////
//		// Allocate our timer
//		//////
//			timer = (STimerX*)iBuilder_allocateBytes(gsTimers, sizeof(STimerX));
//			if (timer)
//			{
//				//////////
//				// Setup the signal info
//				//////
//					sev.sigev_notify			= SIGEV_SIGNAL;
//					sev.sigev_signo				= SIG;
//					sev.sigev_value.sival_ptr	= &timer->timerId;
//					if (timer_create(CLOCKID, &sev, &timer->timerId) == -1)
//						return(false);
//
//
//				//////////
//				// Create the timer
//				//////
//					timer->interval			= uElapse;
//					lnResult				= timer_create(CLOCK_REALTIME, &sev, &timer->timerId);
//					timer->isValid			= (lnResult == 0);
//					timer->winAssociated	= win;
//					timer->_timerFunc		= lpTimerFunc;
//
//
//				//////////
//				// Arm it
//				//////
//					if (timer->isValid)
//					{
//						//////////
//						// Compute interval
//						//////
//							timer->its.it_interval.tv_sec	= (u32)uElapse / 1000;
//							timer->its.it_interval.tv_usec	= (u32)(uElapse % 1000) * 1000000;
//							memcpy(&timer->its.it_value, &timer->its.it_interval, sizeof(timer->its.it_value));
//
//
//						//////////
//						// Set the signal
//						//////
//							timer_settime(timer->timerid, 0, &timer->its, NULL);
//					}
//
//
//				//////////
//				// Indicate success or failure
//				//////
//					return(timer->isValid);
//			}
//
//
//		//////////
//		// If we get here, invalid
//		//////
			return(false);
	}

// Sample code from web:
// #include <stdlib.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <signal.h>
// #include <time.h>
//
// #define CLOCKID CLOCK_REALTIME
// #define SIG SIGRTMIN
//
// #define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
//                         } while (0)
//
// static void
// print_siginfo(siginfo_t *si)
// {
//     timer_t *tidp;
//     int or;
//
//    tidp = si->si_value.sival_ptr;
//
//    printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
//     printf("    *sival_ptr = 0x%lx\n", (long) *tidp);
//
//    or = timer_getoverrun(*tidp);
//     if (or == -1)
//         errExit("timer_getoverrun");
//     else
//         printf("    overrun count = %d\n", or);
// }
//
// static void
// handler(int sig, siginfo_t *si, void *uc)
// {
//     /* Note: calling printf() from a signal handler is not
//        strictly correct, since printf() is not async-signal-safe;
//        see signal(7) */
//
//    printf("Caught signal %d\n", sig);
//     print_siginfo(si);
//     signal(sig, SIG_IGN);
// }
//
// int
// main(int argc, char *argv[])
// {
//     timer_t timerid;
//     struct sigevent sev;
//     struct itimerspec its;
//     long long freq_nanosecs;
//     sigset_t mask;
//     struct sigaction sa;
//
//    if (argc != 3) {
//         fprintf(stderr, "Usage: %s <sleep-secs> <freq-nanosecs>\n",
//                 argv[0]);
//         exit(EXIT_FAILURE);
//     }
//
//    /* Establish handler for timer signal */
//
//    printf("Establishing handler for signal %d\n", SIG);
//     sa.sa_flags = SA_SIGINFO;
//     sa.sa_sigaction = handler;
//     sigemptyset(&sa.sa_mask);
//     if (sigaction(SIG, &sa, NULL) == -1)
//         errExit("sigaction");
//
//    /* Block timer signal temporarily */
//
//    printf("Blocking signal %d\n", SIG);
//     sigemptyset(&mask);
//     sigaddset(&mask, SIG);
//     if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
//         errExit("sigprocmask");
//
//    /* Create the timer */
//
//    sev.sigev_notify = SIGEV_SIGNAL;
//     sev.sigev_signo = SIG;
//     sev.sigev_value.sival_ptr = &timerid;
//     if (timer_create(CLOCKID, &sev, &timerid) == -1)
//         errExit("timer_create");
//
//    printf("timer ID is 0x%lx\n", (long) timerid);
//
//    /* Start the timer */
//
//    freq_nanosecs = atoll(argv[2]);
//     its.it_value.tv_sec = freq_nanosecs / 1000000000;
//     its.it_value.tv_nsec = freq_nanosecs % 1000000000;
//     its.it_interval.tv_sec = its.it_value.tv_sec;
//     its.it_interval.tv_nsec = its.it_value.tv_nsec;
//
//    if (timer_settime(timerid, 0, &its, NULL) == -1)
//          errExit("timer_settime");
//
//    /* Sleep for a while; meanwhile, the timer may expire
//        multiple times */
//
//    printf("Sleeping for %d seconds\n", atoi(argv[1]));
//     sleep(atoi(argv[1]));
//
//    /* Unlock the timer signal, so that timer notification
//        can be delivered */
//
//    printf("Unblocking signal %d\n", SIG);
//     if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
//         errExit("sigprocmask");
//
//    exit(EXIT_SUCCESS);
// }




//////////
//
// Called to delete the indicated timer.
//
//////
	void iHwndX_deleteTimer(SHwndX* win, sptr nIDEvent)
	{
//		s32			lnI;
//		STimerX*	timer;
//
//
//		//////////
//		// Iterate through each timer
//		//////
//			for (lnI = 0, timer = (STimerX*)gsTimers.buffer.data; lnI += sizeof(STimerX), timer++)
//			{
//				// Is this our timer?
//				if (timer->isValid && (!win || timer->winAssociated == win) && timer->nIDEvent == nIDEvent)
//				{
//					// See code sample above
//				}
//			}
	}




//////////
//
// Obtain the next font that's available
//
//////
	SFontX* iHwndX_getNextFont(void)
	{
		u32		lnI;
		SFontX* font;


		//////////
		// Make sure the master list exists
		//////
			if (!gsHfonts)
				iBuilder_createAndInitialize(&gsHfonts, -1);


		//////////
		// Search for an empty slot
		//////
			for (lnI = 0, font = (SFontX*)gsHfonts->buffer; lnI < gsHfonts->populatedLength; lnI += sizeof(SFontX), font++)
			{
				// If this one is not used, return it
				if (!font->isValid)
					break;
			}
			// If we get here, none were found


		//////////
		// Allocate a new slot if need be
		//////
			if (lnI >= gsHfonts->populatedLength)
				font = (SFontX*)iBuilder_appendData(gsHfonts, (s8*)NULL, sizeof(SFontX));



		//////////
		// Indicate success or failure
		//////
			return(font);
	}




///////////
//
// Called to create a new brush
//
//////
	SBrushX* iHwndX_createBrush(bool isSolidBrush, uptr data)
	{
		return(NULL);
	}




///////////
//
// Called to delete a brush
//
//////
	SBrushX* iHwndX_deleteBrush(HBRUSH hbr)
	{
		return(NULL);
	}




//////////
//
// Locate the indicated brush
//
//////
	SBrushX* iHwndX_findBrush_byBrush(HBRUSH hbr)
	{
		return(NULL);
	}




//////////
//
// Create a region for population
//
//////
	SRegionX* iHwndX_createRegion(void)
	{
		//////////
		// Make sure the array is valid
		//////
			if (!gsRegions)
				iBuilder_createAndInitialize(&gsRegions, 1024);


		//////////
		// Create a new region
		//////
			return((SRegionX*)iBuilder_appendData(gsRegions, (s8*)NULL, sizeof(SRegionX)));
	}




//////////
//
// Delete the region for this window (if any)
//
//////
	void iHwndX_deleteRegion(SHwndX* win)
	{
		//////////
		// Make sure we have a window and a region
		//////
			if (win && win->x11 && win->regionx && win->regionPixmap)
			{
				// Is there a region?
				if (iBuilder_isPointer(gsRegions, (uptr)win->regionx))
				{
					//////////
					// Disable it
					//////
						win->regionx->isValid = false;


					//////////
					// Remove the clipping mask
					//////
						XSetClipMask(win->x11->display, win->x11->gc, null0);


					//////////
					// Delete the Pixmap
					//////
						XFreePixmap(win->x11->display, win->regionPixmap);
						win->regionPixmap = null0;


					//////////
					// Delete the regionx itself
					//////
						iBuilder_freeAndRelease(&win->regionx->regionArray);
				}
			}
	}
