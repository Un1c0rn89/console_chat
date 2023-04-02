#include <string>
#include "User.h"

User::User(std::string& name, std::string& login, std::string& password) :
	_name(name), _login(login), _password(password) {}

std::string User::getName() const {
	return _name;
}

std::string User::getLogin() const {
	return _login;
}

std::string User::getPassword() const {
	return _password;
}