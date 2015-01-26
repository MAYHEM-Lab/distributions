CC=gcc
CFLAGS=-g 

LIBS=-lm

all: normal exponential normal.o exponential.o pareto pareto.o

exponential: exponential.c exponential.h
	${CC} ${CFLAGS} -DSTANDALONE -o exponential exponential.c ${LIBS}

normal: normal.c normal.h
	${CC} ${CFLAGS} -DSTANDALONE -o normal normal.c ${LIBS}

pareto: pareto.c pareto.h
	${CC} ${CFLAGS} -DSTANDALONE -o pareto pareto.c ${LIBS}

exponential.o: exponential.c exponential.h
	${CC} ${CFLAGS} -c exponential.c

normal.o: normal.c normal.h
	${CC} ${CFLAGS} -c normal.c

pareto.o: pareto.c pareto.h
	${CC} ${CFLAGS} -c pareto.c

clean:
	rm *.o normal exponential
