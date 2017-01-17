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

using std::string;
using std::cout;
using std::cin;
using std::endl;
using json = nlohmann::json;

const int MAX_ABILITIES_SUM = 80;

class NPC
{
private:
    string _name;
    string _type_NPC;
    int _hitpoints;
    int _level;
    int _strength;
    int _dexterity;
    int _constitution;
    int _intelligence;
    int _wisdom;
    int _charisma;
    
public:
    static bool fValidNameTypeNPC(string datum); // name and type_NPC validation
    
    static bool fValidateAbility(int datum); // NPC's each ability validation
    
    static bool fValidateAbilities(int datum); // NPC's all abilities validation
    
    NPC();
    
    NPC(string name,
        string type_NPC,
        int hitpoints,
        int level,
        int strength,
        int dexterity,
        int constitution,
        int intelligence,
        int wisdom,
        int charisma);
    
    void fRandomizeAbilities(); // fills the character abilities by rolling dices
    
    void fSetAbilities(); // asks user for defining abilities points
    
    void fCreateNPC(); // creates NPC
    
    json fToJson(); // converts NPC data into json
};

#endif /* NPC_hpp */
