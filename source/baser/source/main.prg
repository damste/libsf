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
* IE Helper
*****
	PUBLIC goEventsHandler
	goEventsHandler = CREATEOBJECT("ieEventHandler")
	

*********
* Initialize library and DLL functions
*****
	SET CLASSLIB TO \libsf\source\baser\source\baser.vcx ADDITIVE
	DECLARE INTEGER		Sleep							IN WIN32API							INTEGER nTimeout
	DECLARE INTEGER		baser_load						IN \libsf\source\baser\baser.dll	STRING	cFilename
	DECLARE INTEGER		baser_release					IN \libsf\source\baser\baser.dll	INTEGER	nHandle
	DECLARE INTEGER		baser_populate_row				IN \libsf\source\baser\baser.dll	INTEGER	nHandle, INTEGER nOffset, INTEGER nBase, STRING@ cBufferOut, INTEGER nBufferOut_length
	DECLARE INTEGER		baser_parse_block_by_struct		IN \libsf\source\baser\baser.dll	INTEGER	nHandle, INTEGER nHwnd, INTEGER nOffset, STRING cStruct, INTEGER nStructLength
	DECLARE INTEGER		baser_retrieve_data				IN \libsf\source\baser\baser.dll	INTEGER nId, STRING@ cDataOut, INTEGER tnDataLength


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
		DO FORM baser
	ENDIF


**********
* Wait until the last cow comes home
*****
	READ EVENTS
	CANCEL



DEFINE CLASS ieEventHandler AS Custom
	* For DWebBrowserEvents2 interface, see:  https://msdn.microsoft.com/en-us/library/aa768283(v=vs.85).aspx
	IMPLEMENTS DWebBrowserEvents2 IN "SHDOCVW.DLL"
	
	* Fires before navigation occurs in the given object (on either a window element or a frameset element)
	PROCEDURE DWebBrowserEvents2_BeforeNavigate2 ;
				(toIe				AS Variant, ;
				tcUrl				AS Variant @, ;
				tnFlags				AS Variant @, ;
				tcTargetframename	AS Variant @, ;
				tcPostdata			AS Variant @, ;
				txHeaders			AS Variant @, ;
				tlCancel			AS Logical @) 	AS VOID

		* To cancel navigation?
		IF MESSAGEBOX("Cancel Navigation to?" + CHR(13) + CHR(13) + tcUrl, 4, "BeforeNavigation2") = 6
			tlCancel = .t.
		ENDIF
	ENDPROC

	* Fires to request that the client window size is converted to the host window size
	PROCEDURE DWebBrowserEvents2_ClientToHostWindow ;
			(tnWidth	AS Long @, ;
			tnHeight	AS Long @)		AS VOID
	ENDPROC

	* Fires when the enabled state of a command changes
	PROCEDURE DWebBrowserEvents2_CommandStateChange ;
			(tnCommand	AS Long, ;
			tlEnable	AS Logical)		AS VOID
	ENDPROC

	* Fires when a document is completely loaded and initialized
	PROCEDURE DWebBrowserEvents2_DocumentComplete ;
				(toIe	AS Variant, ;
				tcUrl	AS Variant) 	AS VOID
	ENDPROC

	* Fires when a navigation operation begins
	PROCEDURE DWebBrowserEvents2_DownloadBegin ;
				AS VOID
	ENDPROC

	* Fires when a navigation operation finishes, is halted, or fails
	PROCEDURE DWebBrowserEvents2_DownloadComplete ;
				AS VOID
	ENDPROC

	* Fires after a navigation to a link is completed on a window element or a frameSet element
	PROCEDURE DWebBrowserEvents2_NavigateComplete2 ;
				(toIe	AS Variant, ;
				tcUrl	AS Variant) 		AS VOID
	ENDPROC

	* Creates a new process to handle the navigation
	PROCEDURE DWebBrowserEvents2_NewProcess ;
				(tnCause	AS Long, ;
				toProcess	AS Object, ;
				tlCancel	AS Logical @) 	AS VOID
		* Note:  tnCause should only be:  ProtectedModeRedirect = 0x1
	ENDPROC

	* Fires when a new window is to be created
	PROCEDURE DWebBrowserEvents2_NewWindow2 ;
				(toIe		AS Variant @, ;
				tlCancel	AS Logical @) 	AS VOID
	ENDPROC

	* Raised when a new window is to be created. Extends NewWindow2 with additional information about the new window
	PROCEDURE DWebBrowserEvents2_NewWindow3 ;
				(toIe				AS Variant @, ;
				tlCancel			AS Logical @, ;
				tnFlags				AS Long, ;
				tcBstrUrlContext	AS String, ;
				tcBstrUrl			AS String) 		AS VOID
	ENDPROC

	* Fires when the FullScreen property is changed
	PROCEDURE DWebBrowserEvents2_OnFullScreen ;
				(tlFullScreen	AS Logical) 	AS VOID
	ENDPROC

	* Fires when the MenuBar property is changed
	PROCEDURE DWebBrowserEvents2_OnMenuBar ;
				(tlMenuBar		AS Logical) 	AS VOID
	ENDPROC

	* Fires before the Internet Explorer application quits
	PROCEDURE DWebBrowserEvents2_OnQuit ;
				AS VOID
	ENDPROC

	* Fires when the StatusBar property is changed
	PROCEDURE DWebBrowserEvents2_OnStatusBar ;
				(tlStatusBar	AS Logical) 	AS VOID
	ENDPROC

	* Fires when the TheaterMode property is changed
	PROCEDURE DWebBrowserEvents2_OnTheaterMode ;
				(tlTheatreMode	AS Logical) 	AS VOID
	ENDPROC

	* Fires when the ToolBar property is changed
	PROCEDURE DWebBrowserEvents2_OnToolBar ;
				(tlToolBar		AS Logical) 	AS VOID
	ENDPROC

	* Fires when the Visible property of the object is changed
	PROCEDURE DWebBrowserEvents2_OnVisible ;
				(tlVisible		AS Logical) 	AS VOID
	ENDPROC

	* Fires when a print template is instantiated
	PROCEDURE DWebBrowserEvents2_PrintTemplateInstantiation ;
				(toIe			AS Variant) 	AS VOID
	ENDPROC

	* Fires when a print template is destroyed
	PROCEDURE DWebBrowserEvents2_PrintTemplateTeardown ;
				(toIe			AS Variant) 	AS VOID
	ENDPROC

	* Fires when the progress of a download operation is updated on the object
	PROCEDURE DWebBrowserEvents2_ProgressChange ;
				(tnProgress		AS Long, ;
				tnProgressMax	AS Long)		AS VOID
	ENDPROC

	* Fires when the PutProperty method of the object changes the value of a property
	PROCEDURE DWebBrowserEvents2_PropertyChange ;
				(tcProperty		AS Variant) 	AS VOID
	ENDPROC

	* Fires when the status bar text of the object has changed
	PROCEDURE DWebBrowserEvents2_StatusTextChange ;
				(tcText			AS Variant) 	AS VOID
	ENDPROC

	* Fires when the title of a document in the object becomes available or changes
	PROCEDURE DWebBrowserEvents2_TitleChange ;
				(tcText			AS Variant) 	AS VOID
	ENDPROC

	* Fires when the window of the object is about to be closed by script
	PROCEDURE DWebBrowserEvents2_WindowClosing ;
				(tlIsChildWindow	AS Logical, ;
				tlCancel			AS Logical @) 	AS VOID
	ENDPROC

	* Fires when the object changes its height
	PROCEDURE DWebBrowserEvents2_WindowSetHeight ;
				(tnHeight	AS Long) 	AS VOID
	ENDPROC

	* Fires when the object changes its left position
	PROCEDURE DWebBrowserEvents2_WindowSetLeft ;
				(tnLeft		AS Long) 	AS VOID
	ENDPROC

	* Fires to indicate whether the host window should allow resizing of the object
	PROCEDURE DWebBrowserEvents2_WindowSetResizable ;
				(tlResizeable	AS Logical) 	AS VOID
	ENDPROC

	* Fires when the object changes its top position
	PROCEDURE DWebBrowserEvents2_WindowSetTop ;
				(tnTop		AS Long) 	AS VOID
	ENDPROC

	* Fires when the object changes its width
	PROCEDURE DWebBrowserEvents2_WindowSetWidth ;
				(tnWidth	AS Long) 	AS VOID
	ENDPROC

	* Fires when the visibility state of a content window, such as the browser window or a tab, changes
	PROCEDURE DWebBrowserEvents2_WindowStateChanged ;
				(tnFlags		AS Long, ;
				tnFlagMask		AS Long) 	AS VOID
	ENDPROC

**********
* Documented, but not implemented
*	PROCEDURE DWebBrowserEvents2_UpdatePageStatus
*	ENDPROC
*****

	* Fired to indicate the security level of the current web page contents
	PROCEDURE DWebBrowserEvents2_SetSecureLockIcon ;
				(tnSecureLockIcon	AS Number)		AS VOID
	ENDPROC

	* Fired to indicate the File Download dialog is opening
	PROCEDURE DWebBrowserEvents2_FileDownload ;
				(fActiveDoc		AS Logical @, ;
				tlCancel		AS Logical @)	AS VOID
	ENDPROC

	* Fired when a binding error occurs (window or frameset element)
	PROCEDURE DWebBrowserEvents2_NavigateError ;
				(toIe			AS Variant, ;
				tcUrl			AS Variant, ;
				tcFrame			AS Variant, ;
				tnStatusCode	AS Variant, ;
				tlCancel		AS Logical @)	AS VOID
	ENDPROC

	* Fired when a page is spooled. When it is fired can be changed by a custom templat
	PROCEDURE DWebBrowserEvents2_UpdatePageStatus ;
				(toIe			AS Variant, ;
				tnPage			AS Variant, ;
				tlDone			AS Variant)		AS VOID
	ENDPROC

	* Fired when the global privacy impacted state changes
	PROCEDURE DWebBrowserEvents2_PrivacyImpactedStateChange ;
				(tImpacted		AS Logical)		AS VOID
	ENDPROC

	* Fires to indicate the progress and status of Microsoft Phishing Filter analysis of the current webpage
	PROCEDURE DWebBrowserEvents2_SetPhishingFilterStatus ;
				(tnPhishingFilterStatus		AS Long)		AS VOID
	ENDPROC

	* Fired when a third-party URL is blocked
	PROCEDURE DWebBrowserEvents2_ThirdPartyUrlBlocked ;
				(tcUrl		AS Variant, ;
				tnCount		AS Long)		AS VOID			&& Note:  tnCount is always 0
	ENDPROC

	* Fired when a cross-domain redirect request is blocked
	PROCEDURE DWebBrowserEvents2_RedirectXDomainBlocked ;
				(toIe			AS Variant, ;
				tcStartUrl		AS Variant, ;
				tcRedirectUrl	AS Variant, ;
				tcFrame			AS Variant, ;
				tnStatusCode	AS Variant)		AS VOID
	ENDPROC
ENDDEFINE
