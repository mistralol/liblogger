
#include <stdio.h>

#include "liblogger.h"

namespace liblogger
{

void LogStdout::GetName(std::string *str)
{
	*str = "Stdout";
}

void LogStdout::GetDesc(std::string *str)
{
	*str = "Logs to Stdout";
}

void LogStdout::Log(LogType Type, const std::string str)
{
	printf("%s\n", str.c_str());
	fflush(stdout);
}

};

