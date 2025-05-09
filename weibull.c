#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define RAND() (drand48())
#define SEED(x) (srand48(x))




/*
 * parameters: a, b
 * CDF: 1 - exp((x/a))^b
 */


double InvertedWeibullCDF(double y, double a, double b)
{
	double x = a * pow(-1.0*log(1.0-y),1.0/b);
	return(x);
}

#ifdef STANDALONE

#define Usage "weibull -a a -b b [-c sample_count | -q quantile] [-V]\n"
#define ARGS "a:b:c:Vq:"
double a;
double b;
int Samples;
double Low;
double High;
int Values;
int CDF;
double Quantile;

int main(int argc, char *argv[])
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
	struct timeval tm;

	gettimeofday(&tm,NULL);
	SEED(tm.tv_sec+tm.tv_usec);

	a = 1.0;
	b = 1.0;
	Samples = -1;
	Values = 0;
	Quantile = -1;

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
			case 'q':
				Quantile = atof(optarg);
				break;
			default:
				fprintf(stderr,"unrecognize arg: %c\n",c);
				fprintf(stderr,"usage: %s\n",Usage);
				fflush(stderr);
				exit(1);
		}
	}

	if((Samples < 1) && (Quantile < 0))
	{
		fprintf(stderr,"usage: %s\n",Usage);
		fflush(stderr);
		exit(1);
	}

	if((Samples > 0) && (Quantile > 0) && (Quantile < 1)){
		fprintf(stderr,
		"specify either sample count or quantile of interest\n");
		exit(1);
	}

	/*
 	 * only generates a random sample at this point
 	 */
	if(Quantile > 0) {
		printf("%f\n",InvertedWeibullCDF(Quantile,a,b));
	} else {
		for(i=0; i < Samples; i++ ) {
			printf("%f\n",InvertedWeibullCDF(RAND(),a,b));
		}
	}


	exit(0);
}


#endif
