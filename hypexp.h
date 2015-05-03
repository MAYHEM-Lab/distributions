#ifndef HYPEXPMODES_H
#define HYPEXPMODES_H

#define ia_ep_1 0
#define ia_ep_2 1
#define ia_lambda_1 2
#define ia_lambda_2 3
#define ia_lambda_3 4
#define sample_size 5

#define PARAM_CNT 6

#define LINE_LENGTH (4096)
#define CONFIG_SEPARATORS " \t"


double *ParseConfigFile(char *fname);

int GenerateMarkovSample(void *mdata);

#endif

