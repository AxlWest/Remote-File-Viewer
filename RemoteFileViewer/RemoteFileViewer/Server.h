#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT "1313"
#define DEFAULT_BUFFER_LENGTH 512

class Server
{
	private :

		int result ;
		int receiveBufferLength ;
		int bytesReceived ;
		int senderAdderSize ;

		char receiveBuffer[DEFAULT_BUFFER_LENGTH] ;

		bool loop ;
		bool acceptingAClient ;

		struct addrinfo* addressInfo ;
		struct addrinfo hints ;

		sockaddr_in rxAdder ;
		sockaddr_in senderAdder ;
		
		WSADATA wsaData ;

		//TCP sockets
		SOCKET clientSocket ;
		SOCKET listenSocket ;

	public :

		Server(void) ;
		~Server(void) ;
		int init(void) ;

		int runServer(void) ;
} ;

