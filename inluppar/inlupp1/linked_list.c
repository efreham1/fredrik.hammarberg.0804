#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct list ioopm_list_t;
typedef struct entry entry_t;

struct entry
{
    int value;
    entry_t *next;
};

struct list
{
    entry_t sentinel;
    entry_t *end;
    int length;
};

static entry_t *create_entry(int value, entry_t *next)
{
    entry_t *entry_p = calloc(1, sizeof(entry_t));
    *entry_p = (entry_t) {.value = value, .next = next};
    return entry_p;
}

static void reset_end(ioopm_list_t *ll, entry_t *start_entry)
{
    entry_t *entry = start_entry;
    while(entry->next != NULL)
    {
        entry = entry->next;
    }
    ll->end = entry;
}

ioopm_list_t *ioopm_linked_list_create(void)
{
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
    reset_end(list, &list->sentinel);
    return list;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    ioopm_linked_list_clear(list);
    free(list);
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    entry_t *last_entry_p = list->end;
    entry_t *new_entry_p = create_entry(value, NULL);
    last_entry_p->next = new_entry_p;
    reset_end(list, new_entry_p);
    ++list->length;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    entry_t *new_entry_p = create_entry(value, list->sentinel.next);
    list->sentinel.next = new_entry_p;
    reset_end(list, list->end);
    ++list->length;
}

int ioopm_linked_list_length(ioopm_list_t *list)
{
    return list->length;
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    entry_t *current_entry_p = list->sentinel.next;
    
    for(int i = 0; i < index; i++)
    {
        current_entry_p = current_entry_p->next;
    }
    int entry_value = current_entry_p->value;
    return entry_value;
    
}

static void help_clear(entry_t *entry)
{
    if (entry == NULL)
    {
        return;
    }
    else if (entry->next == NULL)
    {
        free(entry);
        return;
    }
    else
    {
        help_clear(entry->next);
        free(entry);
        return;
    }
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    help_clear(list->sentinel.next);
    list->sentinel.next = NULL;
    reset_end(list, &list->sentinel);
    list->length = 0;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    return list->length == 0;
}

// tester hit ==============================================================

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
    return;
}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    return 0;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    return true;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    return true;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    return;
}