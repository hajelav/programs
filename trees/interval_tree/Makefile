CC=gcc -Wall -g
CFLAGS=-I.
DEPS = ../../utils.h
OBJ = ../../utils.o interval_tree.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

interval_tree: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../../utils.o
		rm -f interval_tree
