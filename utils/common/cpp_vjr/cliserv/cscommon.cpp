//////////
//
// /libsf/utils/common/cpp/cliserv/cscommon.cpp
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
// Constructor, which initializes everything to a fresh, empty, new state
//
//////
	CCSCommon::CCSCommon(void)	:	m_bufferRead					(NULL),
									m_bufferSend					(NULL),
									m_bufferBytesToRead				(0),
									m_bufferBytesToSend				(0),
									m_firstCompletedCommQueueRead	(NULL),
									m_firstCommQueueToSend			(NULL),
									m_firstPartialCommQueueRead		(NULL),
									m_firstUnackCommQueueSend		(NULL),
									m_firstCommQueueToProcess		(NULL),
									m_bufferTotalBytesRead			(0),
									m_bufferTotalBytesSent			(0),
									m_totalBytesPartial				(0),
									m_online						(0),
									m_status						("Not yet connected"),
									m_isServer						(false),
									m_firstWatchdog					(NULL),
									m_totalPingTimes				(0.0),
									m_totalPingCount				(0)
	{
		m_clientInfo = (SConnInfo*)malloc(sizeof(SConnInfo));
		m_serverInfo = (SConnInfo*)malloc(sizeof(SConnInfo));

		// Everything is initialized at compile time
		memset(m_clientInfo,		0, sizeof(SConnInfo));
		memset(m_serverInfo,		0, sizeof(SConnInfo));
		memset(&m_lastPingRequest,	0, sizeof(m_lastPingRequest));
		memset(&m_lastPingAck,		0, sizeof(m_lastPingAck));


		// Create our critical sections for reads/writes
		InitializeCriticalSection(&m_readSemaphore);
		InitializeCriticalSection(&m_sendSemaphore);
		InitializeCriticalSection(&m_commQueueSemaphore);
		InitializeCriticalSection(&m_watchdogSemaphore);
	}




//////////
//
// Destructor, which clears everything which exists
//
//////
	CCSCommon::~CCSCommon(void)
	{
		//////////
		// Free memory
		//////
			if (m_bufferRead)
				free(m_bufferRead);
			if (m_bufferSend)
				free(m_bufferSend);


		//////////
		// Close client socket (if any)
		//////
			if (m_clientInfo->socket)
			{
				shutdown(m_clientInfo->socket, SD_BOTH);
				closesocket(m_clientInfo->socket);
			}


		//////////
		// Close server socket (if any)
		//////
			if (m_serverInfo->socket)
			{
				shutdown(m_serverInfo->socket, SD_BOTH);
				_close(m_serverInfo->socket);
			}
	}




//////////
//
// Called to take the data to send and break it into packets which are staged for
// transmission in the send queue.
//
//////
	u32 CCSCommon::createCommQueueObjectFromBufferAndAddToToSendCommQueue(CClient* cc, s8* tcData, u32 tnDataLength, cs8* tcInternalOrExternal)
	{
		u32			lnTotalBytes;
		SCommQueue*	cq;


		// Make sure there's something to do
		lnTotalBytes = 0;
		if (tcData && tnDataLength > 0)
		{
			// There is something to send.
			// Allocate the commQueue
			cq = iCreateCommQueue((s8*)cgcUser, NULL, tcInternalOrExternal[0], cc->getNextTransactionId());
			if (cq)
			{
				// Prepare the commQueue
				// Fill cq, cq->header, and break the message into parts
				lnTotalBytes = iCreateMessageParts(cc, cq, tcData, tnDataLength, cc->getBlockSize());

				// Lock the send queue and append it (schedule it for transmission)
				lockForCommQueueAccess(identity(), "createCommQueueObjectFromBufferAndAddToToSendCommQueue");

				// Schedule it
				iAppendObjectToCommQueue(&m_firstCommQueueToSend, cq);

				// Unlock the send queue
				unlockForCommQueueAccess(identity(), "createCommQueueObjectFromBufferAndAddToToSendCommQueue");
			}
		}
		// All done
		return(lnTotalBytes);
	}




//////////
//
// Append the specified string to the data left to send to other.
// This function is only called from the send thread, so it is okay to append without a semaphore.
//
//////
	u32 CCSCommon::iLowLevel__appendToSendQueueRaw(s8* tcData, u32 tnDataLength)
	{
		u32 lnLength;
		s8*	m_newPtr;


		//////////
		// Make sure we're online
		//////
			if (!m_online)
				return(-1);		// Failure, not online


		//////////
		// Add data to the send queue
		//////
			if (!m_bufferSend)
			{
				// This is the first data in the send queue
				// Create a copy
				m_bufferSend = (s8*)malloc(tnDataLength);
				if (m_bufferSend)
				{
					// Copy it
					memcpy(m_bufferSend, tcData, tnDataLength);
					// Update our length
					m_bufferBytesToSend = tnDataLength;

				} else {
					// We could not allocate the memory, so it's an error
					m_bufferBytesToSend = 0;
				}

			} else {
				// It already exists, so we are appending to the end
				lnLength	= m_bufferBytesToSend;
				m_newPtr	= (s8*)realloc(m_bufferSend, m_bufferBytesToSend + tnDataLength);
				if (m_newPtr)
				{
					// Update the new pointer
					m_bufferSend	= m_newPtr;
					// Append the new part
					memcpy(m_newPtr + lnLength, tcData, tnDataLength);
					// Increase the length
					m_bufferBytesToSend += tnDataLength;
				}
				//else we could not allocate the memory, so it's an error
			}


			//////////
			// Indicate how many bytes are in the queue
			//////
				return(m_bufferBytesToSend);
	}




//////////
//
// Read the specified block from the read buffer
// This function is only called from the read thread, so it is okay to read without a semaphore.
//
//////
	u32 CCSCommon::readFromReceivedQueue(s8* tcData, u32 tnDataLength, u32* tnIsThereMoreDataToRead)
	{
		u32 lnRetVal;


		//////////
		// Make sure we're online
		//////
			if (!m_online)
				return(-1);		// Failure, not online


		//////////
		// Make sure there's something to read
		//////
			if (m_bufferBytesToRead == 0)
				return(0);		// Nothing to read


		//////////
		// Read the data chunk that's been received
		//////
			// Lock down our access to this data
			lockForReadBufferAccess(identity(), "readFromReceivedQueue");

			// See where we are
			if (tnDataLength < m_bufferBytesToRead)
			{
				// They are requesting only a portion of the remaining content

				//////////
				// Copy the buffer to their destination
				//////
					memcpy(tcData, m_bufferRead, tnDataLength);


				//////////
				// Move the remaining chunk and resize the block
				//////
					memcpy(m_bufferRead,  m_bufferRead + tnDataLength, m_bufferBytesToRead - tnDataLength);
					// The data at the end now is no longer needed
					realloc(m_bufferRead, m_bufferBytesToRead - tnDataLength);
					// Resize the remaining buffer length
					m_bufferBytesToRead -= tnDataLength;


				//////////
				// Indicate how many bytes we copied
				//////
					lnRetVal = tnDataLength;


			} else {
				// Their buffer is the same size or bigger than the content we have
				// So we can return everything


				//////////
				// Indicate how many bytes we will copy
				//////
					lnRetVal = m_bufferBytesToRead;


				//////////
				// Copy the buffer to their destination
				//////
					memcpy(tcData, m_bufferRead, m_bufferBytesToRead);


				//////////
				// Free up the queue, reset the length
				//////
					free(m_bufferRead);
					m_bufferRead			= NULL;
					m_bufferBytesToRead	= 0;
			}

			// Unlock our access to this data
			unlockForReadBufferAccess(identity(), "readFromReceivedQueue");


		//////////
		// All done!
		//////
			return(lnRetVal);
	}




//////////
//
// See if another ping could be scheduled
//
//////
	void CCSCommon::schedulePingRequestIfNeeded(CClient* cc)
	{
		u32				lnLastPingAge;
		SYSTEMTIME		lst;
		SCommQueue*		cq;


		// See if enough time has elapsed to warrant a ping
		iStoreCurrentTime(&lst);
		lnLastPingAge = (u32)iGetSystemtimeDiffInMilliseconds(&lst, &m_lastPingAck);
		if (lnLastPingAge >= _CLISERV_PING_INTERVAL)
		{
			// See if there's already a PING request in the not-yet-sent queue
			if (!searchCommQueueForCommand(m_firstCommQueueToSend, (s8*)cgcPing, NULL, 0))
			{
				// See if there's one that's been sent, but not yet acknowledged
				cq = searchCommQueueForCommand(m_firstUnackCommQueueSend, (s8*)cgcPing, NULL, 0);
				if (cq)
				{
					// There is.  See how long it's been since the last one.
					// If enough time has gone by, we may have lost contact with the remote.
					lnLastPingAge = (u32)iGetSystemtimeDiffInMilliseconds(&lst, &cq->sendTime);
					if (lnLastPingAge >= _CLISERV_PING_INTERVAL)
					{
						// Yeah, we've waited too long.
						// Kill this ping request
						iDetachObjectFromCommQueue(&m_firstUnackCommQueueSend, cq);
						iDeleteCommQueueObject(cq);

						// Issue a new one
						sendPingRequest(cc);
					}

				} else {
					// There are no ping requests in the pipe, it's time to issue one
					sendPingRequest(cc);
				}
			}
		}
	}




//////////
// Added as simple accessors because of the structure needs
//////
	u32 CCSCommon::isOnline(void)						{	return(m_online);				}
	s8* CCSCommon::onlineStatus(void)					{	return(m_status);				}
	s8* CCSCommon::identity(void)						{	return(m_identity);				}
	u32 CCSCommon::bytesInReadQueue(void)				{	return(m_bufferBytesToRead);	}
	u32 CCSCommon::bytesInSendQueue(void)				{	return(m_bufferBytesToSend);	}
	u32 CCSCommon::totalBytesReadQueue(void)			{	return(m_bufferTotalBytesRead);	}
	u32 CCSCommon::totalBytesPartial(void)				{	return(m_totalBytesPartial);	}
	u32 CCSCommon::totalBytesSendQueue(void)			{	return(m_bufferTotalBytesSent);	}





//////////
//
// Set identity as a client
//
//////
	void CCSCommon::setThisInstanceAsClient(SConnInfo* tsClient, s8* tcStatus)
	{
		memcpy(m_clientInfo, tsClient, sizeof(SConnInfo));
		m_socket		= tsClient->socket;
		m_portnum		= tsClient->portnum;
		m_online		= 1;
		m_status		= tcStatus;
		m_identity		= "Client";
		m_isServer		= false;
	}



	
//////////
//
// Set identity as a server
//
//////
	void CCSCommon::setThisInstanceAsServer(SConnInfo* tsServer, s8* tcStatus)
	{
		memcpy(m_serverInfo, tsServer, sizeof(SConnInfo));
		m_socket		= tsServer->socket;
		m_portnum		= tsServer->portnum;
		m_online		= 1;
		m_status		= tcStatus;
		m_identity		= "Server";
		m_isServer		= true;
	}




//////////
// Client getters
//////
	SConnInfo*		CCSCommon::getClient(void)					{	return(m_clientInfo);				}
	sockaddr_in*	CCSCommon::getClientIpAddress(void)			{	return(&m_clientInfo->address);		}
	hostent*		CCSCommon::getClientHosts(void)				{	return(m_clientInfo->host);			}
	u32				CCSCommon::getClientSocket(void)			{	return(m_clientInfo->socket);		}
	u32				CCSCommon::getClientPortNum(void)			{	return(m_portnum);					}


//////////
// Server getters
//////
	SConnInfo*		CCSCommon::getServer(void)					{	return(m_serverInfo);				}
	sockaddr_in*	CCSCommon::getServerIpAddress(void)			{	return(&m_serverInfo->address);		}
	hostent*		CCSCommon::getServerHosts(void)			{	return(m_serverInfo->host);			}
	u32				CCSCommon::getServerSocket(void)			{	return(m_serverInfo->socket);		}
	u32				CCSCommon::getServerPortNum(void)			{	return(m_portnum);					}


//////////
// General Getters
//////
	u32				CCSCommon::getSocket(void)					{	return(m_socket);					}
	u32				CCSCommon::getPortNumber(void)				{	return(m_portnum);					}


//////////
// Read buffer stuff
//////
	s8*				CCSCommon::getReadBuffer(void)					{	return(m_bufferRead);				}
	u32				CCSCommon::getReadBytes(void)					{	return(m_bufferBytesToRead);		}
	void			CCSCommon::increaseTotalReadBytes(u32 tnCount)	{	m_bufferTotalBytesRead += tnCount;	}


//////////
// Send buffer stuff
//////
	s8*				CCSCommon::getSendBytesBuffer(void)				{	return(m_bufferSend);				}
	u32				CCSCommon::getSendQueueBytes(void)				{	return(m_bufferBytesToSend);		}
	void			CCSCommon::increaseTotalSendBytes(u32 tnCount)	{	m_bufferTotalBytesSent += tnCount;	}




//////////
//
// Increase the read queue by the specified number of bytes
//
// Note:  It is up to the caller to rightly populate that memory block.
//        The return value points to the start of the tnNumToAdd bytes added.
//
//////
	s8* CCSCommon::increaseReadBufferSize(u32 tnNumToAdd)
	{
		s8* lpRetVal;
		s8* lpNew;


		// See if we're appending or creating
		if (m_bufferRead)
		{
			// We're increasing the read buffer
			lpNew = (s8*)realloc(m_bufferRead, m_bufferBytesToRead + tnNumToAdd);
			if (lpNew)
			{
				// We're good, append on the space
				lpRetVal				= lpNew + m_bufferBytesToRead;
				m_bufferRead			= lpNew;
				m_bufferBytesToRead		+= tnNumToAdd;

				// Initialize the new block to NULLs
				memset(lpRetVal, 0, tnNumToAdd);

			} else {
				// Not enough memory to allocate the receive
				lpRetVal = NULL;
			}

		} else {
			// We're creating the read buffer
			m_bufferRead			= (s8*)malloc(tnNumToAdd);
			m_bufferBytesToRead		= tnNumToAdd;
			lpRetVal				= m_bufferRead;
		}
		m_bufferTotalBytesRead += tnNumToAdd;

		// Return the pointer
		return(lpRetVal);
	}




//////////
//
// Append the specified data to the end of the read queue buffer
//
//////
	bool CCSCommon::appendToUserReadBuffer(s8* tcData, u32 tnDataLength)
	{
		bool	lbAppended;
		s8*		dest;


		// Make sure there's something to do
		lbAppended = false;
		if (tnDataLength != 0)
		{
			// There is some data
			// Lock our semaphore
			lockForReadBufferAccess(identity(), "appendToUserReadBuffer");

			// Increase our read queue buffer size
			dest = increaseReadBufferSize(tnDataLength);
			if (dest)
			{
				// We're good
				lbAppended = true;
				memcpy(dest, tcData, tnDataLength);
			}

			// Unlock our semaphore
			unlockForReadBufferAccess(identity(), "appendToUserReadBuffer");
		}
		return(lbAppended);
	}





//////////
//
// Resize the send buffer by the size specified, returns a pointer to the new space
//
//////
	s8* CCSCommon::increaseSendBufferSize(u32 tnNumToAdd)
	{
		s8* lpRetVal;
		s8* lpNew;


		// See if we're appending or creating
		if (m_bufferSend)
		{
			// We're increasing the send buffer
			lpNew = (s8*)realloc(m_bufferSend, m_bufferBytesToSend + tnNumToAdd);
			if (lpNew)
			{
				// We're good, append on the space
				lpRetVal			= lpNew + m_bufferBytesToSend;
				m_bufferSend		= lpNew;
				m_bufferBytesToSend	+= tnNumToAdd;

				// Initialize the new block to NULLs
				memset(lpRetVal, 0, tnNumToAdd);

			} else {
				// Not enough memory to allocate the receive
				lpRetVal = NULL;
			}

		} else {
			// We're creating the send buffer
			m_bufferSend			= (s8*)malloc(tnNumToAdd);
			m_bufferBytesToSend		= tnNumToAdd;
			lpRetVal				= m_bufferSend;
		}

		// Return the pointer
		return(lpRetVal);
	}





//////////
//
// Reset the send queue to empty (clear all pending sends, happens when a connection is dropped)
//
//////
	void CCSCommon::resetSendQueueBuffer(void)
	{
		// Remove everything
		if (m_bufferSend)
		{
			free(m_bufferSend);
			m_bufferSend			= NULL;
			m_bufferBytesToSend	= 0;
		}
	}




	bool CCSCommon::appendToUserSendBuffer(s8* tcData, u32 tnDataLength)
	{
		bool	lbAppended;
		s8*		dest;


		// Make sure there's something to do
		lbAppended = false;
		if (tnDataLength != 0)
		{
			// There is some data
			// Lock our semaphore
			lockForSendBufferAccess(identity(), "appendToUserSendBuffer");

			// Increase our read queue buffer size
			dest = increaseSendBufferSize(tnDataLength);
			if (dest)
			{
				// We're good
				lbAppended = true;
				memcpy(dest, tcData, tnDataLength);
			}

			// Unlock our semaphore
			unlockForSendBufferAccess(identity(), "appendToUserSendBuffer");
		}
		return(lbAppended);
	}




//////////
//
// Semaphore locks for access to various functions.  See header for easier visual breakdown.
//
//////
	void CCSCommon::lockForReadBufferAccess(s8* identifier1, s8* identifier2)
	{
		iStoreSemaphoreStack("read buffer lock", identifier1, identifier2);
		EnterCriticalSection(&m_readSemaphore);
	}

	bool CCSCommon::tryLockForReadBufferAccess(s8* identifier1, s8* identifier2)
	{
		bool lbResult;

		lbResult = (TryEnterCriticalSection(&m_readSemaphore) != 0);

		if (lbResult)
			iStoreSemaphoreStack("read buffer try lock", identifier1, identifier2);

		return(lbResult);
	}

	void CCSCommon::unlockForReadBufferAccess(s8* identifier1, s8* identifier2)
	{
		iStoreSemaphoreStack("read buffer unlock", identifier1, identifier2);
		LeaveCriticalSection(&m_readSemaphore);
	}

	void CCSCommon::lockForSendBufferAccess(s8* identifier1, s8* identifier2)
	{
		iStoreSemaphoreStack("send buffer lock", identifier1, identifier2);
		EnterCriticalSection(&m_sendSemaphore);
	}

	void CCSCommon::unlockForSendBufferAccess(s8* identifier1, s8* identifier2)
	{
		iStoreSemaphoreStack("send buffer unlock", identifier1, identifier2);
		LeaveCriticalSection(&m_sendSemaphore);
	}

	void CCSCommon::lockForCommQueueAccess(s8* identifier1, s8* identifier2)
	{
		iStoreSemaphoreStack("commQueue lock", identifier1, identifier2);
		EnterCriticalSection(&m_commQueueSemaphore);
	}

	bool CCSCommon::tryLockForCommQueueAccess(s8* identifier1, s8* identifier2)
	{
		bool lbResult;

		lbResult = TryEnterCriticalSection(&m_commQueueSemaphore) != 0;

		if (lbResult)
			iStoreSemaphoreStack("commQueue try lock", identifier1, identifier2);

		return(lbResult);
	}

	void CCSCommon::unlockForCommQueueAccess(s8* identifier1, s8* identifier2)
	{
		iStoreSemaphoreStack("commQueue unlock", identifier1, identifier2);
		LeaveCriticalSection(&m_commQueueSemaphore);
	}




//////////
//
// Called only to make the initial call to Winsock2
//
// Returns:
//		0				= Error (port is already bound in server mode)
//		tnPortNumber	= Okay, server was launched
//
//////
	void cliserv_initialize(void)
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
// Launches the specified client (connects to a remote server port).
//
// Returns:
//		-1				= Error (port is already bound)
//		tnPortNumber	= Okay
//
//////
	CClient* cliserv_client_launch(u32 tnHwndCallback, s8* tcRemoteIpAddressOrHostName, u32 tnRemoteIpAddressOrHostNameLength, s8* tcLocalIpAddress15, u32 tnPortNumber)
	{
		CClient**	clientPrev;
		CClient*	client;
		CClient*	clientNew;
		s8			remoteIp[80];


		// See where we're adding this item
		if (!gcRootClient)
		{
			// First one
			clientPrev = &gcRootClient;

		} else {
			// We are appending to the chain
			client = gcRootClient;
			while (client)
			{
				// See if this port is already used
				if (client->getClientPortNumber() == tnPortNumber)
					return(client);		// This port is already being used

				// See if there is a valid next item
				if (!client->m_next)
					break;			// Nope, so this is where it will be added

				// Move to next entry
				client = client->m_next;
			}
			clientPrev = &client->m_next;
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
				return(clientNew);
			}
		}
		// Failure!
		return(NULL);
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
	CServer* cliserv_server_launch(u32 tnHwndCallback, s8* tcLocalIpAddress15, u32 tnPortNumber)
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
					return(server);		// This port is already used

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
				return(serverNew);
			}
		}
		// If we get here, failure!
		return(NULL);
	}





//////////
// Store the semaphore entry
//////
	void iStoreSemaphoreStack(s8* tcLocation, s8* tcId1, s8* tcId2)
	{
		// Store this entry
		if (gbSemaphoreStackRecording)
		{
			// Lock for access to the stack
			EnterCriticalSection(&gcsStoreSemaphoreStack);

			// Record the stack
			iAddToGenericList(&gsRootSemaphoreStack, 
								tcLocation,		strlen(tcLocation), 
								tcId1,			strlen(tcId1),
								tcId2,			strlen(tcId2),
								NULL,			0,
								NULL,			0,
								false);

			// Unlock
			LeaveCriticalSection(&gcsStoreSemaphoreStack);
		}
	}




	
//////////
//
// Called to move any completely received CommQueue items from their current
// location in the partially received commQueue into the received commQueue.
//
//////
	bool CCSCommon::parsePartiallyReceivedCommQueueItems(SThreadParams* stp)
	{
		bool			lbFoundOne;
		SCommQueue*		cqNext;
		SCommQueue*		cq;


		// See if there's anything waiting
		lbFoundOne	= false;
		cq			= m_firstPartialCommQueueRead;
		while (cq)
		{
			// Store the next
			cqNext = cq->next;

			// See if all the parts have been received
			if (cq->header.receivedBlocks >= cq->header.maxBlocks)
			{
				// Raise the flag
				lbFoundOne = true;

				// Remove it from where it is now in the partially received CommQueue chain
				iDetachObjectFromCommQueue(&m_firstPartialCommQueueRead, cq);

				// And put it in the received CommQueue chain
				iAppendObjectToCommQueue(&m_firstCompletedCommQueueRead, cq);
			}

			// Move to next item
			cq = cqNext;
		}

		// Return our value
		return(lbFoundOne);
	}



	
//////////
//
// Called to move any completely received CommQueue items from their current
// location into either user data to read on the next call, or into the internal
// process queue.
//
//////
	bool CCSCommon::parseNextReceivedCommQueueItem(SThreadParams* stp)
	{
		u32				lnDataMailId, lnMailId, lnTransactionId;
		bool			lbFoundOne;
		SCommQueue*		cq;
		SParcel*		mail;
		hostent*		host;
		u8*				lcMail;
		u32				lnMailLength;
		in_addr*		ip;
		SParcel*		parcel;
		s8				buffer[256];


		// See if there's anything waiting
		lbFoundOne	= false;
		cq			= m_firstCompletedCommQueueRead;
		if (cq)
		{
			// See if this is an internal or external request
			if (cq->header.ieIdentifier == 'i' || cq->header.ieIdentifier == 'I')
			{
				// It's internal, move it over for processing.
				// Try to lock the process semaphore
				// We're good, we can move it
				// Raise the flag
				lbFoundOne = true;

				// Remove it from where it is now in the completed CommQueue chain
				iDetachObjectFromCommQueue(&m_firstCompletedCommQueueRead, cq);

				// And put it in the process CommQueue chain
				iAppendObjectToCommQueue(&m_firstCommQueueToProcess, cq);

			} else {
				// It's external, move it to the user's read buffer
				// We're good, we can move it to user space
				// Raise the flag
				lbFoundOne = true;

				// Grab the transaction id
				lnTransactionId = cq->header.transactionId;

				// Remove it from where it is now in the completed commQueue chain
				iDetachObjectFromCommQueue(&m_firstCompletedCommQueueRead, cq);

				// Append it to the user's read buffer
				lnDataMailId = iStowMailFromCommQueue(gsProcSelf, this, cq, &mail, false);

				// Delete its contents now that its data's been added to the user's read buffer
				iDeleteCommQueueObject(cq);

				//////////
				// Notify the parent that we have a new client which has connected by mail parcel
				//////
					lcMail			= NULL;
					lnMailLength	= 0;
					host			= stp->client->cscommon()->getClientHosts();

					// Ip address
					ip				= &stp->client->cscommon()->getClientIpAddress()->sin_addr;
					sprintf(buffer, "%u.%u.%u.%u\0", (u32)ip->S_un.S_un_b.s_b1, (u32)ip->S_un.S_un_b.s_b2, (u32)ip->S_un.S_un_b.s_b3, (u32)ip->S_un.S_un_b.s_b4);
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcIpAddress, sizeof(cgcIpAddress) - 1, (u8*)buffer, strlen(buffer));

					// Port number
					if (stp->server)		sprintf(buffer, "%u\0", stp->server->cscommon()->getServerPortNum());
					else					sprintf(buffer, "%u\0", stp->client->cscommon()->getClientPortNum());
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcPortNumber, sizeof(cgcPortNumber) - 1, (u8*)buffer, strlen(buffer));

					// Transaction id
					sprintf(buffer, "%u\0", lnTransactionId);
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcTransactionId, sizeof(cgcTransactionId) - 1, (u8*)buffer, strlen(buffer));

					// The change (connection)
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcChangeType, sizeof(cgcChangeType) - 1, (u8*)cgcIncomingData, sizeof(cgcIncomingData) - 1);

					// Indicate the number of the received bytes
					sprintf(buffer, "%u\0", mail->dataLength);
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcIncomingBytes, sizeof(cgcIncomingBytes) - 1, (u8*)buffer, strlen(buffer));

					// Indicate the mail number to receive the bytes
					sprintf(buffer, "%u\0", lnDataMailId);
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcMailId, sizeof(cgcMailId) - 1, (u8*)buffer, strlen(buffer));

					// Create the mail
					lnMailId = iStowMail(gsProcSelf, lcMail, lnMailLength, &parcel, false);

					// Release the mail
					free(lcMail);


				// Send to server or client this information
				if (stp->server)
				{
					// The server's window needs to be notified that this has happened
					stp->server->postHwndCallbackMessage(WMCLISERV_TRANSACTION_RESPONSE, lnMailId, ip->S_un.S_addr);

				} else if (stp->client) {
					// The server's window needs to be notified that this has happened
					stp->client->postHwndCallbackMessage(WMCLISERV_TRANSACTION_RESPONSE, lnMailId, ip->S_un.S_addr);
				}

			}
		}

		// Return our value
		return(lbFoundOne);
	}



	
//////////
//
// Called to parse any sendQueue items, move them to from the to-send queue into
// the send buffer, and then commQueue items to the waiting-for-acknowledgment queue.
//
//////
	bool CCSCommon::parseSendCommQueueItems(SThreadParams* stp)
	{
		SCommQueue*	cq;


		// Move the next item from the commQueue to the send buffer
		cq = m_firstCommQueueToSend;
		if (cq)
		{
			// Push the bytes for this item to the send queue, and move it to the waiting-for-acknowledgment queue
			sendCommQueueItem(&m_firstCommQueueToSend, &m_firstUnackCommQueueSend, cq);
			return(true);
		}
		// Nothing to do
		return(false);
	}



	
//////////
//
// Looks to see aging data on any sent items to figure out if they need to be re-sent.
// We expect a reply by 15 seconds.  If no reply, then we resend the items that have not
// yet been acknowledged.
//
//////
	bool CCSCommon::resendUnackCommQueueItems(SThreadParams* stp)
	{
		SCommQueue* cq;
		SCommPart*	cp;
		SYSTEMTIME	lst;


		// Make sure there's something to do
		cq = m_firstUnackCommQueueSend;
		if (cq)
		{
			// Get the current time
			iStoreCurrentTime(&lst);

			if (cq->header.ackBlocks >= cq->header.maxBlocks)
			{
				// This one has now been fully acknowledged, it can be removed
				iDetachObjectFromCommQueue(&m_firstUnackCommQueueSend, cq);		// Kick it off the unack queue
				iDeleteCommQueueObject(cq);										// Delete it (which also deletes its parts)
				// All done


// Removed 04/08/2014.  Need to rethink when it's appropriate to act.  It should be on each part because the other
// could be sending us gigabytes of data and each part will be received, but the entire transmission will take well
// beyond our timeout interval.  So, we'll see.
// 			} else if (iGetSystemtimeDiffInMilliseconds(&lst, &cq->sendTime) >= _CLISERV_UNACK_FAILURE_TIMEOUT_INTERVAL) {
// 				// Enough time has elapsed that this entry is a failure from our point of view.
// 				// We simply drop the sent item and silently call it failed
// 				// Note:  in the future we could have a callback upon failure to let the caller know that this item could not be handled
// 				// Delete it, we'll just assume it was received and they didn't acknowledge it.
// 				iDetachObjectFromCommQueue(&m_firstUnackCommQueueSend, cq);
// 				iDeleteCommQueueObject(cq);
// 				// All done.
				

			} else if (iGetSystemtimeDiffInMilliseconds(&lst, &cq->sendTime) >= _CLISERV_UNACK_RESEND_TIMEOUT_INTERVAL) {
				// Enough time has now elapsed for us to be legitimately concerned
				// It may be time to re-send any parts of this item that have not yet been acknowledged
				cp = cq->firstPart;
				while (cp)
				{
					// If this part has not yet been acknowledged
					if (!cp->header.ackSent)
					{
						// This one has not been acknowledged.
						// How long has it been?
						if (iGetSystemtimeDiffInMilliseconds(&lst, &cp->sendTime) >= _CLISERV_UNACK_RESEND_TIMEOUT_INTERVAL)
						{
							// Too long.
							// Resend this block.
							resendCommQueuePart(cq, cp);
							// Note the resend function automatically updates the part's sendTime as of the resend
						}
					}

					// Move to next part
					cp = cp->next;
				}
			}
			// We processed something
			return(true);
		}
		// Nothing to do
		return(false);
	}



	
//////////
//
// Called to physically resend a commQueue item, but that commQueue item will
// not automatically be added to the unack commQueue after being scheduled for
// transmission.  Instead, it will be scheduled for transmission, and then the
// commQueue and commPart object(s) will be deleted.  This, presumably, because
// they either merely need to be injected into the stream without an ack required,
// or because we are resending something that was previously sent, but never ack'd.
//
// Semaphore must be in place before calling this function.
//
//////
	void CCSCommon::resendCommQueuePart(SCommQueue* cq, SCommPart* cp)
	{
		SCommQueue*	cqNew;
		SCommPart*	cpNew;


		// Duplicate the current commQueue and commPart items
		cqNew = duplicateCommQueueObject(cq);
		cpNew = duplicateCommPartObject(cp);

		// Update the header to include the resend information
		cqNew->leaveOutOfSecondCommQueue = true;		// We want this transmitted, but not put in the unack commQueue (because it's already in there)

		// Append it to the toSend commQueue
		iAppendObjectToCommQueue(&m_firstCommQueueToSend, cq);
	}



	
//////////
//
// Called to physically push the cq item to the send buffer, and move it from the rootFrom
// into the rootTo.  Typically these are the toSend and unack commQueues.  However, for special
// (future) purposes these can be left blank.
//
// Note:  It is up to the caller to have properly locked the semaphores for the related commQueues
//
//////
	void CCSCommon::sendCommQueueItem(SCommQueue** rootFrom, SCommQueue** rootTo, SCommQueue* cq)
	{
		SCommPart*	cp;


		// Make sure there's something to do
		if (cq && rootFrom && rootTo)
		{
			if (!cq->firstPart)
			{
				// This is a header-only message
				appendToUserSendBuffer((s8*)&cq->header, sizeof(cq->header));

			} else {
				// Send each part of the message
				cp = cq->firstPart;
				while (cp)
				{
					if (cp->dataLength != 0)
					{
						// Push the header
						appendToUserSendBuffer((s8*)&cp->header, sizeof(cp->header));

						// Push the data
						if (cp->dataLength != 0)
							appendToUserSendBuffer(cp->data, cp->dataLength);

						// Update the time that this was done for this individual part (for the watchdog)
						iStoreCurrentTime(&cp->sendTime);
					}

					// Move to next part
					cp = cp->next;
				}
			}
			// When we get here, it's been pushed to the send queue

			// Update the time that this packet was actually completed being scheduled (for the watchdog)
			iStoreCurrentTime(&cq->sendTime);

			// Remove from the from first commQueue
			iDetachObjectFromCommQueue(rootFrom, cq);

			// Append to the to next/second commQueue if we're supposed to
			if (!cq->leaveOutOfSecondCommQueue /* "if not leave out of second comm queue" is the same logically as "if (putInSecondCommQueue)"*/ )
			{
				// Put in the second commQueu
				iAppendObjectToCommQueue(rootTo, cq);	// Put it in the second commQueue

			} else {
				// Since we're not appending it to the second commQueue after transmission, it's
				// outlived its usefulness and overstayed its welcome!
				// As such, we destroy it and all the parts it has contained within.  Take that!
				iDeleteCommQueueObject(cq);
			}
		}
	}




//////////
//
// Called to start processing the next un-processed item (if any).
//
// Note:  Each new item to be processed is given its own thread.  So, only
//        _CLISERV_MAX_PROCESS_THREADS can be called at any one time.
//
//////
	bool CCSCommon::processAnyInternalCommands(SThreadParams* stp)
	{
		u32			lnProcessedCount;
		SCommQueue*	 cq;


		// Make sure there's something to do and lock access to the structure
		lnProcessedCount	= 0;
		cq					= m_firstCommQueueToProcess;
		if (stp && stp->client && cq)
		{
			// We're processing something
			++lnProcessedCount;

			// Prepare parameters to pass
			memset(&cq->params, 0, sizeof(cq->params));
			memcpy(&cq->params, stp, sizeof(cq->params));
			cq->params.extra2		= cq;
			cq->params.extra3		= &m_firstCommQueueToProcess;
			cq->params.cs			= this;

			// Process
			iProcessInternalRequest(&cq->params);
			iDetachObjectFromCommQueue(&m_firstCommQueueToProcess, cq);
			iDeleteCommQueueObject(cq);
		}

		// If we get here, nothing (new) to process
		return(lnProcessedCount >= 1);
	}




//////////
//
// Delete the specified process SCommQueue item
//
//////
	void CCSCommon::deleteProcessRequest(SCommQueue** cqRoot, SCommQueue* cqToDelete)
	{
		SCommQueue**	cqLast;
		SCommQueue*		cq;


		// Iterate through the chain
		if (cqRoot)
		{
			// Lock access to the structure
			lockForCommQueueAccess(identity(), "deleteProcessRequest");

			// Gather 
			cqLast	= cqRoot;
			cq		= *cqRoot;
			while (cq)
			{
				if (cq == cqToDelete)
				{
					// This is it
					// Delete this item from the chain
					*cqLast = cq->next;

					// Delete all of its contents
					iDeleteCommQueueObject(cq);
				}

				// Move to next item
				cqLast	= &cq->next;
				cq		= cq->next;
			}

			// Unlock access to the structure
			unlockForCommQueueAccess(identity(), "deleteProcessRequest");
		}
	}




//////////
//
// Searches the specified commQueue for the specified condition
// Note:  Appropriate semaphore should already have been locked before calling these functions.
//
//////
	// Search for matching command2 and optional command9
	SCommQueue* CCSCommon::searchCommQueueForCommand(SCommQueue* root, s8* tcCommand2, s8* tcCommand9, u32 tnTransactionId/*Use 0 for do-not-search-transactionId*/)
	{
		SCommQueue* cq;


		// Search through the list
		cq = root;
		while (cq)
		{
			// See if this entry has the specified transaction id
			if (_memicmp(cq->header.command2, tcCommand2, 2) == 0)
			{
				// The 2-byte command matches, see if there's a 9-byte specified
				if (!tcCommand9 || (tcCommand9 && _memicmp(cq->header.command9, tcCommand9, 9) == 0))
				{
					// We're good at the command2 + command9 level ...
					// But, did they also specify a transaction
					if (tnTransactionId == 0 || (tnTransactionId != 0 && cq->header.transactionId == tnTransactionId))
						return(cq);		// This is it
				}
			}

			// Move to next entry
			cq = cq->next;
		}
		// If we get here, not found
		return(NULL);
	}

	// Search for matching 32-bit identifier
	SCommQueue* CCSCommon::searchCommQueueForTransactionId(SCommQueue* root, u32 tnTransactionId)
	{
		SCommQueue* cq;


		// Search through the list
		cq = root;
		while (cq)
		{
			// See if this entry has the specified transaction id
			if (cq->header.transactionId == tnTransactionId)
				return(cq);		// This is it

			// Move to next entry
			cq = cq->next;
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Appends the specified commPart to its related commQueue object (if this is a part that's
// being received from a previously started commQueue bit of traffic), or if it is a new item,
// then creates the related commQueue item on the partially received read commQueue.
//
// Note:  This function locks for read commQueue access.
//
//////
	SCommQueue* CCSCommon::appendToPartiallyReceivedReadCommQueue(SCommPart* cp)
	{
		SCommQueue*		cqNew;
		SCommQueue*		cqRet;
		SCommQueue*		cq;


		// Make sure there's something to do
		cqRet = NULL;
		if (cp)
		{
			// Lock the semaphore
			lockForCommQueueAccess(identity(), "appendToPartiallyReceivedReadCommQueue");

			// Iterate through any partially received items
			if (m_firstPartialCommQueueRead)
			{
				// Iterate through the existing items
				cq = m_firstPartialCommQueueRead;
				while (cq)
				{
					if (cq->header.transactionId == cp->header.transactionId)
					{
						// This is the transaction to which it belongs.
						appendThisPartInSequence(cq, cp);			// Append it to the correct location (in sequence).
						cqRet = cq;									// Set the return value for the item found
						goto unlockSemaphoreWhenFinished;			// All done
					}

					// Move to next item
					cq = cq->next;
				}
				// If we get here, it wasn't found
				// Fall through below to add it to the partially received commQueue
			}


			// Create commQueue entry
			cqNew = iCreateCommQueue(cp->header.command2, cp->header.command9, cp->header.ieIdentifier, cp->header.transactionId);
			if (cqNew)
			{
				// Update the missing info
				cqNew->header.maxBlocks = cp->header.maxBlocks;

				// Append this part to the to the new commQueue entry sequence
				appendThisPartInSequence(cqNew, cp);	// Note:  We call this function rather than just setting "cqNew->firstPart = cp" because it updates cqNew->header with regards to received blocks, plus possibly other future things in a one-stop shopping place

				//Append to the list of partial read commQueue items
				iAppendObjectToCommQueue(&m_firstPartialCommQueueRead, cqNew);
			}
			// Set the return value for the newly added item
			cqRet = cqNew;


unlockSemaphoreWhenFinished:
			// Unlock the semaphore
			unlockForCommQueueAccess(identity(), "appendToPartiallyReceivedReadCommQueue");
		}
		// Return the value
		return(cqRet);
	}




//////////
//
// Within the commQueue item, position this part where it's supposed to go (determined by
// its cp->header.thisBlock number, which is positioned where it should go) relative to other
// already received blocks.  This lets the blocks come in out-of-order and still be received
// internally or externally in the correct sequence.  It also allows for blocks that had to
// be re-sent (due to CRC error, or simply missing) to be inserted where they go.
//
//////
	void CCSCommon::appendThisPartInSequence(SCommQueue* cq, SCommPart* cpNew)
	{
		SCommPart*	cpLast;
		SCommPart*	cpTemp;
		SCommPart*	cp;


		// We have now received another block for this commQueue item
		// Update our received blocks entry
		++cq->header.receivedBlocks;
		iStoreCurrentTime(&cpNew->sendTime);

		// See where we are
		if (!cq->firstPart)
		{
			// It doesn't already exist, so this is the first one
			cq->firstPart	= cpNew;
			cpNew->next		= NULL;
			cpNew->prev		= NULL;

		} else {
			// There's at least one entry, so it will squeeze in here somewhere
			cpLast	= NULL;
			cp		= cq->firstPart;
			while (cp)
			{
				if (cp->header.thisBlock == cpNew->header.thisBlock)
				{
					// We've received a duplicate entry.
					// Ignore it.
					// Back off the received blocks count
					--cq->header.receivedBlocks;
					// Kill the duplicate (bad duplicate! ... bad duplicate!)
					iDeleteCommPartObject(cp);
					// And we're done
					return;

				} else  if (cp->header.thisBlock > cpNew->header.thisBlock) {
					// It goes before this one.
					if (!cpLast)
					{
						// This is the first one, so it goes at the start of the chain
						cpNew->prev		= NULL;
						cpNew->next		= cp;
						cp->prev		= cpNew;
						cq->firstPart	= cpNew;

					} else {
						// It's in the middle of the chain somewhere
						cpTemp			= cp->prev;
						cp->prev		= cpNew;
						cpNew->next		= cp;
						cpNew->prev		= cpTemp;
					}
					// All done!
					break;
				}

				// Move to next part in the chain
				cpLast = cp;
				cp = cp->next;
			}
			if (!cp)
			{
				// We didn't find one it goes before.
				// So, it goes at the end (note this is most typical as data will come in sequentially)
				// Note:  A speedup could be added here by storing the firstPart and lastPart and comparing the sequence to see if it's in sequence, and if so, then just update it without traversing the multiple parts.
				cpLast->next = cpNew;
			}
			// All done!
		}
		// Update this part's received time
		iStoreCurrentTime(&cq->lastReceivedTime);
	}




//////////
//
// Create a commQueue object based on the data in the specified part
//
//////
	SCommQueue* CCSCommon::createCommQueueObjectFromPart(SCommPart* cp)
	{
		SCommQueue* cq;


		// Create a new commQueue entry
		cq = (SCommQueue*)malloc(sizeof(SCommQueue));
		if (cq)
		{
			// Initialize it to emptiness
			memset(cq, 0, sizeof(SCommQueue));

			// Copy over the part's header
			memcpy(&cq->header, &cp->header, sizeof(SCommHeader));
			// All done!
		}
		return(cq);
	}




//////////
//
// Creates an new commQueue item
//
//////
	SCommQueue* CCSCommon::createCommQueueObjectFromScratch(CClient* cc, bool tlSetTransactionId)
	{
		SCommQueue* cq;


		// Create a new commQueue entry
		cq = (SCommQueue*)malloc(sizeof(SCommQueue));
		if (cq)
		{
			// Initialize it to emptiness
			memset(cq, 0, sizeof(SCommQueue));

			// Store the transactionId if needed
			if (tlSetTransactionId)
				cq->header.transactionId = cc->getNextTransactionId();
		}
		return(cq);
	}




//////////
//
// Creates an exact duplicate of the provided commQueueitem
//
//////
	SCommQueue* CCSCommon::duplicateCommQueueObject(SCommQueue* cq)
	{
		SCommQueue* cqNew;


		// Make sure there's something to do
		if (cq)
		{
			cqNew = (SCommQueue*)malloc(sizeof(SCommQueue));
			if (cqNew)
				memcpy(cqNew, cq, sizeof(SCommQueue));

		} else {
			// Hmmm...
			cqNew = NULL;
		}
		// All done
		return(cqNew);
	}




//////////
//
// Creates a acknowledgment response of the thing we've received
//
//////
	void CCSCommon::sendAckBack(SCommPart* cp)
	{
		SCommQueue* cqNew;


		// Create the entries for commQueue and part
		cqNew = createCommQueueObjectFromPart(cp);
		if (cqNew)
		{
			// Update the records
			// Indicate no chain follows, only a header being sent
			cqNew->firstPart			= NULL;
			cqNew->header.bytesOfData	= 0;


			// Store the pertinent information so the sender knows what we're acknowledging
			memcpy(&cqNew->header.command2, cgcAck, 2);								// Copy "AK" for acknowledge
			memset(&cqNew->header.command9, 32, 9);									// Copy spaces for the second part of the command
			cqNew->header.ieIdentifier			= cgcIMsg[0];						// "I" internal message
			cqNew->leaveOutOfSecondCommQueue	= true;								// We're only sending a header, we don't expect a response back to our acknowledgment
			cqNew->header.crc32					= 0;								// Not used for this ack response
			cqNew->header.crc16					= iComputeCrc16((s8*)&cqNew->header, sizeof(SCommHeader) - 2);
			// When we get here, we have our commQueue object prepared


			// lock the semaphore for access
			lockForCommQueueAccess(identity(), "sendAckBack");

			// Schedule it
			iAppendObjectToCommQueue(&m_firstCommQueueToSend, cqNew);

			// unlock the semaphore for access
			unlockForCommQueueAccess(identity(), "sendAckBack");
		}
	}




//////////
//
// Sends a ping response back upon receipt of a pinger
//
//////
	void CCSCommon::sendPingBack(SCommQueue* cq)
	{
		SCommQueue* cqNew;


		// Create the entries for commQueue and part
		cqNew = duplicateCommQueueObject(cq);


		// Update the records
		// Indicate no chain follows, only a header being sent
		cqNew->firstPart			= NULL;
		cqNew->header.bytesOfData	= 0;
		cqNew->header.thisBlock		= 1;
		cqNew->header.maxBlocks		= 1;


		// Store the pertinent information so the sender knows what we're acknowledging
		memcpy(&cqNew->header.command2, cgcPing, 2);							// Copy "PG" for acknowledge
		memset(&cqNew->header.command9, 32, 9);									// Copy spaces for the second part of the command
		cqNew->header.ieIdentifier			= cgcIMsg[0];						// "I" internal message
		cqNew->leaveOutOfSecondCommQueue	= true;								// We're only sending a header, we don't expect a response back to our acknowledgment
		cqNew->header.crc32					= 0;								// Not used for this ack response
		cqNew->header.crc16					= iComputeCrc16((s8*)&cqNew->header, sizeof(SCommHeader) - 2);
		// When we get here, we have our commQueue object prepared


		// lock the semaphore for access
		lockForCommQueueAccess(identity(), "sendPingBack");

		// Schedule it
		iAppendObjectToCommQueue(&m_firstCommQueueToSend, cqNew);

		// unlock the semaphore for access
		unlockForCommQueueAccess(identity(), "sendPingBack");
	}




//////////
//
// Sends a ping request to the other
//
//////
	void CCSCommon::sendPingRequest(CClient* cc)
	{
		SCommQueue* cqNew;
		SYSTEMTIME	lst;


		// lock the semaphore for access
		lockForCommQueueAccess(identity(), "sendPingRequest");

		// Create the entries for commQueue and part
		cqNew = createCommQueueObjectFromScratch(cc, true);

		// Update the records
		// Indicate no chain follows, only a header being sent
		cqNew->firstPart			= NULL;
		cqNew->header.bytesOfData	= 0;
		cqNew->header.thisBlock		= 1;
		cqNew->header.maxBlocks		= 1;


		// Store the pertinent information so the sender knows what we're acknowledging
		memcpy(&cqNew->header.command2, cgcPing, 2);							// Copy "PG" for acknowledge
		memset(&cqNew->header.command9, 32, 9);									// Copy spaces for the second part of the command
		cqNew->header.ieIdentifier			= cgcIMsg[0];						// "I" internal message
		cqNew->header.crc32					= 0;								// Not used for this ack response
		cqNew->header.crc16					= iComputeCrc16((s8*)&cqNew->header, sizeof(SCommHeader) - 2);
		// When we get here, we have our commQueue object prepared


		// Schedule it
		iAppendObjectToCommQueue(&m_firstCommQueueToSend, cqNew);

		// Note the time
		iStoreCurrentTime(&lst);
		setPingRequestTime(&lst);

		// unlock the semaphore for access
		unlockForCommQueueAccess(identity(), "sendPingRequest");
	}




//////////
//
// Acknowledges the specified commQueue part
//
//////
	void CCSCommon::acknowledgeCommQueuePart(SCommQueue* cqAck)
	{
		SCommQueue* cq;
		SCommPart*	cp;


		// lock the semaphore
		lockForCommQueueAccess(identity(), "acknowledgeCommQueuePart");

		// Make sure there's something to do
		if (m_firstUnackCommQueueSend)
		{
			// Iterate through every commQueue object and acknowledge the item found
			cq = m_firstUnackCommQueueSend;
			while (cq)
			{
				if (cq->header.transactionId == cqAck->header.transactionId)
				{
					// This is the commQueue object.
					// Acknowledge this part
					cp = cq->firstPart;
					while (cp)
					{
						if (cp->header.thisBlock == cqAck->header.thisBlock)
						{
							// This is it
							cp->header.ackSent = 1;
							goto finishByUnlockingTheSemaphore;
						}
						// Move to next part
						cp = cp->next;
					}
					// If we get here, the ack wasn't found.
					// It could've been a re-send of a previous ack that just came in late.
					// Regardless, we simply ignore it.
					break;
				}

				// Move to next commQueue object
				cq = cq->next;
			}
			// If we get here, it wasn't found
		}

finishByUnlockingTheSemaphore:
		// unlock the semaphore
		unlockForCommQueueAccess(identity(), "acknowledgeCommQueuePart");
	}




//////////
//
// Resends the specified thisBlock entry in the commQueue from its transactionId
//
//////
	void CCSCommon::resendCommQueueBlock(SCommQueue* cqBlock)
	{
		SCommQueue* cq;
		SCommPart*	cp;


		// lock the semaphore
		lockForCommQueueAccess(identity(), "resendCommQueueBlock");

		// Make sure there's something to do
		if (m_firstUnackCommQueueSend)
		{
			// Iterate through every commQueue object and resend the item found
			cq = m_firstUnackCommQueueSend;
			while (cq)
			{
				if (cq->header.transactionId == cqBlock->header.transactionId)
				{
					// This is the commQueue object.
					// Acknowledge this part
					cp = cq->firstPart;
					while (cp)
					{
						if (cp->header.thisBlock == cqBlock->header.thisBlock)
						{
							// This is it
							// Resend this block
							resendCommQueuePart(cq, cp);
							goto finishByUnlockingTheSemaphore;
						}
						// Move to next part
						cp = cp->next;
					}
					// If we get here, the specified block wasn't found.
					// Ignore it.
					break;
				}

				// Move to next commQueue object
				cq = cq->next;
			}
			// If we get here, it wasn't found
		}

finishByUnlockingTheSemaphore:
		// unlock the semaphore
		unlockForCommQueueAccess(identity(), "resendCommQueueBlock");
	}




//////////
//
// Creates an exact duplicate of the provided commPart item
//
//////
	SCommPart* CCSCommon::duplicateCommPartObject(SCommPart* cp)
	{
		SCommPart* cpNew;


		// Make sure there's something to do
		if (cp)
		{
			cpNew = (SCommPart*)malloc(sizeof(SCommPart));
			if (cpNew)
				memcpy(cpNew, cp, sizeof(SCommPart));

		} else {
			// Hmmm...
			cpNew = NULL;
		}
		// All done
		return(cpNew);
	}




//////////
//
// Creates a single message part from the header and data provided.
//
//////
	SCommPart* CCSCommon::createMessagePart(SCommHeader* ch, s8* tcData, u32 tnDataLength)
	{
		SCommPart* cp;


		// Make sure there is something to create
		cp = NULL;
		if (ch)
		{
			cp = (SCommPart*)malloc(sizeof(SCommPart));
			if (cp)
			{
				// Initialize the new structure
				memset(cp, 0, sizeof(SCommPart));

				// Store the data (we are not re-allocating, this process uses the existing buffer)
				memcpy(&cp->header, ch, sizeof(cp->header));
				cp->data		= tcData;
				cp->dataLength	= tnDataLength;
				// All done
			}
		}
		return(cp);
	}




//////////
//
// Called to check the partially received queue for items that may have been lost in transit.
//
//////
	void CCSCommon::checkPartialReadCommQueueItemsForMissingParts(void)
	{
		u32			lnI;
		bool		lbTimeForAction, lbFound;
		SCommQueue* cq;
		SCommPart*	cp;
		SYSTEMTIME	lst;


		// If anything's waiting, check the partial queues to see what the longest intervals are
		if (m_firstPartialCommQueueRead)
		{
			// Lock access to it
			lockForCommQueueAccess(identity(), "checkPartialReadCommQueueItemsForMissingParts");

			// Iterate through each item to see if any parts remain after the threshold
			cq = m_firstPartialCommQueueRead;
			while (cq)
			{
				// See if this item has been at least our timeout threshold yet
				if (iIsTimeEmpty(&cq->lastReceivedTime))
				{
					// We haven't received a response yet, so we find out how long it's been since we sent it
					// If it's greater than the timeout interval, that's the same as not receiving part of it for some time
					iStoreCurrentTime(&lst);
					lbTimeForAction = (iGetSystemtimeDiffInMilliseconds(&lst, &cq->sendTime) >= _CLISERV_RETRY_TIMEOUT_INTERVAL);

				} else {
					// There is a time, see how it's doing
					lbTimeForAction = (iGetSystemtimeDiffInMilliseconds(&cq->lastReceivedTime, &cq->sendTime) >= _CLISERV_RETRY_TIMEOUT_INTERVAL);
				}

				// If it's time for action, we move
				if (lbTimeForAction)
				{
					// This item needs to have resend requests on all the missing parts
					for (lnI = 1; lnI <= cq->header.maxBlocks; lnI++)
					{
						// See if we already have this part
						lbFound = false;
						cp = cq->firstPart;
						while (cp)
						{
							if (cp->header.thisBlock == lnI)
								break;	// We found it

							// Move to next part
							cp = cp->next;
						}
						// When we get here, we either found it or we didn't
						if (!cp)
							createResendCommand(cq, lnI);		// If we get here, we need to issue a resend request for this item
					}
					// When we get here, any resend requests were issued
				}

				// Move to next item
				cq = cq->next;
			}

			// Unlock access to it
			unlockForCommQueueAccess(identity(), "checkPartialReadCommQueueItemsForMissingParts");
		}
	}




//////////
//
// Called to create a resend command to put into the send queue to the other.
//
//////
	void CCSCommon::createResendCommand(SCommQueue* cq, u32 tnBlock)
	{
		SCommPart*	cp;
		SCommQueue*	cqNew;


		// Create a message part from it and store it for the specified commQueue entry
		cp = createMessagePart(&cq->header, NULL, 0);


		// Populate the header correctly
		memcpy(cp->header.command2, cgcResend, 2);			// "RS" for a request to resend this block
		memset(cp->header.command9, 0, sizeof(cp->header.command9));
		cp->header.thisBlock	= tnBlock;					// Block to resent
		cp->header.ieIdentifier = cgcIMsg[0];				// "I" for an internal command
		cp->header.bytesOfData	= 0;						// No data
		cp->header.crc32		= 0;						// No data, no CRC-32
		cp->header.crc16		= iComputeCrc16((s8*)&cp->header, sizeof(SCommHeader) - 2);
		// TransactionId carries through


		// Build a suitable commQueue object for it
		cqNew = createCommQueueObjectFromPart(cp);
		cqNew->firstPart = cp;


		// Append it to the to-send send queue.
		iAppendObjectToCommQueue(&m_firstCommQueueToSend, cqNew);
	}




//////////
//
// Creates a generic request command for the specified command9 plus data-to-follow
//
//////
	SCommQueue* CCSCommon::createGenericRequestCommand(CClient* cc, s8* tcCommand9, s8* tcData, u32 tnDataLength, u32* tnTransactionId)
	{
		SCommPart*	cp;
		SCommQueue*	cqNew;


		// Build a suitable commQueue object for it
int3_break;
		cqNew = createCommQueueObjectFromScratch(cc, false);
		if (cqNew)
		{
			// Store the transaction id
			if (tnTransactionId)
				*tnTransactionId = cqNew->header.transactionId;		// Store the transaction ID

			// Populate the header correctly
			memcpy(cqNew->header.command2, cgcRequest, 2);			// "RQ" for a request command
			memcpy(cqNew->header.command9, tcCommand9, 9);			// User-specified command
			cqNew->header.ieIdentifier	= cgcIMsg[0];				// "I" for an internal command
			cqNew->header.bytesOfData	= (u16)tnDataLength;		// Trailing data
			cqNew->header.crc32			= iComputeCrc32(tcData, tnDataLength);
			cqNew->header.crc16			= iComputeCrc16((s8*)&cqNew->header, sizeof(SCommHeader) - 2);
			// TransactionId carries through

			// Create a message part from it and store it for the specified commQueue entry
			cp = createMessagePart(&cqNew->header, tcData, tnDataLength);

			// Update the link
			cqNew->firstPart = cp;

			// Append it to the to-send send queue.
			iAppendObjectToCommQueue(&m_firstCommQueueToSend, cqNew);
		}
		return(cqNew);
	}




//////////
//
// Sets the most recent ping request time
//
//////
	void CCSCommon::setPingRequestTime(SYSTEMTIME* st)
	{
		memcpy(&m_lastPingRequest, st, sizeof(SYSTEMTIME));
	}




//////////
//
// Sets the most recent ping response time, and increases the total ping information
//
//////
	void CCSCommon::setPingResponseTime(SYSTEMTIME* st)
	{
		u32 lnDiff;


		// Store the ping response time
		memcpy(&m_lastPingAck, st, sizeof(SYSTEMTIME));

		// Compute the difference
		lnDiff				= (u32)iGetSystemtimeDiffInMilliseconds(&m_lastPingAck, &m_lastPingRequest);
		m_totalPingTimes	+= (f64)lnDiff;
		++m_totalPingCount;
	}




//////////
//
// Returns ping information for last ping time observed, and average ping time over lifetime of app
//
//////
	f32 CCSCommon::getLastPingTime(void)
	{
		f32 lfLast;

		lfLast = (f32)iGetSystemtimeDiffInMilliseconds(&m_lastPingAck, &m_lastPingRequest) / (f32)1000.0;
		if (lfLast > _CLISERV_PING_INTERVAL)
			return(getAveragePingTime());
		else
			return(lfLast);
	}

	f32 CCSCommon::getAveragePingTime(void)
	{
		return((f32)(m_totalPingTimes / (f64)m_totalPingCount / (f64)1000.0));
	}




//////////
//
// Concatenate the parts data into one contiguous block, rather than spread across multiple blocks
//
//////
	s8* CCSCommon::concatenatePartsData(SCommQueue* cq, u32* tnLength)
	{
		u32			lnOffset;
		SCommPart*	cp;
		s8*			lptr;


		// Make sure there's something to do
		lptr = NULL;
		if (cq && cq->firstPart && tnLength)
		{
			// Find out how big it is
			*tnLength = 0;
			cp = cq->firstPart;
			while (cp)
			{
				// Increase by this item's data length
				*tnLength += cp->dataLength;

				// Move to next part
				cp = cp->next;
			}
			// When we get here, we have the size computed

			// Make sure there's something to do
			if (*tnLength != 0)
			{
				// Create a single buffer to hold it all
				lptr = (s8*)malloc(*tnLength);
				if (lptr)
				{
					// Begin copying the parts
					lnOffset = 0;
					cp = cq->firstPart;
					while (cp)
					{
						// Copy this part
						memcpy(lptr + lnOffset, cp->data, cp->dataLength);

						// Move over by this copied block
						lnOffset += cp->dataLength;

						// Move to next part
						cp = cp->next;
					}
					// When we get here, everything's copied
				}
				//else can't allocate, so this process will fail
			}
			//else nothing to do
		}
		//else they're just toying with us
		return(lptr);
	}




//////////
//
// Processes internal requests, which are given by XML commands (assembled by this class as well).
// General XML format:
//		<cliserv>
//			<command cmd="whatever" options.../>
//		</cliserv>
//
// Commands currently supported:
//		<command cmd="msod" window="window title bar text (must be unique)"/>
//		<command cmd="msod" data="window title bar text (must be unique)" fullfetch="yes|no"/>
//
//////
	void CCSCommon::processRequest(SCommQueue* cq, s8* tcData, u32 tnDataLength)
	{
		CXml*	xml;
		CXml*	xmlCliserv;
		CXml*	xmlCommand;
		CXml*	xmlCmd;
// 		CXml*	xmlWindow;
// 		CXml*	xmlData;
// 		CXml*	xmlFullFetch;


		// Load the content for easy cruising
		xml = (CXml*)xml_load(tcData, tnDataLength);
		if ((u32)xml != -1 && (u32)xml != -2)
		{
			xmlCliserv = xml->get_child(cgcCliservRootTag);
			if (xmlCliserv)
			{
				// See what the commands are, and execute them one by one
				xmlCommand = xmlCliserv->get_child();
				while (xmlCommand)
				{
					// We are only processing commands
					if (xmlCommand->tagEquals(cgcCommand))
					{
						// This is a command
						xmlCmd = xmlCommand->get_attribute(cgcCmd);
						if (xmlCmd)
						{


						//////////
						// Process command
						//////
// 							if (xmlCmd->dataEqualsIgnoreCase(cgcWhateverCommand))
// 							{
// 								// We are processing this command
// 								xmlWindow	= xmlCommand->get_attribute(cgcWindow);
// 								xmlData		= xmlCommand->get_attribute(cgcData);
// 								if (xmlWindow)
// 								{
// 									// Attempt to ... the window
// 
// 								} else if (xmlData) {
// 									// Attempt to ... the data
// 								}
// 							}


						// Other commands will go here
						}
					}

					// Move to the next item
					xmlCommand = xmlCommand->get_next();
				}
				// When we get here, we've processed everything (or not)
				// But regardless, we are good to go
			}
		}
	}




//////////
//
// Called to see if the indicated host is the same
//
//////
	bool CCSCommon::compareHosts(hostent* host1, hostent* host2)
	{
		u32			lnI, lnJ;
		in_addr*	addr1;
		in_addr*	addr2;


		// Make sure our environment is sane
		if (host1 && host2 && (s16)host1->h_addrtype >= 0 && (s16)host2->h_addrtype >= 0)
		{
			// Iterate through each host
			for (lnI = 0; host1->h_addr_list[lnI] != 0; lnI++)
			{
				// Grab the first address
				addr1 = (in_addr*)host1->h_addr_list[lnI];

				// Compare against all others
				for (lnJ = 0; host2->h_addr_list[lnI] != 0; lnJ++)
				{
					// Grab the second address
					addr2 = (in_addr*)host2->h_addr_list[lnI];

					// Is it equal?
					if (addr1->S_un.S_addr == addr2->S_un.S_addr)
						return(true);		// Yes, a match
				}
			}
		}
		// If we get here, no match
		return(false);
	}




//////////
//
// Prepares an internal request for the other.
//
// General XML format:
//		<cliserv>
//			<command cmd="whatever" options.../>
//		</cliserv>
//
// Commands currently supported:
//		<command cmd="msod" window="window title bar text (must be unique)"/>
//
//////
// 	u32 CCSCommon::createMsodWindowImageCommand(s8* tcWindowTitle, u32 tnWindowTitleLength)
// 	{
// 		u32			lnXmlSize;
// 		CXml*		xml;
// 		CXml*		xmlCliserv;
// 		CXml*		xmlCommand;
// 		CXml*		xmlCmd;
// 		CXml*		xmlWindow;
// 		XmlData*	lrsWinTitle;
// 		s8*			lptr;			// Holds raw xml after being created
// 
// 
// 		// Create the xml for transmission as a request unto the other
// 		xml = createCommonXmlCommandFramework(&xmlCliserv, &xmlCommand, &xmlCmd, (s8*)cgcMsod, sizeof(cgcMsod) - 1);
// 		if (xml)
// 		{
// 			// We're good
// 			// Append the window title bar text
// 			lrsWinTitle = new XmlData(tcWindowTitle, tnWindowTitleLength);
// 			if (lrsWinTitle)
// 			{
// 				// Title is allocated
// 				xmlWindow = new CXml(new XmlData((s8*)cgcMsodWindow), lrsWinTitle);
// 				if (xmlWindow)
// 				{
// 					// If we get here, the XML expression has been built
// 
// 					// Pipe it to an output string
// 					lnXmlSize = xml->save(NULL, &lptr);
// 
// 					// Free up our memory
// 					delete xml;
// 
// 					// Create a command for it
// // TODO:  Working here
// //					createCommonXmlCommandFramework();
// 
// 				} else {
// 					// Failure
// 					delete xml;
// 				}
// 
// 			} else {
// 				// Failure
// 				delete xml;
// 			}
// 		}
// 		// All done!
// 		return((u32)xml);
// 	}




//////////
//
// Prepares an internal request for the other.
//
// General XML format:
//		<cliserv>
//			<command cmd="whatever" options.../>
//		</cliserv>
//
// Commands currently supported:
//		<command cmd="msod" data="window title bar text (must be unique)" fullfetch="Y|N"/>
//
//////
// 	u32 CCSCommon::createMsodWindowDataCommand(s8* tcWindowTitle, u32 tnWindowTitleLength, u32 tnFullFetch)
// 	{
// 		CXml*	xml;
// 		CXml*	xmlCliserv;
// 		CXml*	xmlCommand;
// 		CXml*	xmlCmd;
// 		CXml*	xmlData;
// 		CXml*	xmlFullFetch;
// 		s8		buffer[256];
// 
// 
// 		// Create the xml for transmission as a request unto the other
// 		xml = createCommonXmlCommandFramework(&xmlCliserv, &xmlCommand, &xmlCmd, (s8*)cgcMsod, sizeof(cgcMsod) - 1);
// 		if (xml)
// 		{
// 			// We're good
// 			memset(buffer, 0, sizeof(buffer));
// 			memcpy(buffer, tcWindowTitle, min(sizeof(buffer) - 1, tnWindowTitleLength));
// 			xmlData			= new CXml("data", buffer);
// 			xmlFullFetch	= new CXml("fullfetch", (s8*)((tnFullFetch == 0) ? cgcN : cgcY));
// 			xmlCommand->append_attribute(xmlData);
// 			xmlCommand->append_attribute(xmlFullFetch);
// 			// Right now, xmlCliserv contains the entire fully formed message
// 		}
// 		// All done!
// 		return((u32)xml);
// 	}




//////////
//
// Prepares the generic structure of an internal request made/sent/issued to the other.
//
// General XML format:
//		<cliserv>
//			<command cmd=""/>
//		</cliserv>
//
//////
	CXml* CCSCommon::createCommonXmlCommandFramework(CXml**	xmlCliserv,
													 CXml**	xmlCommand,
													 CXml**	xmlCmdAttribute,
													 s8*	tcCmd, u32 tnCmdLength,
													 s8*	tcTag)
	{
		CXml*		xml;
		XmlData*	tdData;


		// Create xml
		xml = new CXml();
		if (xml)
		{
			// Create cliserv tag
			*xmlCliserv = new CXml(new XmlData((s8*)cgcCliservRootTag));
			if (*xmlCliserv)
			{
				// Append cliserv tag
				xml->append_child(*xmlCliserv);

				// Create command tag
				*xmlCommand = new CXml(new XmlData((s8*)cgcCommand));
				if (*xmlCommand)
				{
					// Append command tag
					(*xmlCliserv)->append_child(*xmlCommand);

					// Create the cmd text itself
					if (tcCmd && tnCmdLength > 0)
					{
						tdData = new XmlData(tcCmd, tnCmdLength);

						// If the tag is not specified, force it to "cmd"
						if (!tcTag)
							tcTag = (s8*)cgcCmd;

						// Create the attribute tag
						*xmlCmdAttribute = new CXml(new XmlData(tcTag), tdData);
						if (*xmlCmdAttribute)
						{
							// Append the cmd attribute tag
							(*xmlCommand)->append_attribute(*xmlCmdAttribute);
							// We're good
							return(xml);

						} else {
							// Failure
							delete xml;
						}

					} else {
						// We're good
						return(xml);
					}

				} else {
					// Failure
					delete xml;
				}

			} else {
				// Failure
				delete xml;
			}

		}
		// If we get here, error (shouldn't ever happen, except out of memory)
		return(NULL);
	}




//////////
//
// Processes an xml command, sending it to the other
//
// Note:  This thread is spawned once for every request that comes in.  It handles all processing
//        relative to its needs, and then terminates after having filled everything.
//
//////
	u32 CCSCommon::sendCliservDataToOther(CCSCommon* cc, u8* tcData, u32 tnDataLength)
	{
		return(NULL);
	}




//////////
//
// Process an internal request.  Called once for every incoming request.
// Note:  This used to be in separate threads, but due to semaphore locking
//        it was changed.  In the future, it may be a good idea to switch
//        this to handle copies of data, and then to remove them from the
//        original, and if there is a failure or some other need, to add
//        them back in at that time.
//
//////
	void iProcessInternalRequest(SThreadParams* stp)
	{
		u32				lnLength;
		CClient*		client;
		CCSCommon*		cs;
		SCommQueue**	cqRoot;
		SCommQueue*		cq;
		SYSTEMTIME		lst;
		s8*				lptr;


		// Grab our parameters (Note, these are sent here from kickoffNextCommandToProcess() above)
		client		= (CClient*)		stp->extra;
		cq			= (SCommQueue*)		stp->extra2;
		cqRoot		= (SCommQueue**)	stp->extra3;
		cs			=					stp->cs;


		// See what the command is
// PING
		if (_memicmp(cq->header.command2, cgcPing, 2) == 0)
		{
			// We can only process ping stuff if we can check our unack commQueue
			// If we can't lock, this process will remain and will be kicked off in another millisecond or so
			// It's a ping request or response, we're not sure which yet.
			if (cs->searchCommQueueForCommand(cs->getUnackCommQueueSend(), (s8*)cgcPing, NULL, cq->header.transactionId))
			{
				// They are responding to our prior ping request
				// Note the time
				iStoreCurrentTime(&lst);
				cs->setPingResponseTime(&lst);
				// All done!

			} else {
				// They are pinging us
				cs->sendPingBack(cq);
			}
			// All done


// RESEND
		} else if (_memicmp(cq->header.command2, cgcResend, 2) == 0) {
			// It's a resend request (for something previously transmitted that was received in error, or was never received after a timeout)
			cs->resendCommQueueBlock(cq);


// REQUEST
		} else if (_memicmp(cq->header.command2, cgcRequest, 2) == 0) {
			// It's a request for something
			lptr = cs->concatenatePartsData(cq, &lnLength);
			cs->processRequest(cq, lptr, lnLength);
			free(lptr);


// FILL
		} else if (_memicmp(cq->header.command2, cgcFill, 2) == 0) {
			// They are filling a previous request issued by us
			Sleep(0);


// ACK
		} else if (_memicmp(cq->header.command2, cgcAck, 2) == 0) {
			// They are acknowledging a previously sent comm part
			// We'll test their acknowledgment agenda to see if they REALLY know what they're talking about
			cs->acknowledgeCommQueuePart(cq);


/*
// MASS ACK
		} else if (_memicmp(cq->header.command2, cgcMassAck, 2) == 0) {
			// They are acknowledging a group of previously sent comm parts
			Sleep(0);
			cq->isFinished = true;
*/


// UNKNOWN
		} else {
			// We don't know what it is.
			// We ignore it, mark it complete, let it go to the garbage pile, rubbish heap, trash dump.  In any event, it's outta here!
		}
		// When we get here, the command has been processed or not, but we're done
	}




//////////
//
// Creates a standard new commQueue entry with the most basic of information.
// Semaphore does not need to be used here.  Creates an orphan record.
//
//////
	SCommQueue* iCreateCommQueue(s8* tcCommand2, s8* tcCommand9, s8 ieIdentifier, u32 tnTransactionId)
	{
		SCommQueue* cq;


		// Make sure our environment is sane
		cq = NULL;
		if (tcCommand2)
		{
			// Allocate the commqueue header
			cq = (SCommQueue*)malloc(sizeof(SCommQueue));
			if (cq)
			{
				// Prepare the commQueue
				memset(cq, 0, sizeof(SCommQueue));

				// Copy the command2
				memcpy(&cq->header.command2, tcCommand2, 2);				// Two-digit command, one of PG, RS, RQ, FL, AK, MA or UT for ping, resend, request, fill, acknowledge, mass acknowledge or user transmission

				// Copy the command9
				if (tcCommand9)		memcpy(&cq->header.command9, tcCommand9, 9);	// Copy over the 9-byte sub-command
				else				memset(&cq->header.command9, 32, 9);			// Set it to spaces

				// Copy the ieIdentifier
				cq->header.ieIdentifier		= ieIdentifier;					// One digit code of I or E for Internal or External message, indicating whether it came from cliserv itself or a user app

				// Store the transaction number
				cq->header.transactionId	= tnTransactionId;				// A unique ID for this transaction
			}
		}
		// All done
		return(cq);
	}




//////////
//
// Called to determine how long a CommQueue message is.
//
//////
	u32 iGetCommQueueLength(SCommQueue* cq)
	{
		u32			lnLength;
		SCommPart*	cp;


		lnLength	= 0;
		cp			= cq->firstPart;
		while (cp)
		{
			// Append this packet size
			lnLength += cp->dataLength;

			// Move to next part
			cp = cp->next;
		}
		return(lnLength);
	}




//////////
//
// Called to take a large chunk of data and break it down into individual parts.  This is
// used so each part can be transmitted separately, with error checking handled on specific
// portions, re-sending only those portions without affecting the entire lengthy message.
//
//////
	// Note:  Upon entry, cq points to an existing SCommQueue and cq->ch to the main SCommHeader.
	//        This function will still create SCommPart entries for each portion, of which
	//        each has its own SCommHeader entry (just for that part).
	// Note:  At the end of processing, ch indicates how many total blocks/parts there are
	//        in the overall message.  The number of parts will range from 1 to N.
	// Note:  This process follows the proper protocol for communicating data between Cliserv self and others.
	//
	u32 iCreateMessageParts(CClient* cc, SCommQueue* cq, s8* tcData, u32 tnDataLength, u32 tnBlockSize)
	{
		u32				lnByteCount, lnBlock, lnBlocksWritten, lnThisSize, lnTotalSize;
		SCommPart**		cpPrev;
		SCommPart*		cp;
		SCommHeader*	ch;


		if (tnDataLength > 0 && tnBlockSize > sizeof(SCommHeader))
		{
			// Store the total bytes of data per item
			cq->header.bytesOfData	= (u16)tnBlockSize;		// Size of header + block transmitted per block

			// For the block size, we subtract off the size of our header (because it will be sent before each block, making the total block size correct when factored in)
			tnBlockSize				= tnBlockSize - sizeof(SCommHeader);
			cq->header.maxBlocks	= (tnDataLength / tnBlockSize) + 1;		// How many blocks are we sending?

			// Process through for each entry
			ch				= &cq->header;				// Grab an easier reference to the header
			cpPrev			= &cq->firstPart;			// Begin at the beginning
			lnByteCount		= 0;						// Each time we send a block, increases
			lnBlock			= 0;						// Current block number (begins at 1, see ++lnBlock below)
			lnBlocksWritten	= 0;						// Number of blocks written
			lnTotalSize		= 0;						// Total size of the entire message including all headers
			while (lnByteCount < tnDataLength)
			{
				// Prepare for this block/part
				++lnBlock;
				if (tnDataLength - lnByteCount >= tnBlockSize)		lnThisSize = tnBlockSize;
				else												lnThisSize = (tnDataLength - lnByteCount);


				// Create this part
				cp = (SCommPart*)malloc(sizeof(SCommPart));
				if (cp)
				{
					// Initialize the new entry
					memset(cp, 0, sizeof(SCommPart));

					// Update the back/forward links
					if (lnBlock != 1)
						cp->prev = *cpPrev;

					// Point forward to where we are now
					*cpPrev = cp;

					// Copy the existing header as a template
					memcpy(&cp->header, ch, sizeof(SCommHeader));

					// Update the portions
					cp->header.bytesOfData	= (u16)lnThisSize;
					cp->header.thisBlock	= lnBlock;

					// Copy the string for this block portion
					cp->data				= iDuplicateString(tcData + lnByteCount, lnThisSize, true);
					cp->dataLength			= lnThisSize;

					// Update simple CRC values
					cp->header.crc32		= iComputeCrc32(cp->data, lnThisSize);
					cp->header.crc16		= iComputeCrc16((s8*)&cp->header, sizeof(SCommHeader) - 2);

					// All done!
					++lnBlocksWritten;
				}


				// Prepare for the next part
				lnByteCount += lnThisSize;
				lnTotalSize	+= lnThisSize + sizeof(cp->header);
			}
			// When we get here, we're done creating everything

			// All done
			return(lnTotalSize);
		}
		// Error
		return(0);
	}




//////////
//
// Append the specified commQueue object to the specified commQueue queue. :-)
// Semaphore must be in place before calling this function.
//
//////
	void iAppendObjectToCommQueue(SCommQueue** root, SCommQueue* cqNew)
	{
		SCommQueue*	cq;


		// See if we're able to do anything
		if (root)
		{
			if (!*root)
			{
				// This is the first one
				*root = cqNew;

				// Make sure it's not pointing anywhere
				cqNew->next = NULL;
				cqNew->prev = NULL;

			} else {
				// We have to traverse the chain
				cq = *root;
				while (cq->next)
					cq = cq->next;			// Move to next entry

				// Update this entry on the chain
				cq->next	= cqNew;		// The last one points forward to this one
				cqNew->prev = cq;			// This one points backwards to the prevoius one
				cqNew->next = NULL;			// Forward into nothing
			}
		}
	}




//////////
//
// Removes the specified commQueue object from the specified commQueue if it exists.
// Semaphore must be in place before calling this function.
//
//////
	bool iDetachObjectFromCommQueue(SCommQueue** root, SCommQueue* cqDetach)
	{
		bool		lbDetached;
		SCommQueue*	cq;


		// Make sure there's a valid operation to perform
		lbDetached = false;
		if (root)
		{
			if (*root == cqDetach)
			{
				// This is the one to remove
				lbDetached = true;

				// We're deleting the first entry, so the first entry now becomes the one cqDetach was pointing to
				*root = cqDetach->next;

				// Set the one cdDeatch was pointing to back to nothing since it is now the first record
				if (cqDetach->next)		cqDetach->next->prev = NULL;

				// Detach this one's pointer
				cqDetach->next = NULL;				// This one points forward to nothing
				cqDetach->prev = NULL;				// This one points backward to nothing (which is should've already done anyway)
				// All done!

			} else {
				// We're deleting an entry in the chain after the first entry
				cq = (*root)->next;
				while (cq)
				{
					// Is this our man?
					if (cq == cqDetach)
					{
						// This is the one to remove
						lbDetached = true;

						// Update the links for the things around it so it is detached from the chain
						if (cq->prev)		cq->prev->next = cq->next;		// One before this points to the one after this
						if (cq->next)		cq->next->prev = cq->prev;		// One after this points to the one before this

						// Detach this one's pointers
						cq->next = NULL;					// This one points forward to nothing
						cq->prev = NULL;					// This one points backward to nothing

						// All done!
						break;
					}

					// Move to the next entry
					cq = cq->next;
				}
			}
		}
		return(lbDetached);
	}




//////////
//
// Called to delete a commQueue object, with everything it points to internally
// also being deleted. Semaphore must be in place before calling this function.
//
// Note: This SCommQueue record must be detached from any chains before deleted.
//       See iDetachObjectFromCommQueue.
//
//////
	bool iDeleteCommQueueObject(SCommQueue* cqDelete)
	{
		bool		lbDeleted;
		SCommPart*	cpNext;
		SCommPart*	cp;


		// Make sure there's something to do
		lbDeleted = false;
		if (cqDelete)
		{
			// Raise our flag
			lbDeleted = true;


			//////////
			// Delete all of its parts
			//////
				cp = cqDelete->firstPart;
				while (cp)
				{
					// Store the next entry
					cpNext = cp->next;

					// Delete this entry
					iDeleteCommPartObject(cp);

					// Move to next entry
					cp = cpNext;
				}
				// When we get here, everything's deleted
				cqDelete->firstPart = NULL;


			// Delete it
			free(cqDelete);
		}
		return(lbDeleted);
	}




//////////
//
// Called to delete a commPart object, including the data it's received.
// Semaphore must be in place before calling this function.
//
//////
	bool iDeleteCommPartObject(SCommPart* cpDelete)
	{
		bool lbDeleted;


		// Make sure there's something to do
		lbDeleted = false;
		if (cpDelete)
		{
			// Raise our flag
			lbDeleted = true;

			// Delete its data
			if (cpDelete->data)
			{
				free(cpDelete->data);
				cpDelete->data = NULL;
			}
			cpDelete->dataLength = 0;

			// Delete it
			free(cpDelete);
		}
		return(lbDeleted);
	}




//////////
//
// Called to append the specified commQueue item's contents to the read buffer.
// No checking is performed, the contents are merely copied as they are.
//
// Note:  The parts should already be in the correct order.
//
//////
	u32 iAppendCommQueueToUserReadBuffer(CCSCommon* cs, SCommQueue* cq)
	{
		u32			lnTotalBytes;
		SCommPart*	cp;


		// Make sure we have something to do
		lnTotalBytes = 0;
		if (cq)
		{
			// Iterate through each part, and store it
			cp = cq->firstPart;
			while (cp)
			{
				// Append this part
				lnTotalBytes += cp->dataLength;
				cs->appendToUserReadBuffer(cp->data, cp->dataLength);

				// Move to next part
				cp = cp->next;
			}
		}
		// Indicate the total
		return(lnTotalBytes);
	}




//////////
//
// Client reader thread used by multiple potential clients running simultaneously.
//
//////
	DWORD WINAPI iReader(LPVOID param)
	{
		u32				lnCrc32, lnMailId;
		u16				lnCrc16;
		s32				lnNumToRead, lnNumread;
		SThreadParams*	stp;
		CClient*		client;
		CServer*		server;
		CCSCommon*		cs;
		SCommQueue*		cq;
		SCommPart*		cp;
		SCommHeader		ch;
		hostent*		host;
		s8*				lptr;
		u8*				lcMail;
		u32				lnMailLength;
		in_addr*		ip;
		SParcel*		parcel;
		s8				buffer[256];


		// Grab our parameters
		stp		= (SThreadParams*)param;
		client	= stp->client;
		server	= stp->server;
		cs		= stp->cs;


		// Begin our loop
		while (1)
		{
			// Sleep briefly to release timeslice
			Sleep(1);

			// Read the header
			lnNumToRead = recv(cs->getSocket(), (s8*)&ch, sizeof(SCommHeader), 0);
			if (lnNumToRead > 0)
			{
				// There is data to read of packageSize bytes

				// Verify the header CRC-16
				lnCrc16 = iComputeCrc16((s8*)&ch, sizeof(SCommHeader) - 2);
				if (lnCrc16 == ch.crc16)
				{
					// We're good
					// Read the data
					lnNumToRead = (u32)ch.bytesOfData;
					if (lnNumToRead == 0)
					{
						// This was a header-only message, which means it's an internal command for something like a ping or resend request, something that just requires information in the header, no data after.
						if (ch.ieIdentifier == 'I' || ch.ieIdentifier == 'i')
						{
							// It's an internal request
							// Create a message part from it and store it for the specified commQueue entry
							cp = cs->createMessagePart(&ch, NULL, 0);

							// Append it to any partially received read queue.
							// iProcess() will dispatch it to be handled internally at its next iteration (or so the story goes that is...)
							cs->appendToPartiallyReceivedReadCommQueue(cp);

						} else {
							// An error!  Yes, an error I say!
							// An external request has come through with only a header and no data.
							// Uhh... that's not possible for an external (user) request.  Users MUST send data!
							// Somebody is messing with us.  This is not right.  And to be blunt, we will not tolerate such behavior!
							// Best to just ignore the packet and let everyone continue on nicely with their lives, ourselves included.
						}

					} else {
						// It has body data, so allocate and load it
						lptr = (s8*)malloc(lnNumToRead);
						// Append it to the read queue
						if (lptr)
						{
							lnNumread = recv(cs->getSocket(), lptr, lnNumToRead, 0);
							if (lnNumread != lnNumToRead)
							{
								// An error reading
								// Not sure what to do here...
// TODO:  figure out how to handle this not-read-condition properly, the header's been read, but no / not enough data
								_asm int 3;

							} else {
								// We're good
								// The data has been read directly into the temporary

								// Verify the CRC-32 portion
								lnCrc32 = iComputeCrc32(lptr, lnNumToRead);
								if (lnCrc32 == ch.crc32)
								{
									// We're good, we have a properly formed message and properly received data
									// Create a message part from it and store it for the specified commQueue entry
									// Note:  This consumes our lptr (rather than re-allocating)
									cp = cs->createMessagePart(&ch, lptr, lnNumToRead);

									// Send an acknowledgment back to the sender saying "Yeah, man, we got it, thanks for the effort!"
									cs->sendAckBack(cp);

									// Append it to any partially received read queue
									// Note:  We may be receiving a single message in one go, which is very likely actually for small transfers back-and-forth like chat.
									//        However, we still use the established rules for processing data:
									//            1)  We create a partially received entry
									//            2)  We populate into it with the 
									cq = cs->appendToPartiallyReceivedReadCommQueue(cp);


									// Clear out our temp pointer (the memory related to it is in cp->data right now
									lptr = NULL;

								} else {
// TODO:  figure out how to handle this condition.  We read the header and the data, but the CRC-32 didn't match.  Need to request a re-send.
									_asm int 3;
								}
							}

						} else {
							// An error increasing the read queue
							// Not sure what to do
// TODO:  figure out how to handle this out-of-memory condition
							Sleep(0);
						}
					}

				} else {
					// CRC-16 did not match
					// This is bad.  We've received some garbage, so what to do?
// TODO:  figure out how to handle invalid packet headers, which include bytes of data for the packet afterward, or when false data packets were injected into the server's port by a malicious app
					_asm int 3;
				}

			} else if (lnNumToRead == 0) {
				// The connection has been closed
				//////////
				// Notify the parent that we have a new client which has connected by mail parcel
				//////
					lcMail			= NULL;
					lnMailLength	= 0;
					host			= client->cscommon()->getClientHosts();

					// Ip address
					ip				= &client->cscommon()->getClientIpAddress()->sin_addr;
					sprintf(buffer, "%u.%u.%u.%u\0", (u32)ip->S_un.S_un_b.s_b1, (u32)ip->S_un.S_un_b.s_b2, (u32)ip->S_un.S_un_b.s_b3, (u32)ip->S_un.S_un_b.s_b4);
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcIpAddress, sizeof(cgcIpAddress) - 1, (u8*)buffer, strlen(buffer));

					// Port number
					if (server)		sprintf(buffer, "%u\0", server->cscommon()->getServerPortNum());
					else			sprintf(buffer, "%u\0", client->cscommon()->getClientPortNum());
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcPortNumber, sizeof(cgcPortNumber) - 1, (u8*)buffer, strlen(buffer));

					// The change (connection)
					iAppendLabelColonValueString(&lcMail, &lnMailLength, (u8*)cgcChangeType, sizeof(cgcChangeType) - 1, (u8*)cgcDisconnect, sizeof(cgcDisconnect) - 1);

					// Create the mail
					lnMailId = iStowMail(gsProcSelf, lcMail, lnMailLength, &parcel, false);

					// Release the mail
					free(lcMail);


				// Send to server or client this information
				if (server)
				{
					// The server's window needs to be notified that this has happened
					server->postHwndCallbackMessage(WMCLISERV_CLIENT_DISCONNECTED, lnMailId, ip->S_un.S_addr);

				} else if (client) {
					// The server's window needs to be notified that this has happened
					client->postHwndCallbackMessage(WMCLISERV_CLIENT_DISCONNECTED, lnMailId, ip->S_un.S_addr);
				}
				break;

			} else {
				// The receive operation failed
// TODO: When this receive operation fails, what do we do?  We're all wondering!
			}
		}
		// Control will never get here while the connection is active
		return(0);
	}




//////////
//
// Client sender thread used by multiple potential clients running simultaneously.
//
//////
	DWORD WINAPI iSender(LPVOID param)
	{
		s32				lnNumWritten;
		SThreadParams*	stp;
		CClient*		client;
		CCSCommon*		cs;


		// Grab our parameters
		stp		= (SThreadParams*)	param;
		client	= (CClient*)		stp->extra;
		cs		=					stp->cs;


		// Begin our loop
		while (1)
		{
			// See if there's anything to write
			if (cs->getSendQueueBytes() != 0)
			{
				// There is, there is, I do see a putty tat!
				//////////
				// Lock the semaphore
				//////
					cs->lockForSendBufferAccess(cs->identity(), "iSender");


				//////////
				// Write the data
				//////
					lnNumWritten = send(cs->getSocket(), cs->getSendBytesBuffer(), cs->getSendQueueBytes(), 0);
					if (lnNumWritten < 0)
					{
						// An error writing to the port
						// Not sure what to do with this ... could be a socket error

					} else {
						// We're good, remove it from the queue
						cs->resetSendQueueBuffer();
						cs->increaseTotalSendBytes(lnNumWritten);
					}


				//////////
				// Unlock the semaphore
				//////
					cs->unlockForSendBufferAccess(cs->identity(), "iSender");
			}

			// Sleep for 1/1000th of a second
			Sleep(1);
		}

		// Control will never return here, but to keep the compiler from going BLEH!
		return(0);
	}




//////////
//
// Static pinger thread, sends out a ping request every so often.
//
//////
	DWORD WINAPI iPinger(LPVOID param)
	{
		SThreadParams*	stp;
		CClient*		client;
		CCSCommon*		cs;


		// Grab our parameters
		stp		= (SThreadParams*)	param;
		client	= (CClient*)		stp->extra;
		cs		=					stp->cs;


		// Begin our loop
		while (1)
		{
			// It's time for a ping
			if (cs->tryLockForCommQueueAccess(cs->identity(), "schedulePingRequestIfNeeded"))
			{
				// Schedule a ping request if needed
//				cs->schedulePingRequestIfNeeded(client);

				// Unlock our semaphore
				cs->unlockForCommQueueAccess(cs->identity(), "schedulePingRequestIfNeeded");
			}

			// Wait the duration elapses
			Sleep(_CLISERV_PING_INTERVAL);
		}

		// Control will never return here while the connection is active
		return(0);
	}




//////////
//
// Looks for internal requests to process every so often.
// Reads commands, coordinates things and sends back responses.
//
//////
	DWORD WINAPI iProcess(LPVOID param)
	{
		bool			llProcessedAny;
		SThreadParams*	stp;
		CClient*		client;
		CCSCommon*		cs;


		// Grab our parameters
		stp		= (SThreadParams*)	param;
		client	= (CClient*)		stp->extra;
		cs		=					stp->cs;


		// Begin our loop
		while (1)
		{
			//////////
			// Process any receive / send items
			//////
				llProcessedAny = false;
				if (cs->tryLockForCommQueueAccess(cs->identity(), "parseReceivedCommQueueItems"))
				{
					llProcessedAny |= cs->parsePartiallyReceivedCommQueueItems(stp);	// Move (the now-fully received) partial commQueue entries into the received commQueue
					llProcessedAny |= cs->parseNextReceivedCommQueueItem(stp);			// Parse the next received commQueue item
					llProcessedAny |= cs->parseSendCommQueueItems(stp);					// Parse the next send commQueue item
					llProcessedAny |= cs->resendUnackCommQueueItems(stp);				// Check any aging sent-but-not-yet-acknowledged commQueue items, and resend them
					llProcessedAny |= cs->processAnyInternalCommands(stp);				// Process any internal commands that need to be processed

					// Unlock semaphore
					cs->unlockForCommQueueAccess(cs->identity(), "parseReceivedCommQueueItems");
				}


			//////////
			// If we're busy, then just release our timeslice.
			// If we're not busy, wait a couple ticks.
			/////
				Sleep(llProcessedAny ? _CLISERV_PROCESS_SLEEP_INTERVAL_BUSY : _CLISERV_PROCESS_SLEEP_INTERVAL_IDLE);
		}

		// Control will never return here while the connection is active
		return(0);
	}




//////////
//
// Every so many seconds, scans list of two things:
//
//		1)  Running processing threads (those spawned internally for internal commands) in watchdog list, to terminate those which exceed their interval
//		2)  Partially received data.  If a block has not been received when others around it have within th epast 5 seconds, it asks the other to resend.
//
//////
	DWORD WINAPI iWatchdog(LPVOID param)
	{
		SThreadParams*	stp;
		CClient*		client;
		CCSCommon*		cs;


		// Grab our parameters
		stp		= (SThreadParams*)	param;
		client	= (CClient*)		stp->extra;
		cs		=					stp->cs;


		// Begin our loop
		while (1)
		{
			// Move fully received partial commQueue entries into the received commQueue
			cs->checkPartialReadCommQueueItemsForMissingParts();


			//////////
			// Wait a spell
			/////
				Sleep(_CLISERV_WATCHDOG_SLEEP_INTERVAL);
		}

		// Control will never return here while the connection is active
		return(0);
	}




//////////
//
// Called to append a label:value to the existing string if any
//
//////
	void iAppendLabelColonValueString(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u8* tcValue, u32 tnValueLength)
	{
		u32		lnLength;
		u8*		lcData;


		// Make sure the environment is sane
		if (tcData && tnLength && tcLabel && tcValue && tnLabelLength != 0 && tnValueLength != 0)
		{
			// Allocate the memory
			lnLength	= *tnLength + tnLabelLength + tnValueLength + 2;
			lcData		= (u8*)malloc(lnLength);
			if (lcData)
			{
				//////////
				// Copy the existing part
				//////
					if (*tnLength != 0)
						memcpy(lcData, *tcData, *tnLength);


				//////////
				// Append the label
				//////
					memcpy(lcData + *tnLength,						tcLabel,	tnLabelLength);
					memcpy(lcData + *tnLength + 1 + tnLabelLength,	tcValue,	tnValueLength);

					// Append hard-coded components
					lcData[*tnLength + tnLabelLength]						= ':';		// Colon
					lcData[*tnLength + tnLabelLength + 1 + tnValueLength]	= 13;		// Carriage Return


				//////////
				// Free the original
				//////
					if (*tcData)
						free(*tcData);


				//////////
				// Update the pointer
				//////
					*tcData		= lcData;
					*tnLength	= lnLength;
			}
		}
	}

	void iAppendLabelColonValueInteger(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u32 tnValue)
	{
		s8 buffer[32];

		sprintf_s(buffer, sizeof(buffer), "%u\0", tnValue);
		iAppendLabelColonValueString(tcData, tnLength, tcLabel, tnLabelLength, (u8*)buffer, strlen(buffer));
	}

	void iAppendLabelColonValueFloat(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabeLlength, f32 tfValue, u32 tnIntegers, u32 tnDecimals)
	{
		s8 format[32];
		s8 buffer[32];

		sprintf_s(format, sizeof(format), "%%%u.%u%s\\0\0", tnIntegers, tnDecimals, "f");
		sprintf_s(buffer, sizeof(buffer), format, tfValue);
		iAppendLabelColonValueString(tcData, tnLength, tcLabel, tnLabeLlength, (u8*)buffer, strlen(buffer));
	}




//////////
//
// Called to prepend a label:value before the existing string if any
//
//////
	void iPrependLabelColonValueString(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u8* tcValue, u32 tnValueLength)
	{
		u32		lnLength;
		u8*		lcData;


		// Make sure the environment is sane
		if (tcData && tnLength && tcLabel && tcValue && tnLabelLength != 0 && tnValueLength != 0)
		{
			// Allocate the memory
			lnLength	= *tnLength + tnLabelLength + tnValueLength + 2;
			lcData		= (u8*)malloc(lnLength);
			if (lcData)
			{
				//////////
				// Copy the existing part
				//////
					if (*tnLength != 0)
						memcpy(lcData + tnLabelLength + 1 + tnValueLength + 1, *tcData, *tnLength);


				//////////
				// Prepend the label
				//////
					memcpy(lcData,						tcLabel,	tnLabelLength);
					memcpy(lcData + tnLabelLength + 1,	tcValue,	tnValueLength);

					// Append hard-coded components
					lcData[tnLabelLength]						= ':';		// Colon
					lcData[tnLabelLength + 1 + tnValueLength]	= 13;		// Carriage Return


				//////////
				// Free the original
				//////
					if (*tcData)
						free(*tcData);


				//////////
				// Update the pointer
				//////
					*tcData		= lcData;
					*tnLength	= lnLength;
			}
		}
	}

	void iPrependLabelColonValueInteger(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, u32 tnValue)
	{
		s8 buffer[32];

		sprintf_s(buffer, sizeof(buffer), "%u\0", tnValue);
		iPrependLabelColonValueString(tcData, tnLength, tcLabel, tnLabelLength, (u8*)buffer, strlen(buffer));
	}

	void iPrependLabelColonValueFloat(u8** tcData, u32* tnLength, u8* tcLabel, u32 tnLabelLength, f32 tfValue, u32 tnIntegers, u32 tnDecimals)
	{
		s8 format[32];
		s8 buffer[32];

		sprintf_s(format, sizeof(format), "%u.%u%s\\0\0", tnIntegers, tnDecimals, "f");
		sprintf_s(buffer, sizeof(buffer), format, tfValue);
		iPrependLabelColonValueString(tcData, tnLength, tcLabel, tnLabelLength, (u8*)buffer, strlen(buffer));
	}




//////////
//
// Called to obtain the value from a label:value if found
//
//////
	void iGetLabelColonValueString(u8* tcSource, u32 tnSourceLength, u8* tcLabel, u32 tnLabelLength, u8** tcText, u32* tnTextLength)
	{
		u32		lnLabelLength;
		u8*		lcLabel;


		// Locate the line
		iFindLine(tcSource, tnSourceLength, tcLabel, tnLabelLength, &lcLabel, &lnLabelLength, tcText, tnTextLength);
	}

	void iGetLabelColonValueInteger(u8* tcSource, u32 tnSourceLength, u8* tcLabel, u32 tnLabelLength, u32* tnValue)
	{
		u32		lnLabelLength, lnValueLength;
		u8*		lcLabel;
		u8*		lcValue;
		u8		buffer[64];


		// Locate the line
		if (iFindLine(tcSource, tnSourceLength, tcLabel, tnLabelLength, &lcLabel, &lnLabelLength, &lcValue, &lnValueLength))
		{
			memset(buffer, 0, sizeof(buffer));
			memcpy(buffer, lcValue, min(lnValueLength, sizeof(buffer) - 1));
			*tnValue = iiGet_u32(buffer, true);

		} else {
			// Not found
			*tnValue= 0;
		}
	}

	void iGetLabelColonValueFloat(u8* tcSource, u32 tnSourceLength, u8* tcLabel, u32 tnLabelLength, f32* tfValue)
	{
		u32		lnLabelLength, lnValueLength;
		u8*		lcLabel;
		u8*		lcValue;
		u8		buffer[64];


		// Locate the line
		if (iFindLine(tcSource, tnSourceLength, tcLabel, tnLabelLength, &lcLabel, &lnLabelLength, &lcValue, &lnValueLength))
		{
			memset(buffer, 0, sizeof(buffer));
			memcpy(buffer, lcValue, min(lnValueLength, sizeof(buffer) - 1));
			*tfValue = (f32)atof((s8*)&buffer[0]);

		} else {
			// Not found
			*tfValue= 0.0f;
		}
	}




//////////
//
// Called to find the specified label, and then locate the length of the label, the value start,
// and the value length.  Content is expected in the form produced by iAppendLabelColonValueString()
// and related functions, which is of the left-justified form:
//
//		|label1:value1[cr/lf]
//		|label2:value2[cr/lf]
//		|label3:value3[cr/lf][eof]
//
//////
	bool iFindLine(u8* tcSource, u32 tnSourceLength, u8* tcLabelSearch, u32 tnLabelSearchLength, u8** tcLabelFound, u32* tnLabelFoundLength, u8** tcValueFound, u32* tnValueFoundLength)
	{
		u32	lnI, lnLabelFound, lnColonFound;


		// Make sure our environment is sane
		if (tcSource && tcLabelSearch && tcLabelFound && tcValueFound)
		{
			// Begin scanning line by line looking for the search label (case-insensitive)
			for (lnI = 0; lnI < tnSourceLength - tnLabelSearchLength; )
			{
				////////]/
				// Is this a match?
				//////
					if (_memicmp(tcSource + lnI, tcLabelSearch, tnLabelSearchLength) == 0)
					{
						//////////
						// We found a match
						//////
							lnLabelFound = lnI;


						//////////
						// Find the colon
						//////
							for ( ; lnI < tnSourceLength && tcSource[lnI] != ':' && tcSource[lnI] != 13 && tcSource[lnI] != 10; )
								++lnI;	// Scanning forward to find a colon, CR or LF

							if (tcSource[lnI] == ':')
							{
								lnColonFound = lnI;


								//////////
								// Search for the end of line
								//////
									for ( ; lnI < tnSourceLength && tcSource[lnI] != 13 && tcSource[lnI] != 10; )
										++lnI;	// Scanning forward to find a CR or LF

								//////////
								// Update our caller's pointers
								//////
									*tcLabelFound			= tcSource + lnLabelFound;
									*tnLabelFoundLength		= lnColonFound - lnLabelFound;
									*tcValueFound			= tcSource + lnColonFound + 1;
									*tnValueFoundLength		= lnI - lnColonFound - 1;
									// All done
									return(true);
							}
							// If we get here, it wasn't found
					}


				//////////
				// Look for end of line
				//////
					for ( ; lnI < tnSourceLength - tnLabelSearchLength && tcSource[lnI] != 13 && tcSource[lnI] != 10; )
						++lnI;	// Scanning forward to find a CR or LF


				//////////
				// Continue while end of line characters
				//////
					for ( ; lnI < tnSourceLength - tnLabelSearchLength && (tcSource[lnI] == 13 || tcSource[lnI] == 10); )
						++lnI;	// Scanning forward to find the first character after CR or LF

				// When we get here, we're either at EOF or the start of the next line
			}
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Called to obtain the base-10 number from the pointer
//
//////
	u32 iiGet_u32(u8* tcNumber, bool tlSkipLeadingWhitespaces)
	{
		u32 lnI, lnValue;


		// Make sure the environment is sane
		lnValue = 0;
		if (tcNumber)
		{
			// Are we to skip past any leading whitespaces?
			lnI = 0;
			if (tlSkipLeadingWhitespaces)
			{
				// Skip past leading whitespaces using the clunky syntax
				for ( ; tcNumber[lnI] == 9 || tcNumber[lnI] == 32; )
					lnI++;
			}

			// Iterate as long as there are numbers
			for ( ; tcNumber[lnI] >= '0' && tcNumber[lnI] <= '9'; lnI++)
			{
				// Make room for this new 1s digit
				lnValue			= lnValue * 10;

				// Grab the 1s digit
				lnValue			= lnValue + (u32)(tcNumber[lnI] - '0');
			}
			// When we get here, lnValue has been derived
		}
		// Return the number
		return(lnValue);
	}




//////////
//
// Reads data from the mail pipe, returns that data as a pointer
//
//////
	u8* iReadFromPipe(SAppProc* tsProc, u32 tnReadSize, u32* tnActuallyRead)
	{
		u32		lnNumRead;
		u8*		lcData;


		// Make sure our environment is sane
		lcData = NULL;
		if (tsProc && tsProc->pipe && tsProc->pipe->handleRead && tnReadSize != 0)
		{
			// Allocate that much space
			lcData = (u8*)malloc(tnReadSize);
			if (lcData)
			{
				// Initialize our buffer to indicate failure should we fail
				memset(lcData, 0, tnReadSize);

				// Attempt to read that many bytes
				// Note:  If there isn't this much data already in the pipe, it will block the thread
				if (tnActuallyRead)		ReadFile((HANDLE)tsProc->pipe->handleRead, lcData, tnReadSize, tnActuallyRead,	NULL);
				else					ReadFile((HANDLE)tsProc->pipe->handleRead, lcData, tnReadSize, &lnNumRead,		NULL);
			}
		}
		// Return the pointer to our data
		return(lcData);
	}




//////////
//
// Stow the message in the mailbag for retrieval by the remote process
//
//////
	u32 iStowMail(SAppProc* tsProc, u8* tcText, u32 tnTextLength, SParcel** tsMail, bool tlIsEncrypted)
	{
		SParcel* mail;


		// Make sure we have something to do
		if (tsProc && tcText)
		{
			// Store the mail
			mail = iAppendMail(&tsProc->mailbag, tcText, tnTextLength, true, tlIsEncrypted);
			if (mail)
			{
				// If they want the mail parcel also, give it to them
				if (tsMail)
					*tsMail = mail;

				// Return the mail id
				return(mail->uniqueId);
			}
		}
		// Indicate failure
		return(-1);
	}




//////////
//
// Called to create a  mail parcel based on the full text of the received message
// in multiple parts.
//
//////
	u32 iStowMailFromCommQueue(SAppProc* tsProc, CCSCommon* cs, SCommQueue* cq, SParcel** tsMail, bool tlIsEncrypted)
	{
		u32			lnLength;
		SCommPart*	cp;
		u8*			ptr;
		SParcel*	mail;


		// Make sure our environment is sane
		if (tsProc && cs && cq)
		{
			// Determine how big the total message is
			lnLength = iGetCommQueueLength(cq);
			if (lnLength != 0)
			{
				// Create the mail
				mail = iAppendMailByLength(&tsProc->mailbag, lnLength, tlIsEncrypted);
				if (mail)
				{
					// Store it if they requested it
					if (tsMail)
						*tsMail = mail;


					//////////
					// Populate the mail area with the actual data
					//////
						ptr	= mail->data;
						cp	= cq->firstPart;
						while (cp)
						{
							// Copy this part
							memcpy(ptr, cp->data, cp->dataLength);
							ptr += cp->dataLength;

							// Move to next part
							cp = cp->next;
						}
						// When we get here, the mail is populated


					// Delete the CommQueue object and its parts
					return(mail->uniqueId);
				}
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Append the indicated message to the mailbag, and return the unique id for this mail
//
//////
	SParcel* iAppendMail(SParcel** mailbagRoot, u8* tcText, u32 tnTextLength, bool tlCopyString, bool tlIsEncrypted)
	{
		SParcel*	mailNew;
		SParcel*	mail;
		SParcel**	mailPrev;


		// Make sure we have a proper pointer
		if (mailbagRoot && tcText && tnTextLength != 0)
		{
			if (!*mailbagRoot)
			{
				// This is the first mail item
				mailPrev = mailbagRoot;

			} else {
				// append to the end of the chain
				mail = *mailbagRoot;
				while (mail->next)
					mail = mail->next;
				mailPrev = &mail->next;
			}

			// Create the new mailbag entry
			mailNew = (SParcel*)malloc(sizeof(SParcel));
			if (mailNew)
			{
				// Initialize the entry
				memset(mailNew, 0, sizeof(SParcel));

				// Update the back-link
				*mailPrev = mailNew;

				// Store our settings
				if (tlCopyString)
				{
					// Spin off a copy
					iCopyString(&mailNew->data, &mailNew->dataLength, tcText, tnTextLength, false);

				} else {
					// Just store it
					mailNew->data			= tcText;
					mailNew->dataLength		= tnTextLength;
				}

				// Store the unique id, encryption
				mailNew->encrypted	= tlIsEncrypted;
				mailNew->uniqueId	= iGetNextUniqueId();

				// All done
				return(mailNew);
			}
		}
		// Indicate failure
		return(NULL);
	}




//////////
//
// Append the indicated mail by length and return the pointer to it
//
//////
	SParcel* iAppendMailByLength(SParcel** mailbagRoot, u32 tnTextLength, bool tlIsEncrypted)
	{
		SParcel*	mailNew;
		SParcel*	mail;
		SParcel**	mailPrev;


		// Make sure we have a proper pointer
		if (mailbagRoot && tnTextLength != 0)
		{
			if (!*mailbagRoot)
			{
				// This is the first mail item
				mailPrev = mailbagRoot;

			} else {
				// append to the end of the chain
				mail = *mailbagRoot;
				while (mail->next)
					mail = mail->next;
				mailPrev = &mail->next;
			}

			// Create the new mailbag entry
			mailNew = (SParcel*)malloc(sizeof(SParcel));
			if (mailNew)
			{
				// Initialize the entry
				memset(mailNew, 0, sizeof(SParcel));

				// Update the back-link
				*mailPrev = mailNew;

				// Store our settings
				mailNew->data			= (u8*)malloc(tnTextLength);
				memset(mailNew->data, 0, tnTextLength);
				mailNew->dataLength		= tnTextLength;
				mailNew->encrypted		= tlIsEncrypted;
				mailNew->uniqueId		= iGetNextUniqueId();

				// All done
				return(mailNew);
			}
		}
		// Indicate failure
		return(NULL);
	}




//////////
//
// Called to search for the indicated mail parcel.
// Note:  We only search our own incoming mail bag.
//
//////
	SParcel* iFindMail(u32 tnMailId)
	{
		return(iFindMailInProc(gsProcSelf, tnMailId));
	}




//////////
//
// Called to search for the indicated mail parcel.
// Note:  We only search our own incoming mail bag.
//
//////
	SParcel* iFindMailInProc(SAppProc* tsProc, u32 tnMailId)
	{
		SParcel* mail;


		if (tsProc)
		{
			// Iterate through all parcels
			mail = tsProc->mailbag;
			while (mail)
			{
				// See if this is our man
				if (mail->uniqueId == tnMailId)
					break;		// We found it

				// Move to next parcel
				mail = mail->next;
			}
			// Indicate our status
			return(mail);
		}
		// Not a valid process
		return(NULL);
	}




//////////
//
// Called to
//
//////
	SParcel* iReceiveAndStowMail(SAppProc* tsProc, u32 tnMailMessageSize, u32 tnMailMessageId)
	{
		u32			lnLocalMailId, lnNumread;
		u8*			ldata;
		SParcel*	parcel;


		// Make sure our environment is sane
		if (tsProc)
		{
			// Grab the mail message
			ldata = iReadFromPipe(tsProc, tnMailMessageSize, &lnNumread);
			if (ldata)
			{
				// Store the mail message
				lnLocalMailId = iStowMail(tsProc, ldata, tnMailMessageSize, &parcel, false);
				if (lnLocalMailId != -1)
				{
					// Store the remote mailId value
					parcel->remoteMailId = tnMailMessageId;
					return(parcel);
				}
				// If we get here, failure, release our read mail
				free(ldata);
			}
		}
		// If we get here, failure
		return((SParcel*)NULL);
	}




//////////
//
// Called to delete a mail parcel from a mail bag
//
//////
	u32 iDeleteMailParcel(u32 tnMailId)
	{
		SParcel*	mail;
		SParcel**	mailBackLink;


		// Iterate through all our received parcels
		mail			= gsProcSelf->mailbag;
		mailBackLink	= &gsProcSelf->mailbag;
		while (mail)
		{
			// See if this is our man
			if (mail->uniqueId == tnMailId)
			{
				// Yes, delete this item

				// Update the back-link
				*mailBackLink = mail->next;

				// Delete this item
				if (mail->data)
					free(mail->data);

				// Free itself
				free(mail);

				// All done!
				return(0);
			}

			// Move to next parcel
			mailBackLink	= &mail->next;
			mail			= mail->next;
		}
		// If we get here, wasn't found (so technically it's already deleted -- right? :-))
		return(-1);
	}




//////////
//
// Called to validate the email to see if it contains the SParcelForBind structure
//
//////
	s32 iValidateBoundEmail(SParcel* tsMail, SParcelDelivery* tsBindMail)
	{
		// Make sure our environment is sane
		if (tsMail && tsBindMail && tsMail->dataLength >= sizeof(SParcelDelivery) - sizeof(s8*) - sizeof(s8*))
		{
			// We're looking at the data
			memcpy(tsBindMail, tsMail->data, sizeof(SParcelDelivery));
			tsBindMail->messageType	= tsMail->data + sizeof(SParcelDelivery);
			tsBindMail->content		= tsBindMail->messageType + tsBindMail->messageTypeLength;
			if (tsMail->dataLength == sizeof(SParcelDelivery) + tsBindMail->messageTypeLength + tsBindMail->contentLength)
			{
				// We're good in terms of size, but how are we in terms of SHA1-32?
				if (!iValidateParcelDeliverySha1s(tsBindMail))
					return(0);		// Failure

				// If we get here, the header is valid
				return(1);
			}
		}
		// If we get here, failure
		return(0);
	}




//////////
//
// Returns the next unique ID in a running total
//
//////
	u32 iGetNextUniqueId(void)
	{
		u32 lnUniqueId;


		// Lock the semaphore
		EnterCriticalSection(&gsemUniqueId);

		// Get the unique Id
		lnUniqueId = gnNextUniqueId++;

		// Unlock the semaphore
		LeaveCriticalSection(&gsemUniqueId);

		// All done!
		return(lnUniqueId);
	}




//////////
//
// Called to compute the SHA1-32 bit value
// For now we don't use a true SHA-1 algorithm, but just add up the bytes.
//
//////
	u32 iComputeSha1_32(u8* tcData, u32 tnDataLength)
	{
		u32 lnI, lnValue;


		// Value
		lnValue = 0;
		if (tcData)
		{
			// We iterate through each byte an do a computation
			for (lnI = 0; lnI < tnDataLength; lnI++)
			{
				lnValue +=	(u32)tcData[lnI]										+		/* base character */
							iShiftLeft((u32)iSwapBits(tcData[lnI]),			8)		+		/* reverse bit order of base character */
							iShiftLeft((u32)         (255 - tcData[lnI]),	16)		+		/* 255 - base character */
							iShiftLeft((u32)iSwapBits(255 - tcData[lnI]),	24);			/* reverse bit order of (255 - base character) */
			}
		}
		// Indicate our value
		return(lnValue);
	}




//////////
//
// Called to swap the bits of an 8-bit character
//
//////
	u8 iSwapBits(u8 tcChar)
	{
		u8 lc;


		// Swap the bits
		lc	=	((tcChar & 0x1)  << 7) |		/* bit 1 to bit 8 */
				((tcChar & 0x2)  << 5) |		/* bit 2 to bit 7 */
				((tcChar & 0x4)  << 3) |		/* bit 3 to bit 6 */
				((tcChar & 0x8)  << 1) |		/* bit 4 to bit 5 */
				((tcChar & 0x10) >> 1) |		/* bit 5 to bit 4 */
				((tcChar & 0x20) >> 3) |		/* bit 6 to bit 3 */
				((tcChar & 0x40) >> 5) |		/* bit 7 to bit 2 */
				((tcChar & 0x80) >> 7);			/* bit 8 to bit 1 */

		// Indicate the new value
		return(lc);
	}




//////////
//
// Called to shift the 32-bit value left, and wrap the most significant bit around
// to the least significant bit.
//
//////
	u32 iShiftLeft(u32 tnValue, u32 tnBits)
	{
		u32 lnI;


		// Rotate the bits around off the end back to the beginning
		for (lnI = 0; lnI < tnBits; lnI++)
			tnValue = ((tnValue & 0x8000000) != 0 ? 1 : 0) | (tnValue << 1);

		// Indicate the new result
		return(tnValue);
	}




//////////
//
// Called to validate a parcel delivery to make sure it is properly validated
//
//////
	bool iValidateParcelDeliverySha1s(SParcelDelivery* tsPd)
	{
		// Check some header info
		if (!iValidateParcelDeliverylSha1_32_lftve_mt_c(tsPd))
			return(false);		// Failure 

		// Check messageType text
		if (!iValidateParcelDeliverySha1_32_messageType(tsPd))
			return(false);		// Failure 

		// Check content body
		if (!iValidateParcelDeliverySha1_32_content(tsPd))
			return(false);		// Failure 

		// Check in its entirety
		if (!iValidateParcelDeliverySha1_32_all(tsPd))
			return(false);		// Failure 

		// We're good
		return(true);
	}




//////////
//
// Called to compute the SHA1-32 value on the indicated portion of the SParcelForBind header
//
//////
	bool iValidateParcelDeliverylSha1_32_lftve_mt_c(SParcelDelivery* tsBindMail)
	{
		u32		lnSha1_32;


		// Compute the sha1-32 value
		lnSha1_32	= 0;
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->totalMessageLength,	4);
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->fromId,				4);
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->toId,					4);
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->nValue,				4);
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->nExtra,				4);
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->messageTypeLength,	4);
		lnSha1_32	+=	iComputeSha1_32((u8*)&tsBindMail->contentLength,		4);
		return(tsBindMail->sha1_32_lftve_mt_c == lnSha1_32);
	}




//////////
//
// For now we don't use a true SHA-1 algorithm, but just add up the bytes
//
//////
	bool iValidateParcelDeliverySha1_32_messageType(SParcelDelivery* tsPd)
	{
		return(tsPd->messageTypeSha1_32 == iComputeSha1_32(tsPd->messageType, tsPd->messageTypeLength));
	}




//////////
//
// For now we don't use a true SHA-1 algorithm, but just add up the bytes
//
//////
	bool iValidateParcelDeliverySha1_32_content(SParcelDelivery* tsPd)
	{
		return(tsPd->contentLengthSha1_32 == iComputeSha1_32(tsPd->content, tsPd->contentLength));
	}




//////////
//
// For now we don't use a true SHA-1 algorithm, but just add up the bytes
//
//////
	bool iValidateParcelDeliverySha1_32_all(SParcelDelivery* tsPd)
	{
		u32		lnSha1_32;


		// Compute the sha1-32 value
		lnSha1_32	= 0;
		lnSha1_32	+=	iComputeSha1_32((u8*)tsPd,					sizeof(SParcelDelivery) - sizeof(s8*)/*content*/ - sizeof(s8*)/*messageType*/ - sizeof(u32)/*sha1_32_all*/);
		lnSha1_32	+=	iComputeSha1_32((u8*)tsPd->messageType,		tsPd->messageTypeLength);
		lnSha1_32	+=	iComputeSha1_32((u8*)tsPd->content,			tsPd->contentLength);
		return(tsPd->sha1_32_all == lnSha1_32);
	}




//////////
//
// Called to do the exactly equals function as in VFP
//
//////
	bool iEqualEqual(u8* tcLeft, u32 tnLeftLength, u8* tcRight, u32 tnRightLength)
	{
		// Must be the same length to be exactly equal
		if (tnLeftLength == tnRightLength)
			return(_memicmp(tcLeft, tcRight, tnLeftLength) == 0);		// Returns true or false if equal

		// If we get here, does not equal
		return(false);
	}




//////////
//
// Computes simple CRC-32 and CRC-16 algorithms
//
//////
	u32 iComputeCrc32(s8* tcData, u32 tnDataLength)
	{
		u32 lnI, lnCrc32, lnNibble, lnValue;


		// Iterate through every byte performing a simple calculation
		lnCrc32 = 0x12345678;
		for (lnI = 0; lnI < tnDataLength; lnI++)
		{
			lnNibble	= (lnI % 8) * 4;
			lnValue		= ((u32)tcData[lnI]) << lnNibble;
			lnCrc32		+= lnValue;
		}
		// All done
		return(lnCrc32);
	}


	u16 iComputeCrc16(s8* tcData, u32 tnDataLength)
	{
		u16 lnCrc16, lnValue;
		u32 lnI, lnNibble;


		// Iterate through every byte performing a simple calculation
		lnCrc16 = 0x1234;
		for (lnI = 0; lnI < tnDataLength; lnI++)
		{
			lnNibble	= (lnI % 4) * 4;
			lnValue		= ((u16)tcData[lnI]) << lnNibble;
			lnCrc16		+= lnValue;
		}
		// All done
		return(lnCrc16);
	}

	u32 iComputeCrc32_1(s8* tcData, u32 tnDataLength)
	{
		return(iComputeCrc32(tcData, tnDataLength));
	}

	u32 iComputeCrc32_2(s8* tcData, u32 tnDataLength)
	{
		u32 lnI, lnCrc32, lnNibble, lnValue;


		// Iterate through every byte performing a simple calculation
		lnCrc32 = 0x12345678;
		for (lnI = 0; lnI < tnDataLength; lnI++)
		{
			lnNibble	= (8 - (lnI % 8)) * 4;
			lnValue		= ((u32)tcData[lnI]) << lnNibble;
			lnCrc32		+= lnValue;
		}
		// All done
		return(lnCrc32);
	}

	u32 iComputeCrc32_3(s8* tcData, u32 tnDataLength)
	{
		u32 lnI, lnCrc32, lnNibble, lnValue;


		// Iterate through every byte performing a simple calculation
		lnCrc32 = 0x11227788;
		for (lnI = 0; lnI < tnDataLength; lnI++)
		{
			lnNibble	= (lnI % 16) * 2;
			lnValue		= ((u32)tcData[lnI]) << lnNibble;
			lnCrc32		+= lnValue;
		}
		// All done
		return(lnCrc32);
	}

	u32 iComputeCrc32_4(s8* tcData, u32 tnDataLength)
	{
		u32 lnI, lnCrc32, lnNibble, lnValue;


		// Iterate through every byte performing a simple calculation
		lnCrc32 = 0xfedcba98;
		for (lnI = 0; lnI < tnDataLength; lnI++)
		{
			lnNibble	= (16 - (lnI % 16)) * 2;
			lnValue		= ((u32)tcData[lnI]) << lnNibble;
			lnCrc32		+= lnValue;
		}
		// All done
		return(lnCrc32);
	}

	u32 iComputeCrc32_5(s8* tcData, u32 tnDataLength)
	{
		u32 lnI, lnCrc32, lnNibble, lnValue;


		// Iterate through every byte performing a simple calculation
		lnCrc32 = 0x88866511;
		for (lnI = 0; lnI < tnDataLength; lnI++)
		{
			lnNibble	= lnI % 32;
			lnValue		= ((u32)tcData[lnI]) << lnNibble;
			lnCrc32		+= lnValue;
		}
		// All done
		return(lnCrc32);
	}




//////////
//
// Called to duplicate the specified string
//
/////
	s8* iDuplicateString(s8* tcData, s32 tnDataLength, bool tlIncludeTrailingNull, bool tlTrimLeadingSpaces, bool tlTrimTrailingSpaces)
	{
		return((s8*)iDuplicateString((u8*)tcData, tnDataLength, tlIncludeTrailingNull, tlTrimLeadingSpaces, tlTrimTrailingSpaces));
	}

	u8* iDuplicateString(u8* tcData, s32 tnDataLength, bool tlIncludeTrailingNull, bool tlTrimLeadingSpaces, bool tlTrimTrailingSpaces)
	{
		s32		lnLeading, lnTrailing;
		u8*		lcData;


		// Make sure our environment is sane
		lcData = NULL;
		if (tcData)
		{
			// Populate our length if need be
			if (tnDataLength == -1)
				tnDataLength = strlen((s8*)tcData);


			//////////
			// If we need to trim off leading spaces, let's do so
			//////
				if (tlTrimLeadingSpaces)
				{
					// Skip past leading spaces
					for (lnLeading = 0; lnLeading < tnDataLength; lnLeading++)
					{
						// When we find a non-space, exit
						if (tcData[lnLeading] != 32)
							break;
					}
					// When we get here, we're at the end of string, or the first non-space

				} else {
					// No leading spaces
					lnLeading = 0;
				}


			//////////
			// If we need to trim off trailing spaces, let's do so
			//////
				if (tlTrimTrailingSpaces)
				{
					// Skip past trailing spaces
					for (lnTrailing = 0; lnLeading + lnTrailing < tnDataLength; lnTrailing++)
					{
						// When we find a non-space, exit
						if (tcData[tnDataLength - lnTrailing - 1] != 32)
							break;
					}
					// When we get here, we're at the end of string, or the first non-space

				} else {
					// No trailing spaces
					lnTrailing = 0;
				}


			//////////
			// Allocate our buffer (with the optional trailing null added on)
			//////
				lcData = (u8*)malloc(tnDataLength - lnLeading - lnTrailing + ((tlIncludeTrailingNull) ? 1 : 0));
				if (lcData)
				{
					// Copy over our data
					memcpy(lcData, tcData + lnLeading, tnDataLength - lnLeading - lnTrailing);

					// NULL-terminate if need be
					if (tlIncludeTrailingNull)
						lcData[tnDataLength - lnLeading - lnTrailing] = 0;
				}
		}
		// Indicate our status
		return(lcData);
	}




//////////
//
// Copy the string over (if null-terminated, returns the length without the null termination
// character, even though it exists as well.
//
//////
	void iCopyString(u8** tcDst, u32* tnDstLength, u8* tcSrc, u32 tnSrcLength, bool tlNullTerminate)
	{
		u32 lnLength;


		// Make sure our parameters are sane
		if (tcSrc && tcDst)
		{
			// Create a copy of the memory area
			lnLength = tnSrcLength + ((tlNullTerminate) ? 1 : 0);
			*tcDst = (u8*)malloc(lnLength);
			if (*tcDst)
			{
				// Copy over, set the length
				if (tlNullTerminate)
					(*tcDst)[tnSrcLength] = 0;				// NULL terminate the string

				// Copy the string portion
				memcpy(*tcDst, tcSrc, tnSrcLength);

				// Store the destination length if they want it
				if (tnDstLength)
					*tnDstLength = tnSrcLength;

			} else {
				// Unable to copy
				if (tnDstLength)
					*tnDstLength = 0;		// Indicate our failure
			}
		}
	}
