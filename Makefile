HEADERS = xopt.h
OBJECTS = snprintf.o xopt.o

default: libxopt.a
	make -C test

DEFINES += -DHAVE_STDARG_H=1 -DHAVE_STDLIB_H=1

%.o: %.c $(HEADERS)
	gcc -ansi -pedantic -Wall -Wextra -Werror $(DEFINES) -c $< -o $@

libxopt.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f libxopt.a
	make -C test clean
