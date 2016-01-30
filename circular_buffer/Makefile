CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../utils.h
OBJ = ../utils.o circular_buffer.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

cbuffer: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o
		rm -f cbuffer
