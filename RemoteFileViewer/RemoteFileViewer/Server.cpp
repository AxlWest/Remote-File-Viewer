#include "Server.h"

Server::Server(void)
{
	this->result = 0 ;
	this->receiveBufferLength = DEFAULT_BUFFER_LENGTH ;
	this->bytesReceived = 0 ;
	this->senderAdderSize = 0 ;
	
	this->addressInfo = NULL ;

	this->loop = true ;
	this->acceptingAClient = true ;

	this->listenSocket = INVALID_SOCKET ;
	this->clientSocket = INVALID_SOCKET ;
}

Server::~Server(void)
{
}

int Server::init(void)
{
	this->result = WSAStartup(MAKEWORD(2 , 2) , &wsaData) ;

	if(result != 0)
	{
		//WSA failed to start correctly
		//Return 1 for failure
		return 1 ;
	}
	else
	{
		this->senderAdderSize = sizeof(this->senderAdder) ;

		return 0 ;
	}
}

int Server::runServer(void)
{
	ZeroMemory(&this->hints , sizeof(this->hints)) ;

    this->hints.ai_family = AF_INET ;
    this->hints.ai_socktype = SOCK_STREAM ;
    this->hints.ai_protocol = IPPROTO_TCP ;
    this->hints.ai_flags = AI_PASSIVE ;

	this->result = getaddrinfo(NULL , DEFAULT_PORT , &this->hints , &this->addressInfo) ;

    if(this->result != 0) 
    {
        WSACleanup() ;
        return 1 ;
    }

	this->listenSocket = socket(this->addressInfo->ai_family , this->addressInfo->ai_socktype , this->addressInfo->ai_protocol) ;

	if(this->listenSocket == INVALID_SOCKET) 
    {
        freeaddrinfo(this->addressInfo) ;
        WSACleanup() ;

        return 1 ;
    }

	BOOL optVal = TRUE;
    int optLen = sizeof(BOOL);

    if(setsockopt(this->listenSocket , SOL_SOCKET , SO_REUSEADDR , (char*)&optVal , optLen) == SOCKET_ERROR)
    {

        closesocket(this->listenSocket) ;
        WSACleanup() ;

        return 1 ;
    }

	this->result = bind(this->listenSocket , this->addressInfo->ai_addr , (int)this->addressInfo->ai_addrlen) ;

    if(this->result == SOCKET_ERROR) 
    {
		freeaddrinfo(this->addressInfo) ;
		closesocket(this->listenSocket) ;
        WSACleanup() ;

        return 1 ;
    }

	freeaddrinfo(this->addressInfo) ;


	this->result = listen(this->listenSocket , SOMAXCONN) ;
		
	if(this->result == SOCKET_ERROR) 
	{
		freeaddrinfo(this->addressInfo) ;
		closesocket(this->listenSocket) ;
		WSACleanup() ;

		return 1 ;
	}

	do
	{
		if(this->acceptingAClient == true)
		{
			this->clientSocket = accept(this->listenSocket  , NULL , NULL) ;



			
		}
	}
	while(this->loop == true) ;

	WSACleanup() ;
	return 0 ;
}