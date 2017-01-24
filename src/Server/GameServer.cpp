// GameServer.cpp
//
// server
// for 
// SoftServe ITA
//
// Nicholas Tsaruk and Olha Leskovska
// fbt.ksnv@gmail.com, olhalesk@gmail.com
//

#include "Includes/stdafx.hpp"
#include "Includes/HttpServer.hpp"
#include "Includes/IniParser.hpp"
#include "Includes/DataBase.hpp"
#include "Includes/DataValidator.hpp"

using namespace std;

void fHandler(int signal);
void fParseRequest(std::string &path, std::map <std::string, std::string> &http_headers);
void fUserLogIn(std::string &json_response, nlohmann::json &json_request);
bool fRetrieveUserId(std::string &id_user, std::string &session_id);
void fSaveTerrain(std::string &json_response, nlohmann::json &json_request);
void fSaveNpc(std::string &json_response, nlohmann::json &json_request);
void fSendTerrain(std::string &json_response, nlohmann::json &json_request);
void fSendDefinedTerrains(std::string &json_response, nlohmann::json &json_request);
void fSendOwnTerrainsList(std::string &json_response, nlohmann::json &json_request);
void fUserRegistration(std::string &json_response, nlohmann::json &json_request);
HttpServer* pHttp_server;
DataBase data_base;


int main(int argc, char* argv[])
{
    // read data from config.ini file
    IniParser pIni_parser("config.ini");
    auto params = pIni_parser.fGetParams();

    /*for (auto & param: params)
    {
    	cout << param.first + " " + param.second + "\n";
    }*/

    // connect to database
    nlohmann::json json_result = data_base.fConnection(params["database.host"], params["database.username"], params["database.password"], params["database.name"]);
    cout << "data_base.fConnection returned:\n" << json_result << endl;
    cout << json_result["result"] << endl;
    // start HTTP server with correct termination
    pHttp_server = new HttpServer(stoi(params["server.port"]), params["server.root"]);
    // pHttp_server = new HttpServer(15000, "Root/");

    pHttp_server->fGenerateResponse = &fParseRequest; // assign callback function
    signal(SIGINT, fHandler); // listen for SIGINT (aka control-c), if it comes call function named fHandler
    pHttp_server->fRun(); // server's loop waiting for user connections

                          // clear memory and sclose socets (in destructors, etc)
    delete pHttp_server;
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
        response = "{\"error\": \"incorrect api call\"}";
    else
    {
    	if (http_headers.find((string)"Content") == http_headers.end())
    		cout<<"Client must provide \"Content\" http header in his request."<<endl;
    	else
    	{
        	string request_data_content = "";
        	request_data_content = http_headers[(string)"Content"];
        	cout<<request_data_content<<endl;
            if (!request_data_content.length())
                response = "{\"error\": \"request content is empty\"}";
            else
            {
                nlohmann::json json_request = json::parse(request_data_content.c_str());
                cout<<"json_request:"<<json_request<<endl;
                if (path.find("/api/userlogin") != string::npos)
                    fUserLogIn(response, json_request);
                else if (path.find("/api/userregister") != string::npos)
                fUserRegistration(response, json_request);
                else if (path.find("/api/addterrain") != string::npos)
                    fSaveTerrain(response, json_request);
                else if (path.find("/api/loadterrain") != string::npos)
                    fSendTerrain(response, json_request);
                else if (path.find("/api/loaddefinedterrains") != string::npos)
                    fSendDefinedTerrains(response, json_request);
                else if (path.find("/api/loadmyterrainslist") != string::npos)
                    fSendOwnTerrainsList(response, json_request);
                else if (path.find("/api/addnpc") != string::npos)
                    fSaveNpc(response, json_request);
                else
                    response = "{\"error\": \"script is not implemented\"}";
            }
    	}
    }
    pHttp_server->fSetResponse(response.data(), response.length(), "JSON");
}

/**
* parses request string
*/
void fUserLogIn(std::string &json_response, nlohmann::json &json_request)
{
    string username = json_request["username"];
    string password = json_request["password"];
    string query = "SELECT id, username, password FROM Users WHERE username='" + username + "' AND password='" + password + "';";

    nlohmann::json json_result = data_base.fExecuteQuery(query);
    cout << query << "\nRESULT:\n" << json_result << endl;
    string query_result = json_result["result"];
    if (query_result == "success")
    {
        string rows = json_result["rows"];
        if (stoi(rows) > 0)
        {
            string id_user = json_result["data"][0]["id"];

            query = "SELECT id FROM Sessions WHERE id_user=" + id_user + ";";
            json_result = data_base.fExecuteQuery(query);
            cout << query << "\nRESULT:\n" << json_result << endl;
            query_result = json_result["result"];

            if (query_result == "success")
            {
                rows = json_result["rows"];
                cout << "rows:" << rows << "; stoi(rows):" << stoi(rows) << ";\n";
                if (stoi(rows) > 0) // get current active session
                {
                    cout << "case 1\n";
                    string session_id = json_result["data"][0]["id"];
                    json_response = "{\"status\":\"already logged in\", \"session_id\": \"" + session_id + "\"}";
                }
                else // create new session
                {
                    cout << "case 2\n";
                    query = "INSERT INTO Sessions (id_user) VALUES (" + id_user + ");";
                    json_result = data_base.fExecuteQuery(query);
                    cout << query << "\nRESULT:\n" << json_result << endl;
                    query = "SELECT LAST_INSERT_ID() AS id FROM Sessions";
                    json_result = data_base.fExecuteQuery(query);
                    cout << query << "\nRESULT:\n" << json_result << endl;
                    string session_id = json_result["data"][0]["id"];
                    json_response = "{\"status\":\"success\", \"session_id\": \"" + session_id + "\"}";
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

void fUserRegistration(std::string &json_response, nlohmann::json &json_request)
{
    string username = json_request["username"];
    string password = json_request["password"];
    string email = json_request["email"];

    if (DataValidator::fValidate(username, DataValidator::NAME) &&
        DataValidator::fValidate(password, DataValidator::PASSWORD) &&
        DataValidator::fValidate(email, DataValidator::EMAIL)) // checks data
    {
        string query = "INSERT INTO Users (username, password, email, is_active) VALUES ('" + username + "', '" + password + "', '" + email + "', 0);"; // creates query
        nlohmann::json json_result = data_base.fExecuteQuery(query); // executes query
        cout << json_result << endl;
        string query_result = json_result["result"];
        if (query_result == "success")
            json_response = "{\"status\":\"success\", \"message\": \"registered\"}";
        else
            json_response = "{\"status\":\"fail\", \"message\": \"database error\"}";
    }
    else
        json_response = "{\"status\":\"fail\", \"message\": \"invalid data\"}";
}

bool fRetrieveUserId(std::string &id_user, std::string &session_id)
{
    string query = "SELECT id_user FROM Sessions WHERE id = " + session_id;
    nlohmann::json json_result = data_base.fExecuteQuery(query);
    cout << query << "\nRESULT:\n" << json_result << endl;
    string query_result = json_result["result"];
    if (query_result == "success")
    {
        string rows = json_result["rows"];
        if (stoi(rows) > 0)
        {
            id_user = json_result["data"][0]["id_user"];
            return 1;
        }
    }
    return 0;
}


void fSaveTerrain(std::string &json_response, nlohmann::json &json_request)
{
    string session_id = json_request["session_id"];
    string id_user;
    if (fRetrieveUserId(id_user, session_id))
    {
    	cout<<"USER("<<id_user<<") is logged in\n";
        string name = json_request["name"];
        string width = json_request["width"];
        string height = json_request["height"];
        string description = json_request["description"];
        string query = "INSERT INTO Terrain (name, width, height, description, id_owner) VALUES ('" + name + "', " + width + ", " + height + ", '" + description + "', " + id_user + ");";
        nlohmann::json json_result = data_base.fExecuteQuery(query);
        cout << query << "\nRESULT:\n" << json_result << endl;
        string query_result = json_result["result"];

        if (query_result == "success")
        {
            query = "SELECT LAST_INSERT_ID() AS id FROM Terrain";
            json_result = data_base.fExecuteQuery(query);
            cout << query << "\nRESULT:\n" << json_result << endl;
            string terrain_id = json_result["data"][0]["id"];
            json_response = "{\"status\":\"success\", \"terrain_id\": \"" + terrain_id + "\"}";
        }
        else
            json_response = "{\"status\":\"fail\", \"message\": \"terrain is not added, sql query execution failed\"}";
    }
    else
        json_response = "{\"status\":\"fail\", \"message\": \"you are not logged in\"}";
}


void fSaveNpc(std::string &json_response, nlohmann::json &json_request)
{
    string session_id = json_request["session_id"];
    string id_user;
    if (fRetrieveUserId(id_user, session_id))
    {
        string name         = json_request["npc"];
        string type_npc     = json_request["type"];
        string hitpoints    = json_request["hitpoints"];
        string level        = json_request["level"];
        string strength     = json_request["strength"];
        string dexterity    = json_request["dexterity"];
        string constitution = json_request["constitution"];
        string intelligence = json_request["intelligence"];
        string wisdom       = json_request["wisdom"];
        string charisma     = json_request["charisma"];

        string query = "INSERT INTO NPCs (name, type_npc, hitpoints, level, strength, dexterity, constitution, intelligence, wisdom, charisma, id_owner) VALUES ('"+name+"', '"+type_npc+"', '"+hitpoints+"', '"+level+"', '"+strength+"', '"+dexterity+"', '"+constitution+"', '"+intelligence+"', '"+wisdom+"', '"+charisma+"', '"+id_user+"');";
        nlohmann::json json_result = data_base.fExecuteQuery(query);
        cout << query << "\nRESULT:\n" << json_result << endl;
        string query_result = json_result["result"];

        if (query_result == "success")
        {
            query = "SELECT LAST_INSERT_ID() AS id FROM NPCs";
            json_result = data_base.fExecuteQuery(query);
            cout << query << "\nRESULT:\n" << json_result << endl;
            string npc_id = json_result["data"][0]["id"];
            json_response = "{\"status\":\"success\", \"npc_id\": \"" + npc_id + "\"}";
        }
        else
            json_response = "{\"status\":\"fail\", \"message\": \"npc is not added, sql query execution failed\"}";
    }
    else
        json_response = "{\"status\":\"fail\", \"message\": \"you are not logged in\"}";
}

void fSendTerrain(std::string &json_response, nlohmann::json &json_request)
{
    string session_id = json_request["session_id"];
    string id_user;
    if (fRetrieveUserId(id_user, session_id))
    {
        string terrain_id = json_request["terrain_id"];
        string query = "SELECT name, width, height, description, id_owner FROM Terrain WHERE id = " + terrain_id + ";";
        nlohmann::json json_result = data_base.fExecuteQuery(query);
        cout << query << "\nRESULT:\n" << json_result << endl;
        string query_result = json_result["result"];

        if (query_result == "success")
        {
            string rows = json_result["rows"];
            if (stoi(rows) > 0)
            {
                string terrain = json_result["data"][0]["name"];
                string width = json_result["data"][0]["width"];
                string height = json_result["data"][0]["height"];
                string description = json_result["data"][0]["description"];
                string id_owner = json_result["data"][0]["id_owner"];
                json_response = "{\"status\":\"success\", \"terrain\": \"" + terrain + "\", \"terrain_id\": \"" + terrain_id + "\", \"width\": \"" + width + "\", \"height\": \"" + height + "\", \"description\": \"" + description + "\", \"id_owner\": \"" + id_owner + "\"}";
            }
            else
                json_response = "{\"status\":\"fail\", \"message\": \"no terrain that you own with the specified id\"}";
        }
        else
            json_response = "{\"status\":\"fail\", \"message\": \"terrain is not loaded, sql query execution failed\"}";
    }
    else
        json_response = "{\"status\":\"fail\", \"message\": \"you are not logged in\"}";
}

void fSendDefinedTerrains(std::string &json_response, nlohmann::json &json_request)
{
    string session_id = json_request["session_id"];
    string id_user;
    if (fRetrieveUserId(id_user, session_id))
    {
        string type = json_request["type"];
        string count = json_request["count"];
        string query = "SELECT id, name, width, height, description, id_owner FROM Terrain LIMIT "+count+";";
        nlohmann::json json_result = data_base.fExecuteQuery(query);
        cout << query << "\nRESULT:\n" << json_result << endl;
        string query_result = json_result["result"];

        if (query_result == "success")
        {
            string rows = json_result["rows"];
            int rows_qtt = stoi(rows);
            if (rows_qtt > 0)
            {
                json_response = "{\"status\":\"success\", \"terrains_quantity\":\"" + rows + "\", \"list\": [";
                while (rows_qtt--)
                {
                    string terrain_id = json_result["data"][rows_qtt]["id"];
                    string terrain = json_result["data"][rows_qtt]["name"];
                    string width = json_result["data"][rows_qtt]["width"];
                    string height = json_result["data"][rows_qtt]["height"];
                    string description = json_result["data"][rows_qtt]["description"];
                    string id_owner = json_result["data"][rows_qtt]["id_owner"];
                    json_response += "{\"terrain\": \"" + terrain + "\", \"terrain_id\": \"" + terrain_id + "\", \"width\": \"" + width + "\", \"height\": \"" + height + "\", \"description\": \"" + description + "\", \"id_owner\": \"" + id_owner + "\"}";
                    if (rows_qtt)
                        json_response += ",";
                }
                json_response += "]}";
            }
            else
                json_response = "{\"status\":\"warning\", \"message\": \"list of your terrains is empty\"}";
        }
        else
            json_response = "{\"status\":\"fail\", \"message\": \"list of your terrains is not loaded, sql query execution failed\"}";
    }
    else
        json_response = "{\"status\":\"fail\", \"message\": \"you are not logged in\"}";
}

void fSendOwnTerrainsList(std::string &json_response, nlohmann::json &json_request)
{
    string session_id = json_request["session_id"];
    string id_user;
    if (fRetrieveUserId(id_user, session_id))
    {
        string query = "SELECT id, name, width, height, description, id_owner FROM Terrain WHERE id_owner=" + id_user + ";";
        nlohmann::json json_result = data_base.fExecuteQuery(query);
        cout << query << "\nRESULT:\n" << json_result << endl;
        string query_result = json_result["result"];

        if (query_result == "success")
        {
            string rows = json_result["rows"];
            int rows_qtt = stoi(rows);
            if (rows_qtt > 0)
            {
                json_response = "{\"status\":\"success\", \"terrains_quantity\":\"" + rows + "\", \"list\": [";
                while (rows_qtt--)
                {
                	cout<<"hello, dear client\n";
                    string terrain_id = json_result["data"][rows_qtt]["id"];
                    string terrain = json_result["data"][rows_qtt]["name"];
                    string width = json_result["data"][rows_qtt]["width"];
                    string height = json_result["data"][rows_qtt]["height"];
                    string description = json_result["data"][rows_qtt]["description"];
                    string id_owner = json_result["data"][rows_qtt]["id_owner"];
                	cout<<"half way\n";
                    json_response += "{\"terrain\": \"" + terrain + "\", \"terrain_id\": \"" + terrain_id + "\", \"width\": \"" + width + "\", \"height\": \"" + height + "\", \"description\": \"" + description + "\", \"id_owner\": \"" + id_owner + "\"}";
                    if (rows_qtt)
                        json_response += ",";
                }
                json_response += "]}";
            }
            else
                json_response = "{\"status\":\"warning\", \"message\": \"list of your terrains is empty\"}";
        }
        else
            json_response = "{\"status\":\"fail\", \"message\": \"list of your terrains is not loaded, sql query execution failed\"}";
    }
    else
        json_response = "{\"status\":\"fail\", \"message\": \"you are not logged in\"}";
}
