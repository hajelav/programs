CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../utils.h graph.h
OBJ = ../utils.o graph.o graph_main.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

graph: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../utils.o graph.o graph_main.o
		rm -f graph 
