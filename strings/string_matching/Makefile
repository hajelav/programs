CC=gcc -Wall -g
CFLAGS=-I.
DEPS = ../../utils.h
OBJ = ../../utils.o string_matching.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

string_matching: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../../utils.o
		rm -f string_matching
