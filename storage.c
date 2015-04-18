#include "storage.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ngram * start_stor(int n, char ** pref, char * suf)
{
     ngram * ng = malloc (sizeof (ngram));
     if (ng == NULL) goto erall;
     ng->prefix = malloc ((n-1) * sizeof (char*));
     if (ng->prefix == NULL) goto erall;
     int i;
     for (i = 0; i<n-1; i++)
     {
         ng->prefix[i] = malloc(strlen(pref[i]) * sizeof (char));
         if (ng->prefix[i] == NULL) goto erall;
         strcpy (ng->prefix[i], pref[i]);
     }
     ng->sufix = malloc (sizeof (suff*));
     if (ng->sufix == NULL) goto erall;
     ng->sufix[0] = malloc (sizeof (suff));
     if (ng->sufix[0] == NULL) goto erall;
     ng->sufix[0]->word = malloc (strlen(suf) * sizeof char);
     if (ng->sufix[0]->word == NULL) goto erall;
     strcpy(ng->sufix[0]->word, suf);
     init_next_pref(ng->sufix[0], pref, suf, n)
     ng->sufix[0]->prob = 1;
     ng->k = 1;
     return ng;
     
     erall:
     printf("Błąd alokacji pamięci przy tworzeniu bazy danych");
     return NULL;
}

void init_next_pref (suff * s, char ** pref, char * suf, int n)
{
     int i;
     char ** p = pref;
     s->next = malloc (sizeof (ngram));
     s->next->prefix = malloc ((n-1) * sizeof (char*));
     for (i = 1; i<n-1; i++)
        strcpy (p[i-1], pref[i]);
     strcpy (p[n-2], suf);
     for (i = 0; i<n-1; i++)
     {
         s->next->prefix[i] = malloc(strlen(pref[i]) * sizeof (char));
         strcpy (s->next->prefix[i], p[i]);
     }
}

ngram * find_ngram (ngram * start, char ** pref, int n)
{
     ngram * s = start;
     int i;
     for (i = 0; i< s->k; n++)
     {
          if (s->sufix[i]->next == NULL)
          {
             #ifdef DEBUG 
             printf("ngram %g nie posiada wskaźnika na dany ngram", s->suff[i]->next);
             #endif
             continue;
          }
          else if (pref_cmp(s->sufix[i]->next->prefix, pref, n) == 1)
             s = find_ngram (n, pref);
          else
             return s->sufix[i]->next;
     }
     return s;
}

void app_ngram (ngram * start, char ** pref, char * suf, int n)
{
     ngram * ng = find_ngram (start, pref, n);
     int i;
     for (i = 0; i<ng->k; i++)
          if (ng->sufix[i]->word == suf)
          {
             ng->sufix[i]->prob ++;
             return;
          }
     ng->k ++;
     ng->sufix = (suff**) realloc (ng->sufix, ng->k * sizeof (suff*));
     ng->sufix[ng->k-1] = malloc (sizeof (suff));
     ng->sufix[ng->k-1]->word = malloc (strlen(suf) * sizeof (char));
     strcpy (n->sufix[ng->k-1]->word, suf);
     n->sufix[ng->k-1]->prob = 1;
     init_next_pref (ng, pref, suf, n);
}

int pref_cmp (char ** a, char ** b, int n)
{
    int i;
    for (i = 0; i<n-1; i++)
        if (strcmp(a[i], b[i]) != 0) return 1;

    return 0;
}
