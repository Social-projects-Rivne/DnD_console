#include "Includes\UserActions.hpp"

UserActions::UserActions()
{
}

json UserActions::fLogin()
{
	json        user_login_data;  // json login result
	std::string user_login;		  // user login input
	std::string user_pass;		  // user pass input
	SHA256      sha256;			  // sha256 obj

	
	std::cout << "Enter login: ";
	std::getline(std::cin, user_login);  // get user login
	std::cout << "Enter password: ";
	std::getline(std::cin, user_pass);   // get user pass
    user_pass = sha256(user_pass);       // hash user pass

	user_login_data["action"] = "login";
	user_login_data["Login"]    = user_login; // insert into json key Login with value of user login input
	user_login_data["Password"] = user_pass;  // insert into json key Password with value of user hash pass
	return user_login_data;
}

json UserActions::fRegistration()
{
	json user_registration_data;   // json registration resualt
	
	std::string user_username;    //  user input login  
	std::string user_password;    //  user input password
	std::string user_email;       //  user input e-mail;
	std::string repeat_password;  
	SHA256      sha256;			  // sha256 obj

	std::cout << "Enter username: (Username field must not be empty)" << std::endl;;
	std::getline(std::cin, user_username);       // get user username
		
	std::cout << "Enter email: (field may be empty)" << std::endl;;
	std::getline(std::cin, user_email);          // get user email

	std::cout << "Enter password: (Password must be longer than 6 characters and not be empty)" << std::endl;
	std::getline(std::cin, user_password);       // get user password
	
	std::cout << "Please enter password again: " << std::endl; 
	std::cin >> repeat_password;

	user_password = sha256(user_password);       // hash user pass
	repeat_password = sha256(repeat_password);

	if (user_password == repeat_password)        // check user passwords
	{

		user_registration_data["action"] = "registration";
		user_registration_data["username"] = user_username;
		user_registration_data["password"] = user_password;

		return user_registration_data;
	}

}
