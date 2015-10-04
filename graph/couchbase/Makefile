CC=gcc -Wall
CFLAGS=-I.
DEPS = graph_util.h
OBJ = graph_util.o graphs.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

graphs: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o
		rm -f graphs
