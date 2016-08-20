//////////
//
// /libsf/utils/common/cpp/cliserv/cliserv.cpp
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
// Called only to make the initial call to Winsock2
//
// Returns:
//		0				= Error (port is already bound in server mode)
//		tnPortNumber	= Okay, server was launched
//
//////
	RPAPI void rp_cliserv_initialize(void)
	{
		int		lnResult;
		WSADATA wd;


		if (!gbWSA_isInitialized)
		{
			// We request 2.2 or later services (for WinXP and later)
			lnResult = WSAStartup(MAKEWORD(2,2), &wd);
			if (lnResult != 0)
			{
				// This shouldn't happen unless the computer they're running on is too old
				MessageBox(GetDesktopWindow(), "Unable to initialize Winsock 2.2", "Fatal Error", MB_OK);
			}

			// All done
			gbWSA_isInitialized = true;
		}
	}




//////////
//
// Launches the specified server (sets up a listener, which communicates with a remote client)
//
// Returns:
//		-1				= Error (port is already bound)
//		tnPortNumber	= Okay
//
//////
	RPAPI u32 rp_cliserv_server_launch(u32 tnHwndCallback, s8* tcLocalIpAddress15, u32 tnPortNumber)
	{
		CServer**	serverPrev;
		CServer*	server;
		CServer*	serverNew;


		// See where we're adding this item
		if (!gcRootServer)
		{
			// First one
			serverPrev = &gcRootServer;

		} else {
			// We are appending to the chain
			server = gcRootServer;
			while (server)
			{
				// See if this port is already used
				if (server->getServerPortNumber() == tnPortNumber)
					return(-1);		// This port is already used

				// See if there is a valid next item
				if (!server->m_next)
					break;			// Nope, so this is where it will be added

				// Move to next entry
				server = server->m_next;
			}
			serverPrev = &server->m_next;
		}


		// Create the new entry
		serverNew = new CServer();
		if (serverNew)
		{
			// Update the forward link
			*serverPrev = serverNew;

			// Initialize it (when we bind to port we are implicitly stating it's a server)
			if (serverNew->bindToPort(tnPortNumber) == tnPortNumber)
			{
				// We're bound, launch the read/write threads
				serverNew->setHwndCallback(tnHwndCallback);

				// Grab the server IP address or name
				serverNew->getServerIpAddress(tcLocalIpAddress15, 15);

				// Begin listening to the port (spawns a thread which does that)
				serverNew->beginListening();

				// Success!
				return(tnPortNumber);
			}
		}
		// If we get here, failure!
		return(-1);
	}




//////////
//
// Launches the specified client (connects to a remote server)
//
// Returns:
//		-1				= Error (port is already bound)
//		tnPortNumber	= Okay
//
//////
	RPAPI u32 rp_cliserv_client_launch(u32 tnHwndCallback, s8* tcRemoteIpAddressOrHostName, u32 tnRemoteIpAddressOrHostNameLength, s8* tcLocalIpAddress15, u32 tnPortNumber)
	{
		CClient**	clientPrev;
		CClient*	lcClient;
		CClient*	clientNew;
		s8			remoteIp[80];


		// See where we're adding this item
		if (!gcRootClient)
		{
			// First one
			clientPrev = &gcRootClient;

		} else {
			// We are appending to the chain
			lcClient = gcRootClient;
			while (lcClient)
			{
				// See if this port is already used
				if (lcClient->getClientPortNumber() == tnPortNumber)
					return(-1);		// This port is already used

				// See if there is a valid next item
				if (!lcClient->m_next)
					break;			// Nope, so this is where it will be added

				// Move to next entry
				lcClient = lcClient->m_next;
			}
			clientPrev = &lcClient->m_next;
		}


		// Create the new entry
		clientNew = new CClient();
		if (clientNew)
		{
			// Update the forward link
			*clientPrev = clientNew;

			// Initialize it (when we bind to port we are implicitly stating it's a server)
			memset(remoteIp, 0, sizeof(remoteIp));
			memcpy(remoteIp, tcRemoteIpAddressOrHostName, min(tnRemoteIpAddressOrHostNameLength, sizeof(remoteIp) - 1));
			if (clientNew->connectToRemoteServer(remoteIp, tnPortNumber) == tnPortNumber)
			{
				// We're bound, launch the read/write threads
				// Grab the client IP address or name
				clientNew->getClientIpAddress(tcLocalIpAddress15, 15);

				// We're bound, launch the read/write threads
				clientNew->setHwndCallback(tnHwndCallback);

				// Begin reading and writing threads to send/receive data
				clientNew->beginReadWritePingProcessThreads(NULL);

				// Success!
				return(tnPortNumber);
			}
		}
		// Failure!
		return(0);
	}




//////////
//
// Shuts down a previously launched server listening to the specified port
//
//////
	RPAPI void rp_cliserv_server_shutdown(u32 tnPortNumber)
	{
		CServer*	serverNext;
		CServer**	serverPrev;
		CServer*	server;


		//////////
		// Iterate through every server for the server attached to this portnum
		//////
			serverNext	= NULL;
			serverPrev	= &gcRootServer;
			server		= gcRootServer;
			while (server)
			{
				//////////
				// Grab the next server
				//////
					serverNext = server->m_next;


				//////////
				// See if this is the server to delete
				//////
					if (server->getServerPortNumber() == tnPortNumber)
					{
						// This is a match, we're deleting this server
						delete server;

						// Update the forward link
						*serverPrev = serverNext;
						// At this point, it is likely this is the only server
						// However, we'll continue processing just in case (broken pipes, what have you)

					} else {
						// Move the forward-link to this server, as it will persist
						serverPrev	= (CServer**)&server->m_next;
					}


				//////////
				// Move to the next server
				//////
					server = serverNext;
			}
	}




//////////
//
// Shuts down a previously launched server listening to the specified port
//
//////
	RPAPI void rp_cliserv_client_shutdown(u32 tnPortNumber)
	{
		CClient*	clientNext;
		CClient**	clientPrev;
		CClient*	client;


		//////////
		// Iterate through every server for the server attached to this portnum
		//////
			clientNext	= NULL;
			clientPrev	= &gcRootClient;
			client		= gcRootClient;
			while (client)
			{
				//////////
				// Grab the next client
				//////
					clientNext = client->m_next;


				//////////
				// See if this is the client to delete
				//////
					if (client->getClientPortNumber() == tnPortNumber)
					{
						// This is a match, we're deleting this server
						delete client;

						// Update the forward link
						*clientPrev = clientNext;
						// At this point, it is likely this is the only client
						// However, we'll continue processing just in case (broken pipes, what have you)

					} else {
						// Move the forward-link to this client, as it will persist
						clientPrev	= (CClient**)&client->m_next;
					}


				//////////
				// Move to the next client
				//////
					client = clientNext;
			}
	}




//////////
//
// Data specifically read from and written to the specified port after valid connection
//
//////
	RPAPI u32 rp_cliserv_server_get_read_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindServersClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->bytesInReadQueue());

		// If we get here, server wasn't found on that port
		return(-1);
	}

	RPAPI u32 rp_cliserv_server_get_total_bytes_read(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindServersClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->totalBytesReadQueue());

		// If we get here, server wasn't found on that port
		return(-1);
	}

	RPAPI u32 rp_cliserv_server_get_partial_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindServersClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->totalBytesPartial());

		// If we get here, server wasn't found on that port
		return(-1);
	}




//////////
//
// Data specifically read from and written to the specified port after valid connection
//
//////
	RPAPI u32 rp_cliserv_server_read_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber, s8* tcReadBuffer,  u32 tnReadBufferLength)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		if (tnReadBufferLength != 0)
		{
			// Locate the server
			iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
			host = gethostbyname((cs8*)lcIpAddress);
			cc = iFindServersClient(host, tnPortNumber);
			if (cc)
			{
				tnReadBufferLength = cc->cscommon()->readFromReceivedQueue(tcReadBuffer, tnReadBufferLength, NULL);
				return(tnReadBufferLength);
			}
		}
		// If we get here, server wasn't found on that port
		return(-1);
	}




//////////
//
// Data specifically read from and written to the specified port after valid connection
//
//////
	RPAPI u32 rp_cliserv_server_send_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber, s8* tcWriteBuffer, u32 tnWriteBufferLength)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		if (tnWriteBufferLength != 0)
		{
			// Locate the server
			iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
			host = gethostbyname((cs8*)lcIpAddress);
			cc = iFindServersClient(host, tnPortNumber);
			if (cc)
				return(cc->cscommon()->createCommQueueObjectFromBufferAndAddToToSendCommQueue(cc, tcWriteBuffer, tnWriteBufferLength, cgcIMsg));
		}
		// If we get here, server wasn't found on that port
		return(-1);
	}




//////////
//
// Grab the last recorded ping time from the server to client
//
//////
	RPAPI f32 rp_cliserv_server_ping_time(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindServersClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->getLastPingTime());

		// If we get here, server wasn't found on that port
		return((f32)-1.0);
	}




//////////
//
// Grab the average ping time from the server to client
//
//////
	RPAPI f32 rp_cliserv_server_average_ping_time(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindServersClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->getAveragePingTime());

		// If we get here, server wasn't found on that port
		return((f32)-1.0);
	}




//////////
//
// Data specifically read from and written to the specified port after valid connection
//
//////
	RPAPI u32 rp_cliserv_client_get_read_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the client
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->bytesInReadQueue());

		// If we get here, client wasn't found on that port
		return(-1);
	}


	RPAPI u32 rp_cliserv_client_get_total_bytes_read(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the client
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->totalBytesReadQueue());

		// If we get here, client wasn't found on that port
		return(-1);
	}

	RPAPI u32 rp_cliserv_client_get_partial_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the client
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->totalBytesPartial());

		// If we get here, client wasn't found on that port
		return(-1);
	}




//////////
//
// Data specifically read from and written to the specified port after valid connection
//
//////
	RPAPI u32 rp_cliserv_client_read_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber, s8* tcReadBuffer,  u32 tnReadBufferLength)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		if (tnReadBufferLength != 0)
		{
			// Locate the client
			iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
			host = gethostbyname((cs8*)lcIpAddress);
			cc = iFindClient(host, tnPortNumber);
			if (cc)
			{
				tnReadBufferLength = cc->cscommon()->readFromReceivedQueue(tcReadBuffer, tnReadBufferLength, NULL);
				return(tnReadBufferLength);
			}
		}
		// If we get here, client wasn't found on that port
		return(-1);
	}




//////////
//
// Data specifically read from and written to the specified port after valid connection
//
//////
	RPAPI u32 rp_cliserv_client_send_bytes(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber, s8* tcWriteBuffer, u32 tnWriteBufferLength)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		if (tnWriteBufferLength != 0)
		{
			// Locate the client
			iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
			host = gethostbyname((cs8*)lcIpAddress);
			cc = iFindClient(host, tnPortNumber);
			if (cc)
				return(cc->cscommon()->createCommQueueObjectFromBufferAndAddToToSendCommQueue(cc, tcWriteBuffer, tnWriteBufferLength, cgcIMsg));

		}
		// If we get here, client wasn't found on that port
		return(-1);
	}




//////////
//
// Grab the last recorded ping time from the client to server
//
//////
	RPAPI f32 rp_cliserv_client_ping_time(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->getLastPingTime());

		// If we get here, server wasn't found on that port
		return((f32)-1.0);
	}




//////////
//
// Grab the average ping time from the client to server
//
//////
	RPAPI f32 rp_cliserv_client_average_ping_time(u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		CClient*	cc;
		u8			lcIpAddress[256];
		hostent*	host;


		// Locate the server
		iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
		host = gethostbyname((cs8*)lcIpAddress);
		cc = iFindClient(host, tnPortNumber);
		if (cc)
			return(cc->cscommon()->getAveragePingTime());

		// If we get here, server wasn't found on that port
		return((f32)-1.0);
	}
