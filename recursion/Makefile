CC=gcc
CFLAGS=-I.
DEPS = binary_tree.h
OBJ = binary_tree.o waysToReachNstairs.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

waysToReachNstairs: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o
