// GameServer.cpp
//
// server
// for 
// SoftServe ITA
//
// Nicholas Tsaruk
// fbt.ksnv@gmail.com
//

#include "Includes/stdafx.hpp"
#include "Includes/HttpServer.hpp"
#include "Includes/IniParser.hpp"

using namespace std;

void fHandler(int signal);
void fParseRequest(std::string &path, std::map <std::string, std::string> &http_headers);
void fUserLogIn(std::string &json_response);
HttpServer* pHttp_server;


int main(int argc, char* argv[])
{
	// read data from config.in file
		//IniParser* pIni_parser = new IniParser("config.ini");
		//auto params = pIni_parser->fGetParams();



	// start HTTP server with correct termination
		//pHttp_server = new HttpServer(stoi(params["server.port"]), params["server.root"]);
		pHttp_server = new HttpServer(33000, "Root/");

		pHttp_server->fGenerateResponse = &fParseRequest;
		signal(SIGINT, fHandler); // listen for SIGINT (aka control-c), if it comes call function named fHandler
		pHttp_server->fRun(); // server's loop waiting for user connections

    // clear memory // sclose socets (in destructors, etc)
		delete pHttp_server;
		//delete pIni_parser;
}




/**
 * Handles user, OS signals.
 */
void fHandler(int signal)
{
    if (signal == SIGINT) // signal == Ctrl+C
    {
		delete pHttp_server;
		exit(-1);
    }
}

/**
 * parses request string 
 */
void fParseRequest(std::string &path, std::map <std::string, std::string> &http_headers)
{
	string response = "";
    if (path.find("/api/")) // if it is not found or if it is not in the beginning
	{
		response = "{\"error\": \"incorrect api call\"}";
	}
	else
	{
		if (path.find("/api/userlogin") != string::npos)
			fUserLogIn(response);
		else
			response = "{\"error\": \"script is not implemented\"}";
	}
	pHttp_server->fSetResponse(response.data(), response.length(), "JSON");
}

/**
 * parses request string 
 */
void fUserLogIn(std::string &json_response)
{
	json_response = "{\"status\":\"success\", \"session\": \"abcdefj12345notyetimplemented\"}";
}

