#include "HttpClient.hpp"



int main()
{
	try
	{
		

		boost::asio::io_service io_service;
		HttpClient c(io_service, "localhost","33000");//you can write number of port or write port name
		c.GetData("/test.txt");
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
	return 0;
}