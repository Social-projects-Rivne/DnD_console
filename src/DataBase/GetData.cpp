#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>

MYSQL *connection, mysql;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

using namespace std;

void GetData();

void PrintData();

int main()
{
    GetData();
    
    return 0;
}

void GetData()
{
    bool received = false;
    do
    {
        mysql_init(&mysql);
        connection = mysql_real_connect(&mysql,"localhost", "root","qwer","cpp_data",3306,0,0);
        if (connection == NULL)
            cout << mysql_error(&amp;mysql) << endl;
        
        query_state = mysql_query(connection, "select user_count()");
        if (query_state !=0)
            cout << mysql_error(connection) << endl;
        if (connection != NULL && ( row = mysql_fetch_row(result)) != NULL)
            received = true;
    } while(received != true);
    
    result = mysql_store_result(connection);
    
    PrintData();
    
    mysql_free_result(result);
    mysql_close(connection);
}

void PrinData()
{
    while (( row = mysql_fetch_row(result)) != NULL)
    {
        cout << row[0] << endl;
    }
}
