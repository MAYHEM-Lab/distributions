CC=gcc
CFLAGS=-g 

LIBS=-lm

all: normal exponential normal.o exponential.o

exponential: exponential.c exponential.h
	${CC} ${CFLAGS} -DSTANDALONE -o exponential exponential.c ${LIBS}

normal: normal.c normal.h
	${CC} ${CFLAGS} -DSTANDALONE -o normal normal.c ${LIBS}

exponential.o: exponential.c exponential.h
	${CC} ${CFLAGS} -c exponential.c

normal.o: normal.c normal.h
	${CC} ${CFLAGS} -c normal.c

clean:
	rm *.o normal exponential
