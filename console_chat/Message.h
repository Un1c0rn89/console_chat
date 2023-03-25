#pragma once

class Message
{
public:
	Message(std::string& from, std::string& to, std::string& text) : 
		_from(from), _to(to), _text(text) {
		setTime(_time);
	}

	const std::string getFrom() { return _from; }
	const std::string getTo() { return _to; }
	const std::string getText() { return _text; }
	const std::string getTime() { return _time; }	

private:
	std::string _from;
	std::string _to;
	std::string _text;
	std::string _time;

	void setTime(std::string& t) {
		time_t result = time(nullptr);
		const int BUF_SIZE = 26;
		char str[BUF_SIZE];
		ctime_s(str, sizeof str, &result);
		t = str;
	}
};