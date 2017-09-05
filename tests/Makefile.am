
AM_CPPFLAGS=-I../src/
LDADD=../src/.libs/liblogger.a -lpthread

TESTS=callback \
	function \
	file \
	filehourly \
	filedaily \
	pipe \
	stderr \
	stdout \
	stdoutcolor \
	syslog \
	tail \
	remove \
	testfilter \
	tcpserver \
	unixserver \
	logmq \
	streamlogger

check_PROGRAMS=callback \
	function \
	file \
	filehourly \
	filedaily \
	pipe \
	stderr \
	stdout \
	stdoutcolor \
	syslog \
	tail \
	remove \
	testfilter \
	tcpserver \
	unixserver \
	logmq \
	streamlogger

check_HEADERS=examples.h	
	
callback_SOURCES=callback.cpp
function_SOURCES=function.cpp
file_SOURCES=file.cpp
filehourly_SOURCES=filehourly.cpp
filedaily_SOURCES=filedaily.cpp
pipe_SOURCES=pipe.cpp
stderr_SOURCES=stderr.cpp
stdout_SOURCES=stdout.cpp
stdoutcolor_SOURCES=stdoutcolor.cpp
syslog_SOURCES=syslog.cpp
tail_SOURCES=tail.cpp
remove_SOURCES=remove.cpp
testfilter_SOURCES=testfilter.cpp
tcpserver_SOURCES=tcpserver.cpp
unixserver_SOURCES=unixserver.cpp
logmq_SOURCES=logmq.cpp
streamlogger_SOURCES=streamlogger.cpp

