CC=gcc
CFLAGS=-Wall -Wextra -O2

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
HEADER=io.h

LIBDIR=../lib
LIB=$(LIBDIR)/libddio.a
LIBINCDIR=../lib/include
LIBINC=$(LIBINCDIR)/$(HEADER)


.PHONY : lib clean


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
