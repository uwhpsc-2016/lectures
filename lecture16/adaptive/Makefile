# compiler settings
CC=gcc-5
CFLAGS=-Wall -fPIC -fopenmp -lm
LDFLAGS=--shared -fopenmp -lm

# directories
BIN=bin
SRC=src
LIB=lib
INCLUDE=include
TEST=test

# target
LIBTARGET=$(LIB)/libadaptive.so

# sources
LIBSOURCES=$(SRC)/adaptive_serial.c
LIBOBJECTS=$(LIBSOURCES:.c=.o)
TESTSOURCES=$(TEST)/test_serial.c $(TEST)/test_parallel.c
TESTPROGRAMS=$(TESTSOURCES:.c=.out)

.PHONY: all lib test clean clobber

default: all

all: lib test

lib: $(LIBTARGET)

test: lib $(TESTPROGRAMS)

# linking the library
$(LIBTARGET): $(LIBOBJECTS)
	$(CC) $(LDFLAGS) $(LIBOBJECTS) -o $(LIBTARGET)

# compiling library sources
%.o : %.c
	$(CC) -c -I$(INCLUDE) $(CFLAGS) $< -o $@

#	compiling test scripts
%.out : %.c
	$(CC) -I$(INCLUDE) -L$(LIB) -ladaptive $(CFLAGS) $< -o $@

clean:
	@rm -fr $(SRC)/*.o

clobber: clean
	@rm -fd $(LIB)/*.so $(SRC)/*.out
