#include "merch.h"

int hash_function_merch(elem_t key, int No_buckets)
{
    merch_t *merch = key.ptr_v;
    char *name = merch->name;
    int result = 0;
    do
    {
    result += *name;
    } while (*++name != '\0');
    return abs(result % No_buckets);
}

bool lt_merch(elem_t a, elem_t b)
{
    merch_t *merch_a = a.ptr_v;
    char *name_a = merch_a->name;
    merch_t *merch_b = b.ptr_v;
    char *name_b = merch_b->name;
    return strcmp(name_a, name_b)<0;
}

bool eq_merch(elem_t a, elem_t b)
{
    merch_t *merch_a = a.ptr_v;
    char *name_a = merch_a->name;
    merch_t *merch_b = b.ptr_v;
    char *name_b = merch_b->name;
    return strcmp(name_a, name_b)==0;
}