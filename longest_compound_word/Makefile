CC=gcc  -Werror -Wall -g
CFLAGS=-I.
DEPS = trie.h utils.h
OBJ = longest_compound_word.o utils.o trie.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

lcw: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		#rm -f ../../utils.o
		rm -f lcw
