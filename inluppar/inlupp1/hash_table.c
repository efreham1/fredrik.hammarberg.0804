#include "hash_table.h"

#define No_Buckets 50

struct entry_ht
{
    elem_t key;       // holds the key
    elem_t value;     // holds the value
    ht_entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    ht_entry_t buckets[No_Buckets];
    ioopm_hash_function h_fnc;
    ioopm_eq_function compare_equal_keys;
    ioopm_eq_function compare_equal_values;
    ioopm_lt_function compare_lessthan_keys;
};

static ht_entry_t *entry_create(elem_t key, elem_t value, ht_entry_t *next)
{
    ht_entry_t *entry_p = calloc(1, sizeof(ht_entry_t));
    ht_entry_t entry = {.key = key, .value = value, .next = next};
    *entry_p = entry;
    return entry_p;
}

static ht_entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, ht_entry_t *sentinel, elem_t key)
{
    if (sentinel->next == NULL)
    {
        return sentinel; // bucket is empty
    }
    // else
    ht_entry_t *cursor = sentinel;
    ht_entry_t *next_entry = cursor->next;
    while (next_entry != NULL && ht->compare_lessthan_keys(next_entry->key, key))
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

static ht_entry_t *get_sentinel(ioopm_hash_table_t *ht, elem_t key)
{
    /// Calculate the bucket for this entry
    int bucket = ht->h_fnc(key, No_Buckets);
    // get correct sentinel from buckets
    ht_entry_t *sentinel = &ht->buckets[bucket];
    return sentinel;
}

static ht_entry_t *get_sentinel_bucket(ioopm_hash_table_t *ht, int i)
{
    assert(i > -1 && i < No_Buckets);
    /// Calculate the bucket for this entry
    int bucket = i;
    // get correct sentinel from buckets
    ht_entry_t *sentinel = &ht->buckets[bucket];
    return sentinel;
}

// Create a new hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_function, ioopm_eq_function compare_eq_key, ioopm_eq_function compare_eq_values, ioopm_lt_function compare_lt_keys)
{
    ioopm_hash_table_t *hash_table = calloc(1, sizeof(ioopm_hash_table_t));
    hash_table->h_fnc = hash_function;
    hash_table->compare_equal_keys = compare_eq_key;
    hash_table->compare_lessthan_keys = compare_lt_keys;
    hash_table->compare_equal_values = compare_eq_values;
    return hash_table;
}

// Delete a hash table and free its memory
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_clear(ht);
    free(ht);
}

// add key => value entry in hash table ht
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
    ht_entry_t *sentinel = get_sentinel(ht, key);
    ht_entry_t *prev_entry = find_previous_entry_for_key(ht, sentinel, key);
    ht_entry_t *curr_entry = prev_entry->next;

    /// Check if the next entry should be updated or not
    if (curr_entry != NULL && ht->compare_equal_keys(curr_entry->key, key))
    {
        curr_entry->value = value;
    }
    else
    {
        prev_entry->next = entry_create(key, value, curr_entry);
    }
}

// lookup value for key in hash table ht
elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
    ht_entry_t *sentinel = get_sentinel(ht, key);
    ht_entry_t *prev_entry = find_previous_entry_for_key(ht, sentinel, key);
    ht_entry_t *curr_entry = prev_entry->next;

    if (curr_entry != NULL && ht->compare_equal_keys(curr_entry->key, key))
    {
        return &curr_entry->value;
    }
    // else
    return NULL;
}

// remove any mapping from key to a value
elem_t *ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
    ht_entry_t *sentinel = get_sentinel(ht, key);
    ht_entry_t *prev_entry = find_previous_entry_for_key(ht, sentinel, key);
    ht_entry_t *curr_entry = prev_entry->next;

    if (curr_entry != NULL && ht->compare_equal_keys(curr_entry->key, key)) // key found
    {
        elem_t *data_ptr = &curr_entry->value;
        destroy_entry(curr_entry, &prev_entry->next);
        return data_ptr;
    }
    // else
    return NULL; // didn't find key, do nothing and return NULL
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    size_t count = 0;
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
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
    for (int i = No_Buckets - 1; i >= 0; i--)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        if (sentinel->next != NULL)
        {
            return false;
        }
    }
    return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
    for (int i = No_Buckets - 1; i >= 0; i--)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *to_be_destroyed = sentinel->next;
        while (to_be_destroyed != NULL)
        {
            destroy_entry(to_be_destroyed, &to_be_destroyed); // destory current entry and update to_be_destroyed to next entry
        }
        sentinel->next = NULL;
    }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
    ioopm_list_t *list = ioopm_linked_list_create(ht->compare_equal_keys);
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            ioopm_linked_list_append(list, next_entry->key);
            next_entry = next_entry->next;
        }
    }
    return list;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
    ioopm_list_t *list = ioopm_linked_list_create(ht->compare_equal_values);
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            ioopm_linked_list_append(list, next_entry->value);
            next_entry = next_entry->next;
        }
    }
    return list;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate_ht pred, void *arg)
{
    if (ioopm_hash_table_is_empty(ht))
    {
        return false;
    }

    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            elem_t current_key = next_entry->key;
            elem_t current_value = next_entry->value;
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
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            elem_t current_key = next_entry->key;
            elem_t current_value = next_entry->value;
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
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            elem_t current_key = next_entry->key;
            elem_t *current_value_p = &next_entry->value;
            apply_fun(current_key, current_value_p, arg);
            next_entry = next_entry->next;
        }
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            elem_t current_key = next_entry->key;
            if (ht->compare_equal_keys(current_key, key))
            {
                return true;
            }
            next_entry = next_entry->next;
        }
    }
    return false;
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        ht_entry_t *sentinel = get_sentinel_bucket(ht, i);
        ht_entry_t *next_entry = sentinel->next;
        while (next_entry != NULL)
        {
            elem_t current_value = next_entry->value;
            if (ht->compare_equal_values(current_value, value))
            {
                return true;
            }
            next_entry = next_entry->next;
        }
    }
    return false;
}
