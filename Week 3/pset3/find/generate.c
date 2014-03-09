/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // return usage message if user does not input any n or [s]
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convert n into integer
    int n = atoi(argv[1]);

    // if [s] is inputted, convert [s] into integer, and use as seed. Otherwise, seed is null.
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // generate a pseudorandom number for n lines
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // return 0 if no error occurs
    return 0;
}
