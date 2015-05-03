#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include "textlist.h"
#include "hypexp.h"

double *Params;

#define SEED(s) (srand48((s)))
#define RAND() (drand48())

int GetParamLine(TXL *tl, double *params, int pcnt)
{
	char *keyword;
	char *value;

	if(pcnt < 0) {
		return(-1);
	}

	if(pcnt > PARAM_CNT) {
		return(-1);
	}

	if(tl->list->first == NULL) {
		return(-1);
	}
	keyword = (char *)tl->list->first->value.v;
	
	if(tl->list->first->next == NULL) {
		return(-1);
	}
	value = (char *)tl->list->first->next->value.v;

	if(strcmp(keyword,"ep_1") == 0) {
		params[ia_ep_1] = atof(value);
		return(1);
	} else if(strcmp(keyword,"ep_2") == 0) {
		params[ia_ep_2] = atof(value);
		return(1);
	} else if(strcmp(keyword,"lambda_1") == 0) {
		params[ia_lambda_1] = atof(value);
		return(1);
	} else if(strcmp(keyword,"lambda_2") == 0) {
		params[ia_lambda_2] = atof(value);
		return(1);
	} else if(strcmp(keyword,"lambda_3") == 0) {
		params[ia_lambda_3] = atof(value);
		return(1);
	} else if(strcmp(keyword,"sample_size") == 0) {
		params[sample_size] = atof(value);
		return(1);
	}

	return(-1);
}

double *ParseConfigFile(char *fname)
{
	FILE *fd;
	double *params;
	char *line;
	TXL *tl;
	char c;
	int line_no;
	char *s;
	int i;
	int err;

	fd = fopen(fname,"r");
	if(fd == NULL) {
		fprintf(stderr,"couldn't open config file %s\n",fname);
		return(NULL);
	}

	params = (double *)malloc(PARAM_CNT*sizeof(double));
	if(params == NULL) {
		fprintf(stderr,"no space for param list\n");
		fclose(fd);
		return(NULL);
	}

	for(i=0; i < PARAM_CNT; i++)
	{
		params[i] = 0;
	}

	line = (char *)malloc(LINE_LENGTH);
	if(line == NULL) {
		fprintf(stderr,"no space for input line\n");
		free(params);
		fclose(fd);
		return(NULL);
	}

	memset(line,0,LINE_LENGTH);


	line_no = 1;
	while(fgets(line,LINE_LENGTH,fd) != NULL)
	{
		tl = InitTXL();
		if(tl == NULL) {
			fprintf(stderr,"can't get txl\n");
			free(params);
			free(line);
			fclose(fd);
			return(NULL);
		}
		tl = ParseLine(line,CONFIG_SEPARATORS);
		if(tl == NULL) {
			fprintf(stderr,"bad config line at line number %d\n",
					line_no);
			continue;
		}

		s = (char *)tl->list->first->value.v;
		if(s == NULL) {
			fprintf(stderr,"bad config string at line number %d\n",
					line_no);
			continue;
		}
		c = s[0];
		if((c == '#') || (c == '\n')) {
			continue;
		}

		err = GetParamLine(tl,params,PARAM_CNT);
		if(err < 0) {
			fprintf(stderr,"bad param at line number %d\n",line_no);
			/* PrintTXL(tl);*/
		}
		DestroyTXL(tl);
		line_no++;
	}

#if 0
	for(i=0; i < PARAM_CNT; i++)
	{
		printf("params[i]: %f\n",params[i]);
	}
#endif

	free(line);
	return(params);
}



double Generate3PSample(double *params)
{
    
	double x;
	double lambda1=params[ia_lambda_1];
	double lambda2=params[ia_lambda_2];
	double lambda3=params[ia_lambda_3];
	double pr1=params[ia_ep_1];
	double pr2=params[ia_ep_2];
	double hypprob;
	double r1;
	double r2;

	/*
	 * possible if this is an empty model
	 */
	if((lambda1 == 0.0) && (lambda2 == 0.0) && (lambda3 == 0.0)) {
		return(-1);
	}
 
	if (lambda1 < 0.0)
	{
	    	fprintf(stderr,"specify valid lambda1 value\n");
		return(-1);
	}
	if (lambda2 < 0.0)
	{
	    	fprintf(stderr,"specify valid lambda2 value\n");
		return(-1);
	}
again:
	if (pr1 < 0.0 || pr1 > 1.0 || pr2 < 0.0 || pr2 > 1.0 || pr1 + pr2 > 1.0)
	{
	    	fprintf(stderr,"specify valid probabilities\n");
		return(-1);
	}
	r1 = RAND();
	r2 = RAND();
	if (r1 < pr1)
	{
	    x = -1.0 * log(1-r2) / lambda1;
	}
	else if (r1 < (pr1 + pr2))
	{
	    x = -1.0 * log(1-r2) / lambda2;
	}
	else
	{
	    x = -1.0 * log(1-r2) / lambda3;
	}
	return(x);
}

#ifdef STANDALONE

char ParamFile[4096];
int Count;
unsigned int Seed;

#define ARGS "f:C:S:"
char *Usage = "hypexp -f paramfile\n\
\t-C count\n\
\t-S seed (optional)\n";

int main(int argc, char **argv) 
{
	int c;
	int i;
	double value;
	struct timeval tm;
	double *params;
	int has_seed;

	has_seed = 0;

	while((c = getopt(argc,argv,ARGS)) != EOF) {
		switch(c) {
			case 'f':
				strncpy(ParamFile,optarg,sizeof(ParamFile));
				break;
			case 'C':
				Count = atoi(optarg);
				break;
			case 'S':
				Seed = atoi(optarg);
			  	has_seed = 1;
				break;
			default:
				fprintf(stderr,"bad param %c\n",(char)c);
				fprintf(stderr,"%s",Usage);
				exit(1);
		}
	}

	if(ParamFile[0] == 0) {
		fprintf(stderr,"must specify paramfile name\n");
		fprintf(stderr,"%s",Usage);
		exit(1);
	}

	if(Count == 0) {
		fprintf(stderr,"must specify sample count\n");
		fprintf(stderr,"%s",Usage);
		exit(1);
	}

	if(has_seed == 1) {
		SEED(Seed);
	} else {
		gettimeofday(&tm,NULL);
		SEED(tm.tv_usec + tm.tv_sec);
	}

	params = ParseConfigFile(ParamFile);
	if(params == NULL) {
		fprintf(stderr,"error parsing paramfile\n");
		exit(1);
	}

	for(i=0; i < Count; i++) {
		value = Generate3PSample(params);
		printf("%f\n",value);
	}
	free(params);
	exit(0); 

}

#endif


