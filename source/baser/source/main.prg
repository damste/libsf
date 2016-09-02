* main.prg
* Up to 10 files can be loaded from the command line
LPARAMETERS tcFile1, tcFile2, tcFile3, tcFile4, tcFile5, tcFile6, tcFile7, tcFile8, tcFile9, tcFile10
LOCAL lnI, lcFile, llLaunched


**********
* Public values
*****
	PUBLIC WMBASER_CONTENT_IS_READY
	
	* Set the message values
	WMBASER_CONTENT_IS_READY		= 0x400 + 0


*********
* Initialize the DLL
*****
	DECLARE INTEGER		baser_load						IN baser.dll	STRING	cFilename
	DECLARE INTEGER		baser_release					IN baser.dll	INTEGER	nHandle
	DECLARE INTEGER		baser_populate_row				IN baser.dll	INTEGER	nHandle, INTEGER nOffset, INTEGER nBase, STRING@ cBufferOut, INTEGER nBufferOut_length, INTEGER@ nOffsetIncrement
	DECLARE INTEGER		baser_parse_block_by_struct		IN baser.dll	INTEGER	nHandle, HWND nHwnd, INTEGER nOffset, INTEGER nBase, STRING@ cBufferOut, INTEGER nBufferOut_length, STRING cStruct, INTEGER nStructLength
	DECLARE INTEGER		baser_retrieve_data				IN baser.dll	INTEGER nId, STRING@ cDataOut, INTEGER tnDataLength
			


**********
* Iterate through each file and launch them
*****
	llLaunched = .f.
	FOR lnI = 1 TO PCOUNT()
		lcFile = "tcFile" + TRANSFORM(lnI)
		IF TYPE(lcFile) = "C"
			DO FORM baser.vcx WITH &lcFile
			llLaunched = .t.
		ENDIF
	NEXT


**********
* If nothing launched, launch a blank form
*****
	IF !llLaunched
		DO FORM baser.vcx
	ENDIF


**********
* Wait until the last cow comes home
*****
	READ EVENTS
	CANCEL
