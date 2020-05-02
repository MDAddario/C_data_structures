SRCS = define.c hash_pair.c linked_list.c array_list.c hash_table.c
OBJS = ${SRCS:.c=.o}
HDS = ${SRCS:.c=.h}

all: tests

tests: tests.c ${OBJS} ${HDS}
	gcc tests.c ${OBJS} -o tests -g

.c.o: ${SRCS} ${HDS}
	gcc -c $< -lm

clean:
	rm -f tests ${OBJS}

run:
	clear
	./tests
