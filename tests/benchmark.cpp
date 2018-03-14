

#include <liblogger.h>

using namespace liblogger;

static int Benchmark(int count) {
    struct timespec Started, Ended;
    if (clock_gettime(CLOCK_MONOTONIC, &Started) < 0)
        abort();

    for(int i=0;i<count;i++) {
        LogInfo("Some Log message %s %d", "Some String", i);
    }

    if (clock_gettime(CLOCK_MONOTONIC, &Ended) < 0)
        abort();

    uint64_t StartedNanoSeconds = Started.tv_sec * (uint64_t) 1000000000;
    StartedNanoSeconds += Started.tv_nsec;

    uint64_t EndedNanoSeconds = Ended.tv_sec * (uint64_t) 1000000000;
    EndedNanoSeconds += Ended.tv_nsec;

    uint64_t totaltime = EndedNanoSeconds - StartedNanoSeconds;
    uint64_t calltime = totaltime / count;

    return (uint64_t) 1000000000 / calltime;
}

static int BenchmarkStreamer(int count) {
    struct timespec Started, Ended;
    if (clock_gettime(CLOCK_MONOTONIC, &Started) < 0)
        abort();

    for(int i=0;i<count;i++) {
        LOGGER << "Some Log message %s %d" << "Some String" << i << std::endl;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &Ended) < 0)
        abort();

    uint64_t StartedNanoSeconds = Started.tv_sec * (uint64_t) 1000000000;
    StartedNanoSeconds += Started.tv_nsec;

    uint64_t EndedNanoSeconds = Ended.tv_sec * (uint64_t) 1000000000;
    EndedNanoSeconds += Ended.tv_nsec;

    uint64_t totaltime = EndedNanoSeconds - StartedNanoSeconds;
    uint64_t calltime = totaltime / count;

    return (uint64_t) 1000000000 / calltime;
}

static int BenchmarkTrace(int count, int trace) {
    struct timespec Started, Ended;
    if (clock_gettime(CLOCK_MONOTONIC, &Started) < 0)
        abort();

    for(int i=0;i<count;i++) {
        Trace T = Trace(LOGGER_INFO);
        for(int j=0;j<trace;j++)
            T.Log("Some Log message %s %d", "Some String", i);
    }

    if (clock_gettime(CLOCK_MONOTONIC, &Ended) < 0)
        abort();

    uint64_t StartedNanoSeconds = Started.tv_sec * (uint64_t) 1000000000;
    StartedNanoSeconds += Started.tv_nsec;

    uint64_t EndedNanoSeconds = Ended.tv_sec * (uint64_t) 1000000000;
    EndedNanoSeconds += Ended.tv_nsec;

    uint64_t totaltime = EndedNanoSeconds - StartedNanoSeconds;
    uint64_t calltime = totaltime / (count * trace);

    return (uint64_t) 1000000000 / calltime;
}

int main(int argc, char ** argv)
{
    int count = 100000;
    int trace = 100;
	//LogManager::Add();

    printf("Rates are in Messages per second\n");
	printf("           Empty: %d\n", Benchmark(count));
    printf("   EmptyStreamer: %d\n", BenchmarkStreamer(count));
    printf("      EmptyTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");

    LogManager::Add(std::make_shared<LogFile>("/dev/null"));
    printf("         LogFile: %d\n", Benchmark(count));
    printf(" LogFileStreamer: %d\n", BenchmarkStreamer(count));
    printf("    LogFileTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");
	LogManager::RemoveAll();

    LogManager::Add(std::make_shared<LogPipe>("cat > /dev/null"));
    printf("         LogPipe: %d\n", Benchmark(count));
    printf(" LogPipeStreamer: %d\n", BenchmarkStreamer(count));
    printf("    LogPipeTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");
	LogManager::RemoveAll();

    LogManager::Add(std::make_shared<LogTail>(100));
    printf("         LogTail: %d\n", Benchmark(count));
    printf(" LogTailStreamer: %d\n", BenchmarkStreamer(count));
    printf("    LogTailTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");
	LogManager::RemoveAll();

    LogManager::FilterAdd(std::make_shared<LogFilterDup>());
    printf("        LogFilterDup: %d\n", Benchmark(count));
    printf("LogFilterDupStreamer: %d\n", BenchmarkStreamer(count));
    printf("   LogFilterDupTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");
	LogManager::FilterRemoveAll();

    LogManager::FilterAdd(std::make_shared<LogFilterType>(LOGGER_CRIT));
    printf("        LogFilterType: %d\n", Benchmark(count));
    printf("LogFilterTypeStreamer: %d\n", BenchmarkStreamer(count));
    printf("   LogFilterTypeTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");
	LogManager::FilterRemoveAll();

    LogManager::FilterAdd(std::make_shared<LogFilterContains>("World"));
    printf("        LogFilterContains: %d\n", Benchmark(count));
    printf("LogFilterContainsStreamer: %d\n", BenchmarkStreamer(count));
    printf("   LogFilterContainsTrace: %d\n", BenchmarkTrace(count / trace, trace));
    printf("\n");
	LogManager::FilterRemoveAll();


	return 0;
}

