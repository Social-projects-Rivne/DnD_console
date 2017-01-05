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

class Database
{
    MYSQL* CONNECTION; // Database Connection Handle/Decryptor
    
public:
    Database();
    
    void ConnectionOpening();
    
    void GetUserData(std::string user_name, std::string password);
    
    void PutUserData(std::string user_name, std::string password, std::string email);
    
    ~Database();
}; // class Database

#endif /* Database_hpp */
