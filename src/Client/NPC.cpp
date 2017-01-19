//
//  NPC.cpp
//  Client
//
//  Created by Olha Leskovska on 1/15/17.
//  Copyright © 2017 Olha Leskovska. All rights reserved.
//

#include "Includes/NPC.hpp"

NPC::NPC()
{
    _name = "";
    _type_NPC = "";
    _hitpoints = "";
    _level = "";
    _strength = "";
    _dexterity = "";
    _constitution = "";
    _intelligence = "";
    _wisdom = "";
    _charisma = "";
}

NPC::NPC(string name,
         string type_NPC,
         string hitpoints,
         string level,
         string strength,
         string dexterity,
         string constitution,
         string intelligence,
         string wisdom,
         string charisma)
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
    _level = "1";
    
    int sum;
    do
    {
        sum = 0;
        string hitpoints;
        do
        {
            hitpoints = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(hitpoints, DataValidator::ABILITY))
                _hitpoints = hitpoints;
        } while (!DataValidator::fValidate(hitpoints, DataValidator::ABILITY));
        sum += stoi(hitpoints);
        
        string strength;
        do
        {
            strength = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(strength, DataValidator::ABILITY))
                _strength = strength;
        } while (!DataValidator::fValidate(strength, DataValidator::ABILITY));
        sum += stoi(strength);
        
        string dexterity;
        do
        {
            dexterity = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(dexterity, DataValidator::ABILITY))
                _dexterity = dexterity;
        } while (!DataValidator::fValidate(dexterity, DataValidator::ABILITY));
        sum += stoi(dexterity);
        
        string constitution;
        do
        {
            constitution = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(constitution, DataValidator::ABILITY))
                _constitution = constitution;
        } while (!DataValidator::fValidate(constitution, DataValidator::ABILITY));
        sum += stoi(constitution);
        
        string intelligence;
        do
        {
            intelligence = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(intelligence, DataValidator::ABILITY))
                _intelligence = intelligence;
        } while (!DataValidator::fValidate(intelligence, DataValidator::ABILITY));
        sum += stoi(intelligence);
        
        string wisdom;
        do
        {
            wisdom = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(wisdom, DataValidator::ABILITY))
                _wisdom = wisdom;
        } while (!DataValidator::fValidate(wisdom, DataValidator::ABILITY));
        sum += stoi(wisdom);
        
        string charisma;
        do
        {
            charisma = to_string(Dice::fMultipleRollSum(Dice::D4, 4, 3));
            
            if (DataValidator::fValidate(charisma, DataValidator::ABILITY))
                _charisma = charisma;
        } while (!DataValidator::fValidate(charisma, DataValidator::ABILITY));
        sum += stoi(charisma);
    } while (sum > MAX_ABILITIES_SUM);
}

void NPC::fSetAbilities() // asks user for defining abilities points
{
    string level;
    do
    {
        cout << "Input the level: ";
        getline(cin, level);
        
        if (stoi(level) > 0) // level validation
            _level = level;
    } while (stoi(level) <= 0);
    
    int sum;
    do
    {
        sum = 0;
        string hitpoints;
        do
        {
            cout << "Input the ammount of hitpoints: ";
            getline(cin, hitpoints);
            
            if (!DataValidator::fValidate(hitpoints, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _hitpoints = hitpoints;
        } while (!DataValidator::fValidate(hitpoints, DataValidator::ABILITY));
        sum += stoi(hitpoints);
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        string strength;
        do
        {
            cout << "Input the strength-value: ";
            getline(cin, strength);
            
            if (!DataValidator::fValidate(strength, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _strength = strength;
        } while (!DataValidator::fValidate(strength, DataValidator::ABILITY));
        sum += stoi(strength);
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        string dexterity;
        do
        {
            cout << "Input the dexterity-value: ";
            getline(cin, dexterity);
            
            if (!DataValidator::fValidate(dexterity, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _dexterity = dexterity;
        } while (!DataValidator::fValidate(dexterity, DataValidator::ABILITY));
        sum += stoi(dexterity);
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        string constitution;
        do
        {
            cout << "Input the constitution-value: ";
            getline(cin, constitution);
            
            if (!DataValidator::fValidate(constitution, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _constitution = constitution;
        } while (!DataValidator::fValidate(constitution, DataValidator::ABILITY));
        sum += stoi(constitution);
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        string intelligence;
        do
        {
            cout << "Input the intelligence-value: ";
            getline(cin, intelligence);
            
            if (!DataValidator::fValidate(intelligence, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _intelligence = intelligence;
        } while (!DataValidator::fValidate(intelligence, DataValidator::ABILITY));
        sum += stoi(intelligence);
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        string wisdom;
        do
        {
            cout << "Input the wisdom-value: ";
            getline(cin, wisdom);
            
            if (!DataValidator::fValidate(wisdom, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _wisdom = wisdom;
        } while (!DataValidator::fValidate(wisdom, DataValidator::ABILITY));
        sum += stoi(wisdom);
        
        cout << MAX_ABILITIES_SUM - sum << " points left." << endl;
        string charisma;
        do
        {
            cout << "This ability is the last." << endl;
            cout << "Input the charisma-value: ";
            getline(cin, charisma);
            
            if (!DataValidator::fValidate(charisma, DataValidator::ABILITY))
                cout << "This datum should be more than 0 and less than (or equal to) 20!" << endl;
            else
                _charisma = charisma;
        } while (!DataValidator::fValidate(charisma, DataValidator::ABILITY));
        sum += stoi(charisma);
        
        if (sum > MAX_ABILITIES_SUM)
            cout << "The sum of all vability-values should be less than (or equal to) 80!\nTry again!" << endl;
    } while (sum > MAX_ABILITIES_SUM);
}

void NPC::fAddNPC() // creates NPC
{
    cout << "********** NPC **********" << endl;
    string name;
    do
    {
        cout << "Input a name: ";
        getline(cin, name);
        
        if (!DataValidator::fValidate(name, DataValidator::SQL_INJECTION)) // name validation
            cout << "This datum should consist of letters!\n";
        else
            _name = name;
    } while (!DataValidator::fValidate(name, DataValidator::SQL_INJECTION));
    
    string type_NPC;
    do
    {
        cout << "Input the NPC's type: ";
        getline(cin, type_NPC);
        
        if (!DataValidator::fValidate(type_NPC, DataValidator::SQL_INJECTION)) // type_NPC validation
            cout << "This datum should consist of letters!" << endl;
        else
            _type_NPC = type_NPC;
    } while (!DataValidator::fValidate(type_NPC, DataValidator::SQL_INJECTION));
    
    int choice;
    cout << "Choose the way to fill the NPC's abilities:" << endl;
    cout << "1. by rolling dices;" << endl;
    cout << "2. manually" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cin.clear();
    cin.ignore();
    
    switch (choice)
    {
        case 1:
            NPC::fRandomizeAbilities();
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
    npc["npc"] = _name;
    npc["type"] = _type_NPC;
    npc["level"] = _level;
    
    json abilities;
    abilities["hitpoints"] = _hitpoints;
    abilities["strength"] = _strength;
    abilities["dexterity"] = _dexterity;
    abilities["constitution"] = _constitution;
    abilities["intelligence"] = _intelligence;
    abilities["wisdom"] = _wisdom;
    abilities["charisma"] = _charisma;
    
    npc["abilities"] = abilities;
    
    return npc;
}

NPC::~NPC() {}
