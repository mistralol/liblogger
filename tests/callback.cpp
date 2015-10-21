

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

void Function(void *arg, const LogType Type, const std::string &str)
{
	printf("%d - %s\n", Type, str.c_str());
}

int main(int argc, char ** argv)
{
	LogManager::Add(new LogCallBack(NULL, Function));

	examples();

	LogManager::RemoveAll();
	return 0;
}

