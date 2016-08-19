//////////
//
// /libsf/utils/common/cpp/cliserv/cscommon.h
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
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Aug.02.2014
//////
// Change log:
//     Aug.02.2014 - Initial creation
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




class CClient;
class CServer;
class CCSCommon;
struct SAppProc;
struct SList;

//////////
// Common to both client and server
//////
	// Constants for communicating Cliserv changes in connections, new messages, etc., to the indicated callback hwnd (for server or callback)
	const u32	WMCLISERV_CLIENT_CONNECTED							= WM_USER + 500;					// When a client connects, this message is sent to the callback hwnd
	const u32	WMCLISERV_CLIENT_DISCONNECTED						= WM_USER + 501;					// When a client disconnects, this message is sent to the callback hwnd
	const u32	WMCLISERV_SERVER_CONNECTED							= WM_USER + 502;					// When a server connects, this message is sent to the callback hwnd
	const u32	WMCLISERV_SERVER_DISCONNECTED						= WM_USER + 503;					// When a server disconnects, this message is sent to the callback hwnd
	const u32	WMCLISERV_TRANSACTION_RESPONSE						= WM_USER + 504;					// When a remote connect sends us data, this message is sent to indicate the mail parcel for receipt

	const u32	_CLISERV_MAX_PROCESS_THREADS						= 4;								// Maximum of 4 simultaneous processing threads per client/server connection instance
	const u32	_CLISERV_PROCESS_SLEEP_INTERVAL_BUSY				= 0;								// Release timeslice after each iteration, but continue processing
	const u32	_CLISERV_PROCESS_SLEEP_INTERVAL_IDLE				= 2;								// Release timeslice after each iteration, but continue processing
	const u32	_CLISERV_PING_INTERVAL								= 5000;								// Ping every 5 seconds
	const u32	_CLISERV_WATCHDOG_SLEEP_INTERVAL					= 5000;								// Watchdog fires every 5 seconds
	const u32	_CLISERV_RETRY_TIMEOUT_INTERVAL						= 30000;							// If we don't receive packets after 30 seconds, we retry
	const u32	_CLISERV_UNACK_RESEND_TIMEOUT_INTERVAL				= 15000;							// If we don't get an acknowledgment on a send after 15 seconds, we re-send
	const u32	_CLISERV_UNACK_FAILURE_TIMEOUT_INTERVAL				= 60000;							// If we don't get an acknowledgment on a first send after 60 seconds, we consider it a failure

	// Strings used for identifying commands, populates command2 in the SCommHeader
	const s8	cgcPing[]											= "PG";								// Ping
	const s8	cgcResend[]											= "RS";								// Resend
	const s8	cgcRequest[]										= "RQ";								// Request
	const s8	cgcFill[]											= "FL";								// Fill
	const s8	cgcAck[]											= "AK";								// Acknowledge
//	const s8	cgcMassAck[]										= "MA";								// To be implemented later, for now individual single-issue ack receipts are sent/received
	const s8	cgcUser[]											= "UT";								// User text
	const s8	cgcIMsg[]											= "I";								// Internal message
	const s8	cgcEMsg[]											= "E";								// External message

	const u8	cgcInterval[]										= "interval";						// For ping responses, the interval in milliseconds
	const u8	cgcFailures[]										= "failures";						// For ping responses, the number of requests not responded
	const u8	cgcLocalHwnd[]										= "localhwnd";						// For ping response, the local hwnd
	const u8	cgcRemoteHwnd[]										= "remotehwnd";						// For ping response, the remote hwnd
	const u8	cgcBoundHwnd[]										= "boundhwnd";						// For ping response, the bound hwnd

	const u8	cgcIdentifier[]										= "identifier";						// For "do verb x equals" response identifier
	const u8	cgcResponse[]										= "response";						// For "do verb x equals" response
	const u8	cgcValue[]											= "value";							// For general messages, the value
	const u8	cgcExtra[]											= "extra";							// For general messages, the extra value
	const u8	cgcMessage[]										= "message";						// For general messages, the messsage text

	const u8	cgcVerbCmd[]										= "verb";							// For cliserv, for sending a "verb" or "verb x equals" to a remote ip address
	const u8	cgcIpAddress[]										= "ipaddress";						// For cliserv, for indicating the ip address of a connection change
	const u8	cgcPortNumber[]										= "portnumber";						// For cliserv, for indicating the port number of a connection change
	const u8	cgcTransactionId[]									= "transactionid";					// For cliserv, for indicating the transaction id this mail relates to
	const u8	cgcChangeType[]										= "change";							// For cliserv, for indicating the type of connection change (connect or disconnect)
	const u8	cgcIncomingBytes[]									= "incomingbytes";					// For cliserv, for indicating the number of bytes for incoming data
	const u8	cgcMailId[]											= "mailid";							// For cliserv, for indicating the mail id to retrieve additional information
	const u8	cgcConnect[]										= "connect";						// For cliserv, indicates a connection was made
	const u8	cgcDisconnect[]										= "disconnect";						// For cliserv, indicates a disconnect was made
	const u8	cgcIncomingData[]									= "incomingdata";					// For cliserv, indicates data is being transferred

	// XML tags
	const s8	cgcCliservRootTag[]									= "cliserv";
	const s8	cgcCommand[]										= "command";
	const s8	cgcCmd[]											= "cmd";
	const u8	cgcVerb[]											= "verb";
	const u8	cgcVerbX_equals[]									= "verbxequals";
	const s8	cgcAllItems[]										= "[all]";

	// Inquiry Server requests
	const s8	cgc_inquiry_get_applications9[]						= "inqgetapp";
	const s8	cgc_inquiry_login9[]								= "inqlogin ";
	const s8	cgc_inquiry_logout9[]								= "inqlogout";
	const s8	cgc_inquiry_get_status_list9[]						= "inqgetsta";
	const s8	cgc_inquiry_get_priority_list9[]					= "inqgetpri";
	const s8	cgc_inquiry_get_reported_list9[]					= "inqgetrep";
	const s8	cgc_inquiry_get_target_list9[]						= "inqgettar";
	const s8	cgc_inquiry_get_by_date9[]							= "inqbydat ";
	const s8	cgc_inquiry_get_by_status9[]						= "inqbysta ";
	const s8	cgc_inquiry_get_by_priority9[]						= "inqbypri ";
	const s8	cgc_inquiry_get_by_reported9[]						= "inqbyrep ";
	const s8	cgc_inquiry_get_by_target9[]						= "inqbytar ";
	const s8	cgc_inquiry_get_description9[]						= "inqgetdsc";
	const s8	cgc_inquiry_get_comment9[]							= "inqgetcom";
	const s8	cgc_inquiry_update_title9[]							= "inqupdtit";
	const s8	cgc_inquiry_update_description9[]					= "inqupddes";
	const s8	cgc_inquiry_update_comment9[]						= "inqupdcom";
	const s8	cgc_inquiry_update_status9[]						= "inqupdsta";
	const s8	cgc_inquiry_update_priority9[]						= "inqupdpri";
	const s8	cgc_inquiry_update_release9[]						= "inqupdrel";
	const s8	cgc_inquiry_add9[]									= "inqaddnew";
	const s8	cgc_inquiry_add_comment9[]							= "inqaddcom";
	const s8	cgc_inquiry_get_change_history9[]					= "inqgetch ";
	const s8	cgc_inquiry_get_change_history_description9[]		= "inqgetchd";
	const s8	cgc_inquiry_get_change_history_comment9[]			= "inqgetchc";


	// For out processes, and the in process (only one in per instance)
	SAppProc*			gsProcRemotes								= NULL;			// List of processes for Out (one Out can be "speaking" to multiple remote processes)
	SAppProc*			gsProcSelf									= NULL;			// Process holder for the In item, which is stored in self
	CRITICAL_SECTION	gsemUniqueId;												// Used for accessing unique id's one at a time
	u32					gnNextUniqueId								= 0x081069;		// Begin at Rick's birthday. :-)
	bool				gbWSA_isInitialized							= false;		// Used to determine if winsock WSAStartup() needs to be called
	CClient*			gcRootClient								= NULL;			// First client
	CServer*			gcRootServer								= NULL;			// First server
	bool				gbSemaphoreStackRecording					= false;		// Should the semaphore lock/unlock stack be recorded
	SList*				gsRootSemaphoreStack						= NULL;			// Holds semaphore stack traversal (when enabled)
	CRITICAL_SECTION	gcsStoreSemaphoreStack;										// A semaphore used to access the store-semaphore stack (if it's being recorded for debugging)


//////////
// Structures
//////
	// Each time we issue a ping request, it goes into a queue
	// Each time it's acknowledged, we update the last ping time in the associated process
	struct SPingQueue
	{
		SPingQueue*	next;										// Pointer to next ping in the queue
		u32			pingId;										// Unique ID for this ping
		SYSTEMTIME	timeOfRequest;								// When was this request made?
		u64			pingMs;										// Number of milliseconds when the ping was created
	};
	//////////
	//
	// The parcelForBind structure is used to send a message to the bound hwnd, or for messages in
	// the message queue to be polled.
	//
	//////////
	struct SParcelDelivery
	{
	//////////
	//
	// All in hexadecimal (the pipe signs are for visual delineation):
	// 00000000|00000000|00000000|00000000|00000000|00000000|00000000.00000000|00000000.00000000|messageType|content
	// 
	// 00000000:Length
	// 00000000:SHA1-32 of Length, From, To, and the 00000000.00000000 portions of message type and content
	// 00000000:From
	// 00000000:To
	// 00000000:Value
	// 00000000:Extra Value
	// 00000000.00000000:Length of message type, SHA1-32 of message type text
	// 00000000.00000000:Length of content, SHA1-32 of content
	// 00000000:SHA1-32 of entire message from 00000000 in Length to last byte of content
	//
	//////
		u32			totalMessageLength;							// 00000000:Length
		u32			sha1_32_lftve_mt_c;							// 00000000:SHA1-32 of Length, From, To, and the 00000000.00000000 portions of message type and content
		u32			fromId;										// 00000000:From
		u32			toId;										// 00000000:To
		u32			nValue;										// 00000000:Value
		u32			nExtra;										// 00000000:Extra value
		u32			messageTypeLength;							// 00000000.00000000:Length of message type, SHA1-32 of message type text
		u32			messageTypeSha1_32;							// 
		u32			contentLength;								// 00000000.00000000:Length of content, SHA1-32 of content
		u32			contentLengthSha1_32;						// 
		u32			sha1_32_all;								// 00000000:SHA1-32 of entire message from 00000000 in totalMessageLength to last byte of content

		// These are appended based on their messageTypeLength and contentLength components immediately after the above in the message transferred through the named pipe
		u8*			messageType;								// The actual message type text, such as "mail", "mail encrypted", "general message", etc.
		u8*			content;									// The actual content, which is entirely dependent upon what the message type is
	};

	struct SParcel
	{
		SParcel*	next;										// Pointer to next mailbag entry in the chain
		u32			uniqueId;									// Unique mail id number
		u32			remoteMailId;								// The mail id used by the remote app for mail sent to us (we use our own uniqueId, but this is their uniqueId)
		bool		encrypted;									// Is this mail encrypted?

		// Stored data for this entry
		u8*			data;										// Pointer to start of data
		u32			dataLength;									// Length of the data there
	};

	struct SMsgQueue
	{
		SMsgQueue*	next;										// Pointer to the next message in the queue
		u32			number;										// The message that was received
		u32			extra;										// The tnExtra number originally sent
		u32			mailId;										// The tnMailId number if there was an attached text mail
	};

	// A singleton, no link list
	struct SPipe
	{
		int			error;										// If the handleRead failed to open, the error flag is raised, otherwise 0
		u32			handleRead;									// Pipe read handle after being created
		u32			handleWrite;								// Pipe write handle after being created
		u8*			name;										// Name of the pipe in use
		u32			nameLength;									// Length of the pipe name as allocated

		// Information needed by windows to create/connect to the pipe
		SECURITY_ATTRIBUTES sa;									// Security attributes used to create the pipe
	};

	// Application process
	struct SAppProc
	{
		SAppProc*	next;										// Pointer to next process in the chain
		u32			remoteId;										// Application ID for this process
		u32			procId;										// The ID of the launched process
		DWORD		threadId;									// The id of the thread running this process
		HANDLE		threadHandle;								// The handle for this thread
		u32			status;										// See const.h for _STATUS_* constants
		bool		isRunning;									// Set to true initially, when the WMRP_TERMINATE message is received, or we self-terminat, goes false
		bool		wasSpawned;									// Set to true if rp_exec_connect() was used, set to false if rp_exec_spawn_thread() was used

		// A semaphore to lock access to items related to this structure
		CRITICAL_SECTION	cs_mail;							// Used for low-level mail operations
		CRITICAL_SECTION	cs_msgQueue;						// Used for low-level message queue operations
		CRITICAL_SECTION	cs_pipe;							// Used for low-level pipe operations
		CRITICAL_SECTION	cs_generalMessage;					// Used for general messages

		// Ping requests
		SPingQueue*	pingActive;
		u32			pingLastStatus;								// See the const _PING_* constants in const.h
		f32			pingLastSeconds;							// How many seconds since the last ping was acknowledged?
		u32			pingAttempts;								// Each time we request a ping it's incremented, each time we get a response it's decremented
		UINT_PTR	pingTimer;									// Ping timer

		// AppId and mail slots
		SParcel*	mailbag;									// Incoming mail for this process

		// Startup parameters
		u32			mailId_cmdLine;								// Full command line
		u32			mailId_params;								// The parameters to be transferred
		u32			mailId_identity;							// Identity token (used by the remote to validate we are who we say we are)
		u32			mailId_pipe;								// Name of the named pipe to create for this instance/process

		// Data for communicating back and forth
		SPipe*		pipe;										// Two-way communication pipe between us and the remote process

		// Message window
		u32			hwndLocal;									// Our message window that the remote process sends stuff to
		u32			hwndRemote;									// Message window we use to send messages to remote
		u32			hwndBound;									// The VFP form to notify on incoming messages (or 0 if not used)
		SMsgQueue*	firstMsg;									// Message queue is used if hwndBind was 0 (app must call 
	};

	struct SThreadParams
	{
		HANDLE			hthread;			// Handle to the thread
		u32				threadId;			// App-assigned ID for the thread
		u32				retVal;				// Return value for the thread

		void*			extra;				// Extra information to transfer
		void*			extra2;				// Additional extra information to transfer
		void*			extra3;				// Additional extra information to transfer

		// Used for CliServ processing
		CCSCommon*		cs;					// The root CCliServ object
		CClient*		client;				// Stores the client
		CServer*		server;				// If this is a server client, then this value will be non-null

		// Used for SHA1 processing
//		SSha1*			sha1Engine;			// The SHA1 engine used for this thread
	};

	struct SConnInfo
	{
		sockaddr_in		address;			// Address
		u32				addressLength;		// Length of the address name, returned from accept() function
		hostent*		host;				// Host name data
		s32				socket;				// Socket number
		u32				portnum;			// Port number
	};

	// Every message contains this header
	struct SCommHeader
	{
		u16				bytesOfData;		// Number of bytes following this header for this part of the message
		u32				transactionId;		// A unique transaction id number
		u32				thisBlock;			// The number for this block in the chain
		u32				maxBlocks;			// Number of blocks for this item
		union {
			u32			crc32;				// A simple CRC-32 calculation of all bytes in the block (used only initially when sending, this field becomes freed up then after acknowledging CRC32 is okay)
			u32			receivedBlocks;		// Number of valid blocks received so far (when receiving into partial read commQueue)
			u32			ackBlocks;			// The number of blocks that have been acknowledged (after sending in sent-ack commQueue)
		};
		s8				ieIdentifier;		// Internal or External message (internal are CliServ generated, external are user messages)
		s8				command2[2];		// A 2-byte command, one of PG, RS, RQ, FL, AK, MA or UT for ping, resend, request, fill, acknowledge and mass acknowledge (acknowledges many receipts at the same time) and user transmission (see const.h's cgc* string definitions)
		s8				command9[9];		// A 9-byte additional / extra command sequence used if needed, and made available "external" messaging (ieIdentifier above is "E")
		union {
			u16			crc16;				// A simple CRC-16 calculation of all bytes in the header, except this 2-byte field
			u16			ackSent;			// 1-yes, 0-no
		};
		// Total: 32 bytes
	};

	// Messages come in parts, and they are not deleted until they are received
	struct SCommPart
	{
		SCommPart*		next;				// Next part in the comm chain
		SCommPart*		prev;				// Messages can come in out of order, and this is used to order them before decoding.

		SCommHeader		header;				// Header sent / received for this part
		s8*				data;				// Data which was sent or received after the header
		u32				dataLength;			// Length of data block

		// Used for the watchdog
		SYSTEMTIME		sendTime;			// Time this part was received
		u32				retryCount;			// Number of times this part has been retried
		// Note:  Look to header.ackSent to see if this part has been acknowledged
	};

	// Items in the COMM queue, either incoming (receive) or outgoing (send),
	// or after it's been fully received it goes into the "valid message" queue
	struct SCommQueue
	{
		SCommQueue*		next;				// Pointer to next entry in the comm queue
		SCommQueue*		prev;				// Pointer to prev entry in the comm queue chain

		SCommHeader		header;				// First header used by originator
		SYSTEMTIME		sendTime;			// Start time of this comm queue (used to determine resend requests)
		SYSTEMTIME		lastReceivedTime;	// Time of the last received item (may be the entire message, or if in multiple blocks, time of the last received item)
		SCommPart*		firstPart;			// Messages are sent in parts of a specified size (header.

		// Used for special sending (resends of prior sent data)
		bool			leaveOutOfSecondCommQueue; // Should this item be left out of the unack commQueue after being sent?

		// Used for received internal process requests
		SYSTEMTIME		startProcessTime;	// Start time this comm queue item began processing (used for watchdog kill / timeout)
		SThreadParams	params;				// What thread is handling this item?
	};

	struct SWatchdog
	{
		SWatchdog*		next;				// Pointer to next entry in the watchdog chain

		SThreadParams	threadData;			// Data about this thread
		SCommQueue**	cqRoot;				// The root of the CommQueue to remove cq from its list
		SCommQueue*		cq;					// The actual CommQueue object this item relates to
	};

/////////
// Used generically to hold items, a simple link-list with up to four items.
// In use, items one and two can be searched to find three and four.
/////
	struct SList
	{
		SList*		next;				// The next item in the chain
		u32			referenceCount;		// Number of times this item was referenced

		s8*			item1;				// Storage item #1
		union {
			f32		item1f32;			// Item #1 as f32
			u32		item1Length;		// Length of item #1
		};

		s8*			item2;				// Storage item #2
		union {
			f32		item2f32;			// Item #2 as f32
			u32		item2Length;		// Length of item #2
		};

		s8*			item3;				// Storage item #3
		union {
			f32		item3f32;			// Item #3 as f32
			u32		item3Length;		// Length of item #3
		};

		s8*			item4;				// Storage item #4
		union {
			f32		item4f32;			// Item #4 as f32
			u32		item4Length;		// Length of item #4
		};


		// Instance meta data
		s8*			meta;
		union {
			f32		metaf32;
			u32		metaLength;
		};
	};


//////////
// Forward declarations
//////
	// Called once
	void				cliserv_initialize							(void);

	// Launch client or server
	CClient*			cliserv_client_launch						(u32 tnHwndCallback, s8* tcRemoteIpAddressOrHostName, u32 tnRemoteIpAddressOrHostNameLength, s8* tcLocalIpAddress15, u32 tnPortNumber);
	CServer*			cliserv_server_launch						(u32 tnHwndCallback, s8* tcLocalIpAddress15, u32 tnPortNumber);

	void				iStoreSemaphoreStack						(s8* tcLocation, s8* tcId1, s8* tcId2);

	void				iProcessInternalRequest						(SThreadParams* stp);
	SCommQueue*			iCreateCommQueue							(s8* tcCommand2, s8* tcCommand9, s8 ieIdentifier, u32 tnTransactionId);
	u32					iGetCommQueueLength							(SCommQueue* cq);
	u32					iCreateMessageParts							(CClient* cc, SCommQueue* cq, s8* tcData, u32 tnDataLength, u32 tnBlockSize);
	void				iAppendObjectToCommQueue					(SCommQueue** root, SCommQueue* cqNew);
	bool				iDetachObjectFromCommQueue					(SCommQueue** root, SCommQueue* cqDetach);
	bool				iDeleteCommQueueObject						(SCommQueue* cqDelete);
	bool				iDeleteCommPartObject						(SCommPart* cpDelete);
	u32					iAppendCommQueueToUserReadBuffer			(CCSCommon* cs, SCommQueue* cq);

	DWORD WINAPI		iReader										(LPVOID param);		// Runs in separate thread
	DWORD WINAPI		iSender										(LPVOID param);		// Runs in separate thread
	DWORD WINAPI		iPinger										(LPVOID param);		// Runs in separate thread
	DWORD WINAPI		iProcess									(LPVOID param);		// Runs in separate thread
	DWORD WINAPI		iWatchdog									(LPVOID param);		// Runs in separate thread
	DWORD WINAPI		iServerListener								(LPVOID param);		// Runs in separate thread (server.h)

	void				iAppendLabelColonValueString				(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u8* tcValue, u32 tnValueLength);
	void				iAppendLabelColonValueInteger				(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u32 tnValue);
	void				iAppendLabelColonValueFloat					(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, f32 tfValue, u32 tnIntegers, u32 tnDecimals);
	void				iPrependLabelColonValueString				(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u8* tcValue, u32 tnValueLength);
	void				iPrependLabelColonValueInteger				(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u32 tnValue);
	void				iPrependLabelColonValueFloat				(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, f32 tfValue, u32 tnIntegers, u32 tnDecimals);
	void				iGetLabelColonValueString					(u8* tcSource, u32 tnSourceLength, u8* tcLabel, u32 tnLabelLength, u8** tcText, u32** tnTextLength);
	void				iGetLabelColonValueInteger					(u8* tcSource, u32 tnSourceLength, u8* tcLabel, u32 tnLabelLength, u32** tnValue);
	void				iGetLabelColonValueFloat					(u8* tcSource, u32 tnSourceLength, u8* tcLabel, u32 tnLabelLength, f32** tfValue);
	bool				iFindLine									(u8* tcSource, u32 tnSourceLength, u8* tcLabelSearch, u32 tnLabelSearchLength, u8** tcLabelFound, u32* tnLabelFoundLength, u8** tcValueFound, u32* tnValueFoundLength);
	u32					iiGet_u32									(u8* tcNumber, bool tlSkipLeadingWhitespaces);
	u8*					iReadFromPipe								(SAppProc* tsProc, u32 tnReadSize, u32* tnActuallyRead);
	u32					iStowMail									(SAppProc* tsProc, u8* tcText, u32 tnTextLength, SParcel** tsMail, bool tlIsEncrypted);
	u32					iStowMailFromCommQueue						(SAppProc* tsProc, CCSCommon* cs, SCommQueue* cq, SParcel** tsMail, bool tlIsEncrypted);
	SParcel*			iAppendMail									(SParcel** mailbagRoot, u8* tcText,  u32 tnTextLength, bool tlCopyString, bool tlIsEncrypted);
	SParcel*			iAppendMailByLength							(SParcel** mailbagRoot,              u32 tnTextLength, bool tlIsEncrypted);
	SParcel*			iFindMail									(u32 tnMailId);
	SParcel*			iFindMailInProc								(SAppProc* tsProc, u32 tnMailId);
	SParcel*			iReceiveAndStowMail							(SAppProc* tsProc, u32 tnMailMessageSize, u32 tnMailMessageId);
	u32					iDeleteMailParcel							(u32 tnMailId);
	s32					iValidateBoundEmail							(SParcel* tsMail, SParcelDelivery* tsBindMail);
	u32					iGetNextUniqueId							(void);
	u32					iComputeSha1_32								(u8* tcData, u32 tnDataLength);
	u8					iSwapBits									(u8 tcChar);
	u32					iShiftLeft									(u32 tnValue, u32 tnBits);
	bool				iValidateParcelDeliverySha1s				(SParcelDelivery* tsPd);
	bool				iValidateParcelDeliverylSha1_32_lftve_mt_c	(SParcelDelivery* tsPd);
	bool				iValidateParcelDeliverySha1_32_messageType	(SParcelDelivery* tsPd);
	bool				iValidateParcelDeliverySha1_32_content		(SParcelDelivery* tsPd);
	bool				iValidateParcelDeliverySha1_32_all			(SParcelDelivery* tsPd);
	bool				iEqualEqual									(u8* tcLeft, u32 tnLeftLength, u8* tcRight, u32 tnRightLength);
	u32					iComputeCrc32								(s8* tcData, u32 tnDataLength);
	u16					iComputeCrc16								(s8* tcData, u32 tnDataLength);
	u32					iComputeCrc32_1								(s8* tcData, u32 tnDataLength);
	u32					iComputeCrc32_2								(s8* tcData, u32 tnDataLength);
	u32					iComputeCrc32_3								(s8* tcData, u32 tnDataLength);
	u32					iComputeCrc32_4								(s8* tcData, u32 tnDataLength);
	u32					iComputeCrc32_5								(s8* tcData, u32 tnDataLength);
	s8*					iDuplicateString							(s8* tcData, s32 tnDataLength, bool tlIncludeTrailingNull, bool tlTrimLeadingSpaces = false, bool tlTrimTrailingSpaces = false);
	u8*					iDuplicateString							(u8* tcData, s32 tnDataLength, bool tlIncludeTrailingNull, bool tlTrimLeadingSpaces = false, bool tlTrimTrailingSpaces = false);
	void				iCopyString									(u8** tcDst, u32* tnDstLength, u8* tcSrc, u32 tnSrcLength, bool tlNullTerminate);

	// cliserv_sup.cpp
	SAppProc*			iCreateNewSProcess							(SAppProc** root);
	u64					iGetSystemtimeDiffInMilliseconds			(SYSTEMTIME* newestTime, SYSTEMTIME* oldestTime);
	void				iComputeSystemTimeMillieconds				(SYSTEMTIME* time, u64* ms);
	u32					iGetMonthStartDayOfYear						(u32 month, u32 year);
	void				iStoreCurrentTime							(SYSTEMTIME* tp);
	bool				iIsTimeEmpty								(SYSTEMTIME* tp);

	u32					iAddToGenericList							(SList** tsListRoot,	s8* tcItem1,	u32 tnItem1Length, 
																							s8* tcItem2,	u32 tnItem2Length,
																							s8* tcItem3,	u32 tnItem3Length,
																							s8* tcItem4,	u32 tnItem4Length,
																							s8* tcMetaData,	u32 tnMetaDataLength,
																							bool tlNullLengthsAreData);

	u32					iAddToGenericListIfUnique					(SList** tsListRoot,	s8* tcItem1, u32 tnItem1Length,
																							s8* tcItem2, u32 tnItem2Length,
																							s8* tcItem3, u32 tnItem3Length,
																							s8* tcItem4, u32 tnItem4Length,
																							s8* tcMetaData, u32 tnMetaDataLength);
	
	SList*				iSearchGenericList							(SList* tsListRoot,		s8* tcItem1, u32 tnItem1Length, 
																							s8* tcItem2, u32 tnItem2Length,
																							s8* tcItem3, u32 tnItem3Length,
																							s8* tcItem4, u32 tnItem4Length);

	void				iDeleteGenericList							(SList** tsListRoot);
	bool				iIsNeedleInHaystack							(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	bool				iIsNeedleInHaystackCase						(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	bool				iIsNeedleInHaystack							(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart);
	bool				iIsNeedleInHaystackCase						(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart);
	bool				iIsCharacterInHaystack						(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool				iIsCharacterInHaystackCase					(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool				iIsCharacterInHaystackReversed				(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool				iIsCharacterInHaystackReversedCase			(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool				iDoesHaystackStartWithNeedle				(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	bool				iDoesHaystackStartWithNeedleCase			(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	s8					iLowerCharacter								(s8 ch);
	u32					iSkipWhitespaces							(s8* source, u32* offset, u32 maxLength);
	s32					iSendToIpAddress							(u8* tcVerb, u32 tnVerbLength, u8* tcCommand, u32 tnCommandLength, u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber);










//////////
// Common client/server class
//////
	class CCSCommon
	{
	public:
		CCSCommon(void);
		~CCSCommon(void);


		//////////
		// New message transfer by text
		//////
			u32				createCommQueueObjectFromBufferAndAddToToSendCommQueue		(CClient* cc, s8* tcData, u32 tnDataLength, cs8* tcInternalOrExternal);
			u32				iLowLevel__appendToSendQueueRaw								(             s8* tcData, u32 tnDataLength);
			u32				readFromReceivedQueue										(             s8* tcData, u32 tnDataLength, u32* tnIsThereMoreDataToRead);
			void			schedulePingRequestIfNeeded									(CClient* cc);



		//////////
		// Status queries
		//////
			u32				isOnline													(void);
			s8*				onlineStatus												(void);
			s8*				identity													(void);
			u32				bytesInReadQueue											(void);
			u32				bytesInSendQueue											(void);
			u32				totalBytesReadQueue											(void);
			u32				totalBytesPartial											(void);
			u32				totalBytesSendQueue											(void);


		//////////
		// Set identify as a client or server
		//////
			void			setThisInstanceAsClient										(SConnInfo* tsClient, s8* tcStatus);
			void			setThisInstanceAsServer										(SConnInfo* tsServer, s8* tcStatus);


		//////////
		// Client getters
		//////
			SConnInfo*		getClient													(void);
			sockaddr_in*	getClientIpAddress											(void);
			hostent*		getClientHosts												(void);
			u32				getClientSocket												(void);
			u32				getClientPortNum											(void);


		//////////
		// Server getters
		//////
			SConnInfo*		getServer													(void);
			sockaddr_in*	getServerIpAddress											(void);
			hostent*		getServerHosts												(void);
			u32				getServerSocket												(void);
			u32				getServerPortNum											(void);


		//////////
		// General Getters
		//////
			u32				getSocket													(void);
			u32				getPortNumber												(void);
		

		//////////
		// Read buffer stuff
		//////
			s8*				getReadBuffer												(void);
			u32				getReadBytes												(void);
			void			increaseTotalReadBytes										(u32 tnCount);
			s8*				increaseReadBufferSize										(u32 tnNumToAdd);
			bool			appendToUserReadBuffer										(s8* tcData, u32 tnDataLength);
		

		//////////
		// Send buffer stuff
		//////
			s8*				getSendBytesBuffer											(void);
			u32				getSendQueueBytes											(void);
			void			increaseTotalSendBytes										(u32 tnCount);
			s8*				increaseSendBufferSize										(u32 tnNumToAdd);
			void			resetSendQueueBuffer										(void);
			bool			appendToUserSendBuffer										(s8* tcData, u32 tnDataLength);


	//////////
	// Semaphore stuff
	//////
		//////////
		// Buffer
		//////
			// Read
			void			lockForReadBufferAccess										(s8* identifier1, s8* identifier2);
			bool			tryLockForReadBufferAccess									(s8* identifier1, s8* identifier2);
			void			unlockForReadBufferAccess									(s8* identifier1, s8* identifier2);
			// Send
			void			lockForSendBufferAccess										(s8* identifier1, s8* identifier2);
			void			unlockForSendBufferAccess									(s8* identifier1, s8* identifier2);

		//////////
		// commQueue
		//////
			// Read completed
			void			lockForCommQueueAccess										(s8* identifier1, s8* identifier2);
			bool			tryLockForCommQueueAccess									(s8* identifier1, s8* identifier2);
			void			unlockForCommQueueAccess									(s8* identifier1, s8* identifier2);

		//////////
		// Other
		//////
			// Watchdog
			void			lockForWatchdogAccess										(s8* identifier1, s8* identifier2);
			void			unlockForWatchdogAccess										(s8* identifier1, s8* identifier2);


		//////////
		// commQueue stuff
		//////
			bool			parsePartiallyReceivedCommQueueItems						(SThreadParams* stp);
			bool			parseNextReceivedCommQueueItem								(SThreadParams* stp);
			bool			parseSendCommQueueItems										(SThreadParams* stp);
			bool			resendUnackCommQueueItems									(SThreadParams* stp);
			void			resendCommQueuePart											(SCommQueue* cq, SCommPart* cp);
			void			sendCommQueueItem											(SCommQueue** rootFrom, SCommQueue** rootTo, SCommQueue* cq);
			bool			processAnyInternalCommands									(SThreadParams* stp);
			void			deleteProcessRequest										(SCommQueue** root, SCommQueue* cqToDelete);
			SCommQueue*		searchCommQueueForCommand									(SCommQueue*  root, s8* tcCommand2, s8* tcCommand9, u32 tnTransactionId);
			SCommQueue*		searchCommQueueForTransactionId								(SCommQueue*  root, u32 tnTransactionId);
			SCommQueue*		appendToPartiallyReceivedReadCommQueue						(SCommPart* cp);
			void			appendThisPartInSequence									(SCommQueue* cq, SCommPart* cpNew);
			SCommQueue*		createCommQueueObjectFromPart								(SCommPart* cp);
			SCommQueue*		createCommQueueObjectFromScratch							(CClient* cc, bool tlSetTransactionId);
			SCommQueue*		duplicateCommQueueObject									(SCommQueue* cq);
			void			sendAckBack /* LOL funny name, yes? Nyuck nyuck! */			(SCommPart* cp);
			void			sendPingBack												(SCommQueue* cp);
			void			sendPingRequest												(CClient* cc);
			void			acknowledgeCommQueuePart									(SCommQueue* cqAck);
			void			resendCommQueueBlock										(SCommQueue* cqBlock);


		//////////
		// commQueue getters
		//////
			SCommQueue*		getPartialCommQueueRead										(void)			{	return(m_firstPartialCommQueueRead);								}
			SCommQueue*		getCompletedCommQueueRead									(void)			{	return(m_firstCompletedCommQueueRead);								}
			SCommQueue*		getUnackCommQueueSend										(void)			{	return(m_firstUnackCommQueueSend);									}
			SCommQueue*		getCommQueueToSend											(void)			{	return(m_firstCommQueueToSend);										}


		//////////
		// commPart stuff
		//////
			SCommPart*		createMessagePart											(SCommHeader* ch, s8* tcData, u32 tnDataLength);
			SCommPart*		duplicateCommPartObject										(SCommPart* cp);


		//////////
		// Watchdog "callback" stuff (called from client's iWatchdog() thread)
		//////
			void			checkPartialReadCommQueueItemsForMissingParts				(void);


		//////////
		// Cliserv command functions
		//////
			void			createResendCommand											(SCommQueue*  cq, u32 tnBlock);
			SCommQueue*		createGenericRequestCommand									(CClient* cc, s8* tcCommand9, s8* tcData, u32 tnDataLength, u32* tnTransactionId);
// 			u32				createMsodWindowImageCommand								(s8* tcWindowTitle, u32 tnWindowTitleLength);
// 			u32				createMsodWindowDataCommand									(s8* tcWindowTitle, u32 tnWindowTitleLength, u32 tnFullFetch);
			CXml*			createCommonXmlCommandFramework								(CXml** xmlCliserv, CXml** xmlCommand, CXml** xmlCmdAttribute, s8* tcCmd, u32 tnCmdLength, s8* tcTag = NULL);
			u32				sendCliservDataToOther										(CCSCommon* cc, u8* tcData, u32 tnDataLength);



		//////////
		// ping interfaces
		//////
			void			setPingRequestTime											(SYSTEMTIME* st);
			void			setPingResponseTime											(SYSTEMTIME* st);
			f32				getLastPingTime												(void);
			f32				getAveragePingTime											(void);

		//////////
		// internal processing
		//////
			s8*				concatenatePartsData										(SCommQueue* cq, u32* tnLength);
			void			processRequest												(SCommQueue* cq, s8* tcData, u32 tnDataLength);
	static	bool			compareHosts												(hostent* host1, hostent* host2);


	private:
		// Status of connection
		u32					m_online;								// Are we up (bound to the socket, listening)?
		s8*					m_status;								// Current status in words
		s8*					m_identity;								// A visual cue used during debugging, identifying which cliserv identity this is
		bool				m_isServer;								// Is this cliserv instance a server?  If so, sends out pings every so often
		u32					m_socket;								// The socket we are reading from and writing to
		u32					m_portnum;								// Port number in use (server bound to, client sends to)

		// Ping information
		SYSTEMTIME			m_lastPingRequest;						// The last ping request sent to the other
		SYSTEMTIME			m_lastPingAck;							// The last ping response given from the other
		f64					m_totalPingTimes;						// The total of all ping times added together (in milliseconds)
		u32					m_totalPingCount;						// Number of pings issued

		// Semaphores
		CRITICAL_SECTION	m_readSemaphore;						// A semaphore used for recvs/reads to data queues
		CRITICAL_SECTION	m_sendSemaphore;						// A semaphore used for sends/writes from data queues
		CRITICAL_SECTION	m_commQueueSemaphore;					// A semaphore used to obtain completed items from the read queue
		CRITICAL_SECTION	m_watchdogSemaphore;					// A semaphore used to access items to process

		// For received bytes and not yet consumed by caller
		s8*					m_bufferRead;							// Holding bytes left to consume
		u32					m_bufferBytesToRead;					// Number of bytes ready to read
		u32					m_bufferTotalBytesRead;					// How many bytes total have been read?
		u32					m_totalBytesPartial;					// Total bytes we have partially received (when a large item comes in, it might take a while to receive it)
		SCommQueue*			m_firstPartialCommQueueRead;			// The first partial comm queue for lengthy items that aren't yet fully received, once received they are either processed internally, or send on to the user via m_queueRead
		SCommQueue*			m_firstCompletedCommQueueRead;			// Items appended to be received into the read queue

		// For internal items that have been received, and are waiting to be processed
		SCommQueue*			m_firstCommQueueToProcess;				// An internal command that was created, needing to be processed by the process queue

		// For to-send bytes not yet sent by server
		s8*					m_bufferSend;							// Holding bytes left to send
		u32					m_bufferBytesToSend;					// Number of bytes ready to write
		u32					m_bufferTotalBytesSent;					// How many bytes total have been sent?
		SCommQueue*			m_firstCommQueueToSend;					// Items appended ready to be injected into the send queue
		SCommQueue*			m_firstUnackCommQueueSend;			// The first send-complete comm queue item, still waiting for acknowledgment from receiver

		// Watchdog information
		SWatchdog*			m_firstWatchdog;						// Pointer to the first thing the watchdog knows about

		// Connection information for both points
		SConnInfo*			m_clientInfo;							// Client connection information
		SConnInfo*			m_serverInfo;							// Server connection information
	};
