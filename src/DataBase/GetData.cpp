#include <my_global.h>
#include <mysql.h>
#include <iostream>

using namespace std;

MYSQL* CONNECTION; // Database Connection Handle/Decryptor
MYSQL_RES *RESULT; // Resulting Table Handle
MYSQL_ROW ROW; // Rows Handle

void fConnectionOpening();
void fGetData(string user_name, string password);

int main()
{
    fConnectionOpening();
    string user_name = "user1";
    string password = "test";
    fGetData(user_name, password);
    
    // Closing the connection
    mysql_close(CONNECTION);
}

void fConnectionOpening()
{
    // Get the Database Connection Handle
    CONNECTION = mysql_init(NULL);
    if (CONNECTION == NULL)
        // If we can't create the Database Connection Handle
        cout << "Error: can't create a MySQL Connection Handle.\n";
    
    // Connecting to a Database Server
    else if(!mysql_real_connect(CONNECTION, // address of an existing MYSQL structure.
                                "localhost", // host name or an IP address
                                "root", // user's MySQL login ID
                                "root", // password for user
                                "DnD", // database name
                                NULL, // port number for the TCP/IP connection
                                NULL, //  socket or named pipe to use
                                0 // client flag
                                ))
        cout << "Error: can't connect to database.\n" << mysql_error(CONNECTION);
    else
        cout << "The connection is open." << endl;
    
}

void fGetData(string user_name, string password)
{
    string sql_statement = "SELECT username, password FROM Users WHERE username = '";
    sql_statement += user_name;
    sql_statement += "' AND password = '";
    sql_statement += password;
    sql_statement += "';";
    
    //Execute SQL-query
    if (mysql_query(CONNECTION, sql_statement.c_str()) != 0)
        cout << "Error: can't execute SQL-query\n";
    
    // Get a handle to the resulting table
    RESULT = mysql_store_result(CONNECTION);
    if (RESULT == NULL)
        cout << "Error: can't get the result description\n";
    else
    {
        if (mysql_num_rows(RESULT) > 0)
        {
            // Go through all the records of the resulting table
            while ((ROW = mysql_fetch_row(RESULT)) != NULL)
                cout << ROW[0] << " " << ROW[1] << endl;
        }
        else if (mysql_num_rows(RESULT) == 0)
            cout << "No user with these data.\n";
    }
    
    // Free up the memory used by the result table
    mysql_free_result(RESULT);
}
