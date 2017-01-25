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


**********
* Set our paths
*****
	SET PATH TO \libsf\source\baser\source\ ADDITIVE
	

*********
* Initialize library and DLL functions
*****
	SET CLASSLIB TO \libsf\source\baser\source\baser.vcx ADDITIVE
	DECLARE INTEGER		Sleep								IN WIN32API							INTEGER nTimeout
	DECLARE INTEGER		baser_load							IN \libsf\source\baser\baser.dll	STRING	cFilename
	DECLARE INTEGER		baser_release						IN \libsf\source\baser\baser.dll	INTEGER	nHandle
	DECLARE INTEGER		baser_populate_row					IN \libsf\source\baser\baser.dll	INTEGER	nHandle, INTEGER nOffset, INTEGER nBase, STRING@ cBufferOut, INTEGER nBufferOut_length
	DECLARE INTEGER		baser_parse_block_by_struct			IN \libsf\source\baser\baser.dll	INTEGER	nHandle, INTEGER nHwnd, INTEGER nOffset, STRING cStruct, INTEGER nStructLength
	DECLARE INTEGER		baser_render_html					IN \libsf\source\baser\baser.dll	STRING @cHtmlContent, INTEGER tnHtmlContentLength
	DECLARE INTEGER		baser_retrieve_data					IN \libsf\source\baser\baser.dll	INTEGER nId, STRING@ cDataOut, INTEGER tnDataLength
	* Use:  lcHtmlPath270 = SPACE(270)
	*       baser_create_htmltemp_file_content(@lcHtmlPath270, sys(2015), tcHtmlContent, len(tcHtmlContent))
	*       ie.navigate2(left(lcHtmlPath270, lnLenth))
	DECLARE INTEGER		baser_create_htmltemp_file_content	IN \LIBSF\SOURCE\BASER\BASER.DLL	STRING@	cHtmlPathOut270, STRING cTempFilenamePrefix, STRING cContent, INTEGER nContentLength


**********
* Iterate through each file and launch them
*****
	llLaunched = .f.
	FOR lnI = 1 TO PCOUNT()
		lcFile = "tcFile" + TRANSFORM(lnI)
		IF TYPE(lcFile) = "C"
			DO FORM baser WITH &lcFile
			llLaunched = .t.
		ENDIF
	NEXT


**********
* If nothing launched, launch a blank form
*****
	IF !llLaunched
		DO FORM (ADDBS(JUSTPATH(SYS(16))) + "baser.scx")
	ENDIF


**********
* Wait until the last cow comes home
*****
	READ EVENTS
	CANCEL
