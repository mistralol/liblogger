

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	LogManager::Add(new LogStdoutColor());

	examples();

	LogManager::RemoveAll();
	return 0;
}

