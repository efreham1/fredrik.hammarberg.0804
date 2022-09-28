#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct hash_table ioopm_hash_table_t;
typedef struct entry_ht ht_entry_t;

typedef bool(*ioopm_predicate_ht)(int key, char *value, void *extra);
typedef void(*ioopm_apply_function_ht)(int key, char **value, void *extra);


typedef struct list ioopm_list_t;
typedef struct entry_ll ll_entry_t;

typedef bool(*ioopm_int_predicate)(int value, void *extra);
typedef void(*ioopm_apply_int_function)(int *value, void *extra);


