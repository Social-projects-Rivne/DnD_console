//
// http_server
//
// Nicholas Tsaruk
// fbt.ksnv@gmail.com
//

// feature test macro requirements
/*#define _POSIX_C_SOURCE  200809L
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED*/

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LIMIT_REQUEST_FIELDS		  50
#define LIMIT_REQUEST_FIELD_SIZE	4094
#define LIMIT_REQUEST_LINE			8190
#define OCTETS 512 // number of octets for buffered reads

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
// header files
//#include <arpa/inet.h> // for UNIX
#include <winsock2.h> // for Windows
#include <WS2tcpip.h> // for Windows
//#include <Wdbgexts.h> // for Windows
#include <windows.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib") // Windows only

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
//#include <stdbool.h>
//#include <strings.h> // for UNIX
//#include <unistd.h> // for UNIX
#include <cstddef>
#include "Includes\unistd.h" // for Windows

using namespace std;

// prototypes
bool		fConnected();
bool		fError(unsigned short code);
void		fHandler(int signal);
ssize_t		fLoad(void);
string		fLookup(string extension);
ssize_t		fParse(void);
void		fReset(void);
void		fStart(short port, const char* path);
void		fStop(void);

// compulsory variables
string		root = "Root"; // server's root
int			cfd = -1; // file descriptor for sockets // connection file descriptor
int			sfd = -1; // file descriptor for sockets // socket file descriptor
string		request; // buffer for request
FILE*		pFile = NULL; // FILE pointer for files
char*		response_body = NULL; // buffer for response-body

int main(int argc, char* argv[])
{
    //const char* usage = "Usage: server [-p port] /path/to/root"; // usage

    // a global variable defined in errno.h that's "set by system
    // calls and some library functions [to a nonzero value]
    // in the event of an error to indicate what went wrong"
    errno = 0;

    int port = 27015; // default to a random port
    //int port = 80; // default to a random port
    // TODO: read setting from parsed *.ini file, i.e., from STL map

    // ensure port is a non-negative short and path to server's root is specified
    if (port < 0 || port > SHRT_MAX || !root.length())
    {
        cout<<"SERVER ERROR: settings are not acceptable\n";
        return 2; // return 2 just like bash's builtins
    }

    // start server with needed
    fStart(port, root.data());

    signal(SIGINT, fHandler); // listen for SIGINT (aka control-c), if it comes // call function named fHandler

    // accept connections one at a time
    while (true)
    {
        // reset server's state
    	fReset();

        // wait until client is connected
        if (fConnected())
        {
            ssize_t request_size = fParse(); // parse client's HTTP request
            if (request_size < 0)
			{
				cout<<"CLIENT REQUEST FAILED. Error code:"<<request_size<<endl;
                continue;
			}
			

            string haystack = request;
            int needle = haystack.find("\r\n");
            if (needle == -1)
            {
            	fError(400);
                continue;
            }
            if (haystack.length() > LIMIT_REQUEST_LINE)
            {
            	fError(414);
                continue;
            }
            haystack = haystack.substr(0,haystack.length()-2); // extract request's request-line // http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html


            /*
             * TODO delete this lines
             * char * line = new char[needle - haystack + 2 + 1];
            strncpy(line, haystack, needle - haystack + 2);
            line[needle - haystack + 2] = '\0';*/

            // 'line' varriable is haystack with terminating null character
            cout<<"CLIENT REQUEST: "<<haystack<<endl; // log request-line

            // TODO -> DONE: validate request-line
                int sp_loc = haystack.find(' ');
                int qm_loc = haystack.find('?');
                int pnt_loc = haystack.find('.');
                int lsp_loc = haystack.rfind(' ');
                int version_loc = haystack.find("HTTP/1.1");
				
                if (haystack.find("GET") == -1)
                {
                	fError(405);
                    continue;
                }
                if (haystack[4] != '/' || (pnt_loc-sp_loc) < 2 || (pnt_loc-sp_loc) > (lsp_loc-sp_loc))
                {
                	fError(501);
                    continue;
                }
                if (haystack.find('\"') != -1 || ((version_loc - sp_loc) < (lsp_loc-sp_loc)) || sp_loc == lsp_loc)
                {
                	fError(400);
                    continue;
                }
                if (version_loc != -1)
                {
                	fError(505);
                    continue;
                }
            // TODO -> DONE: extract query from request-target
                int tmp_size = 1;
                int tmp_ofs = 0;
                if (qm_loc != -1)
                {
                    tmp_ofs = qm_loc;
                    tmp_size = (lsp_loc - qm_loc);
                }
                else
                	qm_loc = lsp_loc;
				
                string query = haystack.substr(tmp_ofs+1, tmp_size-1);
                cout<<"QUERY: "<<query<<endl;

            // TODO -> DONE: concatenate root and absolute-path
			int tmp_length = root.length() + (qm_loc-sp_loc);
			string path = root + haystack.substr(sp_loc+1, qm_loc-sp_loc);
			cout<<"PATH:"<<path<<endl;

            // TODO -> DONE: ensure path exists
                if (access(path.data(), F_OK) == -1)
                {
                	fError(404);
                    continue;
                }

            // TODO -> DONE: ensure path is readable
                if (access(path.data(), R_OK) == -1)
                {
                	fError(403);
                    continue;
                }

            // TODO -> DONE: extract path's extension
            string extension = path.substr(path.find('.') + 1);
            cout<<"EXTENSION:"<<extension<<endl;

            // look up file's MIME type
            string type = fLookup(extension);
            if (!type.length())
            {
                fError(501);
                continue;
            }

            // open file
            pFile = fopen(path.data(), "r");
            if (pFile == NULL)
            {
                fError(500);
                continue;
            }

            // load file
            ssize_t length = fLoad();
            if (length == -1)
            {
                fError(500);
                continue;
            }

            // respond to client
			/*// UNIX
			string response_str = "HTTP/1.1 200 OK\r\n";
			if (_write(cfd, response_str.data(), response_str.length()) == -1)
				continue;
					
			response_str = "Connection: close\r\n";
			if (_write(cfd, response_str.data(), response_str.length()) == -1)
				continue;
					
			response_str = "Content-Length: "+to_string(length)+"\r\n";
			if (_write(cfd, response_str.data(), response_str.length()) == -1)
				continue;
					
			response_str = "Content-Type: "+type+"\r\n\r\n";
			if (_write(cfd, response_str.data(), response_str.length()) == -1)
				continue;

            if (_write(cfd, response_body, length) == -1)
				continue;*/

			// Windows
			string response_str = "HTTP/1.1 200 OK\r\n";
			if (send( cfd, response_str.data(), response_str.length(), 0 ) == -1)
				continue;
					
			response_str = "Connection: close\r\n";
			if (send( cfd, response_str.data(), response_str.length(), 0 ) == -1)
				continue;
					
			response_str = "Content-Length: "+to_string(length)+"\r\n";
			if (send( cfd, response_str.data(), response_str.length(), 0 ) == -1)
				continue;
					
			response_str = "Content-Type: "+type+"\r\n\r\n";
			if (send( cfd, response_str.data(), response_str.length(), 0 ) == -1)
				continue;

            if (send(cfd, response_body, length, 0) == -1)
				continue;

            // announce OK
            cout<<"HTTP/1.1 200 OK"<<endl;

        }
    }
}

/**
 * Accepts a connection from a client, blocking (i.e., waiting) until one is heard.
 * Upon success, returns true; upon failure, returns false.
 */
bool fConnected(void)
{
    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    socklen_t cli_len = sizeof(cli_addr);
    cfd = accept(sfd, (struct sockaddr*) &cli_addr, &cli_len);
    if (cfd == -1)
	{
		cout << "CONNECTION FAILED\n";
        return false;
	}
		cout << "CONNECTION SUCCESSFUL\n";
    return true;
}

/**
 * Handles client errors (4xx) and server errors (5xx).
 */
bool fError(unsigned short code)
{
    if (cfd == -1) // ensure client's socket is open
        return false;

    if (code < 400 || code > 599) // ensure code is within range
        return false;

    // determine Status-Line's phrase
    // http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6.1
    string phrase;
    switch (code)
    {
        case 400: phrase = "Bad Request"; break;
        case 403: phrase = "Forbidden"; break;
        case 404: phrase = "Not Found"; break;
        case 405: phrase = "Method Not Allowed"; break;
        case 413: phrase = "Request Entity Too Large"; break;
        case 414: phrase = "Request-URI Too Long"; break;
        case 418: phrase = "I'm a teapot"; break;
        case 500: phrase = "Internal Server Error"; break;
        case 501: phrase = "Not Implemented"; break;
        case 505: phrase = "HTTP Version Not Supported"; break;
    }
    if (!phrase.length())
    {
        return false;
    }
	
    // response template
	string error_response = "<html><head><title>"+to_string(code)+" "+phrase+"</title></head><body><h1>"+to_string(code)+" "+phrase+"</h1></body></html>";
	

	/* // UNIX
	string tmp = "HTTP/1.1 "+to_string(code)+" "+phrase+"\r\n";
	if (_write(cfd, tmp.data(), tmp.length()) < 0) // respond with Status-Line
        return false;
	tmp = "Connection: close\r\n";
    if (_write(cfd, tmp.data(), tmp.length()) < 0) // respond with Connection header
        return false;
	tmp = "Content-Length: "+to_string(length)+"\r\n";
    if (_write(cfd, tmp.data(), tmp.length()) < 0) // respond with Content-Length header
        return false;
	tmp = "Content-Type: text/html\r\n";
    if (_write(cfd, tmp.data(), tmp.length()) < 0) // respond with Content-Type header
        return false;
	tmp = "\r\n";
    if (_write(cfd, tmp.data(), tmp.length()) < 0) // respond with CRLF
        return false;
    if (_write(cfd, content, length) == -1) // respond with message-body
        return false;*/
	// Windows
	string tmp = "HTTP/1.1 "+to_string(code)+" "+phrase+"\r\n";
	if (send(cfd, tmp.data(), tmp.length(), 0) < 0) // respond with Status-Line
        return false;
	tmp = "Connection: close\r\n";
    if (send(cfd, tmp.data(), tmp.length(), 0) < 0) // respond with Connection header
        return false;
	tmp = "Content-Length: "+to_string(error_response.length())+"\r\n";
    if (send(cfd, tmp.data(), tmp.length(), 0) < 0) // respond with Content-Length header
        return false;
	tmp = "Content-Type: text/html\r\n";
    if (send(cfd, tmp.data(), tmp.length(), 0) < 0) // respond with Content-Type header
        return false;
	tmp = "\r\n";
    if (send(cfd, tmp.data(), tmp.length(), 0) < 0) // respond with CRLF
        return false;
    if (send(cfd, error_response.data(), error_response.length(), 0) == -1) // respond with message-body
        return false;

    // announce Response-Line
    cout<<"HTTP/1.1 "<<code<<" "<<phrase<<endl;

    return true;
}

/**
 * Loads file into message-body.
 */
ssize_t fLoad(void)
{
    if (!pFile) // ensure file is open
        return -1;

    if (response_body) // ensure body isn't already loaded
        return -1;

	fseek(pFile, 0, SEEK_END);
	int file_size = ftell(pFile);
	char * tmp_bufer = new char[file_size];		memset((void *)tmp_bufer, 0, sizeof(char)*file_size);
	response_body = new char[file_size];		memset((void *)response_body, 0, sizeof(char)*file_size);
	
	fseek(pFile, 0, 0); // return carret back to the file beginning
	ssize_t read_amount = 0;
	while (read_amount < file_size)
	{
		ssize_t bytes_read = fread(tmp_bufer, 1, file_size-read_amount, pFile);
		memcpy(response_body + read_amount, tmp_bufer, bytes_read);
		read_amount += bytes_read;
	}
	delete [] tmp_bufer ;

	return read_amount;
}

/**
 * Handles signals.
 */
void fHandler(int signal)
{
    if (signal == SIGINT) // control-c
    {
        // ensure this isn't considered an error
        // (as might otherwise happen after a recent 404)
        errno = 0;

        // announce stop
        cout<<"Stopping server\n"<<endl;

        fStop(); // stop server
    }
}

/**
 * Returns MIME type for supported extensions, else NULL.
 */
string fLookup(string extension)
{
    // TODO -> DONE

	string str_to_return;
    if (!extension.compare("css"))
        return "text/css";

    if (!extension.compare("html"))
        return "text/html";

    if (!extension.compare("gif"))
        return "image/gif";

    if (!extension.compare("ico"))
        return "image/x-icon";

    if (!extension.compare("jpg"))
        return "image/jpeg";

    if (!extension.compare("js"))
        return "text/javascript";

    if (!extension.compare("png"))
        return "image/png";

    return "";
}

/**
 * Parses an HTTP request.
 */
ssize_t fParse(void)
{
    if (cfd == -1) // ensure client's socket is open
        return -2;

    if (request.length()) // ensure request isn't already parsed
        return -3;

    char * request_portion_buffer = new char[OCTETS]; // buffer for octets

    ssize_t request_length = 0;
    while (true) // parse request
    {
        //ssize_t bytes_read = read(cfd, request_portion_buffer, sizeof(char) * OCTETS); // read from socket in UNIX
        ssize_t bytes_read = recv(cfd, request_portion_buffer, sizeof(char) * OCTETS, 0); // read from socket in Windows
        if (bytes_read == -1) // socket read error
        {
        	fError(500);
            return -4;
        }
        if (bytes_read > 0) // if octets have been read, remember new length
        {
            request += request_portion_buffer;
            request_length += bytes_read;
			if ( (int)request.length() != (int)request_length ) // in case of unsufficient null character were passed
			{
				cout<<"request.length(): "<<request.length()<<" !+ request_length: "<<request_length<<endl;
                return -5;
			}
        }
        else // else if nothing's been read, socket's been closed
            return -6;

		if (request.find("\r\n\r\n") != -1) // search for CRLF CRLF
		{
			request = request.substr(0,request.length()-2); // trim to one CRLF
            if (!request.length())
                return -7;
            break;
		}

        if (request_length - 1 >= LIMIT_REQUEST_LINE + LIMIT_REQUEST_FIELDS * LIMIT_REQUEST_FIELD_SIZE) // if buffer's full and we still haven't found CRLF CRLF, then request is too large
        {
        	fError(413);
            return -8;
        }
    }

	delete [] request_portion_buffer;
    return request_length;
}

/**
 * Resets server's state, deallocating any resources.
 */
void fReset(void)
{
    // free response's body
    if (response_body != NULL)
    {
        delete [] response_body;
        response_body = NULL;
    }

    if (pFile != NULL) // close file
    {
        fclose(pFile);
        pFile = NULL;
    }

    request = ""; // free request

    if (cfd != -1) // close client's socket
    {
        //close(cfd); // UNIX
        closesocket(cfd); // windows
        cfd = -1;
    }
}

/**
 * Starts server.
 */
void fStart(short port, const char* path)
{
    //root = realpath(path, NULL); // full path to server's root on UNIX

	/////////////////
	// for Windows //
		unsigned long root_path_length = 0;
		char  buffer[4096];
		char** lppPart={NULL};

		root_path_length = GetFullPathNameA(path,
					 4096,
					 buffer,
					 lppPart); // full path to server's root on Windows // The file does not need to exist.
    
		if (root_path_length == 0) 
		{
			cout<<"GetFullPathName failed ("<<GetLastError()<<")\n"; // Handle an error condition.
			return;
		}
		else
			root = buffer;
	// for Windows //
	/////////////////

    if (!root.length())
    	fStop();

    if (access(root.data(), F_OK) == -1) // ensure root exists
    	fStop();

	/*if (access(root.data(), X_OK) == -1) // UNIX // ensure root is executable
    	fStop();*/
    if (access(root.data(), W_OK) == -1) // Windows // ensure root is writable
    	fStop();

    cout<<"Using "<<root<<" for server's root"<<endl;

	//////////////////////
	// for windows only //
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0)
		{
			cout<<"WSAStartup failed with error: "<<iResult<<endl;
			return ;
		}
	// for windows only //
	//////////////////////

    sfd = socket(AF_INET, SOCK_STREAM, 0); // create a socket
    if (sfd == -1)
	{
		cout<<"error code:"<<WSAGetLastError()<<": "<<strerror(WSAGetLastError());
    	fStop();
	}


    int optval = 1;
    setsockopt(sfd,
				SOL_SOCKET,
				SO_REUSEADDR, // allow reuse of address (to avoid "Address already in use")
				(char *)&optval,
				sizeof(optval));
	
    // assign name to socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		cout<<"bind function failed"<<endl;
    	fStop();
	}
	
    
    if (listen(sfd, SOMAXCONN) == -1) // listen for connections
	{
		cout<<"connection listen failed"<<endl;
    	fStop();
	}
	
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if (getsockname(sfd, (struct sockaddr*) &addr, &addrlen) == -1)
	{
		cout<<"getsockname function failed"<<endl;
    	fStop();
	}

    cout<<"Listening on port "<<ntohs(addr.sin_port)<<endl;
}

/**
 * Stop server, deallocating any resources.
 */
void fStop(void)
{
    int errsv = errno; // preserve errno across this function's library calls
    fReset(); // reset server's state
    root = ""; // free root, which was allocated by realpath
    if (sfd != -1) // close server socket
	{
        //close(sfd); // UNIX
        closesocket(sfd); // windows
	}
	WSACleanup(); // Windows only

    
    if (errsv == 0) // terminate process
        exit(0);
    else // announce error
    {
        cout<<strerror(errsv)<<endl;
        exit(1);
    }
}
