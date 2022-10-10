#include "inventory.h"

#pragma once

/// @brief Show a TUI for adding merchandise to an inventory
/// @param inventory The inventory to add merchandise to
void ioopm_TUI_inventory_add_merch(ioopm_inventory_t *inventory);

/// @brief List all merchandise in an inventory
/// @param inventory The inventory from which the merchandise will be read from
void ioopm_TUI_inventory_list_merch(ioopm_inventory_t *inventory);

/// @brief Show a TUI for removing merchandise from an inventory
/// @param inventory The inventory to remove merchandise from
void ioopm_TUI_inventory_remove_merch(ioopm_inventory_t *inventory);

/// @brief Show a TUI for editing merchandise in an inventory
/// @param inventory The inventory to edit merchandise in
void ioopm_TUI_inventory_edit_merch(ioopm_inventory_t *inventory);

/// @brief Show a TUI for replenishing merchadise in an inventory
/// @param inventory The inventory to replenish merchandise in
void ioopm_TUI_inventory_repelenish_merch(ioopm_inventory_t *inventory);