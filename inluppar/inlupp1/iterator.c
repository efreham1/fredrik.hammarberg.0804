#include "iterator.h"

typedef struct iterator ioopm_list_iterator_t;
struct iterator
{
    ioopm_list_t *list;
    ll_entry_t *current_entry;
};

struct entry_ll
{
    elem_t value;
    ll_entry_t *next;
};

struct list
{
    ll_entry_t sentinel;
    ll_entry_t *end;
    size_t length;
    ioopm_eq_function compare_equal;
};

ioopm_list_iterator_t *ioopm_iterator_create(ioopm_list_t *list)
{
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    ll_entry_t *first_entry = list->sentinel.next;
    *iter = (ioopm_list_iterator_t){.list = list, .current_entry = first_entry};
    return iter;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
    return iter->current_entry->next != NULL;
}

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    if (ioopm_iterator_has_next(iter))
    {
        iter->current_entry = iter->current_entry->next;
    }
    return iter->current_entry->value;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    iter->current_entry = iter->list->sentinel.next;
}

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
    return iter->current_entry->value;
}
