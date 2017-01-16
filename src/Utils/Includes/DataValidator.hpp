#pragma once
#ifndef _DATA_VALIDATOR_HPP_
#define _DATA_VALIDATOR_HPP_

#include <string>
#include <regex>
#include "json.hpp"

using json = nlohmann::json;

class DataValidator
{
private:
	DataValidator();

	static bool fValidateEmail(const std::string & email);

	static bool fValidateUsername(const std::string & username);

	static bool fValidatePassword(const std::string & password);

	static bool fValidateAbility(const std::string & ability);

	static bool fValidateAbilities(const std::string & abilities);

public:
	enum type {
		EMAIL,
		USERNAME,
		PASSWORD,
		ABILITY,
		ABILITIES,
	};

	static bool fValidate(const std::string & to_validate, const type & t);

	static json fValidate(const json & to_validate);

	static bool fValidate(const std::string & password, const std::string & retry_password);

};

#endif // !_DATA_VALIDATOR_HPP_

