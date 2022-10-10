CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -O2

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
HEADER=vector.h

LIBDIR=../lib
LIB=$(LIBDIR)/libddvector.a
LIBINCDIR=../lib/include
LIBINC=$(LIBINCDIR)/$(HEADER)


.PHONY: lib clean test all


lib: $(LIB) $(LIBINC)

$(LIB): $(LIBDIR) $(OBJ) $(OBJS)
	ar -crs $(LIB) $(OBJS)

$(LIBINC): $(LIBINCDIR) $(SRC)/$(HEADER)
	cp $(SRC)/$(HEADER) $(LIBINCDIR)/$(HEADER)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(LIBINCDIR):
	mkdir $@

clean: 
	rm -rf $(OBJS) 
