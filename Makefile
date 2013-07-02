
include Makefile.Rules

all:
	$(MAKE) -C src
	$(AR) cru liblogger.a src/*.o
	$(CPP) -shared -o liblogger.so src/*.o

clean:
	$(RM) liblogger.a liblogger.so
	$(MAKE) -C src clean


