#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <sys/time.h>

#define RAND() (drand48())
#define SEED(s) (srand48(s))


double Low;
double High;
int Samples;


#define Usage "uniform -c sample_count -l lower-bound -h upper-bound\n"

#define ARGS "c:h:l:"

#ifdef STANDALONE
int main(int argc, char *argv[])
{
	int c;
	int i;
	struct timeval tm;
	double value;
	double r;

	gettimeofday(&tm,NULL);
	SEED(tm.tv_sec+tm.tv_usec);

	Low = 0;
	High = 1.0;
	Samples = 1;

	while((c = getopt(argc,argv,ARGS)) != EOF)
	{
		switch(c)
		{
			case 'l':
				Low = atoi(optarg);
				break;
			case 'h':
				High = atoi(optarg);
				break;
			case 'c':
				Samples = atoi(optarg);
				break;
			default:
				fprintf(stderr,"unrecognize arg: %c\n",c);
				fprintf(stderr,"usage: %s\n",Usage);
				fflush(stderr);
				exit(1);
		}
	}

	if(Low >= High) {
		fprintf(stderr,"lower bound must  be below upper bound\n");
		fflush(stderr);
		exit(1);
	}

	for(i=0; i < Samples; i++)
	{
		r = RAND();
		value = (High - Low)*r + Low;
		printf("%f\n",value);
	}

	fflush(stdout);
	exit(0);
}


#endif
