#include "data_structure.h"
#include <stdbool.h>

#pragma once

typedef struct merchandise merch_t;

struct merchandise
{
    char *name;
    char *description;
    int price;
};

int hash_function_merch(elem_t key, int No_buckets);

bool lt_merch(elem_t a, elem_t b);

bool eq_merch(elem_t a, elem_t b);