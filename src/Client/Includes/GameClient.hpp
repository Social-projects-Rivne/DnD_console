#pragma once

#include "HttpClient.hpp"
#include "UserActions.hpp"


class GameClient
{
	HttpClient *http_client;    // http-client object
	std::string game_session;   // game session
public:
	GameClient();

	void fMenu();

	~GameClient();

};
