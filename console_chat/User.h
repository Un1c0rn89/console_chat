#pragma once

class User
{
public:
	User(std::string login, std::string name, std::string password) : 
		_login(login), _name(name), _password(password){}

	const std::string getLogin() { return _login; }
	//void setLogin(std::string& login) { _login = login; }

	const std::string getName() { return _name; }

	const std::string getPassword() { return _password; }
	//void setPassword(std::string& password) { _password = password; }

private:
	std::string _login;
	std::string _name;
	std::string _password;
};