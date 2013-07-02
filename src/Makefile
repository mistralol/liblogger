
CPP=g++
CPPFLAGS+=-Wall -Werror -DDEBUG -D_GNU_SOURCE -ggdb -std=gnu++0x -fPIC
INCLUDE+=-I../include
MKDEP=gcc -E -MM

SRCS= 	Logger.cpp	\
		LogStdout.cpp \
		LogStderr.cpp \
		LogSyslog.cpp \
		LogCallBack.cpp \
		LogManager.cpp

OBJS=$(SRCS:%.cpp=%.o)


all: ../liblogger.a ../liblogger.so

../liblogger.a: $(OBJS) .depend
	$(AR) cru ../liblogger.a $(OBJS)

../liblogger.so: $(OBJS) .depend
	$(CPP) -shared -o ../liblogger.so $(OBJS)

.cpp.o:
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

.depend: $(SRCS)
	$(MKDEP) $(INCLUDE) $(SRCS) > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

clean:
	$(RM) $(OBJS) .depend
	$(RM) ../liblogger.a ../liblogger.so
	
