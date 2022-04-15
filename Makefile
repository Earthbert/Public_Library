CFLAG = -Wall -Wextra -std=c99 -g
EXEC = main
CC = gcc

all: main

build: main

main: Linkedlist.o Hashtable.o library_op.o user_op.o main.o
	${CC} ${CFLAG} -o ${EXEC} $?

main.o: main.c
	${CC} ${CFLAG} -c -o $@ $?

Hashtable.o: Hashtable.c
	${CC} ${CFLAG} -c -o $@ $?

Linkedlist.o: LinkedList.c
	${CC} ${CFLAG} -c -o $@ $?

user_op.o: user_op.c
	${CC} ${CFLAG} -c -o $@ $?

library_op.o: library_op.c
	${CC} ${CFLAG} -c -o $@ $?

clean:
	rm -f *.o ${EXEC}