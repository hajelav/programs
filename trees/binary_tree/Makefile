CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../../utils.h
OBJ = ../../utils.o binary_tree.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

binary_tree: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../../utils.o
		rm -f binary_tree
