#pragma once

class Message
{
public:
	Message(std::string& from, std::string& to, std::string& text);

	std::string getFrom() const;
	std::string getTo() const;
	std::string getText() const;
	std::string getTime() const;

private:
	std::string _from;
	std::string _to;
	std::string _text;
	std::string _time;

	void setTime(std::string& t);
};