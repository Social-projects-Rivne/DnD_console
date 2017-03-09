// HttpClient.cpp
//
// httpClient
// for
// SoftServe ITA
//
// Kopelyuk Vitaliy
// vkopeluk@gmail.com
//

#include "Includes/HttpClient.hpp"
#include "Includes/Logger.hpp"


/*
Initializes and starts http client.
*/

HttpClient::HttpClient(boost::asio::io_service& io_service, const std::string &server, const std::string &port) : _resolver(io_service), _socket(io_service)
{
    this->_server  =  server;
    this->_port    =  port;

    tcp::resolver::query query(server, port);
    _endpoint_iterator = _resolver.resolve(query);
}


/*
    Method for getting data from server.
*/
void HttpClient::fGet(const std::string &path)
{
    std::ostream request_stream(&_request);
    request_stream << "GET " << path << " HTTP/1.1\r\n";                    // Request type and path
    request_stream << "Host: " << _server << "\r\n";                        // Host "localhost" for example
    request_stream << "Accept: *///*//\r\n";   
    request_stream << "Connection: close\r\n\r\n";
    
    boost::asio::write(_socket, _request);
}

/*
    Method for posting data to server.
*/
void HttpClient::fPost(const std::string &path, const std::string &data)
{
    std::ostream request_stream(&_request);
    request_stream << "POST " << path << " HTTP/1.1\r\n";	                // Request type and path
    request_stream << "Host: " << _server << " \r\n";		                // Host "localhost" for example
    request_stream << "Accept: */*\r\n";
    request_stream << "Content-Type: " << "application/json" << " \r\n";    
    request_stream << "Content-Length: " << data.length() << " \r\n";
    request_stream << "Connection: close\r\n\r\n";
    request_stream << data;                                                 // JSON data
    
    boost::asio::write(_socket, _request);
}

/*
Method for puting data to server.
*/

void HttpClient::fPut(const std::string &path, const std::string &data)
{
    std::ostream request_stream(&_request);
    request_stream << "PUT " << path << " HTTP/1.1\r\n";	                // Request type and path
    request_stream << "Host: " << _server << " \r\n";		                // Host "localhost" for example
    request_stream << "Accept: */*\r\n";
    request_stream << "Content-Type: " << "application/json" << " \r\n";
    request_stream << "Content-Length: " << data.length() << " \r\n";
    request_stream << "Connection: close\r\n\r\n";
    request_stream << data;                                                 // JSON data

    boost::asio::write(_socket, _request);
}

/*
Method for deleting data to server.
*/

void HttpClient::fDelete(const std::string &path, const std::string &data)
{
    std::ostream request_stream(&_request);
    request_stream << "DELETE " << path << " HTTP/1.1\r\n";	                // Request type and path
    request_stream << "Host: " << _server << " \r\n";		                // Host "localhost" for example
    request_stream << "Accept: */*\r\n";
    request_stream << "Content-Type: " << "application/json" << " \r\n";
    request_stream << "Content-Length: " << data.length() << " \r\n";
    request_stream << "Connection: close\r\n\r\n";
    request_stream << data; 
    boost::asio::write(_socket, _request);
}

/*
Method for send request to server.
*/

void HttpClient::fSendRequest(const Methods &method,const std::string &path, const std::string &data=" ")
{
    Logger::fLog("Request was been sended", Logger::type::info);

    switch (method)
    {
    case HttpClient::Methods::_GET:
    {
        fConnect();
        fGet(path);
    }
    break;
    case HttpClient::Methods::_POST:
    {
        fConnect();
        fPost(path, data);
    }
    break;
    case HttpClient::Methods::_PUT:
    {
        fConnect();
        fPut(path,data);
    }
    break;
    case HttpClient::Methods::_DELETE:
    {
        fConnect();
        fDelete(path, data);
    }
    }
}

/*
Method for reading response from server.
*/

void HttpClient::fGetResponse(std::string &response_)
{
    Logger::fLog("Response was been received", Logger::type::info);

    boost::asio::streambuf response;
    boost::asio::read_until(_socket, response, "\r\n");

    // Check that response is OK.
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
        std::cout << "Invalid response\n";

        Logger::fLog("Invalid response\n", Logger::type::error);
    }
    if (status_code != 200)
    {
        Logger::fLog("Response returned with status code " + status_code, Logger::type::warning);

        std::cout << "Response returned with status code " << status_code << "\n";
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(_socket, response, "\r\n\r\n");

    // Process the response headers.
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
        std::cout << header << "\n";
    std::cout << "\n";

    // Write whatever content we already have to output.
    std::ostringstream oss;

    if (response.size() > 0)
    {
        oss << &response;
    }
    // Read until EOF, writing data to output as we go.
    boost::system::error_code error;
    while (boost::asio::read(_socket, response,
        boost::asio::transfer_at_least(1), error))
        oss << &response;

    if (error != boost::asio::error::eof)
    {
        Logger::fLog(error.message(), Logger::type::error);
        throw boost::system::system_error(error);
    }
    response_ = oss.str();
}

/*
Method for connecting  to server.
*/

void HttpClient::fConnect()
{
    Logger::fLog("Connection to: " + _server + " success", Logger::type::info);

    boost::asio::connect(_socket, _endpoint_iterator);
}
