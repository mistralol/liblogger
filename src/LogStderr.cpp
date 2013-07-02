
#include <stdio.h>

#include "liblogger.h"

namespace liblogger {

void LogStderr::GetName(std::string *str) {
	*str = "Stderr";
}

void LogStderr::GetDesc(std::string *str) {
	*str = "Logs to Stderr";
}

void LogStderr::Log(LogType Type, const std::string str) {
	fprintf(stderr, "%s\n", str.c_str());
	fflush(stderr);
}

};
