

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

static void Function(const LogType Type, const std::string &str)
{
	printf("%d - %s\n", Type, str.c_str());
}

int main(int argc, char ** argv)
{
	std::function<void(const LogType, const std::string &)> func = Function;
	LogManager::Add(new LogFunction(func));

	examples();

	LogManager::RemoveAll();
	return 0;
}

