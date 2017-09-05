
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	pid_t pid = fork();
	if (pid == 0) {
		int ret = system("../logmq/logmq");
		exit(WEXITSTATUS(ret));
	}
	if (pid < 0)
		abort();

	LogManager::Add(new LogMQ());

	examples();

	LogManager::RemoveAll();

	if (kill(pid, SIGTERM) < 0)
		abort();

	int status = 0;
	if (waitpid(pid, &status, 0) < 0)
		abort();

	return 0;
}

