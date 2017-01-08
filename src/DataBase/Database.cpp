//
//  Database.cpp
//  DBConnection
//
//  Created by Olha Leskovska on 1/5/17.
//  Copyright © 2017 Olha Leskovska. All rights reserved.
//

#include <my_global.h>
#include <mysql.h>
#include <iostream>
#include "Database.hpp"

using namespace std;

Database::Database()
{
    connection = NULL;
}

void Database::ConnectionOpening()
{
    // Get the Database Connection Handle
    connection = mysql_init(NULL);
    if (connection == NULL)
        // If we can't create the Database Connection Handle
        cout << "Error: can't create a MySQL Connection Handle.\n";
    
    // Connecting to a Database Server
    else if(!mysql_real_connect(connection, // address of an existing MYSQL structure.
                                "localhost", // host name or an IP address
                                "root", // user's MySQL login ID
                                "root", // password for user
                                "DnD", // database name
                                NULL, // port number for the TCP/IP connection
                                NULL, //  socket or named pipe to use
                                0 // client flag
                                ))
        cout << "Error: can't connect to database.\n" << mysql_error(connection);
    else
        cout << "The connection is open." << endl;
}

void Database::GetUserData(string sql_statement)
{
    //Execute SQL-query
    if (mysql_query(connection, sql_statement.c_str()) != 0)
        cout << "Error: can't execute SQL-query\n";
    
    MYSQL_RES* result; // Resulting Table Handle
    MYSQL_ROW row; // Rows Handle
    unsigned long long rows; // Number of rows
    
    // Get a handle to the resulting table
    result = mysql_store_result(connection);
    if (result == NULL)
        cout << "Error: can't get the result description\n";
    else
    {
        if (mysql_num_rows(result) > 0)
        {
            int values_number = mysql_num_fields(result); // Number of values in a row
            rows = mysql_num_rows(result); // Number of rows
            
            for (int index = 0; index < rows; index++)
            {
                // Go through all the records of the resulting table
                while ((row = mysql_fetch_row(result)) != NULL)
                {
                    cout << rows << endl;
                    cout << "Value number: " << values_number << endl;
                    for (int row_number = 0; row_number < rows; row_number++)
                    {
                        for (int value_number = 0; value_number < values_number; value_number++)
                            cout << row[value_number] << " ";
                        cout << endl;
                        
                    }
                }
            }
        }
        else if (mysql_num_rows(result) == 0)
            cout << "No user with these data.\n";
    }
    
    // Free up the memory used by the result table
    mysql_free_result(result);
}

void Database::PutUserData(string sql_statement)
{
    //Execute SQL-query
    if (mysql_query(connection, sql_statement.c_str()) != 0)
        cout << "Error: can't execute SQL-query\n";
    else
        cout << "The user is added.\n";
}

Database::~Database()
{
    // Closing the connection
    mysql_close(connection);
}
