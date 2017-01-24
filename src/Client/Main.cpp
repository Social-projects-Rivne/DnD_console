#include "Includes\GameClient.hpp"



int main()
{

	std::string port;
	std::string host;

	std::cout << "Welcome to DnD game:" << std::endl;
	std::cout << "Enter server name or server ip:" << std::endl;
	std::getline(std::cin, host);
	std::cout << "Enter port:" << std::endl;
	std::getline(std::cin, port);

	GameClient client;   // create game client object
	client.fMenu(host,port);       // call Menu function

	system("pause");
	return 0;
}