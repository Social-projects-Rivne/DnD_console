#include "Includes\GameClient.hpp"

boost::asio::io_service io_service;  // io_service represents your program's link to the operating system's I/O services.




GameClient::GameClient()
{
	http_client = new HttpClient(io_service, "localhost", "33000"); //create http-client with options: host="localhost", port="33000"

}



void GameClient::fMenu()
{

	try
	{
		std::cout << "********** Main Menu **********" << std::endl;
		std::cout << "1. User registration" << std::endl;
		std::cout << "2. User login" << std::endl;
		std::cout << "3. User logout" << std::endl;
		std::cout << "4. Exit" << std::endl;
		int choice = 0;
		std::cout << "Enter choice:" << std::endl;  // user enter option 
		do
		{
			std::cin >> choice;
			
			switch (choice)
			{
			case 1:
				http_client->PostData("/api/userregister", UserActions::fRegistration().dump()); //send POST request for registration
				io_service.run(); // run io_service

				break;
			case 2:
				http_client->PostData("/api/userlogin", UserActions::fLogin().dump()); // send POST request for logining
				
				io_service.run();
				game_session = http_client->fGetSession();
				break;
			case 3:
				http_client->PostData("/api/userlogout", game_session); // drop user session
				io_service.run();
				game_session = UserActions::fLogout(game_session);
				http_client->fSetSession(game_session);
				break;

			}

		} while (choice != 4);
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
