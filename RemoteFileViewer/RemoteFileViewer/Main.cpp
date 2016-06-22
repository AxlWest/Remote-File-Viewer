#include "Server.h"

int main(int argc , char* argv[])
{
	Server* server ;
	server = new Server() ;

	if(server->init() != 0)
	{
		return 1 ;
	}

	server->runServer() ;

	if(server != NULL)
	{
		delete server ;
		server = NULL ;
	}

	return 0 ;
}