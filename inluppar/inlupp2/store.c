#include <stdbool.h>
#include <ctype.h>
#include "ask.h"
#include "undo.h"
#include "cart.h"
#include "inventory.h"
#include "iterator.h"

void TUI_inventory_list_merch(ioopm_inventory_t *inventory);
void TUI_cart_list_contents(ioopm_cart_t *cart);

void TUI_cart_add(ioopm_cart_t *cart, ioopm_inventory_t *inventory)
{
    char *merch_name;
    int cost;
    int pieces;
    TUI_inventory_list_merch(inventory);
    ioopm_ask_cart_merch(inventory, &merch_name, &cost, &pieces);
    ioopm_cart_add(cart, merch_name, cost, pieces);
}

void TUI_cart_remove(ioopm_cart_t *cart)
{
    TUI_cart_list_contents(cart);
    char *merch_name = ioopm_ask_existing_cart_merch_name(cart);
    ioopm_cart_remove(cart, merch_name);
    free(merch_name);
}

void TUI_cart_get_cost(ioopm_cart_t *cart)
{
    int cost = ioopm_cart_get_cost(cart);
    printf("The cost of all the contents in your cart is %d.%d SEK\n", cost/100, cost%100);
}

void TUI_cart_list_contents(ioopm_cart_t *cart)
{
    ioopm_list_t *all_merch = ioopm_cart_get_merch(cart);
    if (ioopm_linked_list_is_empty(all_merch))
    {
        printf("\n___Cart is empty___\n\n");
        return;
    }
    
    ioopm_list_iterator_t *merch_iterator = ioopm_list_iterator(all_merch);
    for (int i = 0; i < ioopm_linked_list_size(all_merch); i++)
    {
        cart_merch_t *current_merch = ioopm_iterator_current(merch_iterator).ptr_v;
        char *name = current_merch->name;
        int pcs = current_merch->pcs;
        printf("%d) %s: %d pcs\n", i+1, name, pcs);
        ioopm_iterator_next(merch_iterator);
    }

    ioopm_iterator_destroy(merch_iterator);
}


void TUI_inventory_add_merch(ioopm_inventory_t *inventory) {

    char *name;
    char *desc;
    int price;

    ioopm_ask_new_inventory_merch(inventory->warehouse, &name, &desc, &price);

    ioopm_inventory_add_merchandise(inventory, name, desc, price);

    if (ioopm_hash_table_has_key(inventory->warehouse, (elem_t) { .ptr_v = name })) {
    printf("%s succesfully added to warehouse\n", name);
    }
}

void TUI_inventory_list_merch(ioopm_inventory_t *inventory) {
    ioopm_list_t *merch_list = ioopm_inventory_get_merchandise_list(inventory);
    if (ioopm_linked_list_is_empty(merch_list))
    {
        printf("\n__________The inventory is empty!__________\n\n");
        return;
    }
    
    ioopm_list_iterator_t *iterator = ioopm_list_iterator(merch_list);

    int i = 1;
    while (true)
    {
        char *current_name = ioopm_iterator_current(iterator).ptr_v;
        inventory_merch_t *current_merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = current_name})->ptr_v;
        int current_price = current_merch->price;
        printf("%d) %s %d.%d SEK  %d in stock\n", i, current_name, current_price/100, current_price%100, current_merch->total_stock);
        if (!ioopm_iterator_has_next(iterator)) break;
        ioopm_iterator_next(iterator);
        if (i%20==0)
        {
            char *answer = ioopm_ask_question_string("\nDo you wish to keep printing merchandise? [y/n]\n");
            if (toupper(*answer) != 'Y') break;
        }
        i++;
    }

    ioopm_linked_list_destroy(merch_list);
    ioopm_iterator_destroy(iterator);
}


void TUI_inventory_remove_merch(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);

    char *merch_name = ioopm_ask_existing_inventory_merch(inventory->warehouse);
    ioopm_inventory_remove_merchandise(inventory, merch_name);
    free(merch_name);
}


void TUI_inventory_edit_merch(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);
    if (ioopm_hash_table_is_empty(inventory->warehouse))
    {
        return;
    }
    
    char *old_name = ioopm_ask_existing_inventory_merch(inventory->warehouse);

    char *new_name = NULL;
    char *new_desc = NULL;
    int new_price = 0;
    char action = '\0';

    while (action != 'F') {
        char *choice = 
            "\nChoose what to edit:\n\n"
            "Edit [n]ame\n"
            "Edit [d]escription\n"
            "Edit [p]rice\n"
            "[F]inished editing";
        char *str = ioopm_ask_question_string(choice);
        action = toupper(*str);
        switch (action)
        {
        case 'N':
            new_name = ioopm_ask_question_string("\nEnter new name:\n");
            break;
        
        case 'D':
            new_desc = ioopm_ask_question_string("\nEnter new description:\n");
            break;
        case 'P':
            new_price = ioopm_ask_question_int("\nEnter new price:\n");
            break;
        case 'F':
            printf("\nMerchandise has been successfully edited.\n");
            break;
        default:
            printf("\nInvalid input\n");
            break;
        }
        free(str);
    }
    ioopm_inventory_edit_merchandise(inventory, old_name, new_name, new_desc, new_price);
    free(old_name);
}

static void show_detailed_stock(ioopm_inventory_t *inventory, char *merch_name)
{
    ioopm_list_t *storage_locations = ioopm_inventory_storage_locations_merch(inventory, merch_name);

    if (!ioopm_linked_list_is_empty(storage_locations)) {

        ioopm_list_iterator_t *iterator = ioopm_list_iterator(storage_locations);

        printf("\nTotal stock of %s: %d\n\nStock per shelf:\n", merch_name, ioopm_inventory_get_stock(inventory, merch_name));

        while (true)
        {
            storage_location_t storage_location = *(storage_location_t *)ioopm_iterator_current(iterator).ptr_v;
            printf("%s) %d\n", storage_location.shelf, storage_location.stock);
            if (!ioopm_iterator_has_next(iterator)) break;
            ioopm_iterator_next(iterator);
        }
        ioopm_iterator_destroy(iterator);
    }
    else
    {
        printf("\n%s is out of stock.\n", merch_name);
    }

    ioopm_linked_list_destroy(storage_locations);

}


void TUI_inventory_show_stock(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);
    if (ioopm_hash_table_is_empty(inventory->warehouse)) return;
    char *merch_name = ioopm_ask_existing_inventory_merch(inventory->warehouse);

    show_detailed_stock(inventory, merch_name);
    
    free(merch_name);
}


void TUI_inventory_replenish_stock(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);
    if (ioopm_hash_table_is_empty(inventory->warehouse)) return;
    char *merch_name = ioopm_ask_existing_inventory_merch(inventory->warehouse);

    char *new_or_old = ioopm_ask_question_string("Would you like to add merchandise to a new shelf?");

    if (toupper(*new_or_old) == 'Y')
    {
        char *shelf = ioopm_ask_new_shelf(inventory->used_shelves);
        int amount = ioopm_ask_question_u_int("How many of the merchandise would you like to add?");
        ioopm_inventory_replenish_new_shelf_stock(inventory, merch_name, amount, shelf);
    }
    else
    {
        char *shelf = ioopm_ask_old_shelf(inventory->used_shelves);
        int amount = ioopm_ask_question_u_int("How many of the merchandise would you like to add?");
        ioopm_inventory_replenish_existing_shelf_stock(inventory, merch_name, amount, shelf);
        free(merch_name);
        free(shelf);
    }
    free(new_or_old);
}

void TUI_inventory_unstock(ioopm_inventory_t *inventory)
{
    char *merch_name = ioopm_ask_existing_inventory_merch(inventory->warehouse);
    show_detailed_stock(inventory, merch_name);
    printf("Which shelf would you like to remove %s from?\n", merch_name);
    char *shelf = ioopm_ask_old_shelf(inventory->used_shelves);
    int amount = ioopm_ask_No_stock(inventory, merch_name, shelf);
    ioopm_inventory_unstock(inventory, merch_name, amount, shelf);
    free(shelf);
    free(merch_name);
}


int do_checkout(ioopm_inventory_t *inventory, ioopm_cart_t *cart)
{
    ioopm_list_t *cart_merch = ioopm_cart_get_merch(cart);
    //TODO remove from inventory
    ioopm_cart_clear(cart);
    return 0;
}

bool int_eq_fun(elem_t a, elem_t b)
{
    return a.int_v == b.int_v;
}

int event_loop(ioopm_inventory_t *inventory, ioopm_cart_t *cart)
{
    char *admin_menu =
        "-----------------Admin menu-----------------\n"
        "Please chose an option by typing its number:\n"
        "1. Add a merchandise to the inventory.\n"
        "2. List all merchandise in the inventory.\n"
        "3. Remove merchandise from the inventory.\n"
        "4. Edit merchandise in the inventory.\n"
        "5. Replenish merchandise in the inventory.\n"
        "6. Undo the previous action.\n"
        "7. Add merchandise to your cart.\n"
        "8. Remove merchandise from your cart.\n"
        "9. Get the cost of your cart's contents.\n"
        "10. List the cart's contents.\n"
        "11. CLear the cart's contents.\n"
        "12. Checkout your cart.\n"
        "13. Exit the menu.\n"
        "14. Show detailed stock of merchandise.\n"
        "15. Remove merchandise from stock.\n";
    
    ioopm_list_t *admin_options = ioopm_linked_list_create(int_eq_fun);
    for (int i = 1; i < 15; i++)
    {
        ioopm_linked_list_append(admin_options, (elem_t) {.int_v = i});
    }
      
    bool admin_access = ioopm_ask_admin_access(inventory->password);
    while (admin_access)
    {   
        switch (ioopm_ask_menu(admin_menu, admin_options))
        {
        case 1:
            TUI_inventory_add_merch(inventory);
            break;
        
        case 2:
            TUI_inventory_list_merch(inventory);
            break;

        case 3:
            TUI_inventory_remove_merch(inventory);
            break;

        case 4:
            TUI_inventory_edit_merch(inventory);
            break;

        case 5:
            TUI_inventory_replenish_stock(inventory);
            break;

        case 6:
            ioopm_undo_undo(inventory, cart);
            break;

        case 7:
            TUI_cart_add(cart, inventory);
            break;

        case 8:
            TUI_cart_remove(cart);
            break;

        case 9:
            TUI_cart_get_cost(cart);
            break;

        case 10:
            TUI_cart_list_contents(cart);
            break;

        case 11:
            ioopm_cart_clear(cart);
            break;

        case 12:
            do_checkout(inventory, cart);
            break;

        case 13:
            ioopm_linked_list_destroy(admin_options);
            return 0;

        case 14:
            TUI_inventory_show_stock(inventory);
            break;

        case 15:
            TUI_inventory_unstock(inventory);
            break;
        }
    }
/*
    char *user_menu =
        "------------------User menu------------------\n"
        "Please chose an option by typing its number:\n"
        "1. Add merchandise to your cart.\n"
        "3. Remove merchandise from your cart.\n"
        "4. Get the cost of your cart's contents.\n"
        "5. List the cart's contents.\n"
        "6. CLear the cart's contents.\n"
        "7. Checkout your cart.\n"
    
    char* user_options = "123456789";

    bool user_access = ioopm_ask_user_access();

    while (user_access)
    {
        char menu_choice = ioopm_ask_menu(user_menu, user_options);
        switch (menu_choice)
        {
        case 1:
            TUI_cart_add(cart);
            break;

        case 2:
            TUI_inventory_list_merch(inventory);
            break;

        case 3:
            TUI_cart_remove(cart);
            break;

        case 4:
            TUI_cart_get_cost(cart);
            break;

        case 5:
            TUI_cart_list_contents(cart);
            break;

        case 6:
            ioopm_cart_clear(cart);
            break;

        case 7:
            do_checkout(inventory, cart);
            break;
        
        case 8:
            ioopm_undo_undo(inventory, cart);
            break;

        case 9:
            return 0;
        }
    } */
    return 1;
}

int main(void)
{
    ioopm_inventory_t *inventory = ioopm_inventory_load();
    ioopm_cart_t *cart = ioopm_cart_create();

    if (event_loop(inventory, cart)==1) return 1;

    ioopm_inventory_save(inventory);
    ioopm_cart_destroy(cart);
    return 0; 
}
