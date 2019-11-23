C=gcc
CFLAGS=-I.
DEPS = helper.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

findkeyb: findkeyb.o
	$(CC) -o findkeyb findkeyb.o 
