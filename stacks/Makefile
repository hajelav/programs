CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../utils.h stacks.h
OBJ = ../utils.o stack.o stack_main.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

stack: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o stack.o stack_main.o
		rm -f stack
