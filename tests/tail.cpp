

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	std::shared_ptr<LogTail> Tail(new LogTail(3));
	LogManager::Add(Tail);

	examples();

	printf("%s\n", Tail->GetData().c_str());
	LogManager::RemoveAll();
	return 0;
}

