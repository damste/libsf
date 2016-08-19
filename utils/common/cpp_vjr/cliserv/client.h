//////////
//
// /libsf/utils/common/cpp/cliserv/client.h
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




//////////
//
// Client-specific code
//
//////
	//class CClient;
	class CServer;
	class CCSCommon;
	struct SThreadParams;

	class CClient
	{
	public:
		CClient(void);
		~CClient(void);


		// Client operations
		u32				connectToRemoteServer						(s8* tcServerIpOrHostName, u32 tnPortNumber);
		u32				beginReadWritePingProcessThreads			(CServer* server);
		void			endReadWritePingProcessThreads				(void);

		// Getter for the ip address or machine name
		CCSCommon*		cscommon									(void)						{	return(m_cscommon);						}
		void			getClientIpAddress							(s8* tcLocalIpAddress15, u32 tnLength);
		u32				getClientPortNumber							(void)						{	return(m_cscommon->getClientPortNum());	}
		u32				getBlockSize								(void)						{	return(m_blockSize);					}
		u32				getNextTransactionId						(void)						{	return(m_nextTransactionId++);			}

		// Client information
		void			setHwndCallback								(u32 tnHwnd)				{	m_hwndCallback	= tnHwnd;				}

		// Basic tasks
		int				postHwndCallbackMessage						(u32 msg, u32 w, u32 l);


	public:
		CClient*		m_next;						// Pointer to the next CClient entry (if any)

	private:
		CCSCommon*		m_cscommon;					// This client's context
		u32				m_hwndCallback;				// The callback hwnd (if any)
		u32				m_blockSize;				// Size of data blocks transmitted from this client (default = 4096)
		u32				m_nextTransactionId;		// The next transaction id that will be used

		SThreadParams*	m_threadRead;				// read (receive) data thread
		SThreadParams*	m_threadWrite;				// write (send) data thread
		SThreadParams*	m_threadPing;				// ping thread which schedules a ping every so often
		SThreadParams*	m_threadProcess;			// process received internal requests thread, sends responses
		SThreadParams*	m_threadWatchdog;			// Watchdog, looks out for threads which have frozen for whatever reason
	};
