#include "storage.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ngram * process (FILE ** inputs, int n)
{
  ngram * ng = NULL;
  int i = 0;
  int j = 0;
  int pos = 0;
  char ** item = malloc (n * sizeof (char*));
  for (i = 0; i<n; i++)
    item[i] = malloc (sizeof(char));
  char ** pref = malloc ((n-1) * sizeof (char*));
  for (i = 0; i<n-1; i++)
    pref[i] = malloc (sizeof(char));
  char * word = malloc(sizeof(char));
  char * suf = malloc(sizeof(char));
  int c = 0;
  
  for (i = 0; i < sizeof(inputs)/sizeof(inputs[0]) ; i++)
  {
    while ((c = fgetc(inputs[i])) != EOF)
    {
      if (c == ' ')
      { 
        item[j] = realloc(item[j], strlen(word) * sizeof(char));
        strcpy(pref[j], word);
        j++;
        if (k == n)
        {
          prep(item, pref, suf, n)
          j = 0;
          if (ng == NULL) ng = start_stor(n, pref, suf);
          else app_ngram(ng, pref, suf, n);
        }
        word = realloc(word, sizeof(char));
      }
      else
      {
          word = realloc(word, (strlen(word)+1) * sizeof(char));
          word[strlen(word)-1] = c;
      }
    }
    
  }
  
}

void prep (char ** in, char ** pref, char * suf, int n)
{
     int i;
     for (i = 0; i<n-2;n++)
     {
         pref[i] = realloc(pref[i], strlen(in[i]) * sizeof (char));
         strcpy(pref[i], in[i]);
         in[i] = realloc(in[i], strlen(in[i+1]) * sizeof (char));
         strcpy(in[i], in[i+1]);
     }
     suf = realloc(suf, strlen(in[n-1]) * sizeof (char));
     strcpy(suf, in[n-1]);

}
