#include "iterator.h"

typedef struct iterator ioopm_list_iterator_t;
struct iterator
{
    ioopm_list_t *list;
    int current_idx;
    int max_idx;
};

ioopm_list_iterator_t *ioopm_iterator_create(ioopm_list_t *list)
{
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    int max_idx = ioopm_linked_list_length(list) - 1;
    *iter = (ioopm_list_iterator_t){.list = list, .current_idx = 0, .max_idx = max_idx};
    return iter;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
    return iter->current_idx < iter->max_idx;
}

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    assert(iter->max_idx > -1);
    if (ioopm_iterator_has_next(iter))
    {
        iter->current_idx++;
    }
    return ioopm_linked_list_get(iter->list, iter->current_idx);
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    iter->current_idx = 0;
}

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
    return ioopm_linked_list_get(iter->list, iter->current_idx);
}
