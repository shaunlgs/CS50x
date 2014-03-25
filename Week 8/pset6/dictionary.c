/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h" 

// number of words loaded from dictionary
extern int wordCount;

// pointer to root of trie
extern node* root; 

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int index = 0;
    int nodeIndex;
    struct node* cursor = root;
    // for each letter in input word
    while (word[index] != '\0')
    {
        // if letter is alphabet, set nodeIndex
        if (isalpha(word[index]))
        {   
            // if letter is uppercase
            if(isupper(word[index]))
            {
                nodeIndex = word[index] - 'A';
            }
            // if letter is lowercase
            else
            {
                nodeIndex = word[index] - 'a';
            }
        }
        // if letter is apostrophe, set nodeIndex
        else
        {
            nodeIndex = 26;
        }
        // go to corresponding element in children 
        // if NULL, word is misspelled
        if (cursor->node[nodeIndex] == NULL)
        {
            return false;
        }
        // if not NULL
        else
        {
            // move to next letter
            cursor = cursor->node[nodeIndex];
        }  
        index++;
    }
    // once at end of input word
    // check if isWord is true
    if (cursor->isWord == true)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file
    FILE* fp = fopen(dictionary, "r");
    
    char word[LENGTH + 1];
    int index = 0;
    char charWord;
    wordCount = 0;
    
    // allocate struct node memory for pointer root
    root = (struct node*) malloc(sizeof(node));
    
    // get each character of dictionary file until its end of file
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // if it is at the end of string
        if (c == '\n')
        {
            word[index] = c;
            // insert word into trie
            wordCount++;
            struct node* cursor = root;
            for (int i = 0; i <= index; i++)
            {
                charWord = word[i];
                // if character is an alphabet
                if (isalpha(charWord))
                {
                    // if the element is NULL, malloc a new node
                    if (cursor->node[charWord - 'a'] == NULL)
                    {
                        cursor->node[charWord - 'a'] = (struct node*) malloc(sizeof(node));
                    }
                    cursor = cursor->node[charWord - 'a'];
                }
                // if character is an apostrophe
                else if (charWord == '\'')
                {
                    // if the element is NULL, malloc a new node
                    if (cursor->node[26] == NULL)
                    {
                        cursor->node[26] = (struct node*) malloc(sizeof(node));
                    }
                    cursor = cursor->node[26];
                }
                // if reach end of the word
                else if (charWord == '\n')
                {
                    cursor->isWord = true;
                }
            }
            // reset index for new word
            index = 0;
        }
        else
        {
            word[index] = c;
            index++;
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if (freeNode(root))
    {
        return true;
    }
    return false;
}

/**
 * Free the memory of node and every node allocated under it.
 */
bool freeNode(struct node* node)
{
    // iterate through all children of node
    for (int i = 0; i < 27; i++)
    {
        // For each child, if that child is not null, then call freeNode() on that child.
        if (node->node[i] != NULL)
        {
            freeNode(node->node[i]);
        }
    }
    // After the loop, free this node itself.
    free(node);

    return true;
}
