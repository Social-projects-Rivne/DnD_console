// HttpServer.hpp
//
// http_server
// for 
// SoftServe ITA
//
// Nicholas Tsaruk
// fbt.ksnv@gmail.com
//
#pragma once

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LIMIT_REQUEST_FIELDS		  50
#define LIMIT_REQUEST_FIELD_SIZE	4094
#define LIMIT_REQUEST_LINE			8190
#define OCTETS 512 // number of octets for buffered reads
#define byte char

class HttpServer
{
private:
	int		port;						// port for listening
	string	root;						// path to server's root
	int		cfd;						// file descriptor for sockets // connection file descriptor
	int		sfd;						// file descriptor for sockets // socket file descriptor
	vector <string> path_exceptions;	//
	string	request;					// buffer for client request
	string	request_line;				// buffer for first line of user request
	map <string, string> request_headers;
	byte*	response_body;				// buffer for response-body
	int		response_body_length;		// size of response-body
	string	response_body_content_type;	// response-body content type
	FILE*	pFile;						// FILE pointer for requested file
	int		state_error;				// server's state. 0 - running; !0 - some errors
	string	state_info;					// informs on state condition

private: /* see cpp file for the below functions descriptions*/
	void	fReset(void);
	bool	fRespond(void);
	bool	fConnected(void);
	bool	fError(unsigned short code, int condition = -1);
	bool	fLoad(void);
	string	fLookup(string extension);
	ssize_t	fParse(void);
public:
	void	fRun(void);
	void	(*fCallBack)(string, map <string, string>);	// pointer to user function that is called in case of exception
	HttpServer(int server_port, string path_to_root);
	~HttpServer(void);
};
