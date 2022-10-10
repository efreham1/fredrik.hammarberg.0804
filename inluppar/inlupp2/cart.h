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

/// @brief Add a merchandise to a cart
/// @param cart The cart where the merchandise will be added
/// @param merch The merchandise to be added
void ioopm_cart_add(ioopm_cart_t *cart, merch_t merch);

/// @brief Remove a merchandise from a cart
/// @param cart The cart where the merchandise will be removed from
/// @param merch Type of merchandise to be removed
/// @param No_merch Number of merchandise of said type to be removed
void ioopm_cart_remove(ioopm_cart_t *cart, char *merch_name, int No_merch);

/// @brief Get the cost of all merchandise in a cart
/// @param cart The cart from where the cost will be calculated
/// @return The cost of the contents in öre
int ioopm_cart_get_cost(ioopm_cart_t *cart);

/// @brief Clear the contents of a cart
/// @param cart The cart to be cleared
void ioopm_cart_clear(ioopm_cart_t *cart);

/// @brief Get a hash table of all merchandise in a cart
/// @param cart The cart to get the merchandise from
/// @return A hash table of all the merchandise
ioopm_hash_table_t *ioopm_cart_get_merch(ioopm_cart_t *cart);