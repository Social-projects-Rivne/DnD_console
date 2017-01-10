//
//  Database.hpp
//


#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include "json.hpp"
#include <string>

using json = nlohmann::json;

class Database
{
    MYSQL* connection; // Database Connection Handle/Decryptor
    
public:
    Database();
    
    json fConnection(std::string host, std::string user_name, std::string password, std::string database_name);
    
    json fExecuteQuery(std::string sql_statement);
    
    json fGetData(std::string sql_statement);
    
    json fPutData(std::string sql_statement);
    
    ~Database();
}; // class Database

#endif /* Database_hpp */
