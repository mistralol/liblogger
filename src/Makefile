
include ../Makefile.Rules

SRCS= 	Logger.cpp	\
		LogStdout.cpp \
		LogStderr.cpp \
		LogSyslog.cpp \
		LogCallBack.cpp \
		LogManager.cpp

OBJS=$(SRCS:%.cpp=%.o)

all: $(OBJS) ../liblogger.a ../liblogger.so

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

	
