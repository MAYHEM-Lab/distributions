
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <sys/time.h>

double Mu;
double Sigma;
double Value;


#define PI (3.14159265)

#define Usage "normal-prob -m mu -s sigma -v value\n"

#define ARGS "m:s:v:"

/*
 * http://mathworld.wolfram.com/NormalDistribution.html
 */
double NormalCDF(double x, double mu, double sigma)
{

	return(0.5 * (1.0 + erf((x - mu) / (sqrt(2.0)*sigma))));
}

	


main(int argc, char *argv[])
{
	int c;
	int i;
	int j;

	Mu = 0.0;
	Sigma = 1.0;
	Value = 0;

	while((c = getopt(argc,argv,ARGS)) != EOF)
	{
		switch(c)
		{
			case 'm':
				Mu = atof(optarg);
				break;
			case 's':
				Sigma = atof(optarg);
				break;
			case 'v':
				Value = atof(optarg);
				break;
			default:
				fprintf(stderr,"unrecognize arg: %c\n",c);
				fprintf(stderr,"usage: %s\n",Usage);
				fflush(stderr);
				exit(1);
		}
	}

	printf("%f\n",NormalCDF(Value,Mu,Sigma));


	exit(0);
}


