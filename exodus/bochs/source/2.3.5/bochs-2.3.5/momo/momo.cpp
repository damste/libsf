// momo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "momo.h"
#define MAX_LOADSTRING 100
#define BUFSIZE 32768 * 2
#define GET_X_LPARAM(lp)    ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)    ((int)(short)HIWORD(lp))
#define BX_MDA_WM_UPDATE_MOUSE_X        WM_USER + 0
#define BX_MDA_WM_UPDATE_MOUSE_Y        WM_USER + 1
#define BX_MDA_WM_UPDATE_MOUSE_BUTTONS  WM_USER + 2
#define BX_MDA_WM_UPDATE_KEY			WM_USER + 3
#define BX_MDA_WM_UPDATE_UP_DOWN		WM_USER + 4



struct BITMAP_INFO
{
    DWORD  Size;
    LONG   Width;
    LONG   Height;
    WORD   Planes;
    WORD   BitCount;
    DWORD  Compression;
    DWORD  SizeImage;
    LONG   XPelsPerMeter;
    LONG   YPelsPerMeter;
    DWORD  ClrUsed;
    DWORD  ClrImportant;
};


// Global Variables:
HINSTANCE hInst;								// current instance
HWND ghWnd;                                     // Handle to MoMo window
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HBITMAP ghbmpMomo = NULL;                       // Window bitmap
HBITMAP ghbmpGraphics = NULL;                   // Graphics view, 720 x 348 pixels for DIB
HBITMAP ghbmpText = NULL;                       // Text view, 640 x 350 pixels (8 x 14 font) for DIB
HDC ghdcMomo = NULL;                            // Device context for momo background
HDC ghdcGraphics = NULL;                        // Device Context for graphics
HDC ghdcText = NULL;                            // Device Context for text
volatile gbAlreadyProcessing = false;           // Are we already processing a screen?


// Data for the Graphics and Text DIB sections
unsigned char* ptrGraphics;                     // Pointer to the graphics bits
BITMAP_INFO biGraphics;                         // Graphics bitmap info header
unsigned char* ptrText;                         // Pointer to the text bits
BITMAP_INFO biText;                             // Text bitmap info header


// Modes for display
enum { _graphics, _text };                      // Enums for current mode
enum { _rgb, _green, _black, _white };
enum { _page1, _page2, _page3, _page4, _page5, _page6, _page7, _page8 };
int mode = _graphics;                           // Default to graphics
int display = _green;                           // Default to green on black
int page = _page1;                              // Default to page 1
unsigned char mda_32kb_buffer[32768];           // 32KB buffer for MDA display
unsigned char mda_32kb_buffer_last[32768];      // 32KB buffer for previous MDA display that was received
bool gbUpdatedBuffer = true;                    // Do we need to update the buffer?

long mda_mouse_x			= 0;                // Holds the x position of the monochrome mouse as it moves around the screen
long mda_mouse_y			= 0;                // Holds the y position of the monochrome mouse as it moves around the screen
long mda_mouse_buttons		= 0;                // Holds the mouse button state of the monochrome mouse as it moves around the screen
long mda_key				= 0;				// Holds the last keycode pressed
long mda_key_up_down		= 0;				// Holds the last state of the last keycode


// Button locations
RECT grcOne         = {   9, 403 + 348,  32, 425 + 348 };
RECT grcTwo         = {  35, 403 + 348,  58, 425 + 348 };
RECT grcThree       = {  61, 403 + 348,  84, 425 + 348 };
RECT grcFour        = {  87, 403 + 348, 110, 425 + 348 };
RECT grcFive        = { 113, 403 + 348, 136, 425 + 348 };
RECT grcSix         = { 139, 403 + 348, 162, 425 + 348 };
RECT grcSeven       = { 165, 403 + 348, 188, 425 + 348 };
RECT grcEight       = { 191, 403 + 348, 214, 425 + 348 };
RECT grcG           = { 556, 403 + 348, 579, 425 + 348 };
RECT grcT           = { 585, 403 + 348, 608, 425 + 348 };
RECT grcRgb         = { 631, 403 + 348, 654, 425 + 348 };
RECT grcGreen       = { 657, 403 + 348, 680, 425 + 348 };
RECT grcBlack       = { 683, 403 + 348, 706, 425 + 348 };
RECT grcWhite       = { 709, 403 + 348, 732, 425 + 348 };
RECT grcPower       = { 735, 403 + 348, 758, 425 + 348 };
RECT grcGraphics    = {  24,  19, 720, 348 };
RECT grcText        = {  64,  19, 672, 348 };



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void                UpdateBuffer(void);
void                SetColors(RGBTRIPLE* fore, RGBTRIPLE* back);
void                DrawGraphics(RGBTRIPLE* fore, RGBTRIPLE* back);
void                DrawText(RGBTRIPLE* fore, RGBTRIPLE* back);
DWORD               pipe_server(LPVOID lpvParam);
void                InstanceThread(LPVOID lpvParam);




int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
    HANDLE hThread; 
    DWORD dwThreadId;


   
    // Initialize the buffer
    memset(&mda_32kb_buffer[0], 0, sizeof(mda_32kb_buffer));
    FILE* lfh = fopen("\\exodus\\bochs\\source\\2.3.5\\bochs-2.3.5\\momo\\mono.dmp", "rb+");
    int numread = (int)fread(&mda_32kb_buffer[0], 1, 32768, lfh);
    fclose(lfh);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MOMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MOMO);

    // Activate the pipe server
    hThread = CreateThread( NULL,               // no security attribute 
                            0,                  // default stack size 
                            (LPTHREAD_START_ROUTINE) pipe_server, 
                            0,                  // thread parameter 
                            0,                  // not suspended 
                            &dwThreadId);       // returns thread ID 


	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MOMO);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    unsigned long x, y;
    RGBTRIPLE* rgbt;
    RECT lrc;

    hInst = hInstance; // Store instance handle in our global variable
    SetRect(&lrc, 0, 0, 768, 431 + 348);
    AdjustWindowRect(&lrc, WS_OVERLAPPEDWINDOW, false);
    ghWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 0, 0, lrc.right - lrc.left, lrc.bottom - lrc.top, NULL, NULL, hInstance, NULL);
    if (!ghWnd)
    {
        return FALSE;
    }


    // Create device contexts
    ghdcMomo        = CreateCompatibleDC(GetDC(GetDesktopWindow()));
    ghdcGraphics    = CreateCompatibleDC(GetDC(GetDesktopWindow()));
    ghdcText        = CreateCompatibleDC(GetDC(GetDesktopWindow()));

    // Load and create graphics

    // Do graphics
    biGraphics.Size             = sizeof(BITMAP_INFO);
    biGraphics.Width            = 720;
    biGraphics.Height           = 348 * 2;
    biGraphics.Planes           = 1;
    biGraphics.BitCount         = 24;
    biGraphics.Compression      = 0;
    biGraphics.SizeImage        = 720 * (348 * 2) * 3;
    biGraphics.XPelsPerMeter    = 3270;
    biGraphics.YPelsPerMeter    = 3270;
    biGraphics.ClrUsed          = 0;
    biGraphics.ClrImportant     = 0;

    // Do text
    biText.Size             = sizeof(BITMAP_INFO);
    biText.Width            = 640;
    biText.Height           = 350;
    biText.Planes           = 1;
    biText.BitCount         = 24;
    biText.Compression      = 0;
    biText.SizeImage        = 640 * 350 * 3;
    biText.XPelsPerMeter    = 3270;
    biText.YPelsPerMeter    = 3270;
    biText.ClrUsed          = 0;
    biText.ClrImportant     = 0;

    // Physically create bitmaps
    ghbmpMomo       = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOMO), IMAGE_BITMAP, 768, 431+348, 0);
    ghbmpGraphics   = CreateDIBSection(ghdcGraphics, (BITMAPINFO*)&biGraphics,  DIB_RGB_COLORS, (void**)&ptrGraphics, 0, 0);
    ghbmpText       = CreateDIBSection(ghdcText,     (BITMAPINFO*)&biText,      DIB_RGB_COLORS, (void**)&ptrText, 0, 0);

    // Update device contexts
    SelectObject(ghdcMomo, ghbmpMomo);
    SelectObject(ghdcGraphics, ghbmpGraphics);
    SelectObject(ghdcText, ghbmpText);

    // Set DIB sections to black stuff
    rgbt = (RGBTRIPLE*)ptrGraphics;
    for (y = 0; y < 348*2; y++)
    {
        for (x = 0; x < 720; x++)
        {
            rgbt->rgbtRed   = 0;
            rgbt->rgbtGreen = 0;
            rgbt->rgbtBlue  = 0;
            ++rgbt;
        }
    }


    rgbt = (RGBTRIPLE*)ptrText;
    for (y = 0; y < 350; y++)
    {
        for (x = 0; x < 640; x++)
        {
            rgbt->rgbtRed   = 0;
            rgbt->rgbtGreen = 0;
            rgbt->rgbtBlue  = 0;
            ++rgbt;
        }
    }

    // Update the screen
    UpdateBuffer();


    // Update the window display
    ShowWindow(ghWnd, nCmdShow);
    UpdateWindow(ghWnd);
    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
    POINT pt;
    long mouse_x;
    long mouse_y;


	switch (message) 
	{
//         case WM_CREATE:
//             SetTimer(hWnd, 1, 100, 0);
//             break;
// 
//         case WM_TIMER:
//             if (gbUpdatedBuffer)
//             {
//                 gbUpdatedBuffer = false;
//                 UpdateBuffer();
//                 InvalidateRect(hWnd, 0, false);
//             }
//             break;
// 
        case BX_MDA_WM_UPDATE_MOUSE_X:
            return mda_mouse_x;

        case BX_MDA_WM_UPDATE_MOUSE_Y:
            return mda_mouse_y;

        case BX_MDA_WM_UPDATE_MOUSE_BUTTONS:
            return mda_mouse_buttons;

		case BX_MDA_WM_UPDATE_KEY:
			return mda_key;

		case BX_MDA_WM_UPDATE_UP_DOWN:
			return mda_key_up_down;

	    case WM_PAINT:
		    hdc = BeginPaint(hWnd, &ps);
            // Draw the image, updated in UpdateBuffer()
            if (mode == _graphics)
                BitBlt(ghdcMomo, 24, 19, 720, 348*2, ghdcGraphics, 0, 0, SRCCOPY);
            else
            {
                BitBlt(ghdcMomo, 24, 19, 720, 348*2, ghdcGraphics, 0, 0, BLACKNESS);
                BitBlt(ghdcMomo, 64, 19, 640, 348, ghdcText, 0, 0, SRCCOPY);
            }
                
            // Draw the thing
		    BitBlt(hdc, 0,  0, 768, 431 + 348, ghdcMomo, 0, 0, SRCCOPY);

		    EndPaint(hWnd, &ps);
		    break;

	    case WM_DESTROY:
		    PostQuitMessage(0);
		    break;

		case WM_KEYDOWN:
			break;

        case WM_LBUTTONDOWN:
            pt.x = ((int)(short)LOWORD(lParam));
            pt.y = ((int)(short)HIWORD(lParam));
            if (PtInRect(&grcOne, pt))
            {
                page = _page1;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcTwo, pt))
            {
                page = _page2;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcThree, pt))
            {
                page = _page3;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcFour, pt))
            {
                page = _page4;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcFive, pt))
            {
                page = _page5;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcSix, pt))
            {
                page = _page6;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcSeven, pt))
            {
                page = _page7;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcEight, pt))
            {
                page = _page8;
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcG, pt))
            {
                mode = _graphics;
                UpdateBuffer();
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcT, pt))
            {
                mode = _text;
                UpdateBuffer();
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcRgb, pt))
            {
                display = _rgb;
                UpdateBuffer();
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcGreen, pt))
            {
                display = _green;
                UpdateBuffer();
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcBlack, pt))
            {
                display = _black;
                UpdateBuffer();
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcWhite, pt))
            {
                display = _white;
                UpdateBuffer();
                InvalidateRect(hWnd, 0, false);
            }
            else if (PtInRect(&grcPower, pt))
            {
                PostQuitMessage(0);
            }
            break;

        case WM_MOUSEMOVE:
            mouse_x             = GET_X_LPARAM(lParam);
            mouse_y             = GET_Y_LPARAM(lParam);
            mda_mouse_buttons   = ((wParam & MK_LBUTTON) != 0 ? 1 : 0) +
                                  ((wParam & MK_RBUTTON) != 0 ? 2 : 0);
            if (mode == _graphics)
            {
                // Graphics mode
                mda_mouse_x = mouse_x - 24;     // Adjust for offset into the visible MoMo screen
                mda_mouse_y = mouse_y - 19;     // Adjust for offset into the visible MoMo screen
                mda_mouse_y /= 2;               // Screen height is doubled in MoMo, reduce mouse position by half
            }
            else
            {
                // Text mode
                mda_mouse_x = mouse_x - 64;     // Adjust for offset into the visible MoMo screen
                mda_mouse_x /= 8;               // Each pixel is 8 x 14, reduce its position by 8 pixels
                mda_mouse_y = mouse_y - 19;     // Adjust for offset into the visible MoMo screen
                mda_mouse_y /= 14;              // Each pixel is 8 x 14, reduce its position by 14 pixels
            }

            // Adjust for zero problems
            if (mda_mouse_x < 0)
                mda_mouse_x = 0;

            if (mda_mouse_y < 0)
                mda_mouse_y = 0;
            break;

	    default:
		    return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void UpdateBuffer(void)
{
    RGBTRIPLE fore;
    RGBTRIPLE back;

    if (!gbAlreadyProcessing)
    {
        gbAlreadyProcessing = true;

        // Set colors
        SetColors(&fore, &back);

        if (mode == _graphics)
        {
            DrawGraphics(&fore, &back);
        }
        else
        {
            DrawText(&fore, &back);
        }

        gbAlreadyProcessing = false;
    }
}

void SetColors(RGBTRIPLE* fore, RGBTRIPLE* back)
{
    // Set the colors
    switch (display)
    {
        case _rgb:
        case _green:
            fore->rgbtRed   = 64;
            fore->rgbtGreen = 255;
            fore->rgbtBlue  = 64;

            back->rgbtRed   = 0;
            back->rgbtGreen = 0;
            back->rgbtBlue  = 0;
            break;

        case _black:
            fore->rgbtRed   = 215;
            fore->rgbtGreen = 255;
            fore->rgbtBlue  = 215;

            back->rgbtRed   = 0;
            back->rgbtGreen = 0;
            back->rgbtBlue  = 0;
           break;

        case _white:
            fore->rgbtRed   = 0;
            fore->rgbtGreen = 0;
            fore->rgbtBlue  = 0;

            back->rgbtRed   = 255;
            back->rgbtGreen = 255;
            back->rgbtBlue  = 255;
            break;

    }
}

void DrawGraphics(RGBTRIPLE* fore, RGBTRIPLE* back)
{
    unsigned char ch, chLast, bit;
    unsigned long i, y, x, offset, offset_line;
    RGBTRIPLE* rgbt;
    RGBTRIPLE* rgbt2;


    // Do all of the scan lines in graphics mode
    offset		= 0;
    offset_line	= 0;
    for (y = 0; y < 348*2; y = y + 2)
    {
        rgbt  = (RGBTRIPLE*)(ptrGraphics + ((biGraphics.Height - y - 1) * biGraphics.Width * 3));
        rgbt2 = (RGBTRIPLE*)(ptrGraphics + ((biGraphics.Height - y - 2) * biGraphics.Width * 3));
        for (x = 0; x < 90; x++)
        {
            ch		= mda_32kb_buffer     [offset + offset_line + x];
/*
            chLast	= mda_32kb_buffer_last[offset + offset_line + x];
            if (ch == chLast)
            {
                // Nothing to do with this one, just move to next 8 pixel block
                rgbt  += 8;
                rgbt2 += 8;
            }
            else
            {
*/
                // We have to update this value
                bit = 0x80;
                for (i = 0; i < 8; i++)
                {
                    if ((ch & bit) != 0)
                    {
                        // Foreground color
                        rgbt->rgbtRed   = fore->rgbtRed;
                        rgbt->rgbtGreen = fore->rgbtGreen;
                        rgbt->rgbtBlue  = fore->rgbtBlue;

                        rgbt2->rgbtRed   = fore->rgbtRed;
                        rgbt2->rgbtGreen = fore->rgbtGreen;
                        rgbt2->rgbtBlue  = fore->rgbtBlue;
                    }
                    else
                    {
                        // Background color
                        rgbt->rgbtRed   = back->rgbtRed;
                        rgbt->rgbtGreen = back->rgbtGreen;
                        rgbt->rgbtBlue  = back->rgbtBlue;

                        rgbt2->rgbtRed   = back->rgbtRed;
                        rgbt2->rgbtGreen = back->rgbtGreen;
                        rgbt2->rgbtBlue  = back->rgbtBlue;
                    }

                    // Move the bit over
                    bit >>= 1;

                    // Move to next position
                    ++rgbt;
                    ++rgbt2;
                }
/*
            }
*/
        }

        // Move through memory banks on successive 8KB blocks
        if (offset_line == 0)
            offset_line = 0x2000;
        else if (offset_line == 0x2000)
            offset_line = 0x4000;
        else if (offset_line == 0x4000)
            offset_line = 0x6000;
        else if (offset_line == 0x6000)
        {
            offset_line = 0;
            offset      += 90;  // Move to next line in each 8KB blocks
        }
    }

    // Update the last buffer
    memcpy(&mda_32kb_buffer_last[0], &mda_32kb_buffer[0], sizeof(mda_32kb_buffer_last));
}

void DrawText(RGBTRIPLE* fore, RGBTRIPLE* back)
{
}


DWORD pipe_server(LPVOID lpvParam)
{ 
    BOOL fConnected; 
    DWORD dwThreadId; 
    HANDLE hPipe, hThread; 
    LPTSTR lpszPipename = "\\\\.\\pipe\\MoMoPipe"; 

    // The main loop creates an instance of the named pipe and 
    // then waits for a client to connect to it. When the client 
    // connects, a thread is created to handle communications 
    // with that client, and the loop is repeated. 

    for ( ; ; )
    { 
        hPipe = CreateNamedPipe(lpszPipename,             // pipe name 
                                PIPE_ACCESS_DUPLEX,       // read/write access 
                                PIPE_TYPE_MESSAGE |       // message type pipe 
                                PIPE_READMODE_MESSAGE |   // message-read mode 
                                PIPE_WAIT,                // blocking mode 
                                PIPE_UNLIMITED_INSTANCES, // max. instances  
                                BUFSIZE,                  // output buffer size 
                                BUFSIZE,                  // input buffer size 
                                NMPWAIT_USE_DEFAULT_WAIT, // client time-out 
                                NULL);                    // no security attribute 

        if (hPipe == INVALID_HANDLE_VALUE) 
            _asm int 3; // MyErrExit("CreatePipe"); 

        // Wait for the client to connect; if it succeeds, 
        // the function returns a nonzero value. If the function returns 
        // zero, GetLastError returns ERROR_PIPE_CONNECTED. 

        fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
        if (fConnected) 
        { 
            // Create a thread for this client. 
            hThread = CreateThread( NULL,              // no security attribute 
                                    0,                 // default stack size 
                                    (LPTHREAD_START_ROUTINE) InstanceThread, 
                                    (LPVOID) hPipe,    // thread parameter 
                                    0,                 // not suspended 
                                    &dwThreadId);      // returns thread ID 

            if (hThread == NULL) 
                _asm int 3; // MyErrExit("CreateThread"); 
            else
                CloseHandle(hThread); 

        } 
        else 
            // The client could not connect, so close the pipe. 
            CloseHandle(hPipe); 
    } 
    return 1; 
} 

void InstanceThread(LPVOID lpvParam) 
{ 
    CHAR chRequest[BUFSIZE]; 
    CHAR chReply[BUFSIZE]; 
    DWORD cbBytesRead, cbReplyBytes, cbWritten;
    BOOL fSuccess; 
    HANDLE hPipe; 

    // The thread's parameter is a handle to a pipe instance. 
    hPipe = (HANDLE)lpvParam; 

    while (1) 
    { 
        // Read client requests from the pipe. 
        fSuccess = ReadFile(hPipe,        // handle to pipe 
                            chRequest,    // buffer to receive data 
                            BUFSIZE,      // size of buffer 
                            &cbBytesRead, // number of bytes read 
                            NULL);        // not overlapped I/O 

        if (! fSuccess || cbBytesRead == 0) 
            break; 

        // Update our display buffer
        memcpy(mda_32kb_buffer, chRequest, max(cbBytesRead, 32768));
        UpdateBuffer();
        InvalidateRect(ghWnd, 0, false);

//         // GetAnswerToRequest(chRequest, chReply, &cbReplyBytes);
        *((long*)&chReply[00]) = mda_mouse_x;
        *((long*)&chReply[04]) = mda_mouse_y;
        *((long*)&chReply[ 8]) = mda_mouse_buttons;
		*((long*)&chReply[12]) = mda_key;
		*((long*)&chReply[16]) = mda_key_up_down;
        cbReplyBytes = 20;

        // Write the reply to the pipe. 
        fSuccess = WriteFile( hPipe,        // handle to pipe 
                              chReply,      // buffer to write from 
                              cbReplyBytes, // number of bytes to write 
                              &cbWritten,   // number of bytes written 
                              NULL);        // not overlapped I/O 

        if (! fSuccess || cbReplyBytes != cbWritten)
            break;
    } 

    // Flush the pipe to allow the client to read the pipe's contents 
    // before disconnecting. Then disconnect the pipe, and close the 
    // handle to this pipe instance. 

    FlushFileBuffers(hPipe); 
    DisconnectNamedPipe(hPipe); 
    CloseHandle(hPipe); 
}
