CC=gcc  -Werror -Wall -g
CFLAGS=-I.
DEPS = trie.h
OBJ = longest_compound_word.o trie.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

lcw: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		#rm -f ../../utils.o
		rm -f lcw
