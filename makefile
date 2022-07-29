CC=gcc
CFLAGS=-g 
EPATH=../euca-cutils

LIBS=-lm ${EPATH}/libutils.a

all: normal exponential normal.o exponential.o pareto pareto.o hypexp hypexp.o normal-prob

exponential: exponential.c exponential.h
	${CC} ${CFLAGS} -DSTANDALONE -o exponential exponential.c ${LIBS}

normal: normal.c normal.h
	${CC} ${CFLAGS} -DSTANDALONE -o normal normal.c ${LIBS}

normal-prob: normal-prob.c normal.h
	${CC} ${CFLAGS} -o normal-prob normal-prob.c ${LIBS}

pareto: pareto.c pareto.h
	${CC} ${CFLAGS} -DSTANDALONE -o pareto pareto.c ${LIBS}

exponential.o: exponential.c exponential.h
	${CC} ${CFLAGS} -c exponential.c

hypexp: hypexp.c hypexp.h
	${CC} ${CFLAGS} -I${EPATH} -DSTANDALONE -o hypexp hypexp.c ${LIBS}

normal.o: normal.c normal.h
	${CC} ${CFLAGS} -c normal.c

pareto.o: pareto.c pareto.h
	${CC} ${CFLAGS} -c pareto.c

hypexp.o: hypexp.c hypexp.h ${EPATH}/textlist.h
	${CC} ${CFLAGS} -I${EPATH} -c hypexp.c

clean:
	rm *.o normal exponential
