#include "cart.h"
#include "inventory.h"

#pragma once

/// @brief Undo the last operation on the inventory or cart
/// @param inventory The inventory in its current state
/// @param cart The cart in its current state
void ioopm_undo_undo(ioopm_inventory_t *inventory, ioopm_cart_t *cart);

void ioopm_undo_save_state(ioopm_inventory_t *inventory, ioopm_cart_t *cart);