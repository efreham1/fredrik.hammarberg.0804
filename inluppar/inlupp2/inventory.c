#include "inventory.h"
#include <stdlib.h>
#include <string.h>



static bool string_compare_function(elem_t e1, elem_t e2) {
  char *str1 = ((char *)e1.pointer);
  char *str2 = ((char *)e2.pointer);

  return strcmp(str1, str2) == 0;
}


static merchandise_t *create_merchandise(char *name, char *desc, int price) {
    merchandise_t *merch = calloc(1, sizeof(merchandise_t));
    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->total_stock = 0;
    merch->storage_locations = ioopm_linked_list_create(string_compare_function);
    return merch;
}


void ioopm_add_merchandise(ioopm_hash_table_t *warehouse, char *name, char *desc, int price) {
    merchandise_t *merch = create_merchandise(name, desc, price);

    elem_t key = { .pointer = name };
    elem_t value = { .pointer = merch };
    ioopm_hash_table_insert(warehouse, key, value);
}


ioopm_list_t *ioopm_get_merchandise_list(ioopm_hash_table_t *warehouse) {
    return ioopm_hash_table_keys(warehouse);
}


void ioopm_remove_merchandise(ioopm_hash_table_t *warehouse, char *merch) {
    elem_t key = { .pointer = merch };
    ioopm_hash_table_remove(warehouse, key);
}


void ioopm_edit_merchandise(ioopm_hash_table_t *warehouse, merchandise_t *merch, char *new_name, char *new_desc, int new_price) {
    if (new_name || new_desc || new_price != 0) {
        char *key = merch->name;

        char *name = new_name ? new_name : key;
        char *desc = new_desc ? new_desc : merch->desc;
        int price = new_price != 0 ? new_price : merch->price;
        int total_stock = merch->total_stock;
        ioopm_list_t *storage_locations = merch->storage_locations;

        merchandise_t *updated_merch = create_merchandise(name, desc, price);
        updated_merch->total_stock = total_stock;
        updated_merch->storage_locations = storage_locations;

        ioopm_remove_merchandise(warehouse, key);
        ioopm_hash_table_insert(warehouse, (elem_t) { .pointer = name }, (elem_t) { .pointer = updated_merch });
    }
    else {
        return;
    }
}

// seg fault
void ioopm_replenish_stock(ioopm_hash_table_t *warehouse, merchandise_t *merch, int quantity, char *shelf) {
    ioopm_list_t *storage_locations = merch->storage_locations;
    ioopm_list_iterator_t *iterator = ioopm_list_iterator(storage_locations);

    if (strcmp(((char *)((storage_location_t *)(ioopm_iterator_current(iterator).pointer))->shelf), shelf) == 0) {
        // test if change to quantity is visible when listing stock
        ((storage_location_t *)ioopm_iterator_current(iterator).pointer)->stock += quantity;
    }
    else {

    }
}