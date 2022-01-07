#https://cs.colby.edu/maxwell/courses/tutorials/maketutor/ 

IDIR = ./include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR = ./src/obj
LDIR = ./lib

_DEPS = cstring.h part1.h part2.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = day4.o cstring.o part1.o part2.o
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

SRCDIR = ./src

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

day4: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *~ core $(INCDIR)/*~
