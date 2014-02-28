/*
 * caesar.c
 * by Shaun Ling
 *
 * Encipher a plaintext into a cryptic message uing caesar cipher,
 * shifting each alphabet in the plaintext by a key in the alphabetical order.
 *
 * Usage: ./caesar key
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    int k;
    string p;

    // check if user inputs 2 command line arguments
    if (argc != 2)
    {
        printf("Usage: /home/cs50/pset2/caesar <key>\n");
        return 1;
    }

    // store user key
    k = atoi(argv[1]);

    // get user plaintext
    p = GetString();

    // loop over each character in the plaintext
    for (int i = 0, m = strlen(p); i < m; i++)
    {
        if (isalpha(p[i]))
        {
            if (isupper(p[i]))
            {
                // turn alphabet from ascii to alphabetical index 0 to 26, then execute caesar cipher
                p[i] = (p[i] - 'A' + k) % 26;
                // turn alpabet from alphabetical index back to ascii
                p[i] = p[i] + 'A';
            }
            else
            {
                // turn alphabet from ascii to alphabetical index 0 to 26, then execute caesar cipher
                p[i] = (p[i] - 'a' + k) % 26;
                // turn alpabet from alphabetical index back to ascii
                p[i] = p[i] + 'a';
            }
        }
    }

    // print enciphered plaintext
    for (int i = 0, m = strlen(p); i < m; i++)
    {
        printf("%c", p[i]);
    }
    printf("\n");
}
