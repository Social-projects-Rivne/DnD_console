#pragma once



#ifndef CHARACTER
#define CHARACTER

#include "json.hpp"
#include <iostream>
#include <string>
#include "Dice.hpp"
#include "DataValidator.hpp"

const int MAX_ABILITIES_SUM_ = 80;

using json = nlohmann::json;


class Character
{

	std::string _name;
	std::string _race;
	std::string _class;
	std::string _experience;
	std::string _hitpoints;
	std::string _level;
	std::string _strength;
	std::string _strength_mod;
	std::string _dexterity;
	std::string _dexterity_mod;
	std::string _constitution;
	std::string _constitution_mod;
	std::string _intelligence;
	std::string _intelligence_mod;
	std::string _wisdom;
	std::string _wisdom_mod;
	std::string _charisma;
	std::string _charisma_mod;
	std::string _owner;

	std::string fSetAbilityMod(std::string ability);

public:

	Character();

	Character(std::string &name,
		std::string &race,
		std::string &_class,
		std::string &experience,
		std::string &hitpoints,
		std::string &level,
		std::string &strength,
		std::string &dexterity,
		std::string &constitution,
		std::string &intelligence,
		std::string &wisdom,
		std::string &charisma,
		std::string &owner
	);

	void fSetOwner(const std::string &owner); // setter for owner

	void fRandomizeAbilities(); // fills the character abilities by rolling dices

	void fSetAbilities(); // asks user for defining abilities points

	void fAddCharacter(); // creates Character
	
	json fToJson(); // converts Character data into json

	~Character();

};
#endif