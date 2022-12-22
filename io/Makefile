CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -O2

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
HEADER=io.h

LIBDIR=../lib
LIB=$(LIBDIR)/libddio.a
LIBINCDIR=../lib/include
LIBINC=$(LIBINCDIR)/$(HEADER)
DYNLIB=$(LIBDIR)/libddio.so

.PHONY: lib clean test all


lib: $(LIB) $(DYNLIB) $(LIBINC)

$(LIB): $(LIBDIR) $(OBJ) $(OBJS)
	ar -crs $(LIB) $(OBJS)

$(DYNLIB): $(LIBDIR) $(OBJ) $(OBJS)
	$(CC) -shared -o $(DYNLIB) $(OBJS)

$(LIBINC): $(LIBINCDIR) $(SRC)/$(HEADER)
	cp $(SRC)/$(HEADER) $(LIBINCDIR)/$(HEADER)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -fPIC -c $< -o $@ $(CFLAGS)

# Rules for making folders

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(LIBINCDIR):
	mkdir $@

# Others

clean: 
	rm -rf $(OBJS)
