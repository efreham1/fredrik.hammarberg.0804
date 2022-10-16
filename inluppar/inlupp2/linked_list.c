#include "linked_list.h"
#include "iterator.h"
#include <stdio.h>
#include <stdlib.h>


static link_t *create_link(elem_t value, link_t *next) {
    link_t *link = calloc(1, sizeof(link_t));
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
    link_t *new_tail = create_link(value, NULL);
    if (ll->head == NULL) {
        ll->head = new_tail;
        ll->tail = new_tail;
        ll->size++;
    }
    else {
        link_t *tmp = ll->tail;
        ll->tail = new_tail;
        tmp->next = new_tail;
        ll->size++;
    }    
}


void ioopm_linked_list_prepend(ioopm_list_t *ll, elem_t value) {
    link_t *new_head = create_link(value, ll->head);
    ll->head = new_head;
    ll->size++; 
}


void ioopm_linked_list_insert(ioopm_list_t *ll, int32_t index, elem_t value) {
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
        link_t *current = ll->head;
        for (int32_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        link_t *replaced = current->next;
        link_t *new_link = create_link(value, replaced);
        current->next = new_link;
        ll->size++; 
    }
}


elem_t ioopm_linked_list_remove(ioopm_list_t *ll, int32_t index) {
    if (index >= ll->size || index < 0) {
        return (elem_t) { .integer = (-1) };
    }
    else if (index == 0) {
        link_t *new_head = ll->head->next;
        elem_t removed_value = ll->head->value;
        free(ll->head);
        ll->head = new_head;
        ll->size--;
        return removed_value;
    }
    else if (index == ll->size -1) {
        link_t *new_tail = ll->head;
        for (int32_t i = 0; i < index - 1; ++i) {
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
        link_t *current = ll->head;
        for (int32_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        link_t *tmp = current->next->next;
        elem_t removed_value = current->next->value;
        free(current->next);   
        current->next = tmp; 
        ll->size--;
        return removed_value;
    }
}


elem_t ioopm_linked_list_get(ioopm_list_t *ll, int32_t index) {
    if (index >= ll->size || index < 0) {
        return (elem_t) { .integer = (-1) };
    }
    else if (index == 0) {
        return ll->head->value;
    }
    else if (index == ll->size -1) {
        return ll->tail->value;
    }
    else {
        link_t *current = ll->head;
        for (int32_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }
}


bool ioopm_linked_list_contains(ioopm_list_t *ll, elem_t element) {
    link_t *current = ll->head;
    for (int32_t i = 0; i < ll->size; ++i) {
        if (ll->eq_fn(current->value, element)) {
            return true;
        }
        current = current->next;
    }
    return false;
}


size_t ioopm_linked_list_size(ioopm_list_t *ll) {
    return ll->size;
}


bool ioopm_linked_list_is_empty(ioopm_list_t *ll) {
    return ll->size == 0;
}


void ioopm_linked_list_clear(ioopm_list_t *ll) {
    link_t *to_remove = ll->head;
    while (to_remove != NULL) {
        link_t *tmp = to_remove;
        to_remove = to_remove->next;
        free(tmp);
    }
}


bool ioopm_linked_list_all(ioopm_list_t *ll, ioopm_predicate prop, void *extra) {
    link_t *current = ll->head;
    bool result = true;
    for (int32_t i = 0; i < ll->size && result; ++i) {
        result = prop((elem_t) { .integer = i }, current->value, extra);
        current = current->next;
    }
    return result;
}


bool ioopm_linked_list_any(ioopm_list_t *ll, ioopm_predicate prop, void *extra) {
    link_t *current = ll->head;
    for (int32_t i = 0; i < ll->size; ++i) {
        elem_t index = { .integer = i };
        if (prop(index, current->value, extra)) {
            return true;
        }    
        current = current->next;
    }
    return false;
}


void ioopm_linked_list_apply_to_all(ioopm_list_t *ll, ioopm_apply_function fun, void *extra) {
    link_t *current = ll->head;
    for (int32_t i = 0; i < ll->size; ++i) {
        elem_t index = { .integer = i };
        fun(index, current->value, extra);
        current = current->next;
    }
}


ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *ll) {
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    iter->head = ll->head;
    iter->current = ll->head;
    iter->next = ll->head->next;
    return iter;
}


bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) {
    return (iter->next != NULL);
}


elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter) {
    link_t *new_current = iter->next;
    link_t *new_next = iter->next != NULL ? iter->next->next : NULL;

    iter->current = new_current;
    iter->next = new_next;

    return iter->current->value;
}


elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter) {
    //TODO (optional)
    return (elem_t) { .integer = 0 };
}


void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element) {
    //TODO (optional)
}


void ioopm_iterator_reset(ioopm_list_iterator_t *iter) {
    iter->current = iter->head;
    iter->next = iter->current->next;
}


elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter) {
    return iter->current->value;
}


void ioopm_iterator_destroy(ioopm_list_iterator_t *iter) {
    free(iter);
}