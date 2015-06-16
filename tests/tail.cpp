

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	LogManager::Init();
	LogTail Tail(3);
	LogManager::Add(&Tail);

	examples();

	LogManager::RemoveAll(false);

	printf("%s\n", Tail.GetData().c_str());
	return 0;
}

