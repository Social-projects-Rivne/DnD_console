#include <my_global.h>
#include <mysql.h>
#include <iostream>
#include "Database.hpp"

using namespace std;

int main()
{
    Database db;
    db.ConnectionOpening();
    
    string user_name =    "new_user",
    password =     "new_password",
    email =        "",
    sql_statement,
    action =       "SELECT";
    
    if (action == "SELECT")
    {
        sql_statement = "SELECT username, password FROM Users WHERE username = '";
        sql_statement += user_name;
        sql_statement += "' AND password = '";
        sql_statement += password;
        sql_statement += "';";
        
        db.GetUserData(sql_statement);
    }
    
    action = "INSERT";
    if (action == "INSERT")
    {
        if (email == "")
        {
            sql_statement = "INSERT INTO Users (username, password, is_active) VALUES ('";
            sql_statement += user_name;
            sql_statement += "', '";
            sql_statement += password;
            sql_statement += "', 0);";
        }
        else
        {
            sql_statement = "INSERT INTO Users (username, password, email, is_active) VALUES ('";
            sql_statement += user_name;
            sql_statement += "', '";
            sql_statement += password;
            sql_statement += "', '";
            sql_statement += email;
            sql_statement += "', 0);";
        }
        
        db.PutUserData(sql_statement);
    }
    
    return 0;
}
