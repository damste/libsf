//////////
//
// /libsf/source/vjr/source/dialogs/dialogs.cpp
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
// Version 0.59
// Copyright (c) 2014-2016 by Rick C. Hodgin
//////
// Last update:
//     Aug.23.2016
//////
// Change log:
//     Aug.23.2016 - Initial creation
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
//////////




//////////
//
// Called to open a table and return the work area it was opened into if it's valid
//
//////
	SWorkArea* iDialog_openTable(void)
	{
		bool		llIsExclusive, llAutoValidate;
		s32			lnWorkArea, start, length;
		SVariable*	varAliasName;
		s8			filename[_MAX_PATH];
		s8			aliasname[_MAX_ALIAS_NAME_LENGTH];


		// Initialize the filename
		memset(filename,  0, sizeof(filename));
		memset(aliasname, 0, sizeof(aliasname));

		// Get the filename
		if (!iDialog_openTable(filename, &start, &length))
			return(NULL);

		// See if the indicated alias already exists
		lnWorkArea = iDbf_get_workArea_byAlias_byName(filename + start, length);
		if (lnWorkArea >= 0)
		{
			// Already exists, so invent a new one
			varAliasName = iFunction_sys2015(0, 0);
			memcpy(aliasname, varAliasName->value.data_s8, varAliasName->value.length);
			iVariable_delete(&varAliasName);
		}

		// Try to open the indicated table
		llIsExclusive	= propGet_settings_Exclusive(_settings);
		llAutoValidate	= propGet_settings_AutoValidate(_settings);
		lnWorkArea = iDbf_open(filename, aliasname, llIsExclusive, true, llAutoValidate, false, false, false, false);
		if (lnWorkArea < 0)
			return(NULL);

		// We have the table open
		return(iDbf_get_workArea_current_wa(lnWorkArea));
	}




//////////
//
// Called to give the open table dialog, asking for a disk file.
//
//////
	bool iDialog_openTable(s8* filenameOut, s32* nameStart, s32* nameLength, bool tlAllowNew)
	{
		OPENFILENAME	ofn;
		s8				curdir[_MAX_PATH];


		// Ready
		memset(&ofn, 0, sizeof(ofn));
		GetCurrentDirectory(sizeof(curdir), curdir);

		// Set
		ofn.lStructSize		= sizeof(ofn);
		ofn.lpstrFilter		= "DBF files\0*.dbf\0";
		ofn.Flags			= OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_PATHMUSTEXIST;
		ofn.lpstrFile		= filenameOut;
		ofn.nMaxFile		= MAX_PATH;
		ofn.lpstrTitle		= "Open Table";
		ofn.lpstrInitialDir	= curdir;
 		ofn.lpstrDefExt		= "dbf";

		// Go!
		return(GetOpenFileName(&ofn) == TRUE);
	}
