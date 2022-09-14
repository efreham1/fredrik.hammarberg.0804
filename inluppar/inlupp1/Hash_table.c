#include "Hash_table.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct hash_table ioopm_hash_table_t;

typedef struct entry entry_t;

struct entry
{
    int key;       // holds the key
    char *value;   // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    entry_t buckets[17];
};

static entry_t *entry_create(int key, char *value, entry_t *next)
{
    entry_t *entry_p = calloc(1, sizeof(entry_t));
    entry_t entry = {.key = key, .value = value, .next = next};
    *entry_p = entry;
    return entry_p;
}

static entry_t *find_previous_entry_for_key(entry_t *sentinal, int key)
{
    if (sentinal->next == NULL)
    {
        return sentinal; //bucket is empty
    }
    //else
    entry_t *previous_entry = sentinal->next;
    while(previous_entry->next != NULL && previous_entry->next->key < key)
    {
        previous_entry = previous_entry->next;
    }
    return previous_entry;
}

static entry_t *destroy_entry(entry_t *entry)
{
    entry_t *next = entry->next;
    free(entry);
    return next;
}
//Create a new hash table
ioopm_hash_table_t *ioopm_hash_table_create(void)
{
    /// Allocate space for a ioopm_hash_table_t = 17 pointers to
    /// entry_t's, which will be set to NULL
    ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
    return result;
}

//Delete a hash table and free its memory
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    for (int i = 16; i>=0; i--)
    {
        entry_t *sentinal = &ht->buckets[i];
        entry_t *to_be_destroyed = sentinal->next;
        while (to_be_destroyed != NULL)
        {
            to_be_destroyed = destroy_entry(to_be_destroyed);
        }
        
    }
    free(&ht->buckets);
    free(ht);
}

//add key => value entry in hash table ht
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
    /// Calculate the bucket for this entry
    int bucket = key % 17;
    /// Search for an existing entry for a key
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = entry->next;

    /// Check if the next entry should be updated or not
    if (next != NULL && next->key == key)
    {
        next->value = value;
    }
    else
    {
        entry->next = entry_create(key, value, next);
    }
    }

//lookup value for key in hash table ht
char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
    int bucket = key%17;

}

//remove any mapping from key to a value
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
    return "tjo bish"; //TODO funkar inte alls
}