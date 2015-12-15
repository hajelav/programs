CC=gcc -Wall -g
CFLAGS=-I.
DEPS = ../utils.h
OBJ = ../utils.o heap.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

heaps: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o
		rm -f heaps
