#include "output.h"
#include "input.h"
#include "storage.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

char ** generate (ngram * ng, int n, int p, int s)
{

     int random = 0;
     int par = 0;
     int sent = 0;
     int sum = 0;
     int i;
     long int counter = 0;


     srand(time(NULL));
     char ** text;
     char * word;

     pref_append(&text, ng->prefix, n, &counter);
     ngram * handle = ng;


     while (par != p || sent != s)
     {

           random = (int)floor(rand() % sum_prob(handle));
           sum = handle->sufix[0]->prob;
           while (random > sum)
                 sum += handle->sufix[i++]->prob;
           append(&text, handle->sufix[i]->word, &counter);
           if (word[strlen(word)-2] == '.')
           {
              sent++;
              random = (int)floor(rand() % 2);
              if (random == 1)
              {
                 append (&text, "\n", &counter);
                 par++;
              }
           }
           handle = handle->sufix[i]->next;
           i = 0;
     }


}

void output( FILE ** inputs, FILE * output, int n, int p, int s)
{
     int total = 0;
     int i = 0;
     ngram * base = process(inputs, in, total);

     char ** text = generate (base, n, p, s);

     while(text[i] != NULL)
          fprintf (output, "%s ", text[i]);

}

void pref_append(char *** out, char ** pref, int n, long int *c)
{

    int i;
    for (i = 0; i<(n-1); i++)
        append (out, pref[i], c);
    return 0;
}

int sum_prob(ngram * ng)
{
    int i = 0;
    int sum = 0;
    while (ng->sufix[i])
          sum += ng->sufix[i++]->prob;
    return sum;
}

void append (char *** out, char * w, long int *c)
{
     *out = realloc (*out, (c+1)* sizeof(char*));
     *out[c] = malloc (strlen(w) * sizeof(char));
     strcpy(*out[c], w);
}
