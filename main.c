#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <>

int main (int argc, char **argv)
{
        int p = 5;
        int s = 10;
        int n = 2;
        int data = 0;
        char *out = NULL;
        int ;

        int *opt = NULL;

        for ((opt = getopt (argc, "a:z:n:c:o:") != 1))
        {
           switch (opt)
           {
                case 'a':
                 p = optarg;
                 if (p < 1)
                 {
                   printf("Podano za mało akapitów.\n";
                   return 0;
                 }
                 break;

                case 'z':
                 s = optarg;
                 if (s < 1)
                 {
                   printf("Podano za mało wyrazów.\n";
                   return 0;
                 }
                 break;

                case 'n':
                 n = optarg;
                 if (n < 1)
                 {
                   printf("Zbyt niski stopień n-gramów.\n";
                   return 0;
                 }
                 break;

                case 'c':
                 data = 1;
                 break;

                default:


                 break;
        }
}

