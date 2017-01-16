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

	static bool fValidateName(const std::string & name);

	static bool fValidatePassword(const std::string & password);

	static bool fValidateAbility(const std::string & ability);

	static bool fValidateAbilities(const std::string & abilities);

	static bool fValidateLength(const std::string & length);

	static bool fValidateSqlInjection(const std::string & msg);

public:
	enum type {
		EMAIL,
		NAME,
		PASSWORD,
		ABILITY,
		ABILITIES,
		LENGTH,
		SQL_INJECTION
	};

	static bool fValidate(const std::string & to_validate, const type & t);

	static json fValidate(const json & to_validate);

	static bool fValidate(const std::string & password, const std::string & retry_password);

};

#endif // !_DATA_VALIDATOR_HPP_

