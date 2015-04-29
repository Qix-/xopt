HEADERS = xopt.h
OBJECTS = snprintf.o xopt.o

default: libxopt.a
	$(MAKE) -C test

DEFINES += -DHAVE_STDARG_H=1 -DHAVE_STDLIB_H=1
DEFINES += -DHAVE_VASPRINTF=1 -DHAVE_ASPRINTF=1
XFLAGS :=

ifdef DEBUG
	XFLAGS += -g2
endif

%.o: %.c $(HEADERS)
	gcc -ansi -pedantic -Wall -Wextra -Werror ${XFLAGS} $(DEFINES) -c $< -o $@

libxopt.a: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	-rm -f libxopt.a
	$(MAKE) -C test clean
