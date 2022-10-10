#include "cart.h"

#pragma once

/// @brief Show a TUI to add merchandise to a cart
/// @param cart The cart where the merchandise will be added to
void ioopm_TUI_cart_add(ioopm_cart_t *cart);

/// @brief Show a TUI to remove merchandise from a cart
/// @param cart The cart where the merchandise will be removed from
void ioopm_TUI_cart_remove(ioopm_cart_t *cart);

/// @brief Print the cost of a carts contents
/// @param cart The cart to get the costs from
void ioopm_TUI_cart_get_cost(ioopm_cart_t *cart);

/// @brief Print all contents in the cart
/// @param cart The cart from where the contents will be retrived
void ioopm_TUI_cart_list_contents(ioopm_cart_t *cart);
