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

private:


};
