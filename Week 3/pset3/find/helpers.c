/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // implement binary search
    int lower = 0;
    int upper = n;
    // while length of list > 0
    while (upper - lower > 0)
    {
        // look at middle of the list
        int guess = (upper + lower) / 2;
        // if number found, return true
        if (values[guess] == value)
        {
            return true;
        }
        // else if guess higher, search left
        else if (values[guess] > value)
        {
            upper = guess - 1;
        }
        // else if guess lower, search right
        else if (values[guess] < value)
        {
            lower = guess + 1;
        }
    }
        
    // return false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement an O(n^2) sorting algorithm (selection sort)
    // for i from 0 to n - 1
    for (int i = 0; i < n; i++)
    {
        int smallest = values[i];
        int smallestIndex = i;
        // for j from i + 1 to n
        for (int j = i + 1; j <= n; j++)
        {
            // find the smallest value
            if (values[j] < smallest)
            {
                smallest = values[j];
                smallestIndex = j;
            }
        }
        // swap the smallest value with the ith value
        values[smallestIndex] = values[i];
        values[i] = smallest;
    }
    return;
}
