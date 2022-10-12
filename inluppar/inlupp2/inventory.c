#include "undo.h"
#include "inventory.h"

struct inventory
{
    int number;
};


void ioopm_inventory_save(ioopm_inventory_t *inventory)
{

}

ioopm_inventory_t *ioopm_inventory_load(void)
{
    ioopm_inventory_t *inventory = calloc(1, sizeof(ioopm_inventory_t));
    return inventory;
}

void ioopm_inventory_remove_merch_list(ioopm_inventory_t *inventory, ioopm_list_t *contents)
{

}