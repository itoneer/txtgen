#include "storage.h"
#include <string.h>

ngram * start_stor(int n, char ** pref, char * suf)
{
     ngram * ng = NULL;
     char ** p = pref; 
     ng = malloc (sizeof ngram);
     ng->prefix = malloc (pref.length() * sizeof (char*));
     int i;
     for (i = 0; i<pref.length(); i++)
     {
         ng->prefix[i] = malloc(pref[i].length() * sizeof char);
         strcpy (ng->prefix[i], pref[i]);
     }
     ng->sufix = malloc (sizeof (suff*));
     ng->sufix[0]->word = malloc (suf.length() * sizeof char);
     strcpy(ng->sufix[0]->word, suf);
     init_next_pref(ng->sufix[0], pref, suf)
     ng->sufix[0]->prob = 1;
     ng->k = 1;
}

void init_next_pref (suff * s, char ** pref, char * suf)
{
     int i;
     char ** p = pref;
     s->next = malloc (sizeof ngram);
     s->next->prefix = malloc (pref.length() * sizeof (char*));
     for (i = 1; i<pref.length(); i++)
        strcpy (p[i-1], pref[i]);
     strcpy (p[pref.length()-1], suf);
     for (i = 0; i<pref.length(); i++)
     {
         s->next->prefix[i] = malloc(pref[i].length() * sizeof char);
         strcpy (s->next->prefix[i], p[i]);
     }
}

ngram * find_ngram (ngram * start, char ** pref)
{
     ngram * n = start;
     int i;
     for (i = 0; i< n->k; n++)
     {
          if (n->sufix[i]->next == NULL)
          {
             #ifdef DEBUG 
             printf("ngram %g nie posiada wskaźnika na następny ngram", n->suff[i]->next);
             #endif
             continue;
          }
          else if (n->sufix[i]->next->prefix != pref)
             n = find_ngram (n, pref);
          else if (n->sufix[i]->next->prefix == pref)
             return n->sufix[i]->next;
     }
     return n;
}

void app_ngram (ngram * start, char ** pref, char * suf)
{
     ngram * n = find_ngram (start, pref);
     int i;
     for (i = 0; i<k; i++)
          if (n->sufix[i]->word == suf)
          {
             n->sufix[i]->prob ++;
             return;
          }
     n->k ++;
     n->sufix = realloc (k * sizeof (suff*));
     n->sufix[k-1]->word = malloc (suf.length() * sizeof char);
     strcpy (n->sufix[k-1]->word, suf);
     n->sufix[k-1]->prob = 1;
     init_next_pref (n, pref, suf);
}
