#include "storage.h"
#include <>

ngram * start_stor(int n, char ** pref, char * suf)
{
     ngram * ng = NULL;
     ng = malloc (sizeof ngram);
     strcpy (ng->prefix, pref);
     ng->sufix = malloc (sizeof suff);
     strcpy(ng->sufix->word, suf);
     ng->sufix->next = malloc (sizeof ngram);
     ng->k = 1;
}
