CLEAR
process_directory("C:\libsf\exodus\source\", .t.)



FUNCTION process_directory
LPARAMETERS tcPath, tlRecurse
LOCAL lnI, lcSaveDir, laFiles

	tcPath = ADDBS(tcPath)
	IF DIRECTORY(tcPath)
		* Save where we are
		lcSaveDir = FULLPATH(CURDIR())
		CD (tcPath)
		
		* Get the files
		DIMENSION laFiles[1]
		ADIR(laFiles, "*.*", "SHD")
		FOR lnI = 1 TO ALEN(laFiles, 1)
			IF NOT INLIST(laFiles[lnI,1], ".", "..")
				IF "D" $ laFiles[lnI, 5]
					* Directory
					IF tlRecurse
						process_directory(ADDBS(tcPath) + laFiles[lnI, 1], tlRecurse)
					ENDIF
				ELSE
					* Is it an assembly file?
					IF INLIST(LOWER(JUSTEXT(laFiles[lnI, 1])), "asm", "asp")
						* Process this file
						WAIT WINDOW "Processing " + tcPath + laFiles[lnI, 1] NOWAIT
						process_file(tcPath + laFiles[lnI, 1])
					ENDIF
				ENDIF
			ENDIF
		NEXT
		
		* Get back to where we once belonged
		CD (lcSaveDir)
	ENDIF




FUNCTION process_file
LPARAMETERS tcPathIn
LOCAL lcAsm, laAlines, lnLines, llSkipCrLf, lcFileOut

	* Make sure it's a file
	IF NOT FILE(tcPathIn)
SET STEP ON
		RETURN
	ENDIF

	* Load the file
	lcAsm = FILETOSTR(tcPathIn)
	
	* Convert to an array
	DIMENSION laLines[1]
	lnLines		= ALINES(laLines, lcAsm)
	lcAsm		= SPACE(0)
	llSkipCrLf 	= .f.
	FOR lnI = 1 to ALEN(laLines, 1)
		IF NOT EMPTY(laLines[lnI])
			* Remove all tabs
			laLines[lnI] = removeTabs(laLines[lnI])
		
			* Put any whitespaces up front
			lnWhitespaces = consecutive(laLines[lnI], CHR(32) + CHR(9))
			IF NOT INLIST(UPPER(GETWORDNUM(laLines[lnI], 2)), "SEGMENT", "ENDS")
				lcAsm = lcAsm + SPACE(lnWhitespaces)
			ENDIF
			IF lnWhitespaces > 0
				laLines[lnI] = SUBSTR(laLines[lnI], lnWhitespaces + 1)
			ENDIF

			DO CASE
				CASE LEFT(laLines[lnI], 1) = ";" AND NOT LEFT(laLines[lnI], 2) = ";;"
					* It's a comment, translate to "//" and copy
					* Note:  We leave the double-;; because it looks nicer than // :-)
					lcAsm = lcAsm + "//" + SUBSTR(laLines[lnI], 2)

				CASE UPPER(GETWORDNUM(laLines[lnI], 1)) == "TITLE"
					* Alter this line
					lcAsm = lcAsm + "// " + ALLTRIM(SUBSTR(laLines[lnI], 6))

				CASE UPPER(GETWORDNUM(laLines[lnI],1)) == "INCLUDE"
					* Change to just "while "
					lcAsm = lcAsm + "#include " + CHR(34) + ALLTRIM(SUBSTR(laLines[lnI], 8)) + CHR(34)

				CASE UPPER(laLines[lnI]) = ".IF"
					* Change to just "if "
					lcAsm = lcAsm + "if " + ALLTRIM(SUBSTR(laLines[lnI], 4)) + CHR(13) + CHR(10) + SPACE(lnWhiteSpaces) + "{"

				CASE UPPER(laLines[lnI]) = ".ELSEIF"
					* Change to just "} else if "
					lcAsm = lcAsm + CHR(13) + CHR(10) + SPACE(lnWhitespaces) + "} else if " + ALLTRIM(SUBSTR(laLines[lnI], 8)) + " {"

				CASE UPPER(laLines[lnI]) = ".ELSE"
					* Change to just "} else {"
					lcAsm = lcAsm + CHR(13) + CHR(10) + SPACE(lnWhiteSpaces) + "} else {" + ALLTRIM(SUBSTR(laLines[lnI], 6))

				CASE UPPER(laLines[lnI]) = ".WHILE"
					* Change to just "while "
					lcAsm = lcAsm + "while " + ALLTRIM(SUBSTR(laLines[lnI], 7)) + CHR(13) + CHR(10) + SPACE(lnWhiteSpaces) + "{"

				CASE UPPER(laLines[lnI]) = ".REPEAT"
					* Change to just "repeat"
					lcAsm = lcAsm + "repeat" + ALLTRIM(SUBSTR(laLines[lnI], 8)) + CHR(13) + CHR(10) + SPACE(lnWhiteSpaces) + "{"

				CASE UPPER(laLines[lnI]) = ".UNTILCXZ"
					* Change to just "} untilcxz"
					lcAsm = lcAsm + "} untilcxz" + ALLTRIM(SUBSTR(laLines[lnI], 10))

				CASE INLIST(UPPER(GETWORDNUM(ALLTRIM(laLines[lnI]), 1)), ".ENDIF", ".ENDW")
					* Change to just "}"
					lcAsm = lcAsm + "}"
				
				CASE laLines[lnI] = "." OR UPPER(GETWORDNUM(laLines[lnI], 1)) == "ASSUME"
					* Ignore it
					llSkipCrLf = .t.
				
				CASE UPPER(GETWORDNUM(laLines[lnI], 2)) == "SEGMENT"
					* Change the line to "abc" + chr(13) + "| at offset 0" + chr(13) + "{"
					lcAsm = ALLTRIM(lcAsm)
					lcAsm = lcAsm + LOWER(GETWORDNUM(laLines[lnI], 2, "'")) + " " + STRTRAN(LOWER(GETWORDNUM(laLines[lnI], 1)), "_", SPACE(0)) + CHR(13) + CHR(10)
					lcAsm = lcAsm + "| at offset 0" + CHR(13) + CHR(10)
					lcAsm = lcAsm + "{"
				
				CASE UPPER(GETWORDNUM(laLines[lnI], 2)) == "ENDS"
					* Change the line to "}"
					lcAsm = ALLTRIM(lcAsm)
					lcAsm = lcAsm + "}" + CHR(13) + CHR(10) + "// " + STRTRAN(LOWER(GETWORDNUM(laLines[lnI], 1)), "_", SPACE(0))
				
				CASE UPPER(GETWORDNUM(laLines[lnI], 2)) == "PROC"
					* Change to "function name {"
					lcAsm = lcAsm + "function " + GETWORDNUM(laLines[lnI], 1) + SUBSTR(laLines[lnI], AT("PROC", UPPER(laLines[lnI])) + 4)
					lcAsm = lcAsm + CHR(13) + CHR(10) + SPACE(MAX(lnWhitespaces, 0)) + "{"
				
				CASE UPPER(GETWORDNUM(laLines[lnI], 2)) == "ENDP"
					* Change to "} // function name"
					lcAsm = lcAsm + "}" + SUBSTR(laLines[lnI], AT("ENDP", UPPER(laLines[lnI])) + 4)
				
				CASE UPPER(GETWORDNUM(laLines[lnI], 1)) = "CALL" AND NOT "word ptr" $ LOWER(laLines[lnI])
					* Change to "name()"
					lcName	= GETWORDNUM(laLines[lnI], 2)
					lcAsm	= lcAsm + lcName + "()" + SUBSTR(laLines[lnI], AT(lcName, laLines[lnI]) + LEN(lcName))
				OTHERWISE
					* Copy as is
					lcAsm = lcAsm + laLines[lnI]
			ENDCASE
		ENDIF
		
		* Add a CR/LF
		IF NOT llSkipCrLf 
			lcAsm = lcAsm + CHR(13) + CHR(10)
		ENDIF
		llSkipCrLf = .f.
	NEXT
	
	* Perform some global fixups
	lcAsm = CHRTRAN(lcAsm, "ÚÄ¿³ÀÙ´ÃÅ", "+-+|++|-+")	&& Changes characters that were used in a custom DOS font for a box
	lcAsm = STRTRAN(lcAsm, " ;", " //")					&& Changes comments to the modern form
	lcAsm = STRTRAN(lcAsm, "//;", " //")				&& Observed in the wild
	lcAsm = STRTRAN(lcAsm, " EQU ", "   = ")			&& Replace all EQU with a simple =
	
	* Perform some syntax change fixups
	lcAsm = STRTRAN(lcAsm, " real4 ptr ",	" <f32> ")
	lcAsm = STRTRAN(lcAsm, " real8 ptr ",	" <f64> ")
	lcAsm = STRTRAN(lcAsm, " real10 ptr ",	" <f80> ")
	lcAsm = STRTRAN(lcAsm, " qword ptr ",	" <u64> ")
	lcAsm = STRTRAN(lcAsm, " fword ptr ",	" <u48> ")
	lcAsm = STRTRAN(lcAsm, " dword ptr ",	" <u32> ")
	lcAsm = STRTRAN(lcAsm, " word ptr ",	" <u16> ")
	lcAsm = STRTRAN(lcAsm, " byte ptr ",	" <u8>  ")

	lcAsm = STRTRAN(lcAsm, ",real4 ptr ",	",<f32> ")
	lcAsm = STRTRAN(lcAsm, ",real8 ptr ",	",<f64> ")
	lcAsm = STRTRAN(lcAsm, ",real10 ptr ",	",<f80> ")
	lcAsm = STRTRAN(lcAsm, ",qword ptr ",	",<u64> ")
	lcAsm = STRTRAN(lcAsm, ",fword ptr ",	",<u48> ")
	lcAsm = STRTRAN(lcAsm, ",dword ptr ",	",<u32> ")
	lcAsm = STRTRAN(lcAsm, ",word ptr ",	",<u16> ")
	lcAsm = STRTRAN(lcAsm, ",byte ptr ",	",<u8>  ")
	
	lcAsm = STRTRAN(lcAsm, "ss:[ebp",		"[ebp")
	lcAsm = STRTRAN(lcAsm, "ss:[esp",		"[esp")
	lcAsm = STRTRAN(lcAsm, " real10 ",		" f80 ")
	lcAsm = STRTRAN(lcAsm, " real8 ",		" f64 ")
	lcAsm = STRTRAN(lcAsm, " real4 ",		" f32 ")
	lcAsm = STRTRAN(lcAsm, " db ",			" u8  ")
	lcAsm = STRTRAN(lcAsm, " dw ",			" u16 ")
	lcAsm = STRTRAN(lcAsm, " dd ",			" u32 ")
	lcAsm = STRTRAN(lcAsm, " dq ",			" u64 ")
	
	lcAsm = STRTRAN(lcAsm, "<f32>  ",		"<f32> ")
	lcAsm = STRTRAN(lcAsm, "<f64>  ",		"<f64> ")
	lcAsm = STRTRAN(lcAsm, "<f80>  ",		"<f80> ")
	lcAsm = STRTRAN(lcAsm, "<u64>  ",		"<u64> ")
	lcAsm = STRTRAN(lcAsm, "<u48>  ",		"<u48> ")
	lcAsm = STRTRAN(lcAsm, "<u32>  ",		"<u32> ")
	lcAsm = STRTRAN(lcAsm, "<u16>  ",		"<u16> ")
	lcAsm = STRTRAN(lcAsm, "<u8>   ",		"<u8>  ")

	* Write the output
	SET SAFETY OFF
	lcFileOut = LOWER(IIF(".asm" $ LOWER(tcPathIn), FORCEEXT(tcPathIn, "lasm"), FORCEEXT(tcPathIn, "lasp")))
	IF FILE(lcFileOut)
		ERASE (lcFileOut)
	ENDIF
	STRTOFILE(lcAsm, lcFileOut)
	SET SAFETY ON



FUNCTION removeTabs
LPARAMETERS tcText
LOCAL lnI, lnOffset, lcText
	lcText		= SPACE(0)
	lnOffset	= 0
	FOR lnI = 1 TO LEN(tcText)
		IF SUBSTR(tcText, lnI, 1) = CHR(9)
			* It's a tab
			lnLength	= IIF(lnOffset % 4 = 0,		4,		4 - (lnOffset % 4))
			lcText		= lcText + SPACE(lnLength)
			lnOffset	= lnOffset + (4 - (lnOffset % 4))

		ELSE
			* Copy the character
			lcText		= lcText + SUBSTR(tcText, lnI, 1)
			lnOffset	= lnOffset + 1
		ENDIF
	NEXT
	
	* Update our result
	RETURN lcText




FUNCTION consecutive
LPARAMETERS tcText, tcChar
LOCAL lnI, lnCount
	* So long as it repeats... count it
	lnCount = 0
    FOR lnI = 1 TO LEN(tcText)
    	IF NOT SUBSTR(tcText, lnI, 1) $ tcChar
    		EXIT
    	ENDIF
    	lnCount = lnCount + 1
    NEXT
    
	* Indicate our count
	RETURN lnCount
