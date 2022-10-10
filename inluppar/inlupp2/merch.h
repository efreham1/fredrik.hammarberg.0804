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

/// @brief The hash function for merchandise
int hash_function_merch(elem_t key, int No_buckets);

/// @brief lt comparison for merchandise
bool lt_merch(elem_t a, elem_t b);

/// @brief eq comparison for merchandise
bool eq_merch(elem_t a, elem_t b);