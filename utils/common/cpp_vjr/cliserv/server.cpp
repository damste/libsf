//////////
//
// /libsf/utils/common/cpp/cliserv/server.cpp
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
// Create the new server instance
//
//////
	CServer::CServer() :	m_acceptClients	(1),
							m_hwndCallback	(0),
							m_firstClient	(NULL),
							m_next			(NULL)
	{
		m_threadListen = (SThreadParams*)malloc(sizeof(SThreadParams));
		memset(m_threadListen, 0, sizeof(SThreadParams));

		m_cscommon = new CCSCommon();
	}




//////////
//
// Destructor
//
//////
	CServer::~CServer(void)
	{
		// End any connected client connections
		endClients();

		// Turn off the listening thread
		endListeningWatchdog();
	}




//////////
//
// Return the server's (local machine) ip address or machine name
//
//////
	void CServer::getServerIpAddress(s8* tcLocalIpAddress15, u32 tnLength)
	{
		SOCKADDR_IN*	sai;
		s8				buffer[16];


		// Identify if we have a valid ip address
		sai = m_cscommon->getServerIpAddress();
		if (!sai)
		{
			// No information
			memcpy(buffer, "0.0.0.0        ", 15);

		} else {
			// It's available, so we write it
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
	int CServer::postHwndCallbackMessage(u32 msg, u32 w, u32 l)
	{
		if (m_hwndCallback != 0)		return((PostMessage((HWND)m_hwndCallback, msg, w, l) == 0) ? -1 : 0);
		else							return(-1);
	}




//////////
//
// Bind to the specified port
//
//////
	u32 CServer::bindToPort(u32 tnPortNumber)
	{
		u32			lnResult, lnI;
		SConnInfo*	sci;
		s8			serverName[80];
		in_addr*	addr;


		// Create our connection structure
		sci = (SConnInfo*)malloc(sizeof(SConnInfo));
		if (sci)
		{
			// Initialize or connection info structure
			memset(sci, 0, sizeof(SConnInfo));

			// Create a socket for this connection
			sci->socket		= socket(AF_INET, SOCK_STREAM, 0);
			lnResult		= gethostname(serverName, sizeof(serverName));
			if (sci->socket >= 0 && lnResult != SOCKET_ERROR)
			{
				// Bind this server to the port
				sci->address.sin_family			= AF_INET;
				sci->address.sin_addr.s_addr	= INADDR_ANY;
				sci->address.sin_port			= htons((u_short)tnPortNumber);
				sci->portnum					= tnPortNumber;

				// Store the server name and ip address
				sci->host						= gethostbyname(serverName);
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

				// Bind to the socket
				lnResult = bind(sci->socket, (sockaddr*)&sci->address, sizeof(sockaddr_in));
				if (lnResult == -1)
				{
					// Failure binding
					free(sci);
					return(0);
				}
				// If we get here, we're bound to the port
				// And we have our SConnInfo structure built
				cscommon()->setThisInstanceAsServer(sci, "Bound");
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
// Spawns a thread for this port to begin accepting clients and spawning
// connections to read/write from them.
//
//////
	u32 CServer::beginListening(void)
	{
		// Create a new thread to begin listening
		memset(m_threadListen, 0, sizeof(SThreadParams));
		m_threadListen->extra	= this;
		m_threadListen->cs		= cscommon();
		m_threadListen->hthread = CreateThread(NULL, NULL, iServerListener, m_threadListen, NULL, &m_threadListen->threadId);

		// If any hthread is NULL, failure, otherwise success
		return(	(u32)m_threadListen->hthread ? 1 : 0);
	}




//////////
//
// Ends the listening and watchdog threads.
//
// Note:  For this server, there may have been many spawned clients connected.
//        they need to be cleaned up elsewhere.
//
//////
	void CServer::endListeningWatchdog(void)
	{
		// Forcibly shut down the watchdog thread (also with extreme prejudice)
		if (m_threadListen->hthread)
		{
			// Shut down our sockets for send/recv
			shutdown(m_cscommon->getSocket(), SD_BOTH);
			closesocket(m_cscommon->getSocket());

			// Wait 1/10th second for everything to politely disconnect
			Sleep(100);

			// Forcibly shut down the listener thread (with extreme prejudice)
			TerminateThread(m_threadListen->hthread, 0);
		}
	}




//////////
//
// End this server's connected clients (which are actually its read/write threads
// for all connections made to the server)
//
//////
	void CServer::endClients(void)
	{
		CClient*	cliNext;
		CClient*	cli;


		// See if there are any clients to free (should always be at least one, because this server uses a CClient object for its reading/writing
		cli = m_firstClient;
		while (cli)
		{
			cliNext = cli->m_next;			// Get the next client
			delete cli;						// Delete this client
			cli = cliNext;					// Move to next client in the chain
		}
	}




//////////
//
// Append this client to the list of known clients for this server
//
//////
	void CServer::appendClient(CClient* clientNew)
	{
		CClient* client;


		if (!m_firstClient)
		{
			// This is the first client
			m_firstClient = clientNew;

		} else {
			// We have to append to the chain
			client = m_firstClient;
			while (client->m_next)
				client = client->m_next;
			client->m_next = clientNew;
		}
	}




//////////
//
// Static server listener thread used by multiple potential servers
// running simultaneously.
//
//////
	DWORD WINAPI iServerListener(LPVOID param)
	{
		u32				lnSocket, lnMailId;
		SThreadParams*	stp;
		CServer*		server;
		CClient*		clientNew;
		CCSCommon*		cs;
		SConnInfo		sci;
		hostent*		host;
		u8*				lcMail;
		u32				lnMailLength;
		in_addr*		ip;
		SParcel*		parcel;
		s8				buffer[256];


		// Grab our parameters
		stp		= (SThreadParams*)param;
		server	= (CServer*)stp->extra;
		cs		= stp->cs;


		// Begin listening
		lnSocket = cs->getSocket();
		listen(lnSocket, 5);


		///////////
		// Enter a permanent loop, constantly listening for new connections, receiving them when made
		// Thread suspends on acceptClient() until a client contacts this computer
		//////
			while (1)
			{
				//////////
				// Store connection, as well as populate name (either IP address, or local host name)
				//////
					memcpy(&sci, cs->getServer(), sizeof(SConnInfo));
					sci.addressLength	= sizeof(sci.address);
					sci.socket			= accept(lnSocket, (sockaddr*)&sci.address, (int*)&sci.addressLength);
					if (sci.socket != -1)
					{
					//////////
					// For this client to which we're now connected, we need to generate a thread
					// to handle communication back and forth with.  To do this, we launch a client
					// thread which has read/write abilities.
					//////
						// Prepare for the communication thread execution
						clientNew = new CClient();
						clientNew->cscommon()->setThisInstanceAsClient(&sci, "Connected");

						// Append this client to the server
						server->appendClient(clientNew);

						// Begin processing
						clientNew->beginReadWritePingProcessThreads(server);

						//////////
						// Notify the parent that we have a new client which has connected by mail parcel
						//////
							lcMail			= NULL;
							lnMailLength	= 0;
							host			= clientNew->cscommon()->getClientHosts();

							// Ip address
							ip				= &clientNew->cscommon()->getClientIpAddress()->sin_addr;
							sprintf(buffer, "%u.%u.%u.%u\0", (u32)ip->S_un.S_un_b.s_b1, (u32)ip->S_un.S_un_b.s_b2, (u32)ip->S_un.S_un_b.s_b3, (u32)ip->S_un.S_un_b.s_b4);
							iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcIpAddress, sizeof(cgcIpAddress) - 1, (u8*)buffer, strlen(buffer));

							// Port number
							sprintf(buffer, "%u\0", server->cscommon()->getServerPortNum());
							iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcPortNumber, sizeof(cgcPortNumber) - 1, (u8*)buffer, strlen(buffer));

							// The change (connection)
							iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcChangeType, sizeof(cgcChangeType) - 1, (u8*)cgcConnect, sizeof(cgcConnect) - 1);

							// Create the mail
							lnMailId = iStowMail(gsProcSelf, lcMail, lnMailLength, &parcel, false);

							// Release the mail
							free(lcMail);

							// Send the message
							server->postHwndCallbackMessage(WMCLISERV_CLIENT_CONNECTED, lnMailId, ip->S_un.S_addr);

					} else {
						// Error
						int error = WSAGetLastError();
						// Wait 1/100th of a second
						Sleep(10);
					}
			}


		//////////
		// Control will never return here
		//////
			return 1;	// Added so the compiler doesn't go "BLEH!" :-)
	}
