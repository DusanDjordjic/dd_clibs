CC=gcc
CFLAGS=-Wall -Wextra -O2

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
HEADER=vector.h

VECTOR_STEP=-DVECTOR_STEP=16

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
	$(CC) -c $< -o $@ $(CFLAGS) $(VECTOR_STEP)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(VECTOR_STEP)

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(LIBINCDIR):
	mkdir $@

clean: 
	rm -rf $(OBJS) 
