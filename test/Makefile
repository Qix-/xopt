OBJECTS = simple-test.o

default: xopt-test

%.o: %.c
	gcc -ansi -pedantic -Wall -Wextra -Werror -c $< -o $@

xopt-test: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f xopt-test
