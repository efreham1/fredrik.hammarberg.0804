#include "inventory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "general_TUI.h"
#include "hash_table_internal.h"
#include "linked_list_internal.h"


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
    free(merch);
}

void ioopm_inventory_remove_merchandise(ioopm_inventory_t *inventory, char *merch_name) {
    elem_t key = { .ptr_v = merch_name };
    elem_t merch = ioopm_hash_table_remove(inventory->warehouse, key);
    free_merch(key, &merch, NULL);
    ioopm_linked_list_remove(inventory->used_shelves,ioopm_linked_list_get_index(inventory->used_shelves, key));
}


void ioopm_inventory_edit_merchandise(ioopm_inventory_t *inventory, char *merch_name, char *new_name, char *new_desc, int new_price) {
    inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v;
    if (new_name || new_desc || new_price != 0) {
        char *key = merch_name;

        char *name = new_name ? new_name : strdup(key);
        char *desc = new_desc ? new_desc : strdup(merch->desc);
        int price = new_price != 0 ? new_price : merch->price;
        int total_stock = merch->total_stock;
        ioopm_list_t *storage_locations = merch->storage_locations;

        inventory_merch_t *updated_merch = create_merchandise(name, desc, price);
        updated_merch->total_stock = total_stock;
        ioopm_linked_list_destroy(updated_merch->storage_locations);
        updated_merch->storage_locations = ioopm_linked_list_copy(storage_locations);

        ioopm_inventory_remove_merchandise(inventory, key);
        ioopm_hash_table_insert(inventory->warehouse, (elem_t) { .ptr_v = name }, (elem_t) { .ptr_v = updated_merch });
    }
    else {
        return;
    }
}


void ioopm_inventory_replenish_existing_shelf_stock(ioopm_inventory_t *inventory, char *merch_name, int quantity, char *shelf) { 
    inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v;
    ioopm_list_t *storage_locations = merch->storage_locations;
    ioopm_list_iterator_t *iterator = ioopm_list_iterator(storage_locations);

    while ((strcmp(((char *)((storage_location_t *)(ioopm_iterator_current(iterator).ptr_v))->shelf), shelf) != 0)) {
        ioopm_iterator_next(iterator);
    }

    ((storage_location_t *)ioopm_iterator_current(iterator).ptr_v)->stock += quantity;
    merch->total_stock += quantity;
    ioopm_iterator_destroy(iterator);
}


void ioopm_inventory_replenish_new_shelf_stock(ioopm_inventory_t *inventory, char *merch_name, int quantity, char *shelf) {
    inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = merch_name})->ptr_v;
    ioopm_list_t *storage_locations = merch->storage_locations;
    
    storage_location_t *new_shelf = calloc(1, sizeof(storage_location_t));
    new_shelf->shelf = shelf;
    new_shelf->stock = quantity;
    
    ioopm_linked_list_append(storage_locations, (elem_t) { .ptr_v = new_shelf });
    ioopm_linked_list_append(inventory->used_shelves, (elem_t) {.ptr_v = shelf});
    merch->total_stock += quantity;
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

static bool string_lt(elem_t e1, elem_t e2)
{
  return (strcmp(e1.ptr_v, e2.ptr_v) < 0);
}

static int get_password(void)
{
    FILE *f = fopen("password.txt", "r");
    
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);
    assert(is_number(buf));

    fclose(f);

    int password = atoi(buf);
    free(buf);
    return password;
}

static int get_str_len_file(FILE *f)
{
    int len = 0;
    char buf = '0';
    while (buf != '\0')
    {
        fread(&buf, sizeof(char), 1, f);
        len++;
    }
    fseek(f, -len*sizeof(char), SEEK_CUR);
    return len;
}

static void save_storage_locs_to_file(ioopm_list_t *storage_locations, FILE *f)
{
    ioopm_linked_list_save_to_file(storage_locations, f);
    ll_entry_t *curr_entry = storage_locations->head;
    while (curr_entry)
    {
        fwrite(curr_entry->value.ptr_v, sizeof(storage_location_t), 1, f);
        char *shelf = ((storage_location_t *) curr_entry->value.ptr_v)->shelf;
        fwrite(shelf, sizeof(char), strlen(shelf)+1, f);
        curr_entry = curr_entry->next;
    }
}

static ioopm_list_t *load_storage_locs_from_file(FILE *f)
{
    ioopm_list_t *list = ioopm_linked_list_load_from_file(f, string_compare_function);
    ll_entry_t *curr_entry = list->head;
    while (curr_entry)
    {
        storage_location_t *sto_loc = calloc(1, sizeof(storage_location_t));
        fread(sto_loc, sizeof(storage_location_t), 1, f);
        curr_entry->value.ptr_v = sto_loc;
        int str_len = get_str_len_file(f);
        char *shelf = calloc(str_len, sizeof(char));
        fread(shelf, sizeof(char), str_len, f);
        ((storage_location_t *) curr_entry->value.ptr_v)->shelf = shelf;
        curr_entry = curr_entry->next;
    }
    return list;
}

static void save_merch_to_file(inventory_merch_t *merch, FILE *f)
{
    fwrite(merch, sizeof(inventory_merch_t), 1, f);
    fwrite(merch->name, sizeof(char), strlen(merch->name)+1, f);
    fwrite(merch->desc, sizeof(char), strlen(merch->desc)+1, f);
    save_storage_locs_to_file(merch->storage_locations, f);
}

inventory_merch_t *load_merch_from_file(FILE *f)
{
    inventory_merch_t *merch = calloc(1, sizeof(inventory_merch_t));
    fread(merch, sizeof(inventory_merch_t), 1, f);
    int str_len = get_str_len_file(f);
    char *name = calloc(str_len, sizeof(char));
    fread(name, sizeof(char), str_len, f);
    merch->name = name;
    int str_len2 = get_str_len_file(f);
    char *desc = calloc(str_len2, sizeof(char));
    fread(desc, sizeof(char), str_len2, f);
    merch->desc = desc;
    merch->storage_locations = load_storage_locs_from_file(f);
    return merch;
}

void ioopm_inventory_save(ioopm_inventory_t *inventory)
{
    FILE *f = fopen("inventory.bin", "wb");

    ioopm_hash_table_save_to_file(inventory->warehouse, f);

    for (int i = 0; i < inventory->warehouse->number_of_buckets; i++)
    {
        ht_entry_t *current_entry = inventory->warehouse->buckets[i].next;
        while (current_entry != NULL)
        {
            save_merch_to_file(current_entry->value.ptr_v, f);
            current_entry = current_entry->next;
        }
    }

    ioopm_linked_list_save_to_file(inventory->used_shelves, f);
    ll_entry_t *curr_entry = inventory->used_shelves->head;
    while (curr_entry)
    {
        char *shelf = curr_entry->value.ptr_v;
        fwrite(shelf, sizeof(char), strlen(shelf)+1, f);
        curr_entry = curr_entry->next;
    }


    fclose(f);

    ioopm_hash_table_apply_to_all(inventory->warehouse, free_merch, NULL);
    ioopm_hash_table_destroy(inventory->warehouse);
    ioopm_linked_list_destroy(inventory->used_shelves);
    free(inventory);
}

ioopm_inventory_t *ioopm_inventory_load()
{
    FILE *f = fopen("inventory.bin", "rb");

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    bool is_empty = size == 0;
    fseek(f, 0, SEEK_SET);

    if (is_empty)
    {
        ioopm_inventory_t *inventory = calloc(1, sizeof(ioopm_inventory_t));
        inventory->warehouse = ioopm_hash_table_create_spec(0.75, 50, string_sum_hash, string_compare_function, merch_compare_function, string_lt);
        inventory->used_shelves = ioopm_linked_list_create(string_compare_function);
        inventory->password = get_password();

        return inventory;
    }
    

    ioopm_inventory_t *inventory = calloc(1, sizeof(ioopm_inventory_t));
    inventory->warehouse = ioopm_hash_table_load_from_file(f, string_sum_hash, string_compare_function, merch_compare_function, string_lt);

    for (int i = 0; i < inventory->warehouse->number_of_buckets; i++)
    {
        ht_entry_t *current_entry = inventory->warehouse->buckets[i].next;
        while (current_entry != NULL)
        {
            current_entry->value.ptr_v = load_merch_from_file(f);
            current_entry->key.ptr_v = ((inventory_merch_t *) current_entry->value.ptr_v)->name;
            current_entry = current_entry->next;
        }
    }

    inventory->used_shelves = ioopm_linked_list_load_from_file(f, string_compare_function);

    ll_entry_t *curr_entry = inventory->used_shelves->head;
    while (curr_entry)
    {
        int str_len = get_str_len_file(f);
        char *shelf = calloc(str_len, sizeof(char));
        fread(shelf, sizeof(char), str_len, f);
        curr_entry->value.ptr_v = shelf;
        curr_entry = curr_entry->next;
    }

    inventory->password = get_password();

    return inventory;
}

void ioopm_inventory_unstock(ioopm_inventory_t *inventory, char *merch_name, int amount, void *shelf)
{
    
}