CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../utils.h
OBJ = ../utils.o strings.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

strings: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o
		rm -f strings
