CC=gcc -Wall -g
CFLAGS=-I.
DEPS = ../utils.h
OBJ = ../utils.o misc.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

misc: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o
		rm -f misc
