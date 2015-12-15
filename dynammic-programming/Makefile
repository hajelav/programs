CC=gcc -Wall -g
CFLAGS=-I.
DEPS = ../utils.h
OBJ = ../utils.o dynamic.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

dynamic: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o
		rm -f dynamic
