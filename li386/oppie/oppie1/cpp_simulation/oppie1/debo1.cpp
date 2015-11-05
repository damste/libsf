//////////
//
// /libsf/li386/oppie/oppie1/cpp_simulation/oppie1/debo1.cpp
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
// Version 0.02
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.26.2014
//////
// Change log:
//     Nov.26.2014 - Initial creation
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
//




//////////
// Global variables
//////
	cs8				cgcDebo1Class[]								= "debo1_oppie1_debugger_window";
	cs8				cgcDebo1Title[]								= "Oppie-1 Debugger v0.02";
	cs8				cgcAppTitle[]								= "Debo1 -- Oppie-1 Debugger";
	cs8				cgcStage1Top[]								= "Stage 1";
	cs8				cgcStage1Bottom[]							= "i-fetch";
	cs8				cgcStage2Top[]								= "Stage 2";
	cs8				cgcStage2Bottom[]							= "i-decode";
	cs8				cgcStage3Top[]								= "Stage 3";
	cs8				cgcStage3Bottom[]							= "d-read";
	cs8				cgcStage4Top[]								= "Stage 4";
	cs8				cgcStage4Bottom[]							= "i-process";
	cs8				cgcStage5Top[]								= "Stage 5";
	cs8				cgcStage5Bottom[]							= "d-write";
	bool			glDebo1_executionIsPaused					= true;
	bool			glDebo1_executionIsSingleStepping			= false;
	bool			glDebo1_executionIsThrottled				= false;
	bool			glDebo1_updateDisplay						= true;
	bool			glRenderIsBusy								= false;
	s32				gnMemoryPage								= 0;			// Multiplied by 1KB to reach starting offset, displaying 1KB per page


//////////
// Render buckets
//////
	SBitmap*		bmpDebo1									= NULL;			// Entire main window
	SBitmap*		bmpStage1									= NULL;			// Stage 1 pipe, i-fetch
	SBitmap*		bmpStage2									= NULL;			// Stage 2 pipe, i-decode
	SBitmap*		bmpStage3									= NULL;			// Stage 3 pipe, d-read
	SBitmap*		bmpStage4									= NULL;			// Stage 4 pipe, i-process
	SBitmap*		bmpStage5									= NULL;			// Stage 5 pipe, d-write
	SBitmap*		bmpMemory									= NULL;			// Memory window
	SBitmap*		bmpRegisters								= NULL;			// Registers window
	SBitmap*		bmpDisassembly								= NULL;			// Disassembly window
	SBitmap*		bmp1Kb										= NULL;			// First KB memory range selection
	SBitmap*		bmp2Kb										= NULL;			// Second KB memory range selection
	SBitmap*		bmp8Bits									= NULL;			// Display memory in 8-bit values
	SBitmap*		bmp16Bits									= NULL;			// Display memory in 16-bit values
	SBitmap*		bmp32Bits									= NULL;			// Display memory in 32-bit values
	SBitmap*		bmp64Bits									= NULL;			// Display memory in 64-bit values
	SBitmap*		bmpF5Run									= NULL;			// For "F5:Run" text
	SBitmap*		bmpF8Step									= NULL;			// For "F8:Step" text
	SBitmap*		bmpF12Throttle								= NULL;			// For "F12:Throttle" text
	SBitmap*		bmp1KbOver									= NULL;			// First KB memory range selection
	SBitmap*		bmp2KbOver									= NULL;			// Second KB memory range selection
	SBitmap*		bmp8BitsOver								= NULL;			// Display memory in 8-bit values
	SBitmap*		bmp16BitsOver								= NULL;			// Display memory in 16-bit values
	SBitmap*		bmp32BitsOver								= NULL;			// Display memory in 32-bit values
	SBitmap*		bmp64BitsOver								= NULL;			// Display memory in 64-bit values
	SBitmap*		bmpF5RunOver								= NULL;			// For "F5:Run" text
	SBitmap*		bmpF8StepOver								= NULL;			// For "F8:Step" text
	SBitmap*		bmpF12ThrottleOver							= NULL;			// For "F12:Throttle" text
	SBitmap*		bmpLibSF_386_x40							= NULL;			// LibSF 386-x40


//////////
// Render colors
//////
//	#define			rgba(r,g,b,a)								(((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) <<  8) + ((b & 0xff)))
	SBgra			titleColor									= { rgba(0, 92, 192, 255) };		// Dark blue
	SBgra			stage1LowColor								= { rgba(255,225,172,255) };		// Orange-ish
	SBgra			stage1HighColor								= { rgba(255,244,224,255) };
	SBgra			stage2LowColor								= { rgba(216,255,255,255) };		// Cyan-ish
	SBgra			stage2HighColor								= { rgba(237,255,255,255) };
	SBgra			stage3LowColor								= { rgba(192,255,192,255) };		// Green-ish
	SBgra			stage3HighColor								= { rgba(235,255,235,255) };
	SBgra			stage4LowColor								= { rgba(231,204,255,255) };		// Purple-ish
	SBgra			stage4HighColor								= { rgba(245,235,255,255) };
	SBgra			stage5LowColor								= { rgba(255,191,255,255) };		// Pinkish
	SBgra			stage5HighColor								= { rgba(255,235,255,255) };
	SBgra			disabledLowColor							= { rgba(235,235,235,255) };		// Grayish
	SBgra			disabledHighColor							= { rgba(250,250,250,255) };
	SBgra			invalidLowColor								= { rgba(255,235,235,255) };		// Reddish
	SBgra			invalidHighColor							= { rgba(255,245,245,255) };
	SBgra			memoryFillColor								= { rgba(242,247,255,255) };		// Blue-ish
	SBgra			memoryBorderColor							= { rgba(217,232,235,255) };		// Darker blue-ish
	SBgra			memoryOptionColor							= { rgba(64,140,255,255) };			// Darkest blue-ish
	SBgra			memoryOptionHighlightColor					= { rgba(255,192,128,255) };		// Striking orangish
	SBgra			registerColor								= { rgba(245,235,255,255) };		// Purple-ish
	SBgra			disassemblyColor							= { rgba(255,255,255,255) };		// Off-white-ish
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
// Forward declarations
//////
	//void					iDebo1_launch						(void);
	void					iiDebo1_render						(void);
	void					iiDebo1_initialize					(void);
	void					iiDebo1_populateStaticImages		(void);
	void					iiDebo1_decodeAssembly_NLines		(SBitmap* bmp, RECT* rc, s32 ip_address, s32 disassembleLineCount, cs8* tcLabelText, SBgra lowColor, SBgra highColor, SBgra textColor);
	void					iiDebo1_colorizeAndText				(SBitmap* bmp, s8* tcText, SBgra fillColor, SBgra textColor, SFont* font);
	void					iiDebo1_renderStageBackground		(SBitmap* bmp, RECT* rc, SBgra textColor, SBgra lowColor, SBgra highColor, cs8* tcTextTop, cs8* tcTextBottom);
	void					iiDebo1_renderTextCentered			(s8* tcText, RECT* rc, bool tlCenterHorizontally);
	void					iiDebo1_renderStage1				(void);
	void					iiDebo1_renderStage2				(void);
	void					iiDebo1_renderStage3				(void);
	void					iiDebo1_renderStage4				(void);
	void					iiDebo1_renderStage5				(void);
	void					iiDebo1_renderRegisters				(void);
	void					iiDebo1_renderDisassembly			(void);
	void					iiDebo1_renderMemory				(void);
	void					iiDebo1_renderMemory_highlightMemory(s32 start, s32 end, s32 address, SBitmap* bmp, RECT* rc, SBgra color, s32 tnBytes);
	DWORD WINAPI			iDebo1_threadProc					(LPVOID lpParameter);
	LRESULT CALLBACK		iDebo1_wndProc						(HWND h, UINT m, WPARAM w, LPARAM l);


//////////
// Include our own logo bitmap
//////
	#include "bmps\bitmaps.h"
	#include "debo1_disasm.cpp"




//////////
//
// Top level for Debo1 (Oppie-1 Debugger)
//
//////
	void iDebo1_launch(s8* tcImageName)
	{
		u32		lnSize, lnNumread;
		FILE*	lfh;


		//////////
		// Initialize our bitmaps
		//////
			iiDebo1_initialize();


		//////////
		// Load the binary image
		//////
			if (tcImageName)
			{
				lfh = fopen(tcImageName, "rb+");
				if (lfh)
				{
					// See how big the file is
					fseek(lfh, 0, SEEK_END);
					lnSize = ftell(lfh);
					fseek(lfh, 0, SEEK_SET);
					if (lnSize != 2048)
					{
						// It's not a proper image
						printf("Image format is incorrect. Should be 2048 bytes (was %u bytes). Terminating.\n", lnSize);
						exit(-1);
					}

					// Load it
					lnNumread = fread(ram, 1, lnSize, lfh);
					fclose(lfh);
					if (lnNumread != lnSize)
					{
						printf("Unable to read %u bytes (read %u) from %s. Terminating.\n", lnSize, lnNumread, tcImageName);
						exit(-2);
					}

					// Success
					printf("Loaded image file %s\n", tcImageName);

				} else {
					// Indicate the fact that we just couldn't open the file due to circumstances entirely beyond our control
					printf("Unable to open %s\n. Terminating.", tcImageName);
					exit(-3);
				}
			}


		///////////
		// Spawn our permanent debugger thread
		//////
			CreateThread(NULL, 0, &iDebo1_threadProc, 0, 0, 0);
	}

	void iiDebo1_initialize(void)
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
		// Create the base bitmaps
		//////
			iBmp_createBySize(bmpDebo1				= iBmp_allocate(),			gnWidth,	gnHeight,	24);
			iBmp_createBySize(bmpStage1				= iBmp_allocate(),			67,			114,		24);
			iBmp_createBySize(bmpStage2				= iBmp_allocate(),			94,			114,		24);
			iBmp_createBySize(bmpStage3				= iBmp_allocate(),			94,			114,		24);
			iBmp_createBySize(bmpStage4				= iBmp_allocate(),			244,		133,		24);
			iBmp_createBySize(bmpStage5				= iBmp_allocate(),			83,			114,		24);
			iBmp_createBySize(bmpMemory				= iBmp_allocate(),			616,		449,		24);
			iBmp_createBySize(bmpRegisters			= iBmp_allocate(),			179,		171,		24);
			iBmp_createBySize(bmpDisassembly		= iBmp_allocate(),			181,		427,		24);
			// Mouse neutral colors
			iBmp_createBySize(bmp1Kb				= iBmp_allocate(),			74,			22,			24);
			iBmp_createBySize(bmp2Kb				= iBmp_allocate(),			74,			22,			24);
			iBmp_createBySize(bmp8Bits				= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmp16Bits				= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmp32Bits				= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmp64Bits				= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmpF5Run				= iBmp_allocate(),			50,			19,			24);
			iBmp_createBySize(bmpF8Step				= iBmp_allocate(),			54,			19,			24);
			iBmp_createBySize(bmpF12Throttle		= iBmp_allocate(),			84,			19,			24);
			// Mouse over colors
			iBmp_createBySize(bmp1KbOver			= iBmp_allocate(),			74,			22,			24);
			iBmp_createBySize(bmp2KbOver			= iBmp_allocate(),			74,			22,			24);
			iBmp_createBySize(bmp8BitsOver			= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmp16BitsOver			= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmp32BitsOver			= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmp64BitsOver			= iBmp_allocate(),			64,			22,			24);
			iBmp_createBySize(bmpF5RunOver			= iBmp_allocate(),			50,			19,			24);
			iBmp_createBySize(bmpF8StepOver			= iBmp_allocate(),			54,			19,			24);
			iBmp_createBySize(bmpF12ThrottleOver	= iBmp_allocate(),			84,			19,			24);
			// Externally rendered
			bmpLibSF_386_x40 = iBmp_rawLoad(cgc_libSF386x40Bmp);


		//////////
		// Populate the static images
		//////
			iiDebo1_populateStaticImages();
	}




//////////
//
// Populates standard images
//
//////
	void iiDebo1_populateStaticImages(void)
	{
		//////////
		// Normal display
		//////
			iiDebo1_colorizeAndText(bmp1Kb,				"1 KB",				memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp2Kb,				"2 KB",				memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp8Bits,			"8 Bits",			memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp16Bits,			"16 Bits",			memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp32Bits,			"32 Bits",			memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp64Bits,			"64 Bits",			memoryOptionColor,				whiteColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmpF5Run,			"F5:Run",			stage4HighColor,				blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmpF8Step,			"F8:Step",			stage4HighColor,				blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmpF12Throttle,		"F12:Throttle",		stage4HighColor,				blackColor,			fontUbuntuMono8);

			// Render a small border around the keystrokes
			iBmp_frameRect(bmpF5Run,		&bmpF5Run->rc,			stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
			iBmp_frameRect(bmpF8Step,		&bmpF8Step->rc,			stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
			iBmp_frameRect(bmpF12Throttle,	&bmpF12Throttle->rc,	stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
		
		
		//////////
		// Mouse is over
		//////
			iiDebo1_colorizeAndText(bmp1KbOver,			"1 KB",				memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp2KbOver,			"2 KB",				memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp8BitsOver,		"8 Bits",			memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp16BitsOver,		"16 Bits",			memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp32BitsOver,		"32 Bits",			memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmp64BitsOver,		"64 Bits",			memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmpF5RunOver,		"F5:Run",			memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmpF8StepOver,		"F8:Step",			memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
			iiDebo1_colorizeAndText(bmpF12ThrottleOver,	"F12:Throttle",		memoryOptionHighlightColor,		blackColor,			fontUbuntuMono8);
	}




//////////
//
// Called to decode three disassembly lines for the indicated IP address
//
//////
	void iiDebo1_decodeAssembly_NLines(SBitmap* bmp, RECT* rc, s32 ip_address, s32 disassembleLineCount, cs8* tcLabelText, SBgra lowColor, SBgra highColor, SBgra textColor)
	{
		s32		lnI, lnOpcodeBytes;
		RECT	lrc;
		s8		buffer[64];

		
		//////////
		// Draw the header label
		//////
			DrawText(bmp->hdc, buffer, strlen(buffer), &lrc, DT_CALCRECT);
			SetRect(&lrc, rc->left, rc->top, rc->right, rc->top + (lrc.bottom - lrc.top));
			iBmp_fillRect(bmp, &lrc, lowColor, lowColor, lowColor, lowColor, false, NULL, false);
			lrc.right -= 5;
			SetTextColor(bmp->hdc, RGB(textColor.red, textColor.grn, textColor.blu));
			DrawText(bmp->hdc, tcLabelText, strlen(tcLabelText), &lrc, DT_RIGHT);
			rc->top += (lrc.bottom - lrc.top);

		
		//////////
		// Iterate for each disassembly line
		//////
			for (lnI = 0, lnOpcodeBytes = 0; lnI < disassembleLineCount; lnI++)
			{
				// Grab the disassembly for this location
				lnOpcodeBytes += iiDebo1_decodeAssembly(buffer, ip_address + lnOpcodeBytes, true, true, ram);

				// Render it
				DrawText(bmp->hdc, buffer, strlen(buffer), &lrc, DT_CALCRECT);
				SetRect(&lrc, rc->left, rc->top, rc->right, rc->top + (lrc.bottom - lrc.top));
				iBmp_fillRect(bmp, &lrc, ((lnI == 0) ? lowColor : highColor), whiteColor, whiteColor, whiteColor, false, NULL, false);
				DrawText(bmp->hdc, buffer, strlen(buffer), &lrc, DT_LEFT);

				// Adjust for next line
				rc->top += (lrc.bottom - lrc.top);
			}
	}




//////////
//
// Fills the background, and draws the text centered
//
//////
	void iiDebo1_colorizeAndText(SBitmap* bmp, s8* tcText, SBgra fillColor, SBgra textColor, SFont* font)
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
	void iiDebo1_render(void)
	{
		RECT lrc;


		//////////
		// Render the sub-components
		//////
			iiDebo1_renderStage1();
			iiDebo1_renderStage2();
			iiDebo1_renderStage3();
			iiDebo1_renderStage4();
			iiDebo1_renderStage5();
			iiDebo1_renderRegisters();
			iiDebo1_renderDisassembly();
			iiDebo1_renderMemory();


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
	void iiDebo1_renderStageBackground(SBitmap* bmp, RECT* rc, SBgra textColor, SBgra lowColor, SBgra highColor, cs8* tcTextTop, cs8* tcTextBottom)
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
	void iiDebo1_renderTextCentered(SBitmap* bmp, s8* tcText, RECT* rc, bool tlCenterHorizontally)
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
// Pipe stage 1 is i-fetch, reads opcodes ahead in the instruction stream
//
//////
	void iiDebo1_renderStage1(void)
	{
		s8		buffer[64];
		SBgra	textColor;


		//////////
		// Standard background coloring
		//////
			if (state.pipeStage >= _STAGE1)
			{
				// Valid
				textColor = blackColor;
				iiDebo1_renderStageBackground(bmpStage1, &bmpStage1->rc, textColor, stage1LowColor, stage1HighColor, cgcStage1Top, cgcStage1Bottom);

			} else {
				// Invalid
				textColor = redGrayColor;
				iiDebo1_renderStageBackground(bmpStage1, &bmpStage1->rc, textColor, invalidLowColor, invalidHighColor, cgcStage1Top, cgcStage1Bottom);
			}


		//////////
		// Stage 1 specific content
		//////
			sprintf(buffer, "ip %03x\nip+0 %02x\nip+1 %02x\nip+2 %02x\0", pipe1.ip, pipe1.i_data1, pipe1.i_data2, pipe1.i_data3);
			SetBkMode(bmpStage1->hdc, TRANSPARENT);
			SetTextColor(bmpStage1->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
			iiDebo1_renderTextCentered(bmpStage1, buffer, &bmpStage1->rc, true);
	}




//////////
//
// Pipe stage 2 is i-decode, which interprets the opcode, determining
// if it is 1-byte or 2-byte, extracts addresses, and source and target
// registers.
//
//////
	void iiDebo1_renderStage2(void)
	{
		s8		buffer[64];
		SBgra	textColor;


		//////////
		// Standard background coloring
		//////
			if (state.pipeStage >= _STAGE2)
			{
				// Valid
				textColor = blackColor;
				iiDebo1_renderStageBackground(bmpStage2, &bmpStage2->rc, textColor, stage2LowColor, stage2HighColor, cgcStage2Top, cgcStage2Bottom);

			} else {
				// Invalid
				textColor = redGrayColor;
				iiDebo1_renderStageBackground(bmpStage2, &bmpStage2->rc, textColor, invalidLowColor, invalidHighColor, cgcStage2Top, cgcStage2Bottom);
			}


		//////////
		// Stage 2 specific content
		//////
			if (pipe2.p2_increment2)
			{
				// Two-byte opcode
				sprintf(buffer, "ip %03x\nop %02x %02x\0", pipe2.ip, pipe2.i_data1, pipe2.i_data2);

			} else {
				// One-byte opcode
				sprintf(buffer, "ip %03x\nop %02x\0", pipe2.ip, pipe2.i_data1);
			}

			if (pipe2.p3_d_read)		sprintf(buffer + strlen(buffer), "\nread [%03x]\0", pipe2.p3_d_read_address);
			else						sprintf(buffer + strlen(buffer), "\n\0");

			if (pipe2.p5_d_write)		sprintf(buffer + strlen(buffer), "\nwrite [%03x]\0", pipe2.p5_d_write_address);
			else						sprintf(buffer + strlen(buffer), "\n\0");

			// Indicate the instruction
			sprintf(buffer + strlen(buffer), "\n\0");
			iiDebo1_decodeAssembly(buffer + strlen(buffer), pipe2.ip, false, false, ram);

			// Draw
			SetBkMode(bmpStage2->hdc, TRANSPARENT);
			SetTextColor(bmpStage2->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
			iiDebo1_renderTextCentered(bmpStage2, buffer, &bmpStage2->rc, true);
	}




//////////
//
// Pipe stage 3 is d-read, to read any memory required by the instruction.
//
//////
	void iiDebo1_renderStage3(void)
	{
		s8		buffer[64];
		SBgra	textColor;


		//////////
		// Standard background coloring
		//////
			if (state.pipeStage >= _STAGE3)
			{
				// Valid
				if (pipe3.p3_d_read)
				{
					// There is a read at this point
					textColor = blackColor;
					iiDebo1_renderStageBackground(bmpStage3, &bmpStage3->rc, textColor, stage3LowColor, stage3HighColor, cgcStage3Top, cgcStage3Bottom);

				} else {
					// No read
					textColor = grayColor;
					iiDebo1_renderStageBackground(bmpStage3, &bmpStage3->rc, textColor, disabledLowColor, disabledHighColor, cgcStage3Top, cgcStage3Bottom);
				}

			} else {
				// Invalid
				textColor = redGrayColor;
				iiDebo1_renderStageBackground(bmpStage3, &bmpStage3->rc, textColor, invalidLowColor, invalidHighColor, cgcStage3Top, cgcStage3Bottom);
			}


		//////////
		// Stage 3 specific content
		//////
			sprintf(buffer, "ip %03x\n\0", pipe3.ip);
			if (pipe3.p3_d_read)
			{
				// Data to read
				sprintf(buffer + strlen(buffer), "read [%03x]\0", pipe3.p3_d_read_address);

			} else {
				// No data t read
				sprintf(buffer + strlen(buffer), "no read\0");
			}
			SetBkMode(bmpStage3->hdc, TRANSPARENT);
			SetTextColor(bmpStage3->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
			iiDebo1_renderTextCentered(bmpStage3, buffer, &bmpStage3->rc, true);
	}




//////////
//
// Pipe stage 4 is i-process, performs the operation specified by the opcode.
//
//////
	void iiDebo1_renderStage4(void)
	{
		RECT	lrc;
		s8		buffer[64];
		SBgra	textColor;


		//////////
		// Standard background coloring
		//////
			SetRect(&lrc, 0, 19, bmpStage4->bi.biWidth - 1, bmpStage4->bi.biHeight - 1);
			if (state.pipeStage >= _STAGE4)
			{
				// Valid
				textColor = blackColor;
				iiDebo1_renderStageBackground(bmpStage4, &lrc, textColor, stage4LowColor, stage4HighColor, cgcStage4Top, cgcStage4Bottom);

			} else {
				// Invalid
				textColor = redGrayColor;
				iiDebo1_renderStageBackground(bmpStage4, &lrc, textColor, invalidLowColor, invalidHighColor, cgcStage4Top, cgcStage4Bottom);
			}


		//////////
		// Keystroke shortcuts
		//////
			BitBlt(bmpStage4->hdc, 28,	0,	bmpF5Run->bi.biWidth - 1,		bmpF5Run->bi.biHeight - 1,			bmpF5Run->hdc,			0, 0, SRCCOPY);
			BitBlt(bmpStage4->hdc, 78,	0,	bmpF8Step->bi.biWidth - 1,		bmpF8Step->bi.biHeight - 1,			bmpF8Step->hdc,			0, 0, SRCCOPY);
			BitBlt(bmpStage4->hdc, 132,	0,	bmpF12Throttle->bi.biWidth - 1,	bmpF12Throttle->bi.biHeight - 1,	bmpF12Throttle->hdc,	0, 0, SRCCOPY);


		//////////
		// Stage 4 specific content
		//////
			sprintf(buffer, "ip %03x\n\0", pipe4.ip);
			iiDebo1_decodeAssembly(buffer + strlen(buffer), pipe4.ip, false, false, ram);
			SetBkMode(bmpStage4->hdc, TRANSPARENT);
			SetTextColor(bmpStage4->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
			lrc.top = 0;
			iiDebo1_renderTextCentered(bmpStage4, buffer, &lrc, true);


		//////////
		// Before and after regs
		//////
			// Before
			if (state.pipeStage >= _STAGE4)
			{
				// Label
				sprintf(buffer, "before\0");
				SetRect(&lrc, 0, 19, 12 + 40, bmpStage4->rc.bottom);
				SetTextColor(bmpStage4->hdc, RGB(stage4HighColor.red,stage4HighColor.grn,stage4HighColor.blu));
				DrawText(bmpStage4->hdc, buffer, strlen(buffer), &lrc, DT_CENTER | DT_SINGLELINE);

				// Content
				sprintf(buffer, "r1 %02x\nr2 %02x\nr3 %02x\nr4 %02x\n%s %s\0", pipe4.before.regs.r1, pipe4.before.regs.r2, pipe4.before.regs.r3, pipe4.before.regs.r4, ((pipe4.before.regs.carry) ? "CY" : "cy"), ((pipe4.before.regs.zero) ? "ZR" : "zr"));
				SetRect(&lrc, 6, 19 + 16, 6 + 40, bmpStage4->rc.bottom);
				SetTextColor(bmpStage4->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
				DrawText(bmpStage4->hdc, buffer, strlen(buffer), &lrc, DT_CENTER);

				// Divider
				lrc.left	= lrc.right + 2;
				lrc.right	= lrc.left + 2;
				iBmp_fillRect(bmpStage4, &lrc, stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
			}

			// Show after only after we've computed
			if (state.pipeStage > _STAGE4)
			{
				// Label
				sprintf(buffer, "after\0");
				SetRect(&lrc, bmpStage4->rc.right - 6 - 40, 19, bmpStage4->rc.right - 6, bmpStage4->rc.bottom);
				SetTextColor(bmpStage4->hdc, RGB(stage4HighColor.red,stage4HighColor.grn,stage4HighColor.blu));
				DrawText(bmpStage4->hdc, buffer, strlen(buffer), &lrc, DT_CENTER | DT_SINGLELINE);

				// Content
				sprintf(buffer, "r1 %02x\nr2 %02x\nr3 %02x\nr4 %02x\n%s %s\0", pipe4.after.regs.r1, pipe4.after.regs.r2, pipe4.after.regs.r3, pipe4.after.regs.r4, ((pipe4.after.regs.carry) ? "CY" : "cy"), ((pipe4.after.regs.zero) ? "ZR" : "zr"));
				SetRect(&lrc, bmpStage4->rc.right - 6 - 40, 19 + 16, bmpStage4->rc.right - 6, bmpStage4->rc.bottom);
				SetTextColor(bmpStage4->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
				DrawText(bmpStage4->hdc, buffer, strlen(buffer), &lrc, DT_CENTER);

				// Divider
				lrc.left	-= 2;
				lrc.right	= lrc.left + 2;
				iBmp_fillRect(bmpStage4, &lrc, stage4LowColor, stage4LowColor, stage4LowColor, stage4LowColor, false, NULL, false);
			}
	}




//////////
//
// Pipe stage 5 is d-write, writes updates back out to main memory
//
//////
	void iiDebo1_renderStage5(void)
	{
		s8		buffer[64];
		SBgra	textColor;


		//////////
		// Standard background coloring
		//////
			if (state.pipeStage >= _STAGE5)
			{
				// Valid
				if (pipe5.p5_d_write)
				{
					// There is a write at this point
					textColor = blackColor;
					iiDebo1_renderStageBackground(bmpStage5, &bmpStage5->rc, textColor, stage5LowColor, stage5HighColor, cgcStage5Top, cgcStage5Bottom);

				} else {
					// No write
					textColor = grayColor;
					iiDebo1_renderStageBackground(bmpStage5, &bmpStage5->rc, textColor, disabledLowColor, disabledHighColor, cgcStage5Top, cgcStage5Bottom);
				}

			} else {
				// Invalid
				textColor = redGrayColor;
				iiDebo1_renderStageBackground(bmpStage5, &bmpStage5->rc, textColor, invalidLowColor, invalidHighColor, cgcStage5Top, cgcStage5Bottom);
			}


		//////////
		// Stage 5 specific content
		//////
			sprintf(buffer, "ip %03x\n\0", pipe5.ip);
			if (pipe5.p5_d_write)
			{
				// Data to write
				sprintf(buffer + strlen(buffer), "write [%03x]\n\0", pipe5.p5_d_write_address);

			} else {
				// No data t read
				sprintf(buffer + strlen(buffer), "no write\n\0");
			}
			iiDebo1_decodeAssembly(buffer + strlen(buffer), pipe5.ip, false, false, ram);
			SetBkMode(bmpStage5->hdc, TRANSPARENT);
			SetTextColor(bmpStage5->hdc, RGB(textColor.red,textColor.grn,textColor.blu));
			iiDebo1_renderTextCentered(bmpStage5, buffer, &bmpStage3->rc, true);
	}




//////////
//
// Register window holds r1,r2,r3,r4, as well as carry? and zero? flags
//
//////
	void iiDebo1_renderRegisters(void)
	{
		RECT lrc;


		//////////
		// Overlay the logo info
		//////
			SetRect(&lrc, 0, 0, bmpRegisters->rc.right, bmpLibSF_386_x40->bi.biHeight);
			iBmp_bitBlt(bmpRegisters, &lrc, bmpLibSF_386_x40);
	}




//////////
//
// Disassembly contains multiple streams, one for each of stage 1 through 5.
// It disassembles two or three upcoming opcodes for each, allowing the
// parallel view through the stages to be examined.
//
//////
	void iiDebo1_renderDisassembly(void)
	{
		RECT lrc;


		//////////
		// Fill the background
		//////
			iBmp_fillRect(bmpDisassembly, &bmpDisassembly->rc, disassemblyColor, disassemblyColor, disassemblyColor, disassemblyColor, false, NULL, false);


		//////////
		// Show disassembly at the various levels
		//////
			SetRect(&lrc, 0, 0, bmpDisassembly->bi.biWidth, bmpDisassembly->bi.biHeight);
			SetBkMode(bmpDisassembly->hdc, TRANSPARENT);
			SelectObject(bmpDisassembly->hdc, fontUbuntuMono8->hfont);


		//////////
		// Stage 1
		//////
			if (state.pipeStage >= _STAGE1)
			{
				// Valid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe1.ip, 4, cgcStage1Bottom, stage1LowColor, stage1HighColor, blackColor);

			} else {
				// Invalid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe1.ip, 4, cgcStage1Bottom, invalidLowColor, invalidHighColor, grayColor);
			}
			lrc.top += 12;


		//////////
		// Stage 2
		//////
			if (state.pipeStage >= _STAGE2)
			{
				// Valid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe2.ip, 4, cgcStage2Bottom, stage2LowColor, stage2HighColor, ((state.pipeStage >= _STAGE2) ? blackColor : grayColor));

			} else {
				// Invalid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe2.ip, 4, cgcStage2Bottom, invalidLowColor, invalidHighColor, grayColor);
			}
			lrc.top += 12;


		//////////
		// Stage 3
		//////
			if (state.pipeStage >= _STAGE3)
			{
				// Valid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe3.ip, 4, cgcStage3Bottom, stage3LowColor, stage3HighColor, ((state.pipeStage >= _STAGE3) ? blackColor : grayColor));

			} else {
				// Invalid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe3.ip, 4, cgcStage3Bottom, invalidLowColor, invalidHighColor, grayColor);
			}
			lrc.top += 12;


		//////////
		// Stage 4
		//////
			if (state.pipeStage >= _STAGE4)
			{
				// Valid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe4.ip, 4, cgcStage4Bottom, stage4LowColor, stage4HighColor, ((state.pipeStage >= _STAGE4) ? blackColor : grayColor));

			} else {
				// Invalid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe4.ip, 4, cgcStage4Bottom, invalidLowColor, invalidHighColor, grayColor);
			}
			lrc.top += 12;


		//////////
		// Stage 5
		//////
			if (state.pipeStage >= _STAGE5)
			{
				// Valid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe5.ip, 4, cgcStage5Bottom, stage5LowColor, stage5HighColor, ((state.pipeStage >= _STAGE5) ? blackColor : grayColor));

			} else {
				// Invalid
				iiDebo1_decodeAssembly_NLines(bmpDisassembly, &lrc, pipe5.ip, 4, cgcStage5Bottom, invalidLowColor, invalidHighColor, grayColor);
			}
	}




//////////
//
// The Oppie-1 memory block is one of two banks, either showing the first
// 1KB of its 2KB RAM, or the second.
//
//////
	void iiDebo1_renderMemory(void)
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
					if (state.pipeStage >= _STAGE1)		iiDebo1_renderMemory_highlightMemory(lnI, lnI + 32, pipe1.ip, bmpMemory, &lrc, stage1LowColor, 3);
					if (state.pipeStage >= _STAGE2)		iiDebo1_renderMemory_highlightMemory(lnI, lnI + 32, pipe2.ip, bmpMemory, &lrc, stage2LowColor, ((pipe2.p2_increment2) ? 2 : 1));
					if (state.pipeStage >= _STAGE3)		iiDebo1_renderMemory_highlightMemory(lnI, lnI + 32, pipe3.ip, bmpMemory, &lrc, stage3LowColor, ((pipe3.p2_increment2) ? 2 : 1));
					if (state.pipeStage >= _STAGE4)		iiDebo1_renderMemory_highlightMemory(lnI, lnI + 32, pipe4.ip, bmpMemory, &lrc, stage4LowColor, ((pipe4.p2_increment2) ? 2 : 1));
					if (state.pipeStage >= _STAGE5)		iiDebo1_renderMemory_highlightMemory(lnI, lnI + 32, pipe5.ip, bmpMemory, &lrc, stage5LowColor, ((pipe5.p2_increment2) ? 2 : 1));


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
	void iiDebo1_renderMemory_highlightMemory(s32 start, s32 end, s32 address, SBitmap* bmp, RECT* rc, SBgra color, s32 tnBytes)
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
	DWORD WINAPI iDebo1_threadProc(LPVOID lpParameter)
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
			wce.lpfnWndProc			= &iDebo1_wndProc;


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
	LRESULT CALLBACK iDebo1_wndProc(HWND h, UINT m, WPARAM w, LPARAM l)
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
						iiDebo1_render();
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
