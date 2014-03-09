/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

extern const int MAX;

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    int lower = 0;
    int upper = n - 1;
    int middle = (lower + upper) / 2;
    // implement a binary searching algorithm
    while (lower <= upper)
    {
        if (array[middle] == value)
        {
            return true;
        }
        else if (array[middle] < value)
        {
            lower = middle + 1;
        }
        else if (array[middle] > value)
        {
            upper = middle - 1;
        }
        middle = (lower + upper) / 2;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n) sorting algorithm
    // initialize temporary array
    int temp[65536] = {0};
    for (int i = 0; i < n; i++)
    {
        // increment one of temp[values] for each values in values[]
        temp[values[i]] += 1;
    }
    int index = 0;
    // reinsert values into values[] from small to big
    for (int j = 0; j < MAX; j++)
    {
        while(temp[j] != 0)
        {
            values[index] = j;
            temp[j]--;
            index++;
        }
    }
}
