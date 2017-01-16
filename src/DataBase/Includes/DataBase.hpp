//
//  DataBase.hpp
//  Olha Leskovs'ka
//


#ifndef DataBase_hpp
#define DataBase_hpp

using json = nlohmann::json;

class DataBase
{
private:
    MYSQL* _connection; // Database Connection Handle/Decryptor
    
public:
    DataBase();
    
    json fConnection(std::string host, std::string user_name, std::string password, std::string database_name);
    
    json fExecuteQuery(std::string sql_statement);
    
    json fGetData(std::string sql_statement);
    
    json fPutData(std::string sql_statement);
    
    ~DataBase();
}; // class DataBase

#endif /* DataBase_hpp */
