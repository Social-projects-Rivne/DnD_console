#pragma once

#include "HttpClient.hpp"
#include "UserActions.hpp"


class GameClient
{
	HttpClient *http_client;
	std::string session;
public:
	GameClient();

	void Menu();

	~GameClient();

};
