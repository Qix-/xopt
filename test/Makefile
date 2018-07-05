.PHONY: all clean

TESTS := simple-test macro-test required-test

all: $(TESTS)

%: %.c ../libxopt.a
	$(CC) -ansi -pedantic-errors -Wall -Wextra -Werror $(CFLAGS) -I.. -L.. -o $@ $< -lxopt

clean:
	rm -f $(TESTS) *.o
