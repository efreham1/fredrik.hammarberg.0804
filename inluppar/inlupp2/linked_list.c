#include "linked_list.h"
#include "iterator.h"
#include "data_structure.h"
#include <stdio.h>
#include <stdlib.h>


struct list {
    ll_entry_t *head;
    ll_entry_t *tail;
    size_t size;
    ioopm_eq_function eq_fn;
};

struct entry_ll {
    elem_t value;
    ll_entry_t *next;
};

static ll_entry_t *create_link(elem_t value, ll_entry_t *next) {
    ll_entry_t *link = calloc(1, sizeof(ll_entry_t));
    link->value = value;
    link->next = next;
    return link;
}


ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function eq_fn) {
    ioopm_list_t *ll = calloc(1, sizeof(ioopm_list_t));
    ll->eq_fn = eq_fn;
    return ll;
}


void ioopm_linked_list_destroy(ioopm_list_t *ll) {
    ioopm_linked_list_clear(ll);
    free(ll);
}


void ioopm_linked_list_append(ioopm_list_t *ll, elem_t value) {
    ll_entry_t *new_tail = create_link(value, NULL);
    if (ll->head == NULL) {
        ll->head = new_tail;
        ll->tail = new_tail;
        ll->size++;
    }
    else {
        ll_entry_t *tmp = ll->tail;
        ll->tail = new_tail;
        tmp->next = new_tail;
        ll->size++;
    }    
}


void ioopm_linked_list_prepend(ioopm_list_t *ll, elem_t value) {
    ll_entry_t *new_head = create_link(value, ll->head);
    ll->head = new_head;
    ll->size++; 
}


void ioopm_linked_list_insert(ioopm_list_t *ll, int index, elem_t value) {
    if (index > ll->size || index < 0) {
        return;
    }
    else if (index == 0) {
        ioopm_linked_list_prepend(ll, value);
    }
    else if (index == ll->size) {
        ioopm_linked_list_append(ll, value);
    }
    else {
        ll_entry_t *current = ll->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        ll_entry_t *replaced = current->next;
        ll_entry_t *new_link = create_link(value, replaced);
        current->next = new_link;
        ll->size++; 
    }
}


elem_t ioopm_linked_list_remove(ioopm_list_t *ll, int index) {
    if (index >= ll->size || index < 0) {
        return (elem_t) { .int_v = (-1) };
    }
    else if (index == 0) {
        ll_entry_t *new_head = ll->head->next;
        elem_t removed_value = ll->head->value;
        free(ll->head);
        ll->head = new_head;
        ll->size--;
        return removed_value;
    }
    else if (index == ll->size -1) {
        ll_entry_t *new_tail = ll->head;
        for (int i = 0; i < index - 1; ++i) {
            new_tail = new_tail->next;
        }
        elem_t removed_value = ll->tail->value;
        free(ll->tail);
        new_tail->next = NULL;
        ll->tail = new_tail;
        ll->size--;
        return removed_value;
    }
    else {
        ll_entry_t *current = ll->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        ll_entry_t *tmp = current->next->next;
        elem_t removed_value = current->next->value;
        free(current->next);   
        current->next = tmp; 
        ll->size--;
        return removed_value;
    }
}


elem_t ioopm_linked_list_get(ioopm_list_t *ll, int index) {
    if (index >= ll->size || index < 0) {
        return (elem_t) { .int_v = (-1) };
    }
    else if (index == 0) {
        return ll->head->value;
    }
    else if (index == ll->size -1) {
        return ll->tail->value;
    }
    else {
        ll_entry_t *current = ll->head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }
}


bool ioopm_linked_list_contains(ioopm_list_t *ll, elem_t element) {
    ll_entry_t *current = ll->head;
    for (int i = 0; i < ll->size; ++i) {
        if (ll->eq_fn(current->value, element)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int ioopm_linked_list_get_index(ioopm_list_t *ll, elem_t element) {
    ll_entry_t *current = ll->head;
    for (int i = 0; i < ll->size; ++i) {
        if (ll->eq_fn(current->value, element)) {
            return i;
        }
        current = current->next;
    }
    return -1;
}


size_t ioopm_linked_list_size(ioopm_list_t *ll) {
    return ll->size;
}


bool ioopm_linked_list_is_empty(ioopm_list_t *ll) {
    return ll->size == 0;
}


void ioopm_linked_list_clear(ioopm_list_t *ll) {
    ll_entry_t *to_remove = ll->head;
    while (to_remove != NULL) {
        ll_entry_t *tmp = to_remove;
        to_remove = to_remove->next;
        free(tmp);
    }
    ll->size=0;
    ll->head = NULL;
}


bool ioopm_linked_list_all(ioopm_list_t *ll, ioopm_predicate_ll prop, void *extra) {
    ll_entry_t *current = ll->head;
    bool result = true;
    for (int i = 0; i < ll->size && result; ++i) {
        result = prop(current->value, extra);
        current = current->next;
    }
    return result;
}


bool ioopm_linked_list_any(ioopm_list_t *ll, ioopm_predicate_ll prop, void *extra) {
    ll_entry_t *current = ll->head;
    for (int i = 0; i < ll->size; ++i) {
        if (prop(current->value, extra)) {
            return true;
        }    
        current = current->next;
    }
    return false;
}


void ioopm_linked_list_apply_to_all(ioopm_list_t *ll, ioopm_apply_function_ll fun, void *extra) {
    ll_entry_t *current = ll->head;
    for (int i = 0; i < ll->size; ++i) {
        fun(&current->value, extra);
        current = current->next;
    }
}

ioopm_list_t *ioopm_linked_list_copy(ioopm_list_t *old_ll)
{
    ioopm_list_iterator_t *iter = ioopm_list_iterator(old_ll);
    ioopm_list_t *new_list = ioopm_linked_list_create(old_ll->eq_fn);
    for (int i = 0; i < ioopm_linked_list_size(old_ll); i++)
    {
        ioopm_linked_list_append(new_list, ioopm_iterator_current(iter));
        ioopm_iterator_next(iter);
    }
    ioopm_iterator_destroy(iter);
    return new_list;
}


ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *ll) {
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    iter->head = ll->head;
    iter->previous = ll->head;
    iter->current = ll->head;
    iter->next = ll->head != NULL ? ll->head->next : NULL;
    iter->list = ll;
    return iter;
}


bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) {
    return (iter->next != NULL);
}


elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter) {
    ll_entry_t *new_previous = iter->previous;
    ll_entry_t *new_current = iter->current;
    ll_entry_t *new_next = iter->next;
    if (iter->next != NULL)
    {
        new_previous = iter->current;
        new_current = iter->next;
        new_next = iter->next->next;
    }
    iter->previous = new_previous;
    iter->current = new_current;
    iter->next = new_next;

    return iter->current->value;
}


elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter) {

    bool change_head = false;

    if (iter->current==iter->head) change_head = true;

    iter->previous->next = iter->next;
    elem_t to_return = iter->current->value;
    free(iter->current);

    ll_entry_t *new_current = iter->current;
    ll_entry_t *new_next = iter->next;
    if (iter->next != NULL)
    {
        new_current = iter->next;
        new_next = iter->next->next;
    }
    iter->current = new_current;
    iter->next = new_next;
    iter->list->size--;

    if (change_head)
    {
        iter->head = iter->current;
        iter->list->head = iter->current;
    }
    

    return to_return;

}


void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element) {
    //TODO (optional)
}


void ioopm_iterator_reset(ioopm_list_iterator_t *iter) {
    iter->previous = iter->head;
    iter->current = iter->head;
    iter->next = iter->current->next;
}


elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter) {
    return iter->current->value;
}


void ioopm_iterator_destroy(ioopm_list_iterator_t *iter) {
    free(iter);
}