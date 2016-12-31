// GameServer.cpp
//
// server
// for 
// SoftServe ITA
//
// Nicholas Tsaruk
// fbt.ksnv@gmail.com
//

#include "Includes\stdafx.hpp"
#include "Includes\HttpServer.hpp"

using namespace std;

void fHandler(int signal);
void * pGlobalServing = nullptr;
int	main(int argc, char* argv[])
{
    // TODO: read setting from parsed *.ini file, i.e., from STL map
	
	HttpServer * pHttp_server = new HttpServer(27015, "Root");
	pGlobalServing = (void*)pHttp_server;
    signal(SIGINT, fHandler); // listen for SIGINT (aka control-c), if it comes // call function named fHandler
	pHttp_server->fRun();
	delete pHttp_server;
}

/**
 * Handles signals.
 */
void fHandler(int signal)
{
    if (signal == SIGINT) // control-c
    {
		delete pGlobalServing;
		exit(-1);
    }
}