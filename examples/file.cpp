

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	LogManager::Init();
	LogManager::Add(new LogFile("/dev/self/fd/1"));

	examples();

	LogManager::RemoveAll(true);
	return 0;
}

