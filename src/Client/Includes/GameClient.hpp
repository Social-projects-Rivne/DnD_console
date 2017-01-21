#pragma once

#include "HttpClient.hpp"
#include "UserActions.hpp"


class GameClient
{
private:
	HttpClient *_http_client;    // http-client object
	std::string _game_session;   // game session
public:
	GameClient();

	void fMenu();
	~GameClient();
private:
	int fGetInput();
	void fDisplayMainMenu();
	void fDisplayDmMenu(const std::string &user_session);
	void fDisplayPlayerMenu(const std::string &user_session);
	void fSwitchMode(const std::string &user_session);
};
