// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Size of the dictionary
int SIZE = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int value = hash(word);

    node *cursor = table[value];
    if (cursor == NULL)
    {
        return false;
    }

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int w_length = strlen(word);

    unsigned int index0 = 0;
    unsigned int index1 = 0;
    unsigned int index2 = 0;

    // Number of places
    int places0 = 3;
    int places1 = 2;

    if (w_length >= 3)
    {
        int count = 0;

        // First three characters
        char first = word[0];
        char second = word[1];
        char third = word[2];

        for (int i = 0; i < places0; i++)
        {
            if (isalpha(word[i]))
            {
                if (count == 0)
                {
                    first = word[i];
                }
                else if (count == 1)
                {
                    second = word[i];
                }
                else if (count == 2)
                {
                    third = word[i];
                }
                count++;
            }
        }
        index0 = (toupper(first) - 'A') * 26 * 26 + (toupper(second) - 'A') * 26 +
                 (toupper(third) - 'A');
    }
    else if (w_length == 2)
    {
        int count = 0;

        // Two characters
        char first = word[0];
        char second = word[1];

        for (int i = 0; i < places1; i++)
        {
            if (isalpha(word[i]))
            {
                if (count == 0)
                {
                    first = word[i];
                }
                else if (count == 1)
                {
                    second = word[i];
                }
                count++;
            }
        }
        index1 = (toupper(first) - 'A') * 26 + (toupper(second) - 'A');
    }
    else if (w_length == 1)
    {
        if (isalpha(word[0]))
        {
            index2 = (toupper(word[0]) - 'A');
        }
    }

    unsigned int hash = index0 + index1 + index2;

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // set table pointers to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // TODO: Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // TODO: Read strings from file
    char w[LENGTH + 1];

    while (fscanf(file, "%s", w) != EOF)
    {
        // TODO: Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, w);
        n->next = NULL;

        // TODO: Hash word to obtain a hash value
        unsigned int index = hash(n->word);

        // TODO: Insert node into hash table
        n->next = table[index];
        table[index] = n;
        SIZE++;
    }

    // close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO: returning SIZE of dictionary
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO: Unload the dictionary
    node *cursor;
    node *tmp;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            if (tmp == NULL)
            {
                return false;
            }

            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
