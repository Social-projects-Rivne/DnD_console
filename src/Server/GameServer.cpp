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
	JSON json_request = http_headers[(string)"Content"];

	Database pData_base;
	data_base.fConnect("localhost", "user", "password", "database");
	string query = "SELECT id, username, password FROM Users WHERE username="+json_request["username"]+" password="+json_request["password"]+";";

	JSON json_result = data_base.fExecuteQuery(query);
	string query_result = json_result["Result"];
	if (query_result == "Success")
	{
		if (stoi(json_result["Rows"]) > 0)
		{
			string user_id = json_result["data"][0]["id"];
			query = "SELECT user_id FROM Sessions WHERE user_id="+user_id+";";
			json_result = data_base.fExecuteQuery(query);
			if (query_result == "Success")
			{
				if (stoi(json_result["Rows"]) > 0) // get current active session
					json_response = "{\"status\":\"already logged in\", \"session_id\": \""+json_result["data"][0]["id"]+"\"}";
				else // create new session
				{
					query = "INSERT INTO Sessions (user_id) VALUES ("+user_id+");";
					json_result = data_base.fExecuteQuery(query);
					query = "SELECT LAST_INSERT_ID() AS id FROM Sessions";
					json_result = data_base.fExecuteQuery(query);
					json_response = "{\"status\":\"success\", \"session_id\": \""+json_result["data"][0]["id"]+"\"}";
				}
			}
			else
				json_response = "{\"status\":\"fail\", \"message\": \"database error\"}";
		}
		else
			json_response = "{\"status\":\"fail\", \"message\": \"no such user or provided password is incorrect\"}";
	}
	else
		json_response = "{\"status\":\"fail\", \"message\": \"database error\"}";
}

