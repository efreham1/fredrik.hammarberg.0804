#pragma once
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"

// Warehouse / Cart logic in separate modules

/*
 * @file inventory.h
 * @author Joel Holmberg, Fredrik Hammarberg
 * @date 19 Oct 2022
 * @brief Simple webstore backend for managing stock, merchandise and storage location in a warehouse.
 *
 * Header file provides definitions and documentation for all the functions that 
 * creates/operates on/destroys merchandise and stock.
 *
 * @see https://uppsala.instructure.com/courses/68435/assignments/130156
 */

typedef struct merch inventory_merch_t;
typedef struct storage_location storage_location_t;
typedef struct inventory ioopm_inventory_t;

struct storage_location {
    char *shelf;
    int stock;
};

struct merch {
    char *name;
    char *desc;
    int price;
    int total_stock;
    ioopm_list_t *storage_locations; 
};

struct inventory {
    ioopm_hash_table_t *warehouse;
    ioopm_list_t *used_shelves;
};

/// @brief add merchandise to warehouse 
/// @param warehouse hash table that represents the warehouse
/// @param name name of merchandise
/// @param desc description of merchandise
/// @param price price of merchandise
void ioopm_inventory_add_merchandise(ioopm_inventory_t *inventory, char *name, char *desc, int price);

/// @brief puts all available merchandise in a linked list
/// @param warehouse hash table to retrieve merchandise from
/// @return A linked list containing all merchandise
ioopm_list_t *ioopm_inventory_get_merchandise_list(ioopm_inventory_t *inventory);

/// @brief removes a piece of merchandise from the warehouse
/// @param warehouse warehouse to remove merchandise from
/// @param merch key of merchandise to be removed
void ioopm_inventory_remove_merchandise(ioopm_inventory_t *inventory, char *merch_name);

/// @brief allows the user to edit the information of a piece of merchandise
/// @param merch merchandise to edit
/// @param new_name new name for merchandise or NULL
/// @param new_desc new description for merchandise or NULL
/// @param new_price new price of merchandise or NULL
void ioopm_inventory_edit_merchandise(ioopm_inventory_t *inventory, char *merch_name ,char *new_name, char *new_desc, int new_price);

/// @brief replenishes stock of merchandise on an existing shelf
/// @param warehouse hash table to operate on
/// @param merch piece of merchandise to replenish stock of
/// @param quantity amount to restock merchandise with
void ioopm_inventory_replenish_existing_shelf_stock(ioopm_inventory_t *inventory, char *merch_name, int quantity, char *shelf);

/// @brief replenishes stock of merchandise on a new shelf
/// @param warehouse hash table to operate on
/// @param merch piece of merchandise to replenish stock of
/// @param quantity amount to restock merchandise with
void ioopm_inventory_replenish_new_shelf_stock(ioopm_inventory_t *inventory, char *merch_name, int quantity, char *shelf);

ioopm_list_t *ioopm_inventory_storage_locations_merch(ioopm_inventory_t *inventory, char *merch_name);

int ioopm_inventory_get_stock(ioopm_inventory_t *inventory, char *merch_name);

ioopm_inventory_t *ioopm_inventory_load();

void ioopm_inventory_save(ioopm_inventory_t *inventory);