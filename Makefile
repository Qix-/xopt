HEADERS = xopt.h
OBJECTS = xopt.o

default: libxopt.a

%.o: %.c $(HEADERS)
	gcc -ansi -pedantic -Wall -Wextra -Werror -c $< -o $@

libxopt.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f libxopt.a
