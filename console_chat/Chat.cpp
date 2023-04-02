#include <iostream>
#include "Chat.h"

void Chat::start() {
	_isWork = true;
}

void Chat::showMainMenu() {
	std::cout << "---Welcome to main menu!---\n";
	while (_isWork && !_currentUser) {
		std::cout << "(1) login\n" <<
			"(2) signup\n" <<
			"(0) exit\n";
		char operation;
		std::cin >> operation;
		switch (operation) {
		case '1':
			logIn();
			break;
		case '2':
			try {
				signUp();
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			_isWork = false;
			break;
		default:
			std::cout << "error: unknown operation!\n";
			break;
		}
	}
}

bool Chat::isCurrentUser() const {
	return _currentUser != nullptr ? true : false;
}

bool Chat::isWork() const {
	return _isWork;
}

std::unique_ptr<User> Chat::getUserByLogin(std::string& login) const {
	for (auto& user : _users) {
		if (login == user.getLogin()) {
			return std::make_unique<User>(user);
		}
	}
	return nullptr;
}

std::unique_ptr<User> Chat::getUserByName(std::string& name) const {
	for (auto& user : _users) {
		if (name == user.getName()) {
			return std::make_unique<User>(user);
		}
	}
	return nullptr;
}

void Chat::logIn() {
	if (_users.empty())
	{
		std::cout << "error: there is no users!\n" <<
			"try to signUp first!\n";
		return;
	}
	std::cout << "enter login:\n";
	std::string login;
	std::cin >> login;
	_currentUser = getUserByLogin(login);

	if (!_currentUser) {
		std::cout << "error: wrong login!\n";
		return;
	}
	else {
		std::cout << "enter password:\n";
		std::string password;
		std::cin >> password;

		while (password != _currentUser->getPassword()) {
			std::cout << "error: wrong password!\n" <<
				"(1) try again\n" <<
				"(0) exit\n";
			char operation;
			std::cin >> operation;
			switch (operation) {
			case '1':
				std::cin >> password;
				break;
			case '0':
				_currentUser = nullptr;
				return;
			default:
				std::cout << "error: unknown operation!\n";
				break;
			}
		}
	}
}

void Chat::signUp() {
	std::cout << "enter name:\n";
	std::string name;
	std::cin >> name;
	if (getUserByName(name) || name == "all") {
		throw UserNameExp();
	}

	std::cout << "enter login:\n";
	std::string login;
	std::cin >> login;
	if (getUserByLogin(login) || login == "all") {
		throw UserLoginExp();
	}

	std::cout << "enter password:\n";
	std::string password;
	std::cin >> password;

	User user(name, login, password);
	_users.push_back(user);
	_currentUser = std::make_unique<User>(user);
}

void Chat::showUserMenu() {
	std::cout << "---Hello, " << _currentUser->getName() << "!---\n";
	while (_currentUser) {
		std::cout << "(1) show my messages\n" <<
			"(2) show chat\n" <<
			"(3) show all users\n" <<
			"(4) send message\n" <<
			"(0) return to main menu\n";
		char operation;
		std::cin >> operation;
		switch (operation) {
		case '1':
			showMyMessages();
			break;
		case '2':
			showChat();
			break;
		case '3':
			showAllUsers();
			break;
		case '4':
			sendMessage();
			break;
		case '0':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "error: unknown operation!\n";
			break;
		}
	}
}

void Chat::showAllUsers() const {
	std::cout << "---All users---\n";
	for (auto& user : _users) {
		std::cout << user.getName();
		if (user.getName() == _currentUser->getName()) {
			std::cout << " <- you";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Chat::sendMessage() {
	std::cout << "---New message---\n" <<
		"to:\n(insert user name or \"all\")\n";
	std::string to;
	std::cin >> to;
	if (to == _currentUser->getName()) {
		std::cout << "error: you can't send messages to yourself!\n";
		return;
	}
	while (!getUserByName(to) && to != "all" && to == _currentUser->getName()) {
		std::cout << "error: user not found!\n" <<
			"(1) try again\n" <<
			"(0) exit\n";
		char operation;
		std::cin >> operation;
		switch (operation) {
		case '1':
			std::cout << "insert user name or \"all\":\n";
			std::cin >> to;
			break;
		case '0':
			return;
		default:
			std::cout << "error: unknown operation!\n";
			break;
		}
	}
	std::cout << "text:\n";
	std::string text;
	std::cin.ignore();
	getline(std::cin, text);

	std::string from = _currentUser->getName();
	Message message(from, to, text);
	_messages.push_back(message);
}

void Chat::showChat() const {
	std::cout << "---Welcome to Chat!---\n\n";
	for (auto& message : _messages) {
		if (message.getTo() == "all") {
			//»сход€щие сообщени€ текущего пользовател€ выдел€ютм€ зеленым
			if (message.getFrom() == _currentUser->getName()) {
				std::cout << "\033[32m";
			}
			std::cout << "time: " << message.getTime() <<
				"from: " << message.getFrom() <<
				"\ntext: " << message.getText() <<
				"\033[0m" << "\n\n";
		}
	}
}

void Chat::showMyMessages() const {
	std::cout << "---My messages:---\n\n";
	for (auto& message : _messages) {
		//¬ход€щие сообщени€ дл€ текущего пользовател€ выдел€ютм€ желтым
		if (message.getTo() == _currentUser->getName()) {
			std::cout << "\033[33m" << "time: " << message.getTime() <<
				"from: " << message.getFrom() <<
				"\ntext: " << message.getText() <<
				"\033[0m" << "\n\n";
		}
		//»сход€щие сообщени€ текущего пользовател€ выдел€ютм€ зеленым
		if (message.getFrom() == _currentUser->getName() && message.getTo() != "all") {
			std::cout << "\033[32m" << "time: " << message.getTime() <<
				"to: " << message.getTo() <<
				"\ntext: " << message.getText() <<
				"\033[0m" << "\n\n";
		}
	}
}