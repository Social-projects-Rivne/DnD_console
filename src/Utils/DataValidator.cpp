#include "Includes/DataValidator.hpp"



DataValidator::DataValidator()
{
}

bool DataValidator::fValidateEmail(const std::string & email)
{
	if (email.find(' ')  != std::string::npos  ||  // check for invalid symbols
		email.find('\'') != std::string::npos ||
		email.find('"')  != std::string::npos  ||
		email.length()   == 0)
	{
		return false;
	}

	const std::regex  validate_email("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	if (!std::regex_match(email, validate_email))
	{
		return false;
	}

	return true;
}

bool DataValidator::fValidateUsername(const std::string & username)
{
	if (username.find(' ')  != std::string::npos ||  // check for invalid symbols
		username.find('\'') != std::string::npos ||
		username.find('"')  != std::string::npos ||
		username.find('*')  != std::string::npos ||
		username.length()   == 0)
	{
		return false;
	}
	return true;
}

bool DataValidator::fValidatePassword(const std::string & password)
{
	if (password.find(' ')  != std::string::npos ||  // check for invalid symbols
		password.find('\'') != std::string::npos ||
		password.find('"')  != std::string::npos ||
		password.find('*')  != std::string::npos ||
		password.length()   != 64)
	{
		return false;
	}

	return true;
}

bool DataValidator::fValidateAbility(const std::string & ability)
{
	int _ability;
	try 
	{
		_ability = std::stoi(ability);
	}
	catch (std::exception e)
	{
		return false;
	}

	if (_ability > 20 || _ability < 0)
		return false;

	return true;
}

bool DataValidator::fValidateAbilities(const std::string & abilities)
{
	json validate = json::parse(abilities);
	int sum = 0;

	for (auto & el : validate)
	{
		if (!fValidateAbility(el))
			return false;
		try
		{
			std::string sum_str = el;
			sum+=std::stoi(sum_str);
		}
		catch (std::exception e)
		{
			return false;
		}
	}

	if (sum > 80 || sum < 0)
		return false;
	return true;
}


bool DataValidator::fValidate(const std::string & to_validate, const type & t)
{
	
	switch (t)
	{
	case DataValidator::EMAIL:
		return fValidateEmail(to_validate);
		break;
	case DataValidator::USERNAME:
		return fValidateUsername(to_validate);
		break;
	case DataValidator::PASSWORD:
		return fValidatePassword(to_validate);
		break;
	case DataValidator::ABILITY:
		return fValidateAbility(to_validate);
		break;
	case DataValidator::ABILITIES:
		return fValidateAbilities(to_validate);
		break;
	default:
		return true;
	}
}

json DataValidator::fValidate(const json & to_validate)
{
	json result;
	for (auto it = to_validate.begin(); it != to_validate.end(); ++it)
	{
		if (it.key() == "email")
		{
			bool res = fValidateEmail(to_validate[it.key()]);
			result[it.key()] = res ? "Validated" : "Failed";
		}
		else if (it.key() == "username")
		{
			bool res = fValidateUsername(to_validate[it.key()]);
			result[it.key()] = res ? "Validated" : "Failed";
		}
		else if (it.key() == "password")
		{
			bool res = fValidatePassword(to_validate[it.key()]);
			result[it.key()] = res ? "Validated" : "Failed";
		}
		else if (it.key() == "abilities")
		{
			bool res = fValidateAbilities(to_validate[it.key()].dump());
			result[it.key()] = res ? "Validated" : "Failed";
		}
		else
		{
			result[it.key()] = "Not implemented";
		}

	}
	return result;
}

bool DataValidator::fValidate(const std::string & password, const std::string & retry_password)
{
	return password == retry_password;
}




