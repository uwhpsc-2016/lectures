# compiler settings
CC=mpicc

# target
LIBTARGET=libhello.so
PROGTARGET=

# sources
CFLAGS=-c -fPIC
LIBSOURCES=hello.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)
INCLUDE=.
LIBDIR=.

.PHONY: all lib clean

default: $(LIBTARGET)

#
# compile commands for targets
#
$(LIBTARGET): $(LIBOBJECTS)
	$(CC) -shared -lm -I$(INCLUDE) $< -o $@

#
# generics
#
%.o : %.c
	$(CC) -I$(INCLUDE) $(CFLAGS) $< -o $@

#
# cleaning
#
clean:
	@rm -fr *.o

clobber: clean
	@rm -fr $(PROGTARGET) $(LIBTARGET)
