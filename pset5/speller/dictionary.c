// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include <ctype.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void removeit(struct node *first);

int wordsnum = 0;

// Number of buckets in hash table
const unsigned int N = 123456;

// Hash table (array of node pointers)
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    /*unsigned int pos = hash(word);

    node *cursor =  table[pos];

    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        } else
        {
            cursor = cursor->next;
        }
    }

    return false;*/

    int len = strlen(word);
    char lowword[len + 1];
    for (int i = 0; i < len; i++)
    {
        lowword[i] = tolower(word[i]);
    }
    lowword[len] = '\0';

    unsigned int pos = hash(lowword);
    node *cursor = table[pos]; //access linked lists are position we want to search for word

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, lowword) != 0)
            cursor = cursor->next;
        else
            return true;
    }
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word) //unsigned int forces value to NOT be negative
{
    //from https://stackoverflow.com/questions/7666509/hash-function-for-string
    unsigned hashval;

    for (hashval = 0; *word != '\0'; word++)
        hashval = *word + 31*hashval;

    return hashval % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL) {
        return false;
    }

    char each[LENGTH + 1]; //buffer

    while (fscanf(file, "%s", each) != EOF)
    {
        node *n = malloc(sizeof(node)); //node for each word
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, each);
        n->next = NULL;

        unsigned int index = hash(each); // Get index of word by hashing it

        if (table[index] == NULL)
        {
            table[index] = n;

        } else { //make that word the first one in linked list for that index position
            n->next = table[index];
            table[index] = n;

        }
        wordsnum++;

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordsnum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *first = table[i];
        removeit(first);
    }
    return true;
}

void removeit(struct node *first)
{
    if (first == NULL)
    {
        return;
    }
    removeit(first -> next);
    free(first);
}
