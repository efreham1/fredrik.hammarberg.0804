#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

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
    *entry_p = (entry_t){.value = value, .next = next};
    return entry_p;
}

static void reset_end(ioopm_list_t *ll, entry_t *start_entry)
{
    entry_t *entry = start_entry;
    while (entry->next != NULL)
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

static entry_t *get_entry(ioopm_list_t *list, int index)
{
    entry_t *current_entry_p = &list->sentinel;
    for (int i = -1; i < index; i++)
    {
        current_entry_p = current_entry_p->next;
    }
    return current_entry_p;
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    assert(index < list->length && index >= 0);
    entry_t *entry = get_entry(list, index);
    int entry_value = entry->value;
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
    int list_length = list->length;
    assert(list_length >= index && index >= 0);

    if (index == 0)
    {
        ioopm_linked_list_prepend(list, value);
        return;
    }

    if (index == list_length)
    {
        ioopm_linked_list_append(list, value);
        return;
    }

    entry_t *entry_before = get_entry(list, index - 1);
    entry_t *entry_after = get_entry(list, index);
    entry_t *entry_p = create_entry(value, entry_after);
    entry_before->next = entry_p;
    list->length++;
    return;
}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    assert(index<list->length);
    entry_t *prev_entry = get_entry(list, index-1);
    entry_t *curr_ent = prev_entry->next;
    int value = curr_ent->value;
    prev_entry->next = curr_ent->next;
    free(curr_ent);
    list->length--;
    return value;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    if (ioopm_linked_list_is_empty(list))
    {
        return false;
    }
    entry_t* current_entry = list->sentinel.next;
    while(current_entry != NULL)
    {
        if (!prop(current_entry->value, extra))
        {
            return false;
        }
        current_entry = current_entry->next;
    }
    return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    if (ioopm_linked_list_is_empty(list))
    {
        return false;
    }
    entry_t* current_entry = list->sentinel.next;
    while(current_entry != NULL)
    {
        if (prop(current_entry->value, extra))
        {
            return true;
        }
        current_entry = current_entry->next;
    }
    return false;
}

static bool is_equal(int value, void* extra)
{
    int *value_for_comparison = extra;
    return value == *value_for_comparison;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    int ele = element;
    return ioopm_linked_list_any(list, (ioopm_int_predicate) is_equal, &ele);
}


void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    entry_t *curr_ent = list->sentinel.next;
    for (int i = 0; i < list->length; i++)
    {
        fun(&curr_ent->value, extra);
        curr_ent = curr_ent->next;
    }
}

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
    return ioopm_iterator_create(list);
}