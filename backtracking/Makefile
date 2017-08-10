CC=gcc -Wall -Werror -g
CFLAGS=-I../
DEPS = ../utils.h
OBJ = ../utils.o backtracking.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

backtracking: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o
		rm -f backtracking
