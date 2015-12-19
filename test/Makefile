OBJECTS = simple-test.o

default: xopt-test

XFLAGS :=

ifdef DEBUG
	XFLAGS += -g2
endif

%.o: %.c
	$(CC) -ansi -pedantic -Wall -Wextra -Werror $(XFLAGS) -I.. -c $< -o $@

xopt-test: $(OBJECTS) ../libxopt.a
	$(CC) -L.. -o $@ $(OBJECTS) -lxopt

clean:
	-rm -f $(OBJECTS)
	-rm -f xopt-test
