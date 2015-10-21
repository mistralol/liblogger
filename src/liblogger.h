

#ifndef LIBLOGGER_H
#define LIBLOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>

#include <string>
#include <list>
#include <map>
#include <memory>
#include <exception>

#include <liblogger/LogException.h>
#include <liblogger/LogType.h>
#include <liblogger/ILogger.h>
#include <liblogger/ILogFilter.h>
#include <liblogger/Logger.h>
#include <liblogger/LogManager.h>
#include <liblogger/LogManagerScopedLock.h>
#include <liblogger/LogStdout.h>
#include <liblogger/LogStdoutColor.h>
#include <liblogger/LogStderr.h>
#include <liblogger/LogSyslog.h>
#include <liblogger/LogFile.h>
#include <liblogger/LogPipe.h>
#include <liblogger/LogCallBack.h>
#include <liblogger/LogTail.h>
#include <liblogger/LogTailIdx.h>

#include <liblogger/LogFilterType.h>
#include <liblogger/LogFilterDup.h>
#include <liblogger/LogFilterCallBack.h>

#endif

