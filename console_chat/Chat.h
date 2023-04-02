#pragma once
#include <exception>
#include <vector>
#include <string>
#include <memory>
#include "User.h"
#include "Message.h"

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is busy"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: user name is busy"; }
};

class Chat
{
public:
	void start();
	void showMainMenu();
	void showUserMenu();
	bool isCurrentUser() const;
	bool isWork() const;

private:
	bool _isWork = false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::unique_ptr<User> _currentUser = nullptr;

	std::unique_ptr<User> getUserByLogin(std::string& login) const;
	std::unique_ptr<User> getUserByName(std::string& name) const;
	void logIn();
	void signUp();
	void showAllUsers() const;
	void sendMessage();
	void showChat() const;
	void showMyMessages() const;
};