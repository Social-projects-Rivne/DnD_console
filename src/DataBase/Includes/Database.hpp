//
//  Database.hpp
//  DBConnection
//
//  Created by Olha Leskovska on 1/5/17.
//  Copyright © 2017 Olha Leskovska. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include "Includes/json.hpp"
#include "Includes/sha256.hpp"

using json = nlohmann::json;

class Database
{
    MYSQL* connection; // Database Connection Handle/Decryptor
    
public:
    Database();
    
    json ConnectionOpening();
    
    json GetUserData(std::string sql_statement);
    
    json PutUserData(std::string sql_statement);
    
    ~Database();
}; // class Database

#endif /* Database_hpp */
