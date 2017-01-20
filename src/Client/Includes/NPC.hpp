//
//  NPC.hpp
//  Client
//
//  Created by Olha Leskovska on 1/15/17.
//  Copyright © 2017 Olha Leskovska. All rights reserved.
//

#ifndef NPC_hpp
#define NPC_hpp

#include <stdio.h>
#include <string>
#include "json.hpp"
#include "DataValidator.hpp"
#include "Dice.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using json = nlohmann::json;

const int MAX_ABILITIES_SUM = 80;

class NPC
{
private:
    string _name;
    string _type_NPC;
    string _hitpoints;
    string _level;
    string _strength;
    string _dexterity;
    string _constitution;
    string _intelligence;
    string _wisdom;
    string _charisma;
    
public:
    
    NPC();
    
    NPC(string name,
        string type_NPC,
        string hitpoints,
        string level,
        string strength,
        string dexterity,
        string constitution,
        string intelligence,
        string wisdom,
        string charisma);
    
    NPC(const NPC &npc); // copy constructor
    
    NPC &operator = (const NPC& npc); // assignment operator =

    void fRandomizeAbilities(); // fills the character abilities by rolling dices
    
    void fSetAbilities(); // asks user for defining abilities points
    
    void fAddNPC(); // creates NPC
    
    void fShowNPC(); // shows NPC in console window
    
    json fToJson(); // converts NPC data into json
    
    ~NPC();
};

#endif /* NPC_hpp */
