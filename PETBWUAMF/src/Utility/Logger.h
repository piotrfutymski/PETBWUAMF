#pragma once
#include <string>
#include <iostream>


class Logger
{
public:
	Logger();
	~Logger();

	static void log(const std::string & msg)
	{
		std::cout << msg << std::endl;
	}
	static void log(const char & msg)
	{
		std::cout << msg << std::endl;
	}


	static void logW(const std::string & msg)
	{
		std::cout << msg;
	}
	static void logW(const char & msg)
	{
		std::cout << msg;
	}
private:


};
