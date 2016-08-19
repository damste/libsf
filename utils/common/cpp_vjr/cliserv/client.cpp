//////////
//
// /libsf/utils/common/cpp/cliserv/client.cpp
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
// Create the client and its related cliserv object
//
//////
	CClient::CClient(void)	:	m_next				(NULL),
								m_blockSize			(4096),
								m_nextTransactionId	(0x10203040)
	{
		m_threadRead		= (SThreadParams*)malloc(sizeof(SThreadParams));
		m_threadWrite		= (SThreadParams*)malloc(sizeof(SThreadParams));
		m_threadPing		= (SThreadParams*)malloc(sizeof(SThreadParams));
		m_threadProcess		= (SThreadParams*)malloc(sizeof(SThreadParams));
		m_threadWatchdog	= (SThreadParams*)malloc(sizeof(SThreadParams));

		memset(m_threadRead,		0, sizeof(SThreadParams));
		memset(m_threadWrite,		0, sizeof(SThreadParams));
		memset(m_threadPing,		0, sizeof(SThreadParams));
		memset(m_threadProcess,		0, sizeof(SThreadParams));
		memset(m_threadWatchdog,	0, sizeof(SThreadParams));

		m_cscommon = new CCSCommon();
	}




//////////
//
// Destructor
//
//////
	CClient::~CClient(void)
	{
		// Kill the read/write threads
		endReadWritePingProcessThreads();

		// Delete the cliserv
		if (m_cscommon)
			delete m_cscommon;
	}




//////////
//
// Connects to the remote server by ip address and port number.
//
// This is virtually identical to CServer::bindToPort(), but the client connects
// to the remote socket, rather than binding to the port (for listening).
//
//////
	u32 CClient::connectToRemoteServer(s8* tcServerIpOrHostName, u32 tnPortNumber)
	{
		u32			lnResult, lnI;
		SConnInfo*	sci;
		s8			clientName[80];
		in_addr*	addr;


		// Create our connection structure
		sci = (SConnInfo*)malloc(sizeof(SConnInfo));
		if (sci)
		{
			// Initialize or connection info structure
			memset(sci, 0, sizeof(SConnInfo));

			// 

			// Create a socket for this connection
			sci->socket		= socket(AF_INET, SOCK_STREAM, 0);
			lnResult		= gethostname(clientName, sizeof(clientName));
			if (sci->socket >= 0 && lnResult != SOCKET_ERROR)
			{
				// Bind this server to the port
				sci->address.sin_family			= AF_INET;
				sci->address.sin_addr.s_addr	= INADDR_ANY;
				sci->address.sin_port			= htons((u_short)tnPortNumber);
				sci->portnum					= tnPortNumber;

				// Store the server name and ip address
				sci->host						= gethostbyname(tcServerIpOrHostName);
				if (sci->host)
				{
					// We're looking for any addresses that are not 127.x.x.x
					for (lnI = 0; sci->host->h_addr_list[lnI] != 0; lnI++)
					{
						addr = (in_addr*)sci->host->h_addr_list[lnI];
						if (addr->S_un.S_un_b.s_b1 != 127)
						{
							// This is the non-127.x.x.x address
							// Store it
							memcpy(&sci->address.sin_addr.S_un, &addr->S_un, sizeof(addr->S_un));
							break;
						}
					}
				}

				// Connect to the socket
				lnResult = connect(sci->socket, (sockaddr*)&sci->address, sizeof(sockaddr_in));
				if (lnResult == -1)
				{
					// Failure connecting
					free(sci);
					return(0);
				}
				// If we get here, we're bound to the port
				// And we have our SConnInfo structure built
				cscommon()->setThisInstanceAsClient(sci, "Connected");
				free(sci);

				// We're good
				return(tnPortNumber);
			}
		}
		// Error if we get here
		return(0);
	}




//////////
//
// Spawns the read/write threads for handling data on a given socket
// (the client socket, as it was created as being an accepted socket
// from a server listener, or being launched explicitly as a client
// connected to a remote server).
//
// If it returns 0, was a failure.
// 1 indicates success.
//
//////
	u32 CClient::beginReadWritePingProcessThreads(CServer* server)
	{
		// Create a new thread to begin reading
		memset(m_threadRead, 0, sizeof(SThreadParams));
		m_threadRead->extra			= this;
		m_threadRead->client		= this;
		m_threadRead->cs			= cscommon();
		m_threadRead->server		= server;
		m_threadRead->hthread		= CreateThread(NULL, NULL, iReader, m_threadRead, NULL, &m_threadRead->threadId);

		// Create a new thread to begin writing
		memset(m_threadWrite, 0, sizeof(SThreadParams));
		m_threadWrite->extra		= this;
		m_threadWrite->client		= this;
		m_threadWrite->cs			= cscommon();
		m_threadWrite->server		= server;
		m_threadWrite->hthread		= CreateThread(NULL, NULL, iSender, m_threadWrite, NULL, &m_threadWrite->threadId);

		// Create a new thread for periodic pinging
		memset(m_threadPing, 0, sizeof(SThreadParams));
		m_threadPing->extra			= this;
		m_threadPing->client		= this;
		m_threadPing->cs			= cscommon();
		m_threadPing->server		= server;
		m_threadPing->hthread		= CreateThread(NULL, NULL, iPinger, m_threadPing, NULL, &m_threadPing->threadId);

		// Create a new thread to process received internal requests
		memset(m_threadProcess, 0, sizeof(SThreadParams));
		m_threadProcess->extra		= this;
		m_threadProcess->client		= this;
		m_threadProcess->cs			= cscommon();
		m_threadProcess->server		= server;
		m_threadProcess->hthread	= CreateThread(NULL, NULL, iProcess, m_threadProcess, NULL, &m_threadProcess->threadId);

		// Create a new thread to process watchdog enforcements (when a newly spawned thread times out, it is killed with extreme prejudice)
		memset(m_threadWatchdog, 0, sizeof(SThreadParams));
		m_threadWatchdog->extra		= this;
		m_threadWatchdog->client	= this;
		m_threadWatchdog->cs		= cscommon();
		m_threadWatchdog->server	= server;
		m_threadWatchdog->hthread	= CreateThread(NULL, NULL, iWatchdog, m_threadWatchdog, NULL, &m_threadWatchdog->threadId);

		// If any hthread is NULL, failure, otherwise success
		return(	(u32)m_threadRead->hthread		? 1 : 0 & 
				(u32)m_threadWrite->hthread		? 1 : 0 & 
				(u32)m_threadPing->hthread		? 1 : 0 & 
				(u32)m_threadProcess->hthread	? 1 : 0 & 
				(u32)m_threadWatchdog->hthread	? 1 : 0);
	}




//////////
//
// Terminate the read/write threads for this client
//
//////
	void CClient::endReadWritePingProcessThreads(void)
	{
		if (m_threadRead->hthread)
			TerminateThread(m_threadRead->hthread, 0);

		if (m_threadWrite->hthread)
			TerminateThread(m_threadWrite->hthread, 0);

		if (m_threadPing->hthread)
			TerminateThread(m_threadPing->hthread, 0);

		if (m_threadProcess->hthread)
			TerminateThread(m_threadProcess->hthread, 0);

		if (m_threadWatchdog->hthread)
			TerminateThread(m_threadWatchdog->hthread, 0);
	}





//////////
//
// Return the client's (local machine) ip address or machine name
//
//////
	void CClient::getClientIpAddress(s8* tcLocalIpAddress15, u32 tnLength)
	{
		SOCKADDR_IN*	sai;
		s8				buffer[16];


		// Grab the IP address in sockaddr_in form
		sai = m_cscommon->getClientIpAddress();
		if (!sai)
		{
			// No information
			memcpy(buffer, "0.0.0.0        ", 15);

		} else {
			// It's available, so we convert it to standard text notation
			sprintf(buffer, "%u.%u.%u.%u",	(u32)sai->sin_addr.S_un.S_un_b.s_b1,
											(u32)sai->sin_addr.S_un.S_un_b.s_b2,
											(u32)sai->sin_addr.S_un.S_un_b.s_b3,
											(u32)sai->sin_addr.S_un.S_un_b.s_b4);
		}
		memcpy(tcLocalIpAddress15, buffer, 15);
	}




//////////
//
// Send the server's callback hwnd a message.
//
//////
	int CClient::postHwndCallbackMessage(u32 msg, u32 w, u32 l)
	{
		if (m_hwndCallback != 0)		return((PostMessage((HWND)m_hwndCallback, msg, w, l) == 0) ? -1 : 0);
		else							return(-1);
	}
