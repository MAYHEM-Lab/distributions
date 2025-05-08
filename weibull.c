#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define RAND() (drand48())

extern void srand48();
extern double drand48();


double a;
double b;
int Samples;
double Low;
double High;
int Values;
int CDF;

/*
 * parameters: a, b
 * CDF: 1 - exp((x/a))^b
 */

extern double pow();
extern double log();
extern int getopt();
extern char *optarg;


#define Usage "weibull -a a -b b -c sample_count [-V]\n"

#define ARGS "a:b:c:V"

double InvertedWeibullCDF(double y, double a, double b)
{
	double x = a * pow(-1.0*log(1.0-y),b);
	return(x);
}

#ifdef STANDALONE

int
main(int argc, char *argv[])
{
	int c;
	int i;
	int j;
	double r;
	double y;
	double value;
	double acc;
	double incr;
	double curr;

	a = 1.0;
	b = 1.0;
	Samples = -1;
	Values = 0;

	while((c = getopt(argc,argv,ARGS)) != EOF)
	{
		switch(c)
		{
			case 'a':
				a = atof(optarg);
				break;
			case 'b':
				b = atof(optarg);
				break;
			case 'c':
				Samples = atoi(optarg);
				break;
			case 'V':
				Values = 1;
				break;
			default:
				fprintf(stderr,"unrecognize arg: %c\n",c);
				fprintf(stderr,"usage: %s\n",Usage);
				fflush(stderr);
				exit(1);
		}
	}

	if(Samples < 1)
	{
		fprintf(stderr,"usage: %s\n",Usage);
		fflush(stderr);
		exit(1);
	}

	/*
 	 * only generates a random sample at this point
 	 */
	for(i=0; i < Samples; i++ ) {
		printf("%f\n",InvertedWeibullCDF(RAND(),a,b));
	}


	exit(0);
}


#endif
