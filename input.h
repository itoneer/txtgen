#ifndef _INPUT_H_
#define _INPUT_H_
#include "storage.h"

char ** prefix (FILE * in, int n, int pos);

char * sufix (FILE * in, int n, int pos);

ngram * process (FILE ** inputs, int n);
#endif
