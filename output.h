#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include "storage.h"

char ** generate (ngram * ng, int n, int p, int s);

void dbase_out (FILE * database, FILE ** inputs, int n, int p, int s);

void output (FILE ** inputs, int n, int p, int s);

void pref_append(char *** out, char ** pref, int n, long int *c);

int sum_prob(ngram * ng);

void append (char *** out, char * w, long int *c);

#endif
