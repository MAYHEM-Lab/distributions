
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define RAND() (drand48())


double a;
double b;
int Samples;
double Low;
double High;
int Values;
int CDF;

/*
 * parameters: lambda
 * PDF: lambda^k * exp(-lambda) / k!
 * CDF: exp(-lambda) * sum(lambda^j/j!) j=0..k
 * mean: lambda
 * var: lambda
 */


#define Usage "poisson -l lambda -c sample_count [-V]\n"

#define ARGS "c:l:V"


int InvertedPoissonCDF(double lambda) {
  int n = 0; //counter of iteration
  double limit; 
  double x;  //pseudo random number

  limit = exp(-lambda);
//  x = rand() / INT_MAX; 
  x = drand48();
  while (x > limit) {
    n++;
//    x *= rand() / INT_MAX;
    x *= drand48();
  }
  return n;
}

double Poisson(unsigned int k, double lambda)
{
  double p = exp(-lambda);
  double f = 1;
  for ( int i=0 ; i<k ; i++ ) f *= lambda/(i+1);     
  return p*f;
}

#ifdef STANDALONE

int
main(int argc, char *argv[])
{
	int c;
	double y;
	double lambda;
	int i;

	Samples = -1;
	/*
 	 * define over x >= b
	 */
	Values = 0;
	CDF = 0;

	while((c = getopt(argc,argv,ARGS)) != EOF)
	{
		switch(c)
		{
			case 'l':
				lambda = atof(optarg);
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

	if(Values != 0)
	{
		for(i=0; i < Samples; i++)
		{
			y = InvertedPoissonCDF(lambda);

			fprintf(stdout,"%d\n", (int)y);
		}
					
	}
	else {
		fprintf(stderr,"only generates samples (using -V flag) for now\n");
	}


	exit(0);
}


#endif
