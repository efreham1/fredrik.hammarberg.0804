#pragma once
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"

// Warehouse / Cart logic in separate modules

/*
 * @file bakend.h
 * @author Joel Holmberg, Fredrik Hammarberg
 * @date 12 Oct 2022
 * @brief Simple webstore backend for managing stock, merchandise and storage location in a warehouse.
 *
 * Header file provides definitions and documentation for all the functions that 
 * creates/operates on/destroys merchandise and stock.
 *
 * @see https://uppsala.instructure.com/courses/68435/assignments/130156
 */

typedef struct merch merchandise_t;
typedef struct storage_location storage_location_t;


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

/// @brief add merchandise to warehouse 
/// @param warehouse hash table that represents the warehouse
/// @param name name of merchandise
/// @param desc description of merchandise
/// @param price price of merchandise
void ioopm_add_merchandise(ioopm_hash_table_t *warehouse, char *name, char *desc, int price);

/// @brief puts all available merchandise in a linked list
/// @param warehouse hash table to retrieve merchandise from
/// @return A linked list containing all merchandise
ioopm_list_t *ioopm_get_merchandise_list(ioopm_hash_table_t *warehouse);

/// @brief removes a piece of merchandise from the warehouse
/// @param warehouse warehouse to remove merchandise from
/// @param merch key of merchandise to be removed
void ioopm_remove_merchandise(ioopm_hash_table_t *warehouse, char *key);

/// @brief allows the user to edit the information of a piece of merchandise
/// @param merch merchandise to edit
/// @param new_name new name for merchandise or NULL
/// @param new_desc new description for merchandise or NULL
/// @param new_price new price of merchandise or NULL
void ioopm_edit_merchandise(ioopm_hash_table_t *warehouse, merchandise_t *merch ,char *new_name, char *new_desc, int new_price);


/// @brief replenishes stock of merchandise
/// @param warehouse hash table to operate on
/// @param merch piece of merchandise to replenish stock of
/// @param quantity amount to restock merchandise with
void ioopm_replenish_stock(ioopm_hash_table_t *warehouse, merchandise_t *merch, int quantity, char *shelf);