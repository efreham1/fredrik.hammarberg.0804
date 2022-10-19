#include "inventory.h"
#include <stdlib.h>
#include <string.h>


static bool string_compare_function(elem_t e1, elem_t e2) {
  char *str1 = ((char *)e1.ptr_v);
  char *str2 = ((char *)e2.ptr_v);

  return strcmp(str1, str2) == 0;
}


static inventory_merch_t *create_merchandise(char *name, char *desc, int price) {
    inventory_merch_t *merch = calloc(1, sizeof(inventory_merch_t));
    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->total_stock = 0;
    merch->storage_locations = ioopm_linked_list_create(string_compare_function);
    return merch;
}


void ioopm_inventory_add_merchandise(ioopm_inventory_t *inventory, char *name, char *desc, int price) {
    inventory_merch_t *merch = create_merchandise(name, desc, price);

    elem_t key = { .ptr_v = name };
    elem_t value = { .ptr_v = merch };
    ioopm_hash_table_insert(inventory->warehouse, key, value);
}


ioopm_list_t *ioopm_inventory_get_merchandise_list(ioopm_inventory_t *inventory) {
    return ioopm_hash_table_keys(inventory->warehouse);
}

void free_storage_locations(elem_t *value, void *extra)
{
    storage_location_t *st_loc = value->ptr_v;
    free(st_loc->shelf);
    free(st_loc);
}

void free_merch(elem_t key, elem_t *value, void *extra)
{
    inventory_merch_t *merch = value->ptr_v;
    free(merch->name);
    free(merch->desc);
    ioopm_linked_list_apply_to_all(merch->storage_locations, free_storage_locations, NULL);
    ioopm_linked_list_destroy(merch->storage_locations);
}

void ioopm_inventory_remove_merchandise(ioopm_inventory_t *inventory, char *merch_name) {
    elem_t key = { .ptr_v = merch_name };
    elem_t merch = ioopm_hash_table_remove(inventory->warehouse, key);
    free_merch(key, &merch, NULL);
}


void ioopm_inventory_edit_merchandise(ioopm_inventory_t *inventory, char *merch_name, char *new_name, char *new_desc, int new_price) {
    inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v;
    if (new_name || new_desc || new_price != 0) {
        char *key = merch_name;

        char *name = new_name ? new_name : key;
        char *desc = new_desc ? new_desc : merch->desc;
        int price = new_price != 0 ? new_price : merch->price;
        int total_stock = merch->total_stock;
        ioopm_list_t *storage_locations = merch->storage_locations;

        inventory_merch_t *updated_merch = create_merchandise(name, desc, price);
        updated_merch->total_stock = total_stock;
        updated_merch->storage_locations = storage_locations;

        ioopm_inventory_remove_merchandise(inventory, key);
        ioopm_hash_table_insert(inventory->warehouse, (elem_t) { .ptr_v = name }, (elem_t) { .ptr_v = updated_merch });
    }
    else {
        return;
    }
}

// seg fault
void ioopm_inventory_replenish_stock(ioopm_inventory_t *inventory, char *merch_name, int quantity, char *shelf) {
    inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v;
    ioopm_list_t *storage_locations = merch->storage_locations;
    ioopm_list_iterator_t *iterator = ioopm_list_iterator(storage_locations);

    if (strcmp(((char *)((storage_location_t *)(ioopm_iterator_current(iterator).ptr_v))->shelf), shelf) == 0) {
        // test if change to quantity is visible when listing stock
        ((storage_location_t *)ioopm_iterator_current(iterator).ptr_v)->stock += quantity;
    }
}

ioopm_list_t *ioopm_inventory_storage_locations_merch(ioopm_inventory_t *inventory, char *merch_name)
{
    return ((inventory_merch_t *) ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v)->storage_locations;
}

int ioopm_inventory_get_stock(ioopm_inventory_t *inventory, char *merch_name)
{
    return ((inventory_merch_t *) ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v)->total_stock;
}

static int string_sum_hash(elem_t e, int buckets) {
  char *name = ((char *)e.ptr_v);
  int result = 0;
  do
    {
      result += *name;
    }
  while (*++name != '\0');
  return abs(result%buckets);
}

static bool merch_compare_function(elem_t e1, elem_t e2) {
  char *str1 = (char *) ((inventory_merch_t *)e1.ptr_v)->name;
  char *str2 = (char *) ((inventory_merch_t *)e2.ptr_v)->name;

  return strcmp(str1, str2) == 0;
}

bool string_lt(elem_t e1, elem_t e2)
{
  return (strcmp(e1.ptr_v, e2.ptr_v) < 0);
}

ioopm_inventory_t *ioopm_inventory_load()
{
ioopm_inventory_t *inventory = calloc(1, sizeof(ioopm_inventory_t));
inventory->warehouse = ioopm_hash_table_create_spec(0.75, 50, string_sum_hash, string_compare_function, merch_compare_function, string_lt);
inventory->used_shelves = ioopm_linked_list_create(string_compare_function);

return inventory;
}

void ioopm_inventory_save(ioopm_inventory_t *inventory)
{
// free hash table/linked list and all their contents
}