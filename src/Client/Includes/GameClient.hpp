#pragma once

#include "HttpClient.hpp"
#include "UserActions.hpp"


class GameClient
{
private:
	//HttpClient *_http_client;    // http-client object
	std::string _game_session;   // game session
public:
	GameClient();

	void fMenu(std::string &host, std::string &port);
	~GameClient();
private:
	char fGetInput();
	void fDisplayMainMenu();
	void fDisplayDmMenu(std::string &host, std::string &port,const std::string &user_session);
	void fDisplayPlayerMenu(const std::string &user_session);
	void fSwitchMode(std::string &host, std::string &port, const std::string &user_session);
	//void SendRequest(std::string &host, std::string &port,const std::string &url, std::string &response, std::string &data);
};
