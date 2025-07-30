// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//counter words
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO check if word is in dictionary
    //hash word to obtain hash value
    unsigned int hash_index = hash(word);

    //traverse linked list, looking for word;
    node *trav = table[hash_index];

    while (trav != NULL)
    {
        //if is the word im looking for
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }

        //if is not
        if ((strcasecmp(word, trav->word) > 0) || (strcasecmp(word, trav->word) < 0))
        {
            trav = trav->next;
        }
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //function that
    unsigned int hash_code = 0;
    int word1 = 0;

    word1 = toupper(word[0]) - 'A';
    hash_code = word1;

    if (hash_code > (N - 1))
    {
        hash_code = hash_code % N;
    }

    return hash_code;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //read file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return false;
    }

    //read strings from the file until the end of file
    char buffer[LENGTH + 1];

    //create new node for every word read
    while (fscanf(input, "%s", buffer) != EOF)
    {
        //create new node for every word
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            fclose(input);
            free(new);
            return false;
        }
        //copy to node
        strcpy(new->word, buffer);
        new->next = NULL;

        //hash the word
        unsigned int hash_index = hash(new->word);

        //insert node to hash
        new->next = table[hash_index];

        //point head of table to new node
        table[hash_index] = new;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //read through every array of hash table
    for (int i = 0; i < N; i++)
    {

        //set trav equal to begining of linked list
        node *trav = table[i];

        //search until the end of linked list
        while (trav != NULL)
        {
            word_counter++;
            trav = trav->next;
        }
    }
    return word_counter;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO unload every memory used
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
