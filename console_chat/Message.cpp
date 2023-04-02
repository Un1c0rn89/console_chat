#include <iostream>
#include "Message.h"

Message::Message(std::string& from, std::string& to, std::string& text) :
	_from(from), _to(to), _text(text) {
	setTime(_time);
}

std::string Message::getFrom() const {
	return _from;
}

std::string Message::getTo() const {
	return _to;
}

std::string Message::getText() const {
	return _text;
}

std::string Message::getTime() const {
	return _time;
}

void Message::setTime(std::string& t) {
	time_t result = time(nullptr);
	const int BUF_SIZE = 26;
	char str[BUF_SIZE];
	ctime_s(str, sizeof str, &result);
	t = str;
}