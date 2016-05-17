# compiler settings
CC=mpicc

# target
LIBTARGET=libshift.so
PROGTARGET=a.out

# sources
CFLAGS=-c -fPIC
LIBSOURCES=shift.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)
PROGSOURCES=main.c
PROGOBJECTS=$(PROGSOURCES:.c=.o)
INCLUDE=.
LIBDIR=.

.PHONY: all lib clean

default: prog

#
# compile commands for targets
#
prog: $(PROGOBJECTS) $(LIBTARGET)
	$(CC) -lshift -lm -L$(LIBDIR) -I$(INCLUDE) $(PROGOBJECTS) -o $(PROGTARGET)

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
