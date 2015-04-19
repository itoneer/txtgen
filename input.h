#ifndef _INPUT_H_
#define _INPUT_H_
#include "storage.h"

ngram * process (FILE ** inputs, int n);

void prep (char ** in, char ** pref, char * suf, int n);

#endif
