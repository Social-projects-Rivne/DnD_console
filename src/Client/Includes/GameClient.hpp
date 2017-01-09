
#include "HttpClient.hpp"
#include "UserActions.hpp"

boost::asio::io_service io_service;

class GameClient
{
	HttpClient *http_client;
public:

	GameClient(std::string server, std::string port)
	{
		http_client = new HttpClient(io_service,server,port);
	}

	void Menu()
	{
		std::cout << "********** Main Menu **********" << std::endl;
		std::cout << "1. User registration" << std::endl;
		std::cout << "2. User login" << std::endl;
		std::cout << "2. User logout" << std::endl;
		
	
	}

	~GameClient()
	{
		delete http_client;
	}
};

void main()
{
	GameClient s("localhost","33000");
	s.Menu();
	system("pause");
}