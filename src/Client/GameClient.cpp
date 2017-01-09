#include "Includes\GameClient.hpp"

boost::asio::io_service io_service;

GameClient::GameClient()
{
	http_client = new HttpClient(io_service, "localhost", "33000");

}

void GameClient::Menu()
{

	try
	{





		std::cout << "********** Main Menu **********" << std::endl;
		std::cout << "1. User registration" << std::endl;
		std::cout << "2. User login" << std::endl;
		std::cout << "3. User logout" << std::endl;
		int choice = 0;
		std::cout << "Enter choice:" << std::endl;

		do
		{
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				http_client->PostData("/api/userregister", UserActions::fRegistration().dump());
				io_service.run();

				break;
			case 2:
				http_client->PostData("/api/userlogin", UserActions::fLogin().dump());
				session = http_client->fGetSession();
				std::cout <<"s:"<< http_client->fGetSession() << std::endl;
				io_service.run();

				break;
			case 3:
				http_client->PostData("/api/userlogout", session);
				
				io_service.run();
				session = UserActions::fLogout(session);
				break;

			}

		} while (choice != 3);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
}

GameClient::~GameClient()
{
	delete http_client;
}
