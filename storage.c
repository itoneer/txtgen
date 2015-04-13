#include "storage.h"
#include <>

ngram * start_stor(int n, char ** pref, char * suf)
{
     ngram * ng = NULL;
     ng = malloc (sizeof ngram);
     ng->prefix = malloc (pref.length() * sizeof char);
     int i;
     for (i = 0; i<pref.length(); i++)
         ng->prefix[i] = malloc(pref[i].length() * sizeof char);
     strcpy (ng->prefix, pref);
     ng->sufix = malloc (sizeof suff);
     ng->sufix->word = malloc (suf.length() * sizeof char);
     strcpy(ng->sufix->word, suf);
     ng->sufix->next = malloc (sizeof ngram);
     ng->sufix->prob = 1;
     ng->k = 1;
}
