# Compiler 

CC=gcc
TESTFLAGS=-Wall -Wextra -g

# Libraries

LIBDIR=lib
LIBINC=lib/include

LIBVEC=$(LIBDIR)/libddvector.a
LIBVEC_H=$(LIBINC)/vector.h

LIBIO=$(LIBDIR)/libddio.a
LIBIO_H=$(LIBINC)/io.h

# Tests

TESTDIR=tests
TESTDIR_SRC=$(TESTDIR)/src
TESTDIR_OBJ=$(TESTDIR)/obj
TESTDIR_BIN=$(TESTDIR)/bin

TESTFILES_SRC=$(wildcard $(TESTDIR_SRC)/*.c)
TESTFILES_OBJ=$(patsubst $(TESTDIR_SRC)/%.c, $(TESTDIR_OBJ)/%.o, $(TESTFILES_SRC)) 

TESTBIN=$(TESTDIR_BIN)/tests

.PHONY: libs clean test all

libs: $(LIBDIR) $(LIBINC) $(LIBVEC) $(LIBIO) 

$(LIBVEC):
	$(MAKE) -C vector lib 

$(LIBIO):
	$(MAKE) -C io lib 

$(LIBDIR):
	mkdir $@

$(LIBINC):
	mkdir $@

$(TESTDIR):
	mkdir $@

$(TESTDIR_OBJ):
	mkdir $@

$(TESTDIR_BIN):
	mkdir $@

test: clean $(LIBDIR) $(LIBINC) $(LIBVEC) $(LIBIO) $(TESTBIN)
	./$(TESTBIN)

$(TESTBIN):  $(TESTFILES_OBJ) $(TESTDIR_BIN)
	$(CC) -o $@ $< $(TESTFLAGS) -L$(LIBDIR) -lddvector -lddio -I$(LIBINC)

$(TESTDIR_OBJ)/%.o:  $(TESTDIR_SRC)/%.c $(TESTDIR_OBJ)
	$(CC) -c $< -o $@ $(TESTFLAGS)

clean:
	rm -rf $(LIBDIR)/*.a $(LIBINC)/*.h $(TESTDIR_OBJ)/*.o $(TESTDIR_BIN)/*;\
	$(MAKE) -C io clean;\
	$(MAKE) -C vector clean
