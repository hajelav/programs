CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../utils.h
OBJ = ../utils.o link_list.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

link_list: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../../utils.o
		rm -f link_list
