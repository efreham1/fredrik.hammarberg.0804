#include "linked_list.h"

#pragma once

typedef struct iterator ioopm_list_iterator_t;

/// @brief Creates a new iterator for a list
/// @param list the linked list to be iterated over
/// @return an iterator positioned on the first element of the list
ioopm_list_iterator_t *ioopm_iterator_create(ioopm_list_t *list);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there is at least one more element otherwise false
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one step if possible. Does not allow iteration on an empty list
/// @param iter the iterator
/// @return the next element
elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter);

/// @brief Reposition the iterator at the first element of the underlying list
/// @param iter the iterator
void ioopm_iterator_reset(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter);

/// @brief Destroy the iterator and return its resources, note that the list is not destroyed
/// @param iter the iterator
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter);