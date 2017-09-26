# Makefile for building answer files

# You DO NOT need to modify this file, unless you ADD new files
# or libraries to your code.
# DO NOT change the target names. The grader assumes that the executable
# name is `answer`.

COMPILER=gcc
OPTIONS=-Wall -std=c99
INCLUDES=-I. #specify include directory here
LIBS=-llytmus_json

SRC=answer.c test_answer.c

OBJS=$(SRC:.c=.o)

all: %.o answer
.PHONY: all

%.o : ${SRC}
	${COMPILER} ${OPTIONS} ${INCLUDES} -c ${SRC}

answer: ${OBJS}
	${COMPILER} -o $@  ${OBJS} ${LIBS}

.PHONY: clean

clean:
	rm -f answer ${OBJS}

Makefile: ;
