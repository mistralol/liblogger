
#include <liblogger.h>

LogException::LogException(const std::string message)
{
	m_message = message;
}

LogException::~LogException()
{

}
		
const char *LogException::what() const throw()
{
	return m_message.c_str();
}

