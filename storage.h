#ifndef _STORAGE_H_
#define _STORAGE_H_

typdef struct {
     char * word;
     ngram * next;
     int prob;
} suff;

typedef struct {
     char **prefix;
     suff **sufix;
     int k;
     int sc;
} ngram;

ngram * start_stor(int n, char ** pref, char * suf);

void init_next_pref (suff * s, char ** pref, char * suf, int n);

ngram * find_ngram (ngram * start, char ** pref, char * suf, int n);

void app_ngram (ngram * start, char ** pref, char * suf, int n);

int pref_cmp (char ** a, char ** b, int n)

void cleanup (ngram * ng);

#endif
