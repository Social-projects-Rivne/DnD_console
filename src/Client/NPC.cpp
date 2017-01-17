//
//  NPC.cpp
//  Client
//
//  Created by Olha Leskovska on 1/15/17.
//  Copyright © 2017 Olha Leskovska. All rights reserved.
//

#include "Includes/NPC.hpp"

bool NPC::fValidNameTypeNPC(string datum)
{
    for (unsigned int i = 0; i < datum.length(); i++)
    {
        if (isalpha(datum[i]))
            return true;
    }
    return false;
}

bool NPC::fValidateAbility(int datum) // NPC's each ability validation
{
    if (datum > 0 && datum <= 20)
        return true;
    else
        return false;
}

bool NPC::fValidateAbilities(int datum)
{
    if (datum > 0 && datum <= MAX_ABILITIES_SUM)
        return true;
    else
        return false;
}

NPC::NPC()
{
    _name = "";
    _type_NPC = "";
    _hitpoints = 0;
    _level = 0;
    _strength = 0;
    _dexterity = 0;
    _constitution = 0;
    _intelligence = 0;
    _wisdom = 0;
    _charisma = 0;
}

NPC::NPC(string name,
         string type_NPC,
         int hitpoints,
         int level,
         int strength,
         int dexterity,
         int constitution,
         int intelligence,
         int wisdom,
         int charisma)
{
    _name = name;
    _type_NPC = type_NPC;
    _hitpoints = hitpoints;
    _level = level;
    _strength = strength;
    _dexterity = dexterity;
    _constitution = constitution;
    _intelligence = intelligence;
    _wisdom = wisdom;
    _charisma = charisma;
}

void NPC::fRandomizeAbilities() // fills the character abilities by rolling dices
{
    
}

void NPC::fSetAbilities() // asks user for defining abilities points
{
    int sum = 0;
    
    do
    {
        int hitpoints;
        do
        {
            cout << "Input the ammount of hitpoints: ";
            cin >> hitpoints;
            
            if (!NPC::fValidateAbility(hitpoints))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _hitpoints = hitpoints;
        } while (!NPC::fValidateAbility(hitpoints));
        sum += hitpoints;
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        int strength;
        do
        {
            cout << "Input the strength-value: ";
            cin >> strength;
            
            if (!NPC::fValidateAbility(strength))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _strength = strength;
        } while (!NPC::fValidateAbility(strength));
        sum += strength;
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        int dexterity;
        do
        {
            cout << "Input the dexterity-value: ";
            cin >> dexterity;
            
            if (!NPC::fValidateAbility(dexterity))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _dexterity = dexterity;
        } while (!NPC::fValidateAbility(dexterity));
        sum += dexterity;
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        int constitution;
        do
        {
            cout << "Input the constitution-value: ";
            cin >> constitution;
            
            if (!NPC::fValidateAbility(constitution))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _constitution = constitution;
        } while (!NPC::fValidateAbility(constitution));
        sum += constitution;
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        int intelligence;
        do
        {
            cout << "Input the intelligence-value: ";
            cin >> intelligence;
            
            if (!NPC::fValidateAbility(intelligence))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _intelligence = intelligence;
        } while (!NPC::fValidateAbility(constitution));
        sum += intelligence;
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        int wisdom;
        do
        {
            cout << "Input the wisdom-value: ";
            cin >> wisdom;
            
            if (!NPC::fValidateAbility(wisdom))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _wisdom = wisdom;
        } while (!NPC::fValidateAbility(wisdom));
        sum += wisdom;
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        int charisma;
        do
        {
            cout << "This ability is the last." << endl;
            cout << "Input the charisma-value: ";
            cin >> charisma;
            
            if (!NPC::fValidateAbility(charisma))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _charisma = charisma;
        } while (!NPC::fValidateAbility(charisma));
        sum += charisma;
    } while (!NPC::fValidateAbilities(sum));
}

void NPC::fCreateNPC() // creates NPC
{
    cout << "********** NPC **********" << endl;
    string name;
    do
    {
        cout << "Input a name: ";
        getline(cin, name);
        
        if (!NPC::fValidNameTypeNPC(name))
            cout << "This datum should consist of letters!\n";
        else
            _name = name;
    } while (!NPC::fValidNameTypeNPC(name));
    
    string type_NPC;
    do
    {
        cout << "Input the NPC's type: ";
        getline(cin, type_NPC);
        
        if (!NPC::fValidNameTypeNPC(type_NPC))
            cout << "This datum should consist of letters!" << endl;
        else
            _type_NPC = type_NPC;
    } while (!NPC::fValidNameTypeNPC(type_NPC));
    
    int level;
    do
    {
        cout << "Input the level: ";
        cin >> level;
        if (level > 0)
            _level = level;
    } while (level <= 0);
    
    int choice;
    cout << "Choose the way to fill the NPC's abilities:" << endl;
    cout << "1. by rolling dices;" << endl;
    cout << "2. manually" << endl;
    cout << "Your choice: ";
    cin >> choice;
    
    switch (choice)
    {
        case 1:
            break;
        case 2:
            NPC::fSetAbilities();
            break;
        default:
            cout << "Unexpected operation." << endl;
            break;
    }
}

json NPC::fToJson()
{
    json npc;
    
    npc["NPC"] = _name;
    npc["type_NPC"] = _type_NPC;
    npc["hitpoints"] = _hitpoints;
    npc["level"] = _level;
    npc["strength"] = _strength;
    npc["dexterity"] = _dexterity;
    npc["constitution"] = _constitution;
    npc["intelligence"] = _intelligence;
    npc["wisdom"] = _wisdom;
    npc["charisma"] = _charisma;
    
    return npc.dump();
}
