.PHONY: all clean

all: simple-test macro-test

%.o: %.c
	$(CC) -ansi -pedantic -Wall -Wextra -Werror $(CFLAGS) -I.. -c $< -o $@

simple-test: simple-test.o ../libxopt.a
	$(CC) -L.. -o $@ $< -lxopt
macro-test: macro-test.o ../libxopt.a
	$(CC) -L.. -o $@ $< -lxopt

clean:
	-rm -f $(OBJECTS) simple-test macro-test *.o
