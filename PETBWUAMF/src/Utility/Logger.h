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
#ifdef DEBUG

		std::cout << msg << std::endl;

#endif 

	}
	static void logW(const std::string & msg)
	{
#ifdef DEBUG

		std::cout << msg;

#endif 

	}
	static void logW(const char & msg)
	{
#ifdef DEBUG

		std::cout << msg;

#endif 

	}
private:


};
