#include "Logger.h"


namespace Didax
{

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::log(const std::string & msg)
{
	std::cout << msg << std::endl;
}

}