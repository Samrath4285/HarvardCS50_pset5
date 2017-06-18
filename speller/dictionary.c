/**
 * Implements a dictionary's functionality.
 * Uses Jenkins One at a time Hash Function 
 * https://en.wikipedia.org/wiki/Jenkins_hash_function
 */

#include "dictionary.h"


#define HASHTABLE_SIZE 98317 //the internet + trial and error told me this was a good prime # to use

//Global Variables: HashTable, Dictionary word count, boolean for if the dict loads successfully
node *hashTable[HASHTABLE_SIZE];
unsigned int wordCount = 0;
bool loaded = false;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //Hash the checked word
    unsigned int searchedHash = hash(word, strlen(word));
    //set ptr to the head of the linked list for that hash
    node *ptr = hashTable[searchedHash];
    
    //Loop until the end of linked list, or the searched word is found
    while (ptr != NULL)
    {
        //Word is found
        if (strcmp((ptr->word), word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    //word not found
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "%s could not be opened", dictionary);
        return 1;
    }
    
    //Initialize Hashtable Values to Null
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }
    
    //Allocate memory for up to 46 characters for a dictionary word
    char *word = malloc((LENGTH + 1) * sizeof(char));
    //unsigned int bumpcount = 0;
    while (fscanf(file, "%s", word) != EOF)
    {
        wordCount++;
        node *newNode = malloc(sizeof(struct node));
        
        //Memory error handling
        if (newNode == NULL)
        {
            fprintf(stderr, "Malloc Error in load");
            return false;
        }
        
        //copy word into newNode's word member variable "word"
        strcpy(newNode->word, word);
        
        //hash the word
        unsigned int bucket = hash(word, strlen(word));

        //If bucket is empty
        if (hashTable[bucket] == NULL)
        {
            hashTable[bucket] = newNode;
        }
        
        /*
        bucket not empty, add to front of linked list (list will be unsorted)
        Since we are not allowed to pre-process dictionaries and store their data structure ahead of time,
        it is likely more efficient to have to search an unsorted list than sort each list.  Each list will likely be very short
        if an appropriately size hash-table is used.
        */
        else
        {
            newNode->next = hashTable[bucket];
            hashTable[bucket] = newNode;
        }
    }
    free(word);
    fclose(file);
    loaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (loaded)
    {
        return wordCount;
    }
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    /*
    Goes through each linked list in the hashTable individually, freeing all of the memory that was allocated.
    This is done by using a temporary pointer to traverse each linked list, removing each node one at a time
    */
    for (unsigned int index = 0; index < HASHTABLE_SIZE; index++){
        node *ptr = hashTable[index];
        while (ptr != NULL){
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}

/**
 * Jenkins one-at-a-time hashing algorithm
 */
unsigned int hash(const char *key, size_t len)
{
    unsigned int hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % HASHTABLE_SIZE;
}