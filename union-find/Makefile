CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../utils.h uf.h
OBJ = ../utils.o uf.o uf_main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

uf: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
	rm -f *.o
	rm -f ../utils.o uf.o uf_main.o
	rm -f uf
