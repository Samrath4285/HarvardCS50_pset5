#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "%s could not be opened", dictionary);
        return 1;
    }
    char *word = malloc((LENGTH + 1) * sizeof(char));
    while (fscanf(file, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            fprintf(stderr, "Malloc Error in load");
            return false;
        }
        
        strcpy(newNode->word, word);
        
        unsigned long bucket = hash(word, strlen(word));
        
        //If bucket is empty
        if (hashTable[bucket] == NULL)
        {
            hashTable[bucket] = newNode;
        }
        
        //bucket not empty, add to front
        else
        {
            newNode->next = hashTable[bucket];
            hashTable[bucket]->next = newNode;
        }
        
    }
    return true;
}