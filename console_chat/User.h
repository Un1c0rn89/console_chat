#pragma once

class User
{
public:
	User(std::string& name, std::string& login, std::string& password);

	std::string getLogin() const;
	std::string getName() const;
	std::string getPassword() const;

private:
	std::string _name;
	std::string _login;
	std::string _password;
};