// momo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "VeMo.h"
#define BUFSIZE 32768
#define MAX_LOADSTRING 100
#define GET_X_LPARAM(lp)    ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)    ((int)(short)HIWORD(lp))
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef long s32;
typedef short s16;
typedef char s8;
typedef float f32;
typedef double f64;




// For DIBs
struct BITMAP_INFO
{
    u32     Size;
    s32     Width;
    s32     Height;
    u16     Planes;
    u16     BitCount;
    u32     Compression;
    u32     SizeImage;
    s32     XPelsPerMeter;
    s32     YPelsPerMeter;
    u32     ClrUsed;
    u32     ClrImportant;
};




// Data for all of the windows VeMo is displaying, including their DIB sections
struct VEMO_SCREENS
{
    HWND            hwnd;                       // Handle to MoMo window
    HBITMAP         hbmp;                       // Window bitmap
    HDC             hdc;                        // Device context for Vemo background
    unsigned char*  ptr;                        // Pointer to the graphics bits
    BITMAP_INFO     bi;                         // Graphics bitmap info header
    long            mouse_x;                    // X-coord of mouse in window
    long            mouse_y;                    // Y-coord of mouse in window
    unsigned long   mouse_buttons;              // Button counter of mouse in window
};




// Global Variables:
HINSTANCE       hInst;							// current instance
HWND            ghWnd;                          // Handle to MoMo window
TCHAR           szTitle[MAX_LOADSTRING];		// The title bar text
TCHAR           szWindowClass[MAX_LOADSTRING];	// the main window class name
LPTSTR          lpszPipename = "\\\\.\\pipe\\VeMoPipe";
VEMO_SCREENS*   ghvs;                           // Pointer to root screen




// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
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


   	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_VEMO);


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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize         = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= 0;
	return RegisterClassEx(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    RECT lrc, lrc2;


    // Store instance handle in our global variable
    hInst = hInstance;
    SetRect(&lrc, 0, 0, 320, 200);
    AdjustWindowRect(&lrc, WS_OVERLAPPEDWINDOW, false);
    GetWindowRect(GetDesktopWindow(), &lrc2);
    ghWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                         ((lrc2.right - lrc2.left) - (lrc.right - lrc.left)) / 2,
                         ((lrc2.bottom - lrc2.top) - (lrc.bottom - lrc.top)) / 2,
                         lrc.right - lrc.left, lrc.bottom - lrc.top, NULL, NULL, hInstance, NULL);
    if (!ghWnd)
    {
        return FALSE;
    }


    // Update the window display
    ShowWindow(ghWnd, nCmdShow);
    UpdateWindow(ghWnd);
    return TRUE;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
    POINT pt;


	switch (message) 
	{
	    case WM_PAINT:
		    hdc = BeginPaint(hWnd, &ps);
		    EndPaint(hWnd, &ps);
		    break;

	    case WM_DESTROY:
		    PostQuitMessage(0);
		    break;

        case WM_LBUTTONDOWN:
            pt.x = ((int)(short)LOWORD(lParam));
            pt.y = ((int)(short)HIWORD(lParam));
            break;

        case WM_MOUSEMOVE:
//             mouse_x             = GET_X_LPARAM(lParam);
//             mouse_y             = GET_Y_LPARAM(lParam);
//             mouse_buttons       = ((wParam & MK_LBUTTON) != 0 ? 1 : 0) +
//                                   ((wParam & MK_RBUTTON) != 0 ? 2 : 0);
            break;

	    default:
		    return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




DWORD pipe_server(LPVOID lpvParam)
{ 
    BOOL fConnected; 
    DWORD dwThreadId; 
    HANDLE hPipe, hThread; 

    // The main loop creates an instance of the named pipe and 
    // then waits for a client to connect to it. When the client 
    // connects, a thread is created to handle communications 
    // with that client, and the loop is repeated. 

    for (;;) 
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

//         // GetAnswerToRequest(chRequest, chReply, &cbReplyBytes);
        cbReplyBytes = 12;

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
