#https://cs.colby.edu/maxwell/courses/tutorials/maketutor/ 

IDIR = ./include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR = ./src/obj
LDIR = ./lib

_DEPS = node.h list.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = main.o node.o list.o
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

SRCDIR = ./src

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *~ core $(INCDIR)/*~
