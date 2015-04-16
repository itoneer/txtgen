#include "storage.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

ngram * process (FILE ** inputs, int n)
{
  ngram * ng = NULL;
  int i = 0;
  int j = 0;
  int k = 0;
  int pos = 0;
  char ** item = malloc (n * sizeof (char*));
  for (i = 0; i<n; i++)
    item[i] = calloc (sizeof(char));
  char ** pref = malloc ((n-1) * sizeof (char*));
  for (i = 0; i<n-1; i++)
    pref[i] = calloc (sizeof(char));
  vec * word = vec_init();
  vec * suf = vec_init();
  char c = 0;
  
  for (i = 0; i < sizeof(inputs)/sizeof(inputs[0]) ; i++)
  {
    while (c = fgetc(inputs[i]) != EOF)
    {
      if (c == ' ')
      { 
        copy(word, pref[j]);
        k++;
        if (k == n)
        {
          pref = prefix(word, n);
          suf = sufix(word);
          k = 0;
          if (ng == NULL) ng = start_stor(n, pref, suf);
          else app_ngram(ng, pref, suf, n);
        }
        empty (word);
      }
      else add(word, c);
    }
    
  }
  
  
}
