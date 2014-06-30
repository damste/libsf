//////////
//
// /libsf/source/vjr/vjr_sup.cpp
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




void initialize(HACCEL* hAccelTable)
{
	HRESULT hRes;


	// Keyboard shortcuts
	*hAccelTable = LoadAccelerators(ghInstance, MAKEINTRESOURCE(IDC_VJR));

	// Taskbar interface
	hRes = OleInitialize(NULL);
	CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&giTaskbar);

	// Initialize our builder
	iBuilder_createAndInitialize(&gWindows,	-1);
	iBuilder_createAndInitialize(&gFonts,	-1);

	// Initialize our critical sections
	InitializeCriticalSection(&gcsUniqueIdAccess);

	// Get startup time
	systemStartedMs = iTime_getLocalMs();

	// Default font
	gsFont = iFont_create(cgcUbuntu, 10, FW_NORMAL, 0, 0);


	//////////
	// Load our icons and images
	//////
		bmpVjrIcon	= iBmp_rawLoad(cgc_appIconBmp);
		bmpVjrIcon	= iBmp_rawLoad(cgc_jdebiAppIconBmp);

		// Create a 1x1 no image bitmap placeholder
		bmpNoImage	= iBmp_allocate();
		iBmp_createBySize(bmpNoImage, 1, 1, 32);

		bmpClose	= iBmp_rawLoad(cgc_closeBmp);
		bmpMaximize	= iBmp_rawLoad(cgc_maximizeBmp);
		bmpMinimize	= iBmp_rawLoad(cgc_minimizeBmp);
		bmpMove		= iBmp_rawLoad(cgc_moveBmp);

		bmpArrowUl	= iBmp_rawLoad(cgc_arrowUlBmp);
		bmpArrowUr	= iBmp_rawLoad(cgc_arrowUrBmp);
		bmpArrowLl	= iBmp_rawLoad(cgc_arrowLlBmp);
		bmpArrowLr	= iBmp_rawLoad(cgc_arrowLrBmp);


	// Create our message window
	iInit_createMessageWindow();

	// Create our default objects
	iInit_createDefaultObjects();

	// Create our main screen window
	iInit_createScreenForm();
	iInit_createJDebiForm();
}




//////////
//
// Creates the message window used for communicating actions
//
//////
	void iInit_createMessageWindow(void)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;


		//////////
		// Register the classes if need be
		//////
			while (1)
			{
				if (!GetClassInfoExA(ghInstance, cgcMessageWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.lpszClassName		= cgcMessageWindowClass;
					classa.lpfnWndProc			= &iWndProc_messageWindow;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}

				// Register the general window class if need be
				if (!GetClassInfoExA(ghInstance, cgcWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
					classa.lpszClassName		= cgcWindowClass;
					classa.hIcon				= LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_VJR));
					classa.hCursor				= LoadCursor(NULL, IDC_ARROW);
					classa.lpfnWndProc			= &iWndProc_screenWindow;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}



			//////////
			// Create the message window
			//////
				ghwndMsg = CreateWindowA(cgcMessageWindowClass, cgcMessageWindowClass, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, ghInstance, 0);
				if (ghwndMsg)
				{
					// Read events
					CreateThread(NULL, 0, &iReadEvents_messageWindow, 0, 0, 0);
					return;
				}
				break;
			}
			// We should never get here
			MessageBoxA(NULL, "Error creating Visual FreePro Jr's message window.", "VJr - Fatal Error", MB_OK);
	}




//////////
//
// In order for a window pointer to be valid, it must be in the range gWindows->data to
// gWindows->data + gWindows->populatedLength.
//
//////
	bool isValidWindow(u32 w)
	{
		return(w >= (u32)gWindows->data && w < (u32)(gWindows->data + gWindows->populatedLength));
	}




//////////
//
// Thread to handle message window events
//
//////
	DWORD WINAPI iReadEvents_messageWindow(LPVOID lpParameter)
	{
		MSG msg;


		// Read until the message window goes bye bye
		while (GetMessage(&msg, ghwndMsg, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When we get here, we're shutting down
		return 0;
	}




//////////
//
// Processes internal messages to process things internally.
//
//////
	LRESULT CALLBACK iWndProc_messageWindow(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Loads the default settings for each object, populating them in turn.
//
//////
	void iInit_createDefaultObjects(void)
	{
		SSubObjEmpty*		subobj_empty;
		SSubObjForm*		subobj_form;
		SSubObjSubform*		subobj_subform;
		SSubObjLabel*		subobj_label;
		SSubObjTextbox*		subobj_textbox;
		SSubObjButton*		subobj_button;
		SSubObjEditbox*		subobj_editbox;
		SSubObjImage*		subobj_image;
		SSubObjCheckbox*	subobj_checkbox;
		SSubObjOption*		subobj_option;
		SSubObjRadio*		subobj_radio;


		//////////
		// Create each initial subobj
		//////
			subobj_empty			= iSubobj_createEmpty(NULL, NULL);
			subobj_form				= iSubobj_createForm(NULL, NULL);
			subobj_subform			= iSubobj_createSubform(NULL, NULL);
			subobj_label			= iSubobj_createLabel(NULL, NULL);
			subobj_textbox			= iSubobj_createTextbox(NULL, NULL);
			subobj_button			= iSubobj_createButton(NULL, NULL);
			subobj_editbox			= iSubobj_createEditbox(NULL, NULL);
			subobj_image			= iSubobj_createImage(NULL, NULL);
			subobj_checkbox			= iSubobj_createCheckbox(NULL, NULL);
			subobj_option			= iSubobj_createOption(NULL, NULL);
			subobj_radio			= iSubobj_createRadio(NULL, NULL);


		//////////
		// Create each default object
		//////
			gobj_defaultEmpty		= iObj_create(_OBJECT_TYPE_EMPTY,		(void*)subobj_empty);
			gobj_defaultForm		= iObj_create(_OBJECT_TYPE_FORM,		(void*)subobj_form);
			gobj_defaultSubform		= iObj_create(_OBJECT_TYPE_SUBFORM,	(void*)subobj_subform);
			gobj_defaultLabel		= iObj_create(_OBJECT_TYPE_LABEL,		(void*)subobj_label);
			gobj_defaultTextbox		= iObj_create(_OBJECT_TYPE_TEXTBOX,	(void*)subobj_textbox);
			gobj_defaultButton		= iObj_create(_OBJECT_TYPE_BUTTON,	(void*)subobj_button);
			gobj_defaultImage		= iObj_create(_OBJECT_TYPE_IMAGE,		(void*)subobj_image);
			gobj_defaultCheckbox	= iObj_create(_OBJECT_TYPE_CHECKBOX,	(void*)subobj_checkbox);
			gobj_defaultOption		= iObj_create(_OBJECT_TYPE_OPTION,	(void*)subobj_option);
			gobj_defaultRadio		= iObj_create(_OBJECT_TYPE_RADIO,		(void*)subobj_radio);


		/////////
		// Delete each initial subobj since they've now been copied onto the default objects
		//////
			iSubobj_deleteEmpty		(subobj_empty,		true);
			iSubobj_deleteForm		(subobj_form,		true);
			iSubobj_deleteSubform	(subobj_subform,	true);
			iSubobj_deleteLabel		(subobj_label,		true);
			iSubobj_deleteTextbox	(subobj_textbox,	true);
			iSubobj_deleteButton		(subobj_button,		true);
			iSubobj_deleteEditbox	(subobj_editbox,	true);
			iSubobj_deleteImage		(subobj_image,		true);
			iSubobj_deleteCheckbox	(subobj_checkbox,	true);
			iSubobj_deleteOption		(subobj_option,		true);
			iSubobj_deleteRadio		(subobj_radio,		true);
	}




//////////
//
// Called to find or create the KSI interface window
//
//////
	SObject* iInit_createScreenForm(void)
	{
// 		s32				lnLeft, lnTop;
// 		RECT			lrc;
// 		SFont*			font;
// 		SSize			client, nonclient, overall;
// 
// 
// 		//////////
// 		// Create the object
// 		//////
// 			gobj_screen	= iObjectCreate(_OBJECT_TYPE_FORM, gobj_defaultForm);
// 
// 
// 		//////////
// 		// Find out how big the window should be
// 		//////
// 			iComputeScreenWindowClientAreaDimensions(&client);
// 			iComputeScreenWindowNonclientAreaDimensions(&nonclient);
// 			overall.width	= client.width + nonclient.width;
// 			overall.height	= client.height + nonclient.width;
// 			iAdjustScreenWindowDimensions(&overall);
// 
// 
// 		//////////
// 		// Physically create the interface window
// 		//////
// 			GetWindowRect(GetDesktopWindow(), &lrc);
// 			lnLeft	= ((lrc.right - lrc.left) - overall.width)  / 2;
// 			lnTop	= ((lrc.bottom - lrc.top) - overall.height) / 2;
// 
// 
// 		//////////
// 		// Create the fonts
// 		//////
// 			font				= iFontCreate(cgcWindowTitleBarFont, 10,	FW_BOLD, false, false);
// 			winScreen.font		= iFontDuplicate(font);
// 
// 
// 		//////////
// 		// Draw the initial window state
// 		//////
// 			iResizeScreenWindow(true);
		return(NULL);
	}




//////////
//
// 
//
//////
	SObject* iInit_createJDebiForm(void)
	{
// 		s32				lnLeft, lnTop;
// 		RECT			lrc;
// 		SFont*			font;
// 		SSize			client, nonclient, overall;
// 
// 
// 		//////////
// 		// Create the object
// 		//////
// 			gobj_jdebi	= iObjectCreate(_OBJECT_TYPE_FORM, gobj_defaultForm);
// 
// 
// 			//////////
// 			// Find out how big the window should be
// 			//////
// 				iComputeJDebiWindowClientAreaDimensions(&client);
// 				iComputeJDebiWindowNonclientAreaDimensions(&nonclient);
// 				overall.width	= client.width + nonclient.width;
// 				overall.height	= client.height + nonclient.width;
// 				iAdjustJDebiWindowDimensions(&overall);
// 
// 
// 			//////////
// 			// Physically create the interface window
// 			//////
// 				GetWindowRect(GetDesktopWindow(), &lrc);
// 				lnLeft	= ((lrc.right - lrc.left) - overall.width)  / 2;
// 				lnTop	= ((lrc.bottom - lrc.top) - overall.height) / 2;
// 
// 			//////////
// 			// Create the font
// 			//////
// 				font				= iFontCreate(cgcWindowTitleBarFont, 10,	FW_BOLD, false, false);
// 				winJDebi.font		= iFontDuplicate(font);
// 
// 
// 			//////////
// 			// Draw the initial window state
// 			//////
// 				iResizeJDebiWindow(true);
		return(NULL);
	}




//////////
//
// Called to resize the window if need be based upon new client size settings
//
//////
	void iResizeScreenWindow(bool tlForce)
	{
// 		s32		lnLeft, lnTop;
// 		RECT	lrcDesktop;
// 		SSize	client, nonclient, overall;
// 
// 
// 		//////////
// 		// Find out how big the window should be
// 		//////
// 			iComputeScreenWindowClientAreaDimensions(&client);
// 			iComputeScreenWindowNonclientAreaDimensions(&nonclient);
// 			overall.width	= client.width + nonclient.width;
// 			overall.height	= client.height + nonclient.width;
// 			iAdjustScreenWindowDimensions(&overall);
// 
// 
// 		//////////
// 		// Determine the windows desktop size
// 		//////
// 			GetWindowRect(GetDesktopWindow(), &lrcDesktop);
// 
// 		
// 		//////////
// 		// If the window size is different than this, we need to resize it
// 		//////
// 			lnLeft	= (lrcDesktop.right  - lrcDesktop.left)  / 16;
// 			lnTop	= (lrcDesktop.bottom - lrcDesktop.top)   / 16;
// 			iSetScreenWindowSize(lnLeft, lnTop, overall.width, overall.height, tlForce);
	}




//////////
//
// Called to resize the JDebi window
//
//////
	void iResizeJDebiWindow(bool tlForce)
	{
// 		s32		lnLeft, lnTop;
// 		RECT	lrcDesktop;
// 		SSize	client, nonclient, overall;
// 		SSize	clientScreen, nonclientScreen, overallScreen;
// 
// 
// 		//////////
// 		// Find out how big the window should be
// 		//////
// 			iComputeJDebiWindowClientAreaDimensions(&client);
// 			iComputeJDebiWindowNonclientAreaDimensions(&nonclient);
// 			overall.width	= client.width + nonclient.width;
// 			overall.height	= client.height + nonclient.width;
// 			iAdjustJDebiWindowDimensions(&overall);
// 			
// 			// Main screen
// 			iComputeScreenWindowClientAreaDimensions(&clientScreen);
// 			iComputeScreenWindowNonclientAreaDimensions(&nonclientScreen);
// 			overallScreen.width		= clientScreen.width + nonclientScreen.width;
// 			overallScreen.height	= clientScreen.height + nonclientScreen.width;
// 			iAdjustScreenWindowDimensions(&overallScreen);
// 
// 
// 		//////////
// 		// Determine the windows desktop size
// 		//////
// 			GetWindowRect(GetDesktopWindow(), &lrcDesktop);
// 
// 		
// 		//////////
// 		// If the window size is different than this, we need to resize it
// 		//////
// 			lnLeft	= winScreen.rc.right;
// 			lnTop	= winScreen.rc.top;
// 			iSetJDebiWindowSize(lnLeft, lnTop, ((lrcDesktop.right - lrcDesktop.left) - overallScreen.width) - (2 * winScreen.rc.left), overallScreen.height, tlForce);
	}




//////////
//
// Called to programmatically set the screen window size after a resize
//
//////
	void iSetScreenWindowSize(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce)
	{
// 		bool llChangedSomething;
// 
// 
// 		// Do we need to resize?
// 		if (!IsWindowVisible(ghwndScreen) && !tlForce)
// 			return;
// 
// 		// Begin resizing
// 		ShowWindow(ghwndScreen, SW_RESTORE);
// 		llChangedSomething = tlForce;
// 		if (winScreen.rc.right - winScreen.rc.left != tnWidth || winScreen.rc.bottom - winScreen.rc.top != tnHeight)
// 		{
// 			// Yes
// 			llChangedSomething = true;
// 			SetWindowPos(ghwndScreen, NULL, 0, 0, tnWidth, tnHeight,	SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE);
// 		}
// 
// 
// 		// Do we need to move?
// 		if (winScreen.rc.left != tnLeft || winScreen.rc.top != tnTop)
// 		{
// 			// Yes
// 			llChangedSomething = true;
// 			SetWindowPos(ghwndScreen, NULL, tnLeft, tnTop, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
// 		}
// 
// 
// 		// Get the current size
// 		SetRect(&winScreen.rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);
// 
// 
// 		// Did we change anything?
// 		if (llChangedSomething)
// 		{
// 			//////////
// 			// If there's already an image, release it
// 			//////
// 				DeleteObject((HGDIOBJ)winScreen.bmp.hbmp);
// 				DeleteDC(winScreen.bmp.hdc);
// 				memset(&winScreen.bmp, 0, sizeof(SBitmap));
// 
// 
// 			//////////
// 			// Create the buffers for it
// 			//////
// 				winScreen.bmp.hdc		= CreateCompatibleDC(GetDC(GetDesktopWindow()));
// 				winScreen.bmp.hbmp		= iCreateBitmap(winScreen.bmp.hdc, tnWidth, tnHeight, 1, 32, (void**)&winScreen.bmp.bd, &winScreen.bmp.bh, &winScreen.bmp.bi);
// 				winScreen.bmp.rowWidth	= iBmpComputeRowWidth(&winScreen.bmp);
// 				SelectObject(winScreen.bmp.hdc, winScreen.bmp.hbmp);
// 
// 
// 			//////////
// 			// Redraw the window
// 			//////
// 				GetClientRect(ghwndScreen, &winScreen.rcClient);
// 				iRedrawScreen(&winScreen);
// 		}
	}




//////////
//
// Called to programmatically set the JDebi window size after a resize
//
//////
	void iSetJDebiWindowSize(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce)
	{
// 		bool llChangedSomething;
// 
// 
// 		// Do we need to resize?
// 		if (!IsWindowVisible(ghwndJDebi) && !tlForce)
// 			return;
// 
// 		// Begin resizing
// 		ShowWindow(ghwndJDebi, SW_RESTORE);
// 		llChangedSomething = tlForce;
// 		if (winJDebi.rc.right - winJDebi.rc.left != tnWidth || winJDebi.rc.bottom - winJDebi.rc.top != tnHeight)
// 		{
// 			// Yes
// 			llChangedSomething = true;
// 			SetWindowPos(ghwndJDebi, NULL, 0, 0, tnWidth, tnHeight,	SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE);
// 		}
// 
// 
// 		// Do we need to move?
// 		if (winJDebi.rc.left != tnLeft || winJDebi.rc.top != tnTop)
// 		{
// 			// Yes
// 			llChangedSomething = true;
// 			SetWindowPos(ghwndJDebi, NULL, tnLeft, tnTop, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
// 		}
// 
// 
// 		// Get the current size
// 		SetRect(&winJDebi.rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);
// 
// 
// 		// Did we change anything?
// 		if (llChangedSomething)
// 		{
// 			//////////
// 			// If there's already an image, release it
// 			//////
// 				DeleteObject((HGDIOBJ)winJDebi.bmp.hbmp);
// 				DeleteDC(winJDebi.bmp.hdc);
// 				memset(&winJDebi.bmp, 0, sizeof(SBitmap));
// 
// 
// 			//////////
// 			// Create the buffers for it
// 			//////
// 				winJDebi.bmp.hdc		= CreateCompatibleDC(GetDC(GetDesktopWindow()));
// 				winJDebi.bmp.hbmp		= iCreateBitmap(winJDebi.bmp.hdc, tnWidth, tnHeight, 1, 32, (void**)&winJDebi.bmp.bd, &winJDebi.bmp.bh, &winJDebi.bmp.bi);
// 				winJDebi.bmp.rowWidth	= iBmpComputeRowWidth(&winJDebi.bmp);
// 				SelectObject(winJDebi.bmp.hdc, winJDebi.bmp.hbmp);
// 
// 
// 			//////////
// 			// Redraw the window
// 			//////
// 				GetClientRect(ghwndJDebi, &winJDebi.rcClient);
// 				iRedrawJDebi(&winJDebi);
// 		}
	}




//////////
//
// Processes messages from the interface window, to forward on to the original window
//
//////
	LRESULT CALLBACK iWndProc_screenWindow(HWND h, UINT m, WPARAM w, LPARAM l)
	{
// 
// // 		s32				id, event;
// 		HDC				lhdc;
// 		PAINTSTRUCT		ps;
// 
// 
// 		// See if we know this hwnd
// 		// It was one of our windows
// 		switch (m)
// 		{
// 			case WM_LBUTTONDOWN:
// 				glMouseLeftButton = true;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_LBUTTONUP:
// 				if (glMoving || glResizing)
// 					ReleaseCapture();
// 
// 				glMouseLeftButton = false;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_RBUTTONDOWN:
// 				glMouseRightButton = true;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_RBUTTONUP:
// 				glMouseRightButton = false;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_MBUTTONDOWN:
// 				glMouseMiddleButton = true;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_MBUTTONUP:
// 				glMouseMiddleButton = false;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_RBUTTONDBLCLK:
// 			case WM_LBUTTONDBLCLK:
// 			case WM_MBUTTONDBLCLK:
// 			case WM_MOUSEHWHEEL:
// 			case WM_MOUSEWHEEL:
// 			case WM_MOUSEMOVE:
// 				glMouseLeftButton	= ((w & MK_LBUTTON) != 0);		// The left mouse button is down
// 				glMouseMiddleButton	= ((w & MK_MBUTTON) != 0);		// The middle mouse button is down
// 				glMouseRightButton	= ((w & MK_RBUTTON) != 0);		// The right mouse button is down
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_KEYDOWN:
// 			case WM_KEYUP:
// //			case WM_CHAR:
// //			case WM_DEADCHAR:
// 			case WM_SYSKEYDOWN:
// 			case WM_SYSKEYUP:
// //			case WM_SYSCHAR:
// //			case WM_SYSDEADCHAR:
// 				return 0;
// 				break;
// 
// 			case WM_CAPTURECHANGED:
// 				if (glMoving)
// 				{
// 					// Stop the movement
// // TODO:					iStopMove();
// 
// 				} else if (glResizing) {
// 					// Stop the resize
// // TODO:					iStopResize();
// 
// 				} else {
// 					// Make sure our flags are lowered
// 					glMoving	= false;
// 					glResizing	= false;
// 				}
// 				break;
// 
// 			case WM_PAINT:
// 				// Paint it
// 				lhdc = BeginPaint(h, &ps);
// 				BitBlt(lhdc, 0, 0, winScreen.bmp.bi.biWidth, winScreen.bmp.bi.biHeight, winScreen.bmp.hdc, 0, 0, SRCCOPY);
// 				EndPaint(h, &ps);
// 				return 0;
// 		}
// 
		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}




//////////
//
// 
//
//////
	LRESULT CALLBACK iWndProc_jDebiWindow(HWND h, UINT m, WPARAM w, LPARAM l)
	{
// 
// // 		s32				id, event;
// 		HDC				lhdc;
// 		PAINTSTRUCT		ps;
// 
// 
// 		// See if we know this hwnd
// 		// It was one of our windows
// 		switch (m)
// 		{
// 			case WM_LBUTTONDOWN:
// 				glMouseLeftButton = true;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_LBUTTONUP:
// 				if (glMoving || glResizing)
// 					ReleaseCapture();
// 
// 				glMouseLeftButton = false;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_RBUTTONDOWN:
// 				glMouseRightButton = true;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_RBUTTONUP:
// 				glMouseRightButton = false;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_MBUTTONDOWN:
// 				glMouseMiddleButton = true;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_MBUTTONUP:
// 				glMouseMiddleButton = false;
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_RBUTTONDBLCLK:
// 			case WM_LBUTTONDBLCLK:
// 			case WM_MBUTTONDBLCLK:
// 			case WM_MOUSEHWHEEL:
// 			case WM_MOUSEWHEEL:
// 			case WM_MOUSEMOVE:
// 				glMouseLeftButton	= ((w & MK_LBUTTON) != 0);		// The left mouse button is down
// 				glMouseMiddleButton	= ((w & MK_MBUTTON) != 0);		// The middle mouse button is down
// 				glMouseRightButton	= ((w & MK_RBUTTON) != 0);		// The right mouse button is down
// 				return(iProcessMouseMessage(m, w, l));
// 				break;
// 
// 			case WM_KEYDOWN:
// 			case WM_KEYUP:
// //			case WM_CHAR:
// //			case WM_DEADCHAR:
// 			case WM_SYSKEYDOWN:
// 			case WM_SYSKEYUP:
// //			case WM_SYSCHAR:
// //			case WM_SYSDEADCHAR:
// 				return 0;
// 				break;
// 
// 			case WM_CAPTURECHANGED:
// 				if (glMoving)
// 				{
// 					// Stop the movement
// // TODO:					iStopMove();
// 
// 				} else if (glResizing) {
// 					// Stop the resize
// // TODO:					iStopResize();
// 
// 				} else {
// 					// Make sure our flags are lowered
// 					glMoving	= false;
// 					glResizing	= false;
// 				}
// 				break;
// 
// 			case WM_PAINT:
// 				// Paint it
// 				lhdc = BeginPaint(h, &ps);
// 				BitBlt(lhdc, 0, 0, winJDebi.bmp.bi.biWidth, winJDebi.bmp.bi.biHeight, winJDebi.bmp.hdc, 0, 0, SRCCOPY);
// 				EndPaint(h, &ps);
// 				return 0;
// 				break;
// 		}

		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}




//////////
//
// Called to shutdown the system politely, closing everything that's open
//
//////
	bool iShutdownPolitely(void)
	{
		return(true);
	}




//////////
//
// Compute the client area dimensions based on the current settings
//
//////
	void iComputeScreenWindowClientAreaDimensions(SSize* size)
	{
		RECT lrc;


		//////////
		// Iterate through each item
		//////
			// Default to half the overall screen size
			GetWindowRect(GetDesktopWindow(), &lrc);
			size->width		= (lrc.right - lrc.left) * 7 / 16;
			size->height	= (lrc.bottom - lrc.top) * 7 / 8;

			// When we get here, they are set by value, either to the minimum, or to the maximum
			// Note:  They could be hugely too large.  The caller will have to deal with that.
	}

	void iComputeScreenWindowNonclientAreaDimensions(SSize* size)
	{
		//////////
		// Set minimum dimensions
		//////
			size->width		= 8 + 8;		// left + right
			size->height	= 24 + 24;		// top + bottom
	}

	void iAdjustScreenWindowDimensions(SSize* size)
	{
		s32		lnDesktopWidth, lnDesktopHeight, lnWidthOverhang, lnHeightOverhang;
		f32		lfWidthRatio, lfHeightRatio;
		RECT	lrc;


		//////////
		// Find out how big the desktop is
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);


		//////////
		// Make sure we're smaller than that
		//////
			lnDesktopWidth		= lrc.right - lrc.left;
			lnDesktopHeight		= lrc.bottom - lrc.top;
			if (size->width < lnDesktopWidth && size->height < lnDesktopHeight)
				return;		// We're good


		//////////
		// Find out which size needs to be decreased the most
		//////
			lnWidthOverhang		= size->width  - lnDesktopWidth;
			lnHeightOverhang	= size->height - lnDesktopHeight;
			lfWidthRatio		= ((f32)lnWidthOverhang  + (f32)lnDesktopWidth)  / (f32)lnDesktopWidth;
			lfHeightRatio		= ((f32)lnHeightOverhang + (f32)lnDesktopHeight) / (f32)lnDesktopHeight;
			if (lfWidthRatio >= lfHeightRatio)
			{
				// Adjust down by the width's ratio
				size->width		= lnDesktopWidth;
				size->height	= (s32)((f32)size->height / lfWidthRatio);

			} else {
				// Adjust down by the height's ratio
				size->width		= (s32)((f32)size->width / lfHeightRatio);
				size->height	= lnDesktopHeight;
			}
	}




//////////
//
// Compute the client area JDebi window dimensions
//
//////
	void iComputeJDebiWindowClientAreaDimensions(SSize* size)
	{
		RECT lrc;


		//////////
		// Iterate through each item
		//////
			// Default to one sixth wide, one eighth tall of the overall screen size
			GetWindowRect(GetDesktopWindow(), &lrc);
			size->width		= (lrc.right - lrc.left) * 7 / 16;
			size->height	= (lrc.bottom - lrc.top) * 7 / 8;
	}

	void iComputeJDebiWindowNonclientAreaDimensions(SSize* size)
	{
		//////////
		// Set minimum dimensions
		//////
			size->width		= 8 + 8;		// left + right
			size->height	= 24 + 24;		// top + bottom
	}

	void iAdjustJDebiWindowDimensions(SSize* size)
	{
		s32		lnDesktopWidth, lnDesktopHeight, lnWidthOverhang, lnHeightOverhang;
		f32		lfWidthRatio, lfHeightRatio;
		RECT	lrc;


		//////////
		// Find out how big the desktop is
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);


		//////////
		// Make sure we're smaller than that
		//////
			lnDesktopWidth		= lrc.right - lrc.left;
			lnDesktopHeight		= lrc.bottom - lrc.top;
			if (size->width < lnDesktopWidth && size->height < lnDesktopHeight)
				return;		// We're good


		//////////
		// Find out which size needs to be decreased the most
		//////
			lnWidthOverhang		= size->width  - lnDesktopWidth;
			lnHeightOverhang	= size->height - lnDesktopHeight;
			lfWidthRatio		= ((f32)lnWidthOverhang  + (f32)lnDesktopWidth)  / (f32)lnDesktopWidth;
			lfHeightRatio		= ((f32)lnHeightOverhang + (f32)lnDesktopHeight) / (f32)lnDesktopHeight;
			if (lfWidthRatio >= lfHeightRatio)
			{
				// Adjust down by the width's ratio
				size->width		= lnDesktopWidth;
				size->height	= (s32)((f32)size->height / lfWidthRatio);

			} else {
				// Adjust down by the height's ratio
				size->width		= (s32)((f32)size->width / lfHeightRatio);
				size->height	= lnDesktopHeight;
			}
	}




//////////
//
// Time functions
//
//////
	s64 iTime_computeMilliseconds(SYSTEMTIME* time)
	{
		s64 lnMs;
		

		// Compute the milliseconds
		lnMs	=		(time->wMilliseconds)
					+	(time->wSecond			* 1000)
					+	(time->wMinute			* 1000 * 60)
					+	(time->wHour			* 1000 * 60 * 60)
					+	(time->wDay				* 1000 * 60 * 60 * 24)
					+	(time->wMonth			* 1000 * 60 * 60 * 24 * 31)
					+	(time->wYear			* 1000 * 60 * 60 * 24 * 31 * 366);
		return(lnMs);
	}

	s64 iTime_getSystemMs(void)
	{
		SYSTEMTIME time;
		GetSystemTime(&time);
		return(iTime_computeMilliseconds(&time));
	}

	s64 iTime_getLocalMs(void)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		return(iTime_computeMilliseconds(&time));
	}

	s64 iMath_delta(s64 tnBaseValue, s64 tnSubtractionValue)
	{
		return(tnBaseValue - tnSubtractionValue);
	}




//////////
//
// Called to duplicate the indicated string
//
//////
	s8* iDuplicateString(s8* tcText)
	{
		u32		lnLength;
		s8*		ptr;


		// Allocate it
		lnLength	= strlen(tcText) + 1;
		ptr			= (s8*)malloc(lnLength);

		// Copy it (including the trailing null)
		if (ptr)
			memcpy(ptr, tcText, lnLength);

		// All done
		return(ptr);
	}




//////////
//
// Called to duplicate a font that was found from the list of known system fonts
//
//////
	SFont* iFont_duplicate(SFont* fontSource)
	{
		SFont* font;


		// Make sure our environment is sane
		font = NULL;
		if (fontSource)
		{
			//////////
			// Allocate a new pointer
			//////
				font = iFont_allocate();
				if (!font)
					return(font);


			//////////
			// Create a copy
			//////
				font->hdc					= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				font->hfont					= CreateFont(fontSource->_sizeUsedForCreateFont, 0, 0, 0, fontSource->_weight, (fontSource->_italics != 0), (fontSource->_underline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, fontSource->name.data);
				SelectObject(font->hdc, font->hfont);
				iDatum_duplicate(&font->name, fontSource->name.data, fontSource->name.length);
				font->_size					= fontSource->_size;
				font->_weight				= fontSource->_weight;
				font->_italics				= fontSource->_italics;
				font->_underline			= fontSource->_underline;
				memcpy(&font->tm, &fontSource->tm, sizeof(font->tm));
		}
		// Indicate our success or failure
		return(font);
	}




//////////
//
// Allocate an empty structure
//
//////
	SFont* iFont_allocate(void)
	{
		SFont* font;


		// Allocate the indicated size
		font = (SFont*)malloc(sizeof(SFont));

		// If allocated, initialize it
		if (font)
			memset(font, 0, sizeof(SFont));

		// Indicate our success or failure
		return(font);
	}





//////////
//
// Create a new font
//
//////
	SFont* iFont_create(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline)
	{
		u32		lnI, lnLength;
		SFont*	font;


		//////////
		// See if the indicated font already exists
		//////
			lnLength = strlen(tcFontName);
			for (lnI = 0; lnI < gFonts->populatedLength; lnI += sizeof(SFont))
			{
				// Grab the pointer
				font = (SFont*)(gFonts->data + lnI);

				// See if it matches
				if (font->_size == tnFontSize && font->_weight == tnFontWeight && font->_italics == tnItalics && font->_underline == tnUnderline && font->name.length == lnLength)
					if (_memicmp(font->name.data, tcFontName, lnLength) == 0)
						return(font);
			}


		//////////
		// Allocate a new pointer
		//////
			font = (SFont*)iBuilder_allocateBytes(gFonts, sizeof(SFont));
			if (!font)
				return(font);

			// Initialize
			memset(font, 0, sizeof(SFont));


		//////////
		// Populate
		//////
			font->hdc						= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			font->_sizeUsedForCreateFont	= -MulDiv(tnFontSize, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			font->hfont						= CreateFont(font->_sizeUsedForCreateFont, 0, 0, 0, tnFontWeight, (tnItalics != 0), (tnUnderline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
			SelectObject(font->hdc, font->hfont);
			iDatum_duplicate(&font->name, (s8*)tcFontName, lnLength);
			font->_size						= tnFontSize;
			font->_weight					= tnFontWeight;
			font->_italics					= tnItalics;
			font->_underline				= tnUnderline;

			// Find out the text metrics
			GetTextMetricsA(font->hdc, &font->tm);


		// Indicate our success
		return(font);
	}




//////////
//
// Free the indicated font resource
//
//////
	void iFont_free(SFont* font, bool tlFreeSelf)
	{
		if (font)
		{
			//////////
			// Free components
			//////
				DeleteObject((HGDIOBJ)font->hfont);
				DeleteDC(font->hdc);


			//////////
			// Free self
			//////
				if (tlFreeSelf)
					free(font);
		}
	}




//////////
//
// A particular font occupies a certain physical amount of text relative to the rectangle it inhabits.
// In order for this font to be scaled up, the font dynamics will need to change somewhat as per the limitations
// within the font design.  As such, we have to scan upward to find the closest matching font that is equal to
// or less than the ratios indicated at the current size, yet for the desired size.
//
//////
	u32 iFont_findClosestSizeMatch(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired)
	{
		s32			lnI, lnJ, lnTextLength, lnFontBold;
		f64			lfRatioH, lfRatioV, lfRatioHThis, lfRatioVThis;
		SSize		size[200];
		RECT		lrc;
		SFont*		font;


		// Iterate from the current size upward for a maximum of 200 font point sizes, but also not more than 3x its current point size
		lnTextLength	= strlen(tcText);
		lnFontBold		= ((tnFontBold) ? FW_BOLD : FW_NORMAL);
		for (lnI = 0; lnI == 0 || (lnI < 200 && (s32)(tnFontSize + lnI) < (s32)(tnFontSize * 3) && lrc.bottom < (s32)((f32)tnHeightDesired * 1.25f) && lrc.right < (s32)((f32)tnWidthDesired * 1.25f)); lnI++)
		{
			// Grab this font
			font = iFont_create(tcFontName, tnFontSize + lnI, lnFontBold, tnFontItalic, tnFontUnderline);

			// Find out how big this font would be drawn for this text
			SetRect(&lrc, 0, 0, 0, 0);
			DrawText(font->hdc, tcText, lnTextLength, &lrc, DT_CALCRECT);
			size[lnI].fWidth	= (f32)(lrc.right - lrc.left);
			size[lnI].fHeight	= (f32)(lrc.bottom - lrc.top);
		}
		// When we get here, we have all of the fonts computed
		// size[0] contains the raw font
		// We search for size[1..N] which has the font which most closely matches its proportions for the tnWidthDesired, tnHeightDesired,
		// as per the ratio 

		// Compute the size[0]
		lfRatioH	= (f64)(size[0].fWidth)  / (f64)tnWidth;
		lfRatioV	= (f64)(size[0].fHeight) / (f64)tnHeight;

		// Search backwards to find the first one that matches
		for (lnJ = lnI - 1; lnJ > 0; lnJ--)
		{
			if ((s32)size[lnJ].fWidth <= (s32)tnWidthDesired && (s32)size[lnJ].fHeight <= (s32)tnHeightDesired)
			{
				// Calculate this item's size
				lfRatioHThis	= (f64)(size[lnJ].fWidth)  / (f64)tnWidthDesired;
				lfRatioVThis	= (f64)(size[lnJ].fHeight) / (f64)tnHeightDesired;

				// See if we've found our font
				if (lfRatioHThis <= lfRatioH && lfRatioVThis <= lfRatioV)
					return(tnFontSize + (u32)lnJ);
			}
		}
		// If we get here, we couldn't find one ... indicate failure
		return(0);
	}




//////////
//
// Called to process the mouse messages.
//
//////
	int iProcessMouseMessage(UINT m, WPARAM w, LPARAM l)
	{
		// Translate the mouse from the scaled position to its real position
		iTranslateMousePosition((POINTS*)&l);

		// If it's not in the client area, 
		if (glMouseInClientArea)
		{
			// It's in the client area

// TODO:			iProcessClientMouseEvents((POINTS*)&l);

		} else {
			// It's in the non-client area
// TODO:			iProcessNonclientMouseEvents((POINTS*)&l);
		}

		return 0;
	}




//////////
//
// Called to translate the mouse position for the source window.
//
//////
	void iTranslateMousePosition(POINTS* pt)
	{
// 		POINT lpt;
// 
// 
// 		//////////
// 		// If we're a valid window, process the mouse
// 		//////
// 			if (winScreen.rc.right > winScreen.rc.left)
// 			{
// 				// Get the mouse pointer in screen coordinates
// 				if (glMoving || glResizing)
// 					GetCursorPos(&lpt);
// 
// 				// Translate our SHORT points structure to the LONG point structure
// 				lpt.x				= pt->x;
// 				lpt.y				= pt->y;
// 				gMousePosition.x	= lpt.x;
// 				gMousePosition.y	= lpt.y;
// 
// 				if (glMoving || glResizing)
// 					return;
// 
// 				// Are we inside the client area?
// 				if (PtInRect(&winScreen.rcClient, lpt))
// 				{
// 					// We are.  We are.  We are in the client area. :-)
// 					glMouseInClientArea = true;
// 
// 					// Update our caller for the translated point
// 					pt->x	= (s16)gMousePosition.x;
// 					pt->y	= (s16)gMousePosition.y;
// 
// 				} else {
// 					glMouseInClientArea = false;
// 				}
// 			}
// 			// else leave the mouse state as it is
	}




//////////
//
// EditChainManager processing
//
//////
	bool iEditChainManager_duplicate(SEditChainManager** root, SEditChainManager* ecmSource, bool tlIncludeUndoHistory)
	{
		SEditChainManager*	ecmNew;
		SEditChain*			ecSource;
		SEditChain*			ecNew;
		SEditChain*			ecLast;
		SEditChain**		ecPrev;
		SExtraInfo*			eiSource;
		SExtraInfo*			eiNew;
		SExtraInfo**		eiPrev;
		SBuilder*			xlatRoot;
		STranslate*			xlat;


		// Create the master record
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		ecmNew = (SEditChainManager*)malloc(sizeof(SEditChainManager));
		if (ecmNew)
		{
			//////////
			// Initialize
			//////
				memcpy(ecmNew, ecmSource, sizeof(SEditChainManager));


			//////////
			// Remove the connection to any undo history
			// Note:  The undo history will be copied and translated separately if need be
			//////
				ecmNew->undoHistory = NULL;
				iBuilder_createAndInitialize(&xlatRoot, -1);
				// Note:  We create the translation regardless so we can update the ecmNew-> members which relate to cursor line, highlighted, etc.


			//////////
			// Update caller
			//////
				*root = ecmNew;
				// Right now:
				//		ecmNew		-- our new SEC
				//		ecmSource	-- SEC to duplicate


			//////////
			// Indicate where we'll be updating
			//////
				ecPrev	= &ecmNew->ecFirst;
				ecLast	= NULL;


			//////////
			// Duplicate the chain
			//////
				ecSource = ecmSource->ecFirst;
				while (ecSource)
				{
					//////////
					// Create a new entry for this one
					//////
						ecNew = (SEditChain*)malloc(sizeof(SEditChain));
						if (ecNew)
						{
							// Create a translation for original pointers to new pointers
							if (tlIncludeUndoHistory)
							{
								// Create the translation for this ecSource <--> ecNew
								xlat = (STranslate*)iBuilder_allocateBytes(xlatRoot, sizeof(STranslate));
								if (xlat)
								{
									// Create the translation
									xlat->p1	= ecSource;									// The old pointer in the undoHistory will point to
									xlat->p2	= ecNew;									// the new pointer
								}
							}

						} else {
							// Should not happen.
							return(false);
						}


					//////////
					// Copy source information to new
					//////
						memcpy(ecNew, ecSource, sizeof(SEditChain));
						*ecPrev		= ecNew;												// Update the prior record to point here
						ecNew->prev	= ecLast;												// Point backward to the previous entry
						ecNew->next	= NULL;													// Currently points forward to nothing


					//////////
					// Duplicate its data
					//////
						ecNew->sourceCode = NULL;
						iDatum_duplicate(ecNew->sourceCode, ecSource->sourceCode);


					//////////
					// General purpose extra data
					//////
						if (ecSource->extra_info)
						{
							// Copy any extra_info that's relevant
							eiPrev		= &ecNew->extra_info;
							eiSource	= ecSource->extra_info;
							while (eiSource)
							{
								//////////
								// Duplicate this entry
								//////
									// Are we duplicating by a function call?  Or manually?
									if (*(u32*)&eiSource->extra_info_duplicate != 0)
									{
										// Function call
										eiNew = eiSource->extra_info_duplicate(ecmSource, ecSource, ecSource->extra_info);
										// Right now, eiNew has either been updated or not depending on the decision making process in extra_info_duplicate().

									} else {
										// Manual duplication
										eiNew = (SExtraInfo*)malloc(sizeof(SExtraInfo));
										if (eiNew)
										{
											// Copy everything
											memcpy(eiNew, eiSource, sizeof(SExtraInfo));

											// Clear, and then duplicate the info datum
											memset(&eiNew->info, 0, sizeof(eiNew->info));
											iDatum_duplicate(&eiNew->info, &eiSource->info);

										} else {
											// Should not happen
											return(false);
										}
									}


								//////////
								// Update the back-link if need be
								//////
									if (eiNew)
									{
										*eiPrev	= eiNew;
										eiPrev	= &eiNew->next;
									}


								//////////
								// Move to next extra_info
								//////
									eiSource = eiSource->next;
							}
						}


					//////////
					// Move to next entry to duplicate
					//////
						ecLast		= ecNew;
						ecPrev		= &ecNew->next;
						ecSource	= ecSource->next;
				}


			//////////
			// Translate each of the ecmSource pointers for ecmNew
			// Note:  The rest of them use uid lookups
			//////
				ecmNew->ecFirst				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecFirst);
				ecmNew->ecLast				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecLast);
				ecmNew->ecTop				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecTop);
				ecmNew->ecCursorLine		= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLine);
				ecmNew->ecCursorLineLast	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLineLast);
				ecmNew->ecSelectedLineStart	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineStart);
				ecmNew->ecSelectedLineEnd	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineEnd);


			//////////
			// Free the pointers
			//////
				iBuilder_freeAndRelease(&xlatRoot);


			//////////
			// Indicate success
			//////
				return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to free the edit chain manager content, and optionally itself
//
//////
	void iEditChainManager_free(SEditChainManager** root, bool tlFreeSelf)
	{
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		// Make sure our environment is sane
		if (root && *root)
		{
			//////////
			// Free undo history
			//////
				if ((*root)->undoHistory)
					iEditChainManager_free(&(*root)->undoHistory, true);


			//////////
			// Free content
			//////
				iEditChain_free(&(*root)->ecFirst, true);


			//////////
			// Free self
			//////
				if (tlFreeSelf)
				{
					free(*root);
					*root = NULL;
				}
		}
	}




//////////
//
// Free the edit chain
//
//////
	void iEditChain_free(SEditChain** root, bool tlFreeSelf)
	{
		SEditChain*		chain;
		SEditChain*		chainNext;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		// Make sure our environment is sane
		if (root && *root)
		{
			// Repeat throughout the entire chain
			chain = *root;
			while (chain)
			{
				//////////
				// Note next item in chain
				//////
					chainNext = chain->next;


				//////////
				// Delete any extra information associated with this chain entry
				//////
					iExtraInfo_free(NULL, chain, &chain->extra_info, true);


				//////////
				// Delete this item's components
				//////
					iDatum_free(chain->sourceCode, true);


				//////////
				// Free self
				//////
					if (tlFreeSelf)
						free(chain);


				//////////
				// Move to next item in the chain
				//////
					chain = chainNext;
			}


			//////////
			// Free self
			//////
				if (tlFreeSelf)
					*root = NULL;	// It would've been freed above, so we just update the pointer
		}
	}




//////////
//
// Added to do a simple top-down translation of the pointers from p1 to p2.
//
//////
	void* iTranslate_p1_to_p2(SBuilder* root, void* ptr)
	{
		u32				lnI, lnCount;
		STranslate*		xlat;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		//////////
		// Iterate in a top-down manner
		//////
			lnCount	= root->populatedLength / sizeof(STranslate);
			xlat	= (STranslate*)root->data;
			for (lnI = 0; lnI < lnCount; lnI++, xlat++)
			{
				// See if this translation is the translation
				if (xlat->p1 == ptr)
					return(xlat->p2);		// Yes
			}
			// If we get here, not found


		//////////
		// Indicate failure
		//////
			return(NULL);
	}

	void* iTranslate_p2_to_p1(SBuilder* root, void* ptr)
	{
		u32				lnI, lnCount;
		STranslate*		xlat;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		//////////
		// Iterate in a top-down manner
		//////
			lnCount = root->populatedLength / sizeof(STranslate);
			xlat	= (STranslate*)root->data;
			for (lnI = 0; lnI < lnCount; lnI++, xlat++)
			{
				// See if this translation is the translation
				if (xlat->p2 == ptr)
					return(xlat->p1);		// Yes
			}
			// If we get here, not found


		//////////
		// Indicate failure
		//////
			return(NULL);
	}




//////////
//
// Called to free the extra info associated with this entry
//
//////
	void iExtraInfo_free(SEditChainManager* ecm, SEditChain* ec, SExtraInfo** root, bool tlFreeSelf)
	{
		SExtraInfo*		ei;
		SExtraInfo*		eiNext;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		// Make sure our environment is sane
		if (root && *root)
		{
			// Iterate through all entries in the chain
			ei = *root;
			while (ei)
			{
				//////////
				// Note the next entry
				//////
					ei = ei->next;


				//////////
				// Free the data contained within
				// Note:  If they have an extra_info_free() function defined, we need to call it first so they can release whatever is contained within the info block
				//////
					if (*(u32*)&ei->extra_info_free != 0)
					{
						// Free anything within using the callback
						ei->extra_info_free(NULL, ec, ei);
						// At this point we anything it had inside is now free
					}

					// Now, manually free the actual info block itself
					iDatum_free(&ei->info, false);


				//////////
				// Free self if need be
				//////
					if (tlFreeSelf)
						free(ei);


				//////////
				// Move to next entry
				//////
					ei = eiNext;
			}
		}
	}




//////////
//
// Datum storage
//
//////
	SDatum* iDatum_allocate(s8* data, u32 dataLength)
	{
		SDatum* datumNew;


		// Allocate our new datum
		datumNew = (SDatum*)malloc(sizeof(SDatum));
		if (datumNew)
		{
			// Initialize
			memset(datumNew, 0, sizeof(SDatum));

			// Populate
			iDatum_duplicate(datumNew, data, dataLength);
		}

		// Indicate our status
		return(datumNew);
	}

	void iDatum_duplicate(SDatum* datum, s8* data, u32 dataLength)
	{
		// Make sure our environment is sane
		if (datum && data)
		{
			// We may need to set the length
			if (dataLength == -1)
				dataLength = strlen(data);

			// Release anything that's already there
			iiDatum_free(datum);

			// Store the new data
			datum->data = (s8*)malloc(dataLength);

			// Copy over if we were successful
			if (datum->data)
			{
				memcpy(datum->data, data, dataLength);
				datum->length = dataLength;
			}
		}
	}

	void iDatum_duplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		if (datumDst && datumSrc && datumSrc->data)
			iDatum_duplicate(datumDst, datumSrc->data, datumSrc->length);
	}

	// Returns -1, 0, or 1 (indicating left is less than, equal to, or greater than right)
	s32 iDatum_compare(SDatum* datumLeft, SDatum* datumRight)
	{
		s32 lnResult;


		// Default to invalid data
		lnResult = -2;
		if (datumLeft && datumRight)
		{
			// Do a standard compare
			lnResult = memcmp(datumLeft->data, datumRight->data, min(datumLeft->length, datumRight->length));
		}

		// Indicate our result
		return(lnResult);
	}

	void iDatum_free(SDatum* datum, bool tlFreeSelf)
	{
		if (datum)
		{
			// Delete the content
			iiDatum_free(datum);

			// Delete self if need be
			if (tlFreeSelf)
				free(datum);
		}
	}

	void iiDatum_free(SDatum* datum)
	{
		// Store the data
		if (datum->data)
		{
			free(datum->data);
			datum->data = NULL;
		}

		// Reset the length to zero
		datum->length = 0;
	}
