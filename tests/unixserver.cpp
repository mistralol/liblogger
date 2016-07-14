

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	LogManager::Add(new LogUnixServer("/tmp/TestLogServer"));

	sleep(2);

	examples();

	LogManager::RemoveAll();
	return 0;
}

