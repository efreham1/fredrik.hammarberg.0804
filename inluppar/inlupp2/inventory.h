#include "hash_table.h"
#include "merch.h"

#pragma once

typedef struct inventory ioopm_inventory_t;


void ioopm_inventory_save(ioopm_inventory_t *inventory);

ioopm_inventory_t *ioopm_inventory_load(void);

void ioopm_inventory_remove_merch_hash_table(ioopm_hash_table_t *contents);