#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    int cents;
    int count = 0;

    do
    {
    printf("O hai! How much change is owed?\n");
    dollars = GetFloat();
    cents = round(dollars*100);
    }
    while (dollars < 0);

    while (cents / 25 > 0)
    {
        count++;
        cents -= 25;
    }
    while (cents / 10 > 0)
    {
        count++;
        cents -= 10;
    }
    while (cents / 5 > 0)
    {
        count++;
        cents -= 5;
    }
    while (cents / 1 > 0)
    {
        count++;
        cents -= 1;
    }

    printf("%i\n", count);
}
