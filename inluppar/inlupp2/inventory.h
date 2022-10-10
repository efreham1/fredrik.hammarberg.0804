#include "hash_table.h"
#include "merch.h"

#pragma once

typedef struct inventory ioopm_inventory_t;

/// @brief Save an inventory to file and destroy the one in memory
/// @param inventory The inventory to be saved
void ioopm_inventory_save(ioopm_inventory_t *inventory);

/// @brief Load an inventory from file and place it in memory
/// @return The loaded inventory
ioopm_inventory_t *ioopm_inventory_load();

/// @brief Remove all merch listed in a hash table from inventory
/// @param inventory The inventory to remove from
/// @param contents The contents to remove
void ioopm_inventory_remove_merch_hash_table(ioopm_inventory_t *inventory, ioopm_hash_table_t *contents);