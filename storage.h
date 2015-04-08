#include <>

typdef struct {
     char * word;
     ngram * next;
     int prob;
} suff;

typedef struct {
     char **prefix;
     suff * sufix;
     int k;
} ngram;

ngram * start_stor();

ngram * app_ngram (ngram * start);

ngram * find_ngram (ngram * start, char * a);
}
