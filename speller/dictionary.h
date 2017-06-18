/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// maximum length for a word
#define LENGTH 45


typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}node;

/**
 * Hashing algorithm.  Generates an unsigned int when given a string and a table size
 * Uses Jenkins One at a time Hash Function 
 * https://en.wikipedia.org/wiki/Jenkins_hash_function
 */

unsigned int hash(const char *key, size_t len);

/**
 * Returns true if word is in dictionary else false.
 */
 
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
