OBJECTS = simple-test.o

default: xopt-test

%.o: %.c
	gcc -ansi -pedantic -Wall -Wextra -Werror -I.. -c $< -o $@

xopt-test: $(OBJECTS) ../libxopt.a
	gcc -L.. -lxopt -o $@ $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f xopt-test
