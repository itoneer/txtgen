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
     for (i = 1; i<(n-1); i++)
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
     ngram * tmp;
     s->sc = 1;
     int i;
     for (i = 0; i<s->k; i++)
     {
          if (s->sufix[i]->next == NULL)
             continue;

          else if (pref_cmp(s->sufix[i]->next->prefix, pref, n) == 1 &&
                   s->sufix[i]->next->sc == 0)
          {
             tmp = find_ngram (s->sufix[i]->next, pref, n);
             if(tmp != NULL)
             {
                cleanup(s);
                cleanup(tmp);
                return tmp;
             }
          }
          else
          {
             cleanup(s);
             return s->sufix[i]->next;
          }
     }
     cleanup(s);
     return NULL;
}


void app_ngram (ngram * start, char ** pref, char * suf, int n)
{
     ngram * ng = find_ngram (start, pref, n);
     char ** p2 = malloc((n-1) * sizeof(char*));
     int i;
     for (i = 0; i<(n-2); i++)
     {
         p2[i] = malloc(strlen(pref[i+1]) * sizeof(char));
         strcpy(p2[i], pref[i+1]);
     }
     p2[n-2] = malloc(strlen(suf) * sizeof (char));
     strcpy(p2[n-2], suf);

     for (i = 0; i<ng->k; i++)
     {
          if (strcmp(ng->sufix[i]->word, suf) == 0)
          {
             ng->sufix[i]->prob ++;
             return;
          }
     }
     ng->k ++;
     ng->sufix = (suff**) realloc (ng->sufix, ng->k * sizeof (suff*));
     ng->sufix[ng->k-1] = malloc (sizeof (suff));
     ng->sufix[ng->k-1]->word = malloc (strlen(suf) * sizeof (char));
     strcpy (ng->sufix[ng->k-1]->word, suf);
     ng->sufix[ng->k-1]->prob = 1;
     ng->sufix[ng->k-1]->next = find_ngram(start, p2, n);
     if (ng->sufix[ng->k-1]->next == NULL)
         init_next_pref (ng->sufix[ng->k-1], pref, suf, n);
     else
     {
         for (i = 0; i<(n-2); i++)
         {
             pref[i] = malloc(strlen(pref[i+1]) * sizeof(char));
             strcpy(pref[i], pref[i+1]);
         }
         pref[n-2] = malloc(strlen(suf) * sizeof (char));
         strcpy(pref[n-2], suf);

     }

}

int pref_cmp (char ** a, char ** b, int n)
{
    int i;
    for (i = 0; i<n-1; i++)
        if (strcmp(a[i], b[i]) != 0) return 1;

    return 0;
}

void cleanup (ngram * ng)
{
     int i = 0;
     ng->sc = 0;
     if (ng->sufix != NULL)
        while (ng->sufix[i] != NULL)
        {
              if (ng->sufix[i]->next != NULL && ng->sufix[i]->next->sc == 1)
                 cleanup (ng->sufix[i]->next);
              i++;
        }
}
