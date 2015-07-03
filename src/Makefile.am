
AM_CPPFLAGS=

lib_LTLIBRARIES=liblogger.la

liblogger_la_LDFLAGS = -version-info 1:0:0

liblogger_la_SOURCES=Logger.cpp LogManager.cpp LogType.cpp \
		LogCallBack.cpp \
		LogFile.cpp \
		LogPipe.cpp \
		LogStderr.cpp \
		LogStdout.cpp \
		LogStdoutColor.cpp \
		LogSyslog.cpp \
		LogTail.cpp 


include_HEADERS=liblogger.h

otherincludedir = $(includedir)/liblogger

otherinclude_HEADERS=liblogger/LogManager.h liblogger/ILogger.h liblogger/LogType.h \
	liblogger/LogCallBack.h \
	liblogger/LogFile.h \
	liblogger/Logger.h \
	liblogger/LogPipe.h \
	liblogger/LogStderr.h \
	liblogger/LogStdout.h \
	liblogger/LogStdoutColor.h \
	liblogger/LogSyslog.h \
	liblogger/LogTail.h  


