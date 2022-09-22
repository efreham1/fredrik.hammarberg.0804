#include <stdbool.h>
#include "linked_list.h"

typedef struct list ioopm_list_t;
typedef struct entry entry_t;

struct list
{
    entry_t start;
    entry_t end;
    entry_t length;
};

struct entry
{
    int value;
    entry_t *next;
    entry_t *previous;
};

ioopm_list_t *ioopm_linked_list_create(void)
{
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
    return list;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{

}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{

}

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{

}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{

}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{

}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{

}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{

}

int ioopm_linked_list_size(ioopm_list_t *list)
{

}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{

}

void ioopm_linked_list_clear(ioopm_list_t *list)
{

}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{

}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{

}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{

}