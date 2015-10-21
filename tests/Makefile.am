
AM_CPPFLAGS=-I../src/
LDADD=../src/.libs/liblogger.a -lpthread

TESTS=callback \
	file \
	pipe \
	stderr \
	stdout \
	stdoutcolor \
	syslog \
	tail \
	remove \
	testfilter

check_PROGRAMS=callback \
	file \
	pipe \
	stderr \
	stdout \
	stdoutcolor \
	syslog \
	tail \
	remove \
	testfilter
	
	
callback_SOURCES=callback.cpp
file_SOURCES=file.cpp
pipe_SOURCES=pipe.cpp
stderr_SOURCES=stderr.cpp
stdout_SOURCES=stdout.cpp
stdoutcolor_SOURCES=stdoutcolor.cpp
syslog_SOURCES=syslog.cpp
tail_SOURCES=tail.cpp
remove_SOURCES=remove.cpp
testfilter_SOURCES=testfilter.cpp


