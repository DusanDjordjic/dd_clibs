# Compiler 

CC=gcc
TESTFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -g

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
TESTDIR_BIN=$(TESTDIR)/bin
TESTFILES_SRC=$(wildcard $(TESTDIR_SRC)/*.c)
TESTFILES_BIN=$(patsubst $(TESTDIR_SRC)/%.c, $(TESTDIR_BIN)/%, $(TESTFILES_SRC));

.PHONY: libs clean test all

libs: $(LIBDIR) $(LIBINC) $(LIBVEC) $(LIBIO) 

# Execute nested Makefiles

$(LIBVEC):
	$(MAKE) -C vector lib 

$(LIBIO):
	$(MAKE) -C io lib 

# Rules for making folders 

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

# Rules for tests
# Firts clean and than build everything again
# And run all of the tests

test: clean $(LIBDIR) $(LIBINC) $(LIBVEC) $(LIBIO) $(TESTFILES_BIN)
	for test in $(TESTFILES_BIN) do ./$$test ; done

$(TESTDIR_BIN)/%: $(TESTDIR_SRC)/%.c
	$(CC) -o $@ $< $(TESTFLAGS) -L$(LIBDIR) -lddvector -lddio -lcriterion -I$(LIBINC)

# Others

clean:
	rm -rf $(LIBDIR)/*.a $(LIBDIR)/*.so $(LIBINC)/*.h $(TESTDIR_OBJ)/*.o $(TESTDIR_BIN)/*;\
	$(MAKE) -C io clean;\
	$(MAKE) -C vector clean
