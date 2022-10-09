#include "common_definitions.h"
#include "hash_table.h"
#pragma once

typedef struct cart ioopm_cart_t;

/// @brief Create a new empty cart
/// @return An empty cart
ioopm_cart_t *ioopm_cart_create();

/// @brief Destroy a cart and return it's resources
/// @param cart The cart to be destroyed
void ioopm_cart_destroy(ioopm_cart_t *cart);

/// @brief Bring up a TUI for adding merchandise to a cart
/// @param cart The cart where the merchandise will be added
void ioopm_cart_add(ioopm_cart_t *cart);

/// @brief Bring up a TUI for removing merchandise from a cart
/// @param cart The cart where the merchandise will be removed from
void ioopm_cart_remove(ioopm_cart_t *cart);

/// @brief Get the cost of all merchandise in a cart
/// @param cart The cart from where the cost will be calculated
void ioopm_cart_get_cost(ioopm_cart_t *cart);

/// @brief List the contents of a cart
/// @param cart The cart that the contents will be read from
void ioopm_cart_list_contents(ioopm_cart_t *cart);

/// @brief Clear the contents of a cart
/// @param cart The cart to be cleared
void ioopm_cart_clear(ioopm_cart_t *cart);

/// @brief Get a list of all merchandise in a cart
/// @param cart The cart to get the merchandise from
/// @return A linked list of all the merchandise
ioopm_hash_table_t *ioopm_cart_get_merch(ioopm_cart_t *cart);