#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#define RAND() (drand48())


double Lambda;
int Samples;
int Values;


#define Usage "exponential -l lambda -c sample_count\n"

#define ARGS "c:l:V"

double ExpCDF(double x, double lam)
{
	if(x < 0) {
		return(0);
	}

	return(1.0 - exp(-1.0*lam*x));
}

double InvExp(double p, double lam)
{
	return(-1.0 * log(1.0 - p)/lam);
}


#ifdef STANDALONE
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

	Lambda = 1.0;
	while((c = getopt(argc,argv,ARGS)) != EOF)
	{
		switch(c)
		{
			case 'l':
				Lambda = atof(optarg);
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

	for(i=0; i < Samples; i++)
	{
		r = RAND();
		
		value = InvExp(r,Lambda);
		fprintf(stdout,"%f\n",value);
				
	}

	fflush(stdout);


	exit(0);
}


#endif
