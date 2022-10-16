#pragma once
#include <stdbool.h>
#include "data_structure.h"

/*
 * @file hash_table.h
 * @author Joel Holmberg, Viktor Lundin
 * @date 4 Oct 2022
 * @brief Simple iterator for a linked list.
 *
 * Header file provides definitions and documentation for all the functions that 
 * creates/operates on/destroys an iterator intended for using the interface.
 *
 * @see https://uppsala.instructure.com/courses/68435/assignments/130155
 */

typedef struct iter ioopm_list_iterator_t;

struct iter {
    ll_entry_t *head;
    ll_entry_t *current;
    ll_entry_t *next;
};

/// @brief Create an iterator for a given list
/// @param list the list to be iterated over
/// @return an iteration position at the start of list
ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *ll);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there is at least one more element 
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
/// @return the next element
elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter);

/// NOTE: REMOVE IS OPTIONAL TO IMPLEMENT 
/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element
/// elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter);

/// NOTE: INSERT IS OPTIONAL TO IMPLEMENT 
/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
/// void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);