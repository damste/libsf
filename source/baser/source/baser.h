//////////
//
// /libsf/source/baser/source/baser1.cpp
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
//     Aug.31.2016
//////
// Change log:
//     Aug.31.2016 - Initial creation
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




//////////
// Global variables
//////
	bool			glBaser_isRunning							= false;
	s32				gnWidth										= 800;
	s32				gnHeight									= 600;

	// Bitmaps
	SBitmap*		bmp512b										= NULL;
	SBitmap*		bmp1Kb										= NULL;
	SBitmap*		bmpF12Throttle								= NULL;

	SBitmap*		bmp512bOver									= NULL;
	SBitmap*		bmp1KbOver									= NULL;
	SBitmap*		bmpF12ThrottleOver							= NULL;




//////////
// Render colors
//////
	SBgra			titleColor									= { rgba(0, 92, 192, 255) };		// Dark blue
	SBgra			orangeLowColor								= { rgba(255,225,172,255) };		// Orange-ish
	SBgra			orangeHighColor								= { rgba(255,244,224,255) };
	SBgra			cyanLowColor								= { rgba(216,255,255,255) };		// Cyan-ish
	SBgra			cyanHighColor								= { rgba(237,255,255,255) };
	SBgra			greenLowColor								= { rgba(192,255,192,255) };		// Green-ish
	SBgra			greenHighColor								= { rgba(235,255,235,255) };
	SBgra			purpleLowColor								= { rgba(231,204,255,255) };		// Purple-ish
	SBgra			purpleHighColor								= { rgba(245,235,255,255) };
	SBgra			pinkLowColor								= { rgba(255,191,255,255) };		// Pinkish
	SBgra			pinkHighColor								= { rgba(255,235,255,255) };
	SBgra			disabledLowColor							= { rgba(235,235,235,255) };		// Grayish
	SBgra			disabledHighColor							= { rgba(250,250,250,255) };
	SBgra			invalidLowColor								= { rgba(255,235,235,255) };		// Reddish
	SBgra			invalidHighColor							= { rgba(255,245,245,255) };
	SBgra			memoryFillColor								= { rgba(242,247,255,255) };		// Blue-ish
	SBgra			memoryBorderColor							= { rgba(217,232,235,255) };		// Darker blue-ish
	SBgra			memoryOptionColor							= { rgba(64,140,255,255) };			// Darkest blue-ish
	SBgra			memoryOptionHighlightColor					= { rgba(255,192,128,255) };		// Striking orangish
	SBgra			registerColor								= { rgba(245,235,255,255) };		// Purple-ish
	SBgra			textColor									= { rgba(255,255,255,255) };		// White
	SBgra			redGrayColor								= { rgba(235,205,205,255) };




//////////
// Fonts in use
//////
	u8				cgcUbuntu[]									= "Ubuntu";
	u8				cgcUbuntuMono[]								= "Ubuntu Mono";
	SFont*			fontUbuntuMono8								= NULL;
	SFont*			fontUbuntuMono10							= NULL;
	SFont*			fontUbuntu14								= NULL;


//////////
// Callback messages
//////
	u32				_WMBASER_CONTENT_IS_READY					= WM_USER + 0;




//////////
// Forward declarations
//////
	// Public declarations (see baser.def)
	int						baser_load							(s8 tcFilename);
	int						baser_release						(int tnHandle);
	int						baser_populate_row					(int tnHandle,              int tnOffset, int tnBase, s8* tcBufferOut, int tnBufferOut_length);
	int						baser_parse_block_by_struct			(int tnHandle, HWND tnHwnd, int tnOffset, cs8* cStruct, int nStructLength);
	int						baser_retrieve_data					(int nId, s8* cDataOut, int tnDataLength);

	// Internal declarations
	bool					iBaser_launch						(s8* tcImageName);
	void					iiBaser_initialize					(void);
	void					iiBaser_populateStaticImages		(void);
	void					iiBaser_colorizeAndText				(SBitmap* bmp, s8* tcText, SBgra fillColor, SBgra textColor, SFont* font);
	void					iiBaser_render						(void);
	void					iiBaser_renderMemory				(void);

	DWORD WINAPI			iBaser_threadProc					(LPVOID lpParameter);
	LRESULT CALLBACK		iBaser_wndProc						(HWND h, UINT m, WPARAM w, LPARAM l);




//////////
//
// Top level for Baser
//
//////
	bool iBaser_launch(s8* tcImageName)
	{
		u32			lnSize, lnNumread;
		FILE*		lfh;
		SBuilder*	builder;
		s8			buffer[_MAX_PATH * 2];


		//////////
		// Initialize our bitmaps
		//////
			iiBaser_initialize();


		//////////
		// Load the binary image
		//////
			builder = NULL;
			if (!iBuilder_asciiReadFromFile(&builder, (u8*)tcImageName))
			{
				sprintf(buffer, "Unable to load:\n\n%s", tcImageName);
				MessageBox(NULL, buffer, "Failure Loading", MB_OK);
				return(false);
			}


		///////////
		// Spawn our permanent debugger thread
		//////
			CreateThread(NULL, 0, &iBaser_threadProc, 0, 0, 0);
	}




//////////
//
// Initialize baser
//
//////
	void iiBaser_initialize(void)
	{

		//////////
		// Window size
		//////
			gnWidth		= 800;
			gnHeight	= 600;


		//////////
		// Create the base fonts
		//////
			iBuilder_createAndInitialize(&gFonts, -1);
			fontUbuntuMono8		= iFont_create(cgcUbuntuMono,	8,	FW_NORMAL, 0, 0);
			fontUbuntuMono10	= iFont_create(cgcUbuntuMono,	10,	FW_NORMAL, 0, 0);
			fontUbuntu14		= iFont_create(cgcUbuntu,		14,	FW_NORMAL, 0, 0);


		//////////
		// Populate the static images
		//////
			iiBaser_populateStaticImages();

	}




//////////
//
// Populates standard images
//
//////
	void iiBaser_populateStaticImages(void)
	{
		//////////
		// Normal display
		//////
			iiBaser_colorizeAndText(bmp512b,			"512b",				memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiBaser_colorizeAndText(bmp1Kb,				"1Kb",				memoryOptionColor,				whiteColor,			fontUbuntuMono8);
// 			iiBaser_colorizeAndText(bmpF12Throttle,		"F12:Throttle",		stage4HighColor,				blackColor,			fontUbuntuMono8);

			// Render a small border around the keystrokes
			iBmp_frameRect(bmp512b,			&bmp512b->rc,			stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
			iBmp_frameRect(bmp1Kb,			&bmp1Kb->rc,			stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
// 			iBmp_frameRect(bmpF12Throttle,	&bmpF12Throttle->rc,	stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
		
		
		//////////
		// Mouse is over
		//////
			iiBaser_colorizeAndText(bmp512bOver,		"512b",				memoryOptionHighlightColor,		whiteColor,			fontUbuntuMono8);
			iiBaser_colorizeAndText(bmp1KbOver,			"1Kb",				memoryOptionHighlightColor,		whiteColor,			fontUbuntuMono8);
// 			iiBaser_colorizeAndText(bmpF12ThrottleOver,	"F12:Throttle",		memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
	}




//////////
//
// Fills the background, and draws the text centered
//
//////
	void iiBaser_colorizeAndText(SBitmap* bmp, s8* tcText, SBgra fillColor, SBgra textColor, SFont* font)
	{
		
		//////////
		// Fill background
		//////
			iBmp_fillRect(bmp, &bmp->rc, fillColor, fillColor, fillColor, fillColor, false, NULL, false);


		//////////
		// Center text
		//////
			SelectObject(bmp->hdc, font->hfont);
			SetBkMode(bmp->hdc, TRANSPARENT);
			SetTextColor(bmp->hdc, RGB(textColor.red, textColor.grn, textColor.blu));
			DrawText(bmp->hdc, tcText, strlen(tcText), &bmp->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
	}




//////////
//
// Called to render the Debo1 window.
// Note:  Renders into the bmpDebo1->hdc bitmap for later copying with BitBlt().
// Note:  The file debo-1.png was used as a template for this construction.
//
//////
	void iiBaser_render(void)
	{
		RECT lrc;


		//////////
		// Render the sub-components
		//////
			iiBaser_renderStage1();


		//////////
		// The main window has a white background, and then each component is rendered atop
		//////
			FillRect(bmpDebo1->hdc, &bmpDebo1->rc, (HBRUSH)GetStockObject(WHITE_BRUSH));


		//////////
		// Title
		//////
			CopyRect(&lrc, &bmpDebo1->rc);
			--lrc.top;
			lrc.left += 8;
			SelectObject(bmpDebo1->hdc, fontUbuntu14->hfont);
			SetBkMode(bmpDebo1->hdc, TRANSPARENT);
			SetTextColor(bmpDebo1->hdc, RGB(titleColor.red, titleColor.grn, titleColor.blu));
			DrawText(bmpDebo1->hdc, cgcAppTitle, strlen(cgcAppTitle), &lrc, DT_LEFT);


		//////////
		//  Pipeline stages
		//////
			BitBlt(bmpDebo1->hdc, 5, 28,	bmpStage1->bi.biWidth, bmpStage1->bi.biHeight, bmpStage1->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 78, 28,	bmpStage2->bi.biWidth, bmpStage2->bi.biHeight, bmpStage2->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 178, 28,	bmpStage3->bi.biWidth, bmpStage3->bi.biHeight, bmpStage3->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 278, 9,	bmpStage4->bi.biWidth, bmpStage4->bi.biHeight, bmpStage4->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 528, 28,	bmpStage5->bi.biWidth, bmpStage5->bi.biHeight, bmpStage5->hdc, 0, 0, SRCCOPY);


		//////////
		// Registers
		//////
			BitBlt(bmpDebo1->hdc, 618, 2,	bmpRegisters->bi.biWidth, bmpRegisters->bi.biHeight, bmpRegisters->hdc, 0, 0, SRCCOPY);


		//////////
		// Disassembly
		//////
			BitBlt(bmpDebo1->hdc, 618, 173,	bmpDisassembly->bi.biWidth, bmpDisassembly->bi.biHeight, bmpDisassembly->hdc, 0, 0, SRCCOPY);


		//////////
		// Memory
		//////
			BitBlt(bmpDebo1->hdc, 0, 154,	bmpMemory->bi.biWidth, bmpMemory->bi.biHeight, bmpMemory->hdc, 0, 0, SRCCOPY);
	}




//////////
//
// Generic pipeline render background
//
//////
	void iiBaser_renderStageBackground(SBitmap* bmp, RECT* rc, SBgra textColor, SBgra lowColor, SBgra highColor, cs8* tcTextTop, cs8* tcTextBottom)
	{
		RECT lrcTop, lrcBot, lrcIn;


		//////////
		// Background
		//////
			SetRect(&lrcIn,		rc->left + 3,	rc->top + 16,	rc->right - 3,	rc->bottom - 16);
			iBmp_fillRect(bmp, rc,		lowColor,	lowColor,	lowColor,	lowColor,	false, &lrcIn,	true);
			iBmp_fillRect(bmp, &lrcIn,	highColor,	highColor,	highColor,	highColor,	false, NULL,	false);


		//////////
		// Text
		//////
			if (tcTextTop)
			{
				// Upper 16-pixel block
				SetRect(&lrcTop, rc->left, rc->top, rc->right, rc->top + 16);
				SelectObject(bmp->hdc, fontUbuntuMono8->hfont);
				SetBkMode(bmp->hdc, TRANSPARENT);
				SetTextColor(bmp->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
				DrawText(bmp->hdc, tcTextTop, strlen(tcTextTop), &lrcTop, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			if (tcTextBottom)
			{
				// Lower 16-pixel block
				SetRect(&lrcBot, rc->left, rc->bottom - 16, rc->right, rc->bottom);
				SelectObject(bmp->hdc, fontUbuntuMono8->hfont);
				SetBkMode(bmp->hdc, TRANSPARENT);
				SetTextColor(bmp->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
				DrawText(bmp->hdc, tcTextBottom, strlen(tcTextBottom), &lrcBot, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
	}




//////////
//
// Draws the indicated buffer of text centered vertically and left-aligned
//
//////
	void iiBaser_renderTextCentered(SBitmap* bmp, s8* tcText, RECT* rc, bool tlCenterHorizontally)
	{
		s32		lnI, lnILast, lnLength, lnPass, lnTotalHeight, lnMaxWidth, lnFontHeight;
		RECT	lrc, lrcSize;


		// Iterate 
		lnLength = strlen(tcText);
		for (lnPass = 0; lnPass < 2; lnPass++)
		{
			if (lnPass == 0)
			{
				// First pass we're computing
				for (lnI = 0, lnILast = 0, lnTotalHeight = 0, lnMaxWidth = 0, lnFontHeight = 0; lnI < lnLength; lnI++)
				{
					if (tcText[lnI] == '\n' || tcText[lnI + 1] == 0)
					{
						// We've reached the end of the line (so to speak)
						DrawText(bmp->hdc, tcText + lnILast, lnI - lnILast + ((tcText[lnI + 1] == 0) ? 1 : 0), &lrcSize, DT_CALCRECT);

						// Increase the height
						lnTotalHeight	+= (lrcSize.bottom - lrcSize.top);
						lnFontHeight	= max((lrcSize.bottom - lrcSize.top), lnFontHeight);

						// Set the max width
						lnMaxWidth = max(lnMaxWidth, (lrcSize.right - lrcSize.left));

						// Indicate the last part
						lnILast = lnI + 1;
					}
				}

			} else {
				// Establish our rectangle
				SetRect(&lrc,	((tlCenterHorizontally) ? 0 : ((rc->right - rc->left - lnMaxWidth) / 2)),
								((rc->bottom - rc->top - lnTotalHeight) / 2),
								rc->right, rc->bottom);

				// Second pass we're drawing
				for (lnI = 0, lnILast = 0; lnI < lnLength; lnI++)
				{
					if (tcText[lnI] == '\n' || tcText[lnI + 1] == 0)
					{
						// Draw it
						DrawText(bmp->hdc, tcText + lnILast, lnI - lnILast + ((tcText[lnI + 1] == 0) ? 1 : 0), &lrc, DT_LEFT | ((tlCenterHorizontally) ? DT_CENTER : 0));

						// Move down for the next go
						lrc.top += lnFontHeight;

						// Indicate the last part
						lnILast = lnI + 1;
					}
				}
			}
		}
	}




//////////
//
// The Oppie-1 memory block is one of two banks, either showing the first
// 1KB of its 2KB RAM, or the second.
//
//////
	void iiBaser_renderMemory(void)
	{
		s32		lnI, lnJ, lnOffset;
		RECT	lrc, lrcAddress, lrcDelta;
		s8		buffer[256];


		//////////
		// Fill the background
		//////
			SetRect(&lrc, 35, 23, bmpMemory->bi.biWidth - 1, bmpMemory->bi.biHeight - 1);
			iBmp_fillRect(bmpMemory, &bmpMemory->rc, memoryBorderColor, memoryBorderColor, memoryBorderColor, memoryBorderColor, false, &lrc, true);
			iBmp_fillRect(bmpMemory, &lrc, memoryFillColor, memoryFillColor, memoryFillColor, memoryFillColor, false, NULL, false);
			SetRect(&lrc, 0, 23, 35, bmpMemory->bi.biHeight - 1);
			iBmp_fillRect(bmpMemory, &lrc, memoryOptionColor, memoryOptionColor, memoryOptionColor, memoryOptionColor, false, NULL, false);


		//////////
		// Options
		//////
			if (gnMemoryPage == 0)
			{
				// 1 KB page
				BitBlt(bmpMemory->hdc, 36,	0, bmp1KbOver->bi.biWidth - 1,	bmp1KbOver->bi.biHeight - 1,	bmp1KbOver->hdc,	0, 0, SRCCOPY);
				BitBlt(bmpMemory->hdc, 111,	0, bmp2Kb->bi.biWidth - 1,		bmp2Kb->bi.biHeight - 1,		bmp2Kb->hdc,		0, 0, SRCCOPY);

			} else {
				// 2 KB page
				BitBlt(bmpMemory->hdc, 36,	0, bmp1Kb->bi.biWidth - 1,		bmp1Kb->bi.biHeight - 1,		bmp1Kb->hdc,		0, 0, SRCCOPY);
				BitBlt(bmpMemory->hdc, 111,	0, bmp2KbOver->bi.biWidth - 1,	bmp2KbOver->bi.biHeight - 1,	bmp2KbOver->hdc,	0, 0, SRCCOPY);
			}

			BitBlt(bmpMemory->hdc, 357, 0, bmp8BitsOver->bi.biWidth - 1, bmp8BitsOver->bi.biHeight - 1, bmp8BitsOver->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpMemory->hdc, 422, 0, bmp16Bits->bi.biWidth - 1, bmp16Bits->bi.biHeight - 1, bmp16Bits->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpMemory->hdc, 488, 0, bmp32Bits->bi.biWidth - 1, bmp32Bits->bi.biHeight - 1, bmp32Bits->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpMemory->hdc, 552, 0, bmp64Bits->bi.biWidth - 1, bmp64Bits->bi.biHeight - 1, bmp64Bits->hdc, 0, 0, SRCCOPY);


		//////////
		// Memory page
		//////
			sprintf(buffer, "000:\0");
			CopyRect(&lrcAddress, &lrc);
			SetRect(&lrc, 40, 25, bmpMemory->bi.biWidth - 1, bmpMemory->bi.biHeight - 1);
			SetBkMode(bmpMemory->hdc, TRANSPARENT);
			SelectObject(bmpMemory->hdc, fontUbuntuMono8->hfont);
			DrawText(bmpMemory->hdc, buffer, strlen(buffer), &lrcDelta, DT_CALCRECT);
			lrcDelta.bottom -= 2;
			for (lnI = gnMemoryPage * 1024; lnI < (gnMemoryPage + 1) * 1024; lnI += 32)
			{
				//////////
				// Display the address
				//////
					sprintf(buffer, " %03x:\0", lnI);
					SetTextColor(bmpMemory->hdc, RGB(whiteColor.red, whiteColor.grn, whiteColor.blu));
					DrawText(bmpMemory->hdc, buffer, strlen(buffer), &lrcAddress, DT_LEFT);


				//////////
				// Contents
				//////
					// Build the line
					memset(buffer, 32, 32 * 3);
					for (lnOffset = 0, lnJ = lnI, buffer[0] = 0; lnOffset < 32; lnOffset++)
						sprintf(buffer + (lnOffset * 3), "%02x \0", ram[lnJ + lnOffset]);

					// Draw the line
					SetTextColor(bmpMemory->hdc, RGB(blackColor.red, blackColor.grn, blackColor.blu));
					DrawText(bmpMemory->hdc, buffer, 32 * 3, &lrc, DT_LEFT | DT_SINGLELINE);


				//////////
				// If any of the addresses are in this range, highlight them
				//////
					if (state.pipeStage >= _STAGE1)		iiBaser_renderMemory_highlightMemory(lnI, lnI + 32, pipe1.ip, bmpMemory, &lrc, stage1LowColor, 3);
					if (state.pipeStage >= _STAGE2)		iiBaser_renderMemory_highlightMemory(lnI, lnI + 32, pipe2.ip, bmpMemory, &lrc, stage2LowColor, ((pipe2.p2_increment2) ? 2 : 1));
					if (state.pipeStage >= _STAGE3)		iiBaser_renderMemory_highlightMemory(lnI, lnI + 32, pipe3.ip, bmpMemory, &lrc, stage3LowColor, ((pipe3.p2_increment2) ? 2 : 1));
					if (state.pipeStage >= _STAGE4)		iiBaser_renderMemory_highlightMemory(lnI, lnI + 32, pipe4.ip, bmpMemory, &lrc, stage4LowColor, ((pipe4.p2_increment2) ? 2 : 1));
					if (state.pipeStage >= _STAGE5)		iiBaser_renderMemory_highlightMemory(lnI, lnI + 32, pipe5.ip, bmpMemory, &lrc, stage5LowColor, ((pipe5.p2_increment2) ? 2 : 1));


				//////////
				// Move down
				//////
					lrcAddress.top	+= (lrcDelta.bottom - lrcDelta.top);
					lrc.top			+= (lrcDelta.bottom - lrcDelta.top);
			}
	}




//////////
//
// Called to highlight a portion of memory as it is processing
//
//////
	void iiBaser_renderMemory_highlightMemory(s32 start, s32 end, s32 address, SBitmap* bmp, RECT* rc, SBgra color, s32 tnBytes)
	{
		s32		lnI, lnCharWidth, lnCharHeight;
		RECT	lrc;
		s8		buffer[16];


		//////////
		// Initialize
		//////
			buffer[0] = '0';
			DrawText(bmp->hdc, buffer, 1, &lrc, DT_CALCRECT);
			lnCharWidth		= (lrc.right - lrc.left);
			lnCharHeight	= (lrc.bottom - lrc.top);
			SetTextColor(bmp->hdc, RGB(blackColor.red, blackColor.grn, blackColor.blu));


		//////////
		// Draw each byte individually
		//////
			for (lnI = 0; lnI < tnBytes; lnI++)
			{
				// Is this byte in range?
				if (address + lnI >= start && address + lnI <= end)
				{
					// It starts in the range
					sprintf(buffer, "%02x\0", ram[address + lnI]);

					// Draw around it
					SetRect(&lrc, rc->left + ((address - start + lnI) * 3 * lnCharWidth) - lnCharWidth / 2, rc->top, rc->left + (2 * lnCharWidth) + ((address - start + lnI) * 3 * lnCharWidth) + lnCharWidth / 2, rc->top + lnCharHeight);
					iBmp_fillRect(bmp, &lrc, color, color, color, color, false, NULL, false);

					// Draw text
					SetRect(&lrc, rc->left + ((address - start + lnI) * 3 * lnCharWidth), rc->top, rc->left + (2 * lnCharWidth) + ((address - start + lnI) * 3 * lnCharWidth), rc->top + lnCharHeight);
					DrawText(bmp->hdc, buffer, 2, &lrc, DT_LEFT);
				}
			}
	}




//////////
//
// Main loop for Debo1
//
//////
	DWORD WINAPI iBaser_threadProc(LPVOID lpParameter)
	{
		WNDCLASSEX	wce;
		HWND		hwnd;
		RECT		lrc, lrcDesktop;
		MSG			msg;


		//////////
		// Create the class
		//////
			memset(&wce, 0, sizeof(wce));
			wce.cbSize				= sizeof(wce);
			wce.hInstance			= GetModuleHandle(NULL);
			wce.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			wce.lpszClassName		= cgcDebo1Class;
			wce.hCursor				= LoadCursor(NULL, IDC_ARROW);
			wce.lpfnWndProc			= &iBaser_wndProc;


		//////////
		// Register the class
		//////
			RegisterClassEx(&wce);


		//////////
		// Center the window
		//////
			GetClientRect(GetDesktopWindow(), &lrcDesktop);
			SetRect(&lrc,	max( (lrcDesktop.right  - lrcDesktop.left - gnWidth)  / 2, 0),
							max( (lrcDesktop.bottom - lrcDesktop.top  - gnHeight) / 2, 0),
								((lrcDesktop.right  - lrcDesktop.left - gnWidth)  / 2) + gnWidth,
								((lrcDesktop.bottom - lrcDesktop.top  - gnHeight) / 2) + gnHeight);

			// Adjust for the borders
			AdjustWindowRect(&lrc, WS_OVERLAPPEDWINDOW, FALSE);


		//////////
		// Create and show the window
		//////
			hwnd = CreateWindow(cgcDebo1Class, cgcDebo1Title, WS_OVERLAPPEDWINDOW, lrc.left, lrc.top, lrc.right - lrc.left, lrc.bottom - lrc.top, NULL, NULL, GetModuleHandle(NULL), NULL);
			ShowWindow(hwnd, SW_SHOW);


		//////////
		// Create a 100ms timer (10x per second)
		//////
			SetTimer(hwnd, NULL, 100, NULL);


		//////////
		// Enter main loop
		//////
			while (glOppie1_isRunning && GetMessage(&msg, hwnd, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			TerminateThread(GetCurrentThread(), 0);
			return(0);
	}




//////////
//
// Callback for processing the main debo window
//
//////
	LRESULT CALLBACK iBaser_wndProc(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		PAINTSTRUCT ps;


		switch (m)
		{
			case WM_CLOSE:
				exit(0);
				break;

			case WM_TIMER:
				// Timer fires 20x per second
				if (glDebo1_executionIsThrottled)
					glDebo1_executionIsPaused = false;

				// If we have anything to update in the debugger, signal it
				if (glDebo1_updateDisplay)
					InvalidateRect(h, NULL, FALSE);

				break;

			case WM_KEYDOWN:
				glDebo1_updateDisplay = true;
				switch (w)
				{
					case VK_ESCAPE:
						glDebo1_executionIsPaused = true;
						break;

					case VK_F5:
						// Run
						glDebo1_executionIsSingleStepping	= false;
						glDebo1_executionIsPaused			= false;
						break;

					case VK_F8:
						// Single-step
						glDebo1_executionIsSingleStepping	= true;
						glDebo1_executionIsPaused			= false;
						break;

					case VK_F12:
						// Throttle;
						glDebo1_executionIsThrottled		= true;
						glDebo1_executionIsSingleStepping	= false;
						glDebo1_executionIsPaused			= false;
						break;
				}
				break;

			case WM_LBUTTONDOWN:
				glOppie1_isRunning = false;
				break;

			case WM_PAINT:
				BeginPaint(h, &ps);
				if (glDebo1_updateDisplay)
				{
					// Lower the flag
					glDebo1_updateDisplay = false;

					// Rebuild the display
					if (!glRenderIsBusy)
					{
						glRenderIsBusy = true;
						iiBaser_render();
						glRenderIsBusy = false;
					}
				}

				// BitBlt our content from the buffer
				BitBlt(ps.hdc, 0, 0, gnWidth, gnHeight, bmpDebo1->hdc, 0, 0, SRCCOPY);

				EndPaint(h, &ps);
				return 0;
				break;
		}
		return(DefWindowProc(h, m, w, l));
	}
