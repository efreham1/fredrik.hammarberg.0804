#include "iterator.h"
#include <stdbool.h>
#include <stdlib.h>

struct iterator
{
    ioopm_list_t *list;
    int current_idx;
    int max_idx;
};

ioopm_list_iterator_t *ioopm_iterator_create(ioopm_list_t *list)
{
    ioopm_list_iterator_t *iterator = calloc(1, sizeof(ioopm_list_iterator_t *));
    int max_idx = ioopm_linked_list_length(list)-1;
    *iterator = (ioopm_list_iterator_t){.list = list, .current_idx = 0, .max_idx = max_idx};
    
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);

int ioopm_iterator_next(ioopm_list_iterator_t *iter);

void ioopm_iterator_reset(ioopm_list_iterator_t *iter);

int ioopm_iterator_current(ioopm_list_iterator_t *iter);

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);