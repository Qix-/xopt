HEADERS = xopt.h
OBJECTS = xopt.o

.PHONY: all clean

all: libxopt.a
	$(MAKE) -C test

%.o: %.c $(HEADERS)
	$(CC) -ansi -pedantic -Wall -Wextra -Werror $(CFLAGS) $(DEFINES) -c $< -o $@

libxopt.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f libxopt.a
	$(MAKE) -C test clean
