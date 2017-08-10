CC=gcc -Wall -g
CFLAGS=-I.
DEPS = ../../utils.h trie.h
OBJ = ../../utils.o trie.o trie_main.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

trie: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../../utils.o trie.o trie_main.o
		rm -f trie
