#include "hash_table.h"

#define No_Buckets 17

struct entry_ht
{
    int key;       // holds the key     
    char *value;   // holds the value
    ht_entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    ht_entry_t buckets[No_Buckets];
};

static ht_entry_t *entry_create(int key, char *value, ht_entry_t *next)
{
    ht_entry_t *entry_p = calloc(1, sizeof(ht_entry_t));
    ht_entry_t entry = {.key = key, .value = value, .next = next};
    *entry_p = entry;
    return entry_p;
}

static ht_entry_t *find_previous_entry_for_key(ht_entry_t *sentinel, int key)
{
    if (sentinel->next == NULL)
    {
        return sentinel; //bucket is empty
    }
    //else
    ht_entry_t *cursor = sentinel;
    ht_entry_t *next_entry = cursor->next;
    while(next_entry != NULL && next_entry->key < key)
    {
        cursor = next_entry;
        next_entry = cursor->next;
    }
    ht_entry_t *previous_entry = cursor;
    return previous_entry;
}

static void destroy_entry(ht_entry_t *entry, ht_entry_t **next_entry)
{
    ht_entry_t *next_entry_local = entry->next;
    free(entry);
    *next_entry = next_entry_local;
}

static ht_entry_t *get_sentinel(ioopm_hash_table_t *ht, int key)
{
    /// Calculate the bucket for this entry
    int bucket = abs(key%No_Buckets);
    //get correct sentinel from buckets
    ht_entry_t *sentinel = &ht->buckets[bucket];
    return sentinel;
    
}
//Create a new hash table
ioopm_hash_table_t *ioopm_hash_table_create(void)
{
    /// Allocate space for a ioopm_hash_table_t = No_Buckets pointers to
    /// ht_entry_t's, which will be set to NULL
    ioopm_hash_table_t *hash_table = calloc(1, sizeof(ioopm_hash_table_t));
    return hash_table;
}

//Delete a hash table and free its memory
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_clear(ht);
    free(ht);
}

//add key => value entry in hash table ht
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
    ht_entry_t *sentinel = get_sentinel(ht, key);
    ht_entry_t *prev_entry = find_previous_entry_for_key(sentinel, key);
    ht_entry_t *curr_entry = prev_entry->next;

    /// Check if the next entry should be updated or not
    if (curr_entry != NULL && curr_entry->key == key)
    {
        curr_entry->value = value;
    }
    else
    {
        prev_entry->next = entry_create(key, value, curr_entry);
    }
}

//lookup value for key in hash table ht
char **ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
    ht_entry_t *sentinel = get_sentinel(ht, key);
    ht_entry_t *prev_entry = find_previous_entry_for_key(sentinel, key);
    ht_entry_t *curr_entry = prev_entry->next;

    if (curr_entry != NULL && curr_entry->key == key)
    {
        return &curr_entry->value;
    }
    //else
    return NULL;
}

//remove any mapping from key to a value
char **ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
    ht_entry_t *sentinel = get_sentinel(ht, key);
    ht_entry_t *prev_entry = find_previous_entry_for_key(sentinel, key);
    ht_entry_t *curr_entry = prev_entry->next;

    if (curr_entry != NULL && curr_entry->key == key) //key found
    {
        char **data_ptr = &curr_entry->value;
        destroy_entry(curr_entry, &prev_entry->next);
        return data_ptr;
    }
    //else
    return NULL; //didn't find key, do nothing and return NULL
    
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    size_t count = 0;
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            count += 1;
            next_entry = next_entry->next;
        }
        
        
    }
    return count;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
    for (int i = No_Buckets-1; i>=0; i--)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        if (sentinel->next != NULL)
        {
            return false;
        } 
    }
    return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
    for (int i = No_Buckets-1; i>=0; i--)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *to_be_destroyed = sentinel->next;
        while (to_be_destroyed != NULL)
        {
            destroy_entry(to_be_destroyed, &to_be_destroyed); //destory current entry and update to_be_destroyed to next entry
        }
        sentinel->next = NULL;
    }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
    ioopm_list_t *list = ioopm_linked_list_create();
    for(int i = 0; i<No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            ioopm_linked_list_append(list, next_entry->key);
            next_entry = next_entry->next;
        }        
    }
    return list;
}

char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
    char **result = calloc(ioopm_hash_table_size(ht), sizeof(char *));
    int idx = 0;
    for(int i = 0; i<No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            result[idx] = next_entry->value;
            idx++;
            next_entry = next_entry->next;
        }        
    }
    if (idx==0)
    {
        free(result);
        return NULL;
    }
    return result;
}


bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate_ht pred, void *arg)
{
    if (ioopm_hash_table_is_empty(ht))
    {
        return false;
    }
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            int current_key = next_entry->key;
            char *current_value = next_entry->value;
            if (!pred(current_key, current_value, arg))
            {
                return false;
            }
            next_entry = next_entry->next;
        }
    }
    return true;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate_ht pred, void *arg)
{
    if (ioopm_hash_table_is_empty(ht))
    {
        return false;
    }
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            int current_key = next_entry->key;
            char *current_value = next_entry->value;
            if (pred(current_key, current_value, arg))
            {
                return true;
            }
            next_entry = next_entry->next;
        }
    }
    return false;
}


void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function_ht apply_fun, void *arg)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            int current_key = next_entry->key;
            char **current_value_p = &next_entry->value;
            apply_fun(current_key, current_value_p, arg);
            next_entry = next_entry->next;
        }
    }
    
}

static bool has_key(int key, char *value, void *extra)
{
    int *looking_for = extra;
    return key==*looking_for;
}

static bool has_value(int key, char *value, void *extra)
{
    char **looking_for = extra;
    return strcmp(value, *looking_for)==0;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
    return ioopm_hash_table_any(ht, has_key, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
    return ioopm_hash_table_any(ht, has_value, &value);
}
