CC=gcc -Wall -Werror -g
CFLAGS=-I.
DEPS = ../../utils.h
OBJ = ../../utils.o ip_range.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

ip_range: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
		rm -f *.o
		rm -f ../../utils.o
		rm -f ip_range
