//////////
//
// /libsf/utils/common/cpp/cliserv/server.h
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
// Server-specific code
//
//////
	class CClient;
	//class CServer;
	class CCSCommon;
	struct SThreadParams;

	class CServer
	{
	public:
		CServer();
		~CServer(void);


		// Basic server operations
		u32				bindToPort								(u32 tnPortNumber);
		u32				beginListening							(void);
		void			endListeningWatchdog					(void);
		void			endClients								(void);


		// Append the specified client
		void			appendClient							(CClient* clientNew);


		// Getter for the ip address or machine name
		CCSCommon*		cscommon								(void)						{	return(m_cscommon);						}
		void			getServerIpAddress						(s8* tcLocalIpAddress15, u32 tnLength);
		u32				getServerPortNumber						(void)						{	return(m_cscommon->getServerPortNum());	}


		// Client information
		u32				isAcceptingClients						(void)						{	return(m_acceptClients);				}
		void			setAcceptingClients						(void)						{	m_acceptClients = 1;					}
		void			setNotAcceptingClients					(void)						{	m_acceptClients = 0;					}
		void			setHwndCallback							(u32 tnHwnd)				{	m_hwndCallback	= tnHwnd;				}
		CClient*		firstClient								(void)						{	return(m_firstClient);					}

		// Basic tasks
		int				postHwndCallbackMessage					(u32 msg, u32 w, u32 l);


	public:
		CServer*		m_next;						// Pointer to the next CServer entry (if any)

	private:
		u32				m_acceptClients;			// Are we currently accepting new clients?
		u32				m_hwndCallback;				// The callback hwnd (if any)
		CClient*		m_firstClient;				// First client this server is connected to
		CCSCommon*		m_cscommon;					// This server's context

		SThreadParams*	m_threadListen;				// listening thread (accepting new sockets)
	};
