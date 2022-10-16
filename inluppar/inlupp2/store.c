#include <stdbool.h>
#include "ask.h"
#include "undo.h"
#include "cart.h"
#include "inventory.h"
#include "iterator.h"

void TUI_inventory_list_merch(ioopm_hash_table_t *warehouse) {
    ioopm_list_t *merch_list = ioopm_get_merchandise_list(warehouse);
    ioopm_list_iterator_t *iterator = ioopm_list_iterator(merch_list);
    int size = ioopm_hash_table_size(warehouse);

    printf("\n%d) %s", 1, ((char *)ioopm_iterator_current(iterator).pointer)); 

    bool condition = true;
    for (int j = 1; j < size && condition; ++j) {
        if (j % 20 == 0 && 'Y' != ((char)toupper(*(ask_question_string("\nDo you wish to keep printing merchandise? [y/n]\n"))))) {
            condition = false;
        }
        else if (ioopm_iterator_has_next(iterator)) {
            printf("\n%d) %s", j+1, ((char *)ioopm_iterator_next(iterator).pointer));
        }
        else {
            condition = false;
        }
    }
    ioopm_linked_list_destroy(merch_list);
    ioopm_iterator_destroy(iterator);
}


void TUI_inventory_remove_merch(ioopm_hash_table_t *warehouse) {
    TUI_inventory_list_merch(warehouse);

    char *merch = ask_question_string("\n\nMerchandise to remove:\n");
    if (ioopm_hash_table_lookup(warehouse, (elem_t) { .pointer = merch }, &((elem_t) { .pointer = NULL }))) {
        ioopm_remove_merchandise(warehouse, merch);
    }
    else {
        printf("\n%s does not exist (check spelling)", merch);
    }

    if (!ioopm_hash_table_lookup(warehouse, (elem_t) { .pointer = merch }, &((elem_t) { .pointer = NULL }))) {
        printf("\n%s removed succesfully from warehouse", merch);
    }
    else {
        printf("\nSomething went wrong, try again");
    }
}


void TUI_inventory_edit_merch(ioopm_hash_table_t *warehouse) {
    TUI_inventory_list_merch(warehouse);
    char *merch = ask_question_string("\nMerchandise to edit:\n");

    elem_t result = { .pointer = NULL };
    if (ioopm_hash_table_lookup(warehouse, (elem_t) { .pointer = merch }, &result)) {

        char *new_name = NULL;
        char *new_desc = NULL;
        int new_price = 0;
        char action;

        while (action != 'F') {
            printf(
                "\nChoose what to edit:\n\n"
                "Edit [n]ame\n"
                "Edit [d]escription\n"
                "Edit [p]rice\n"
                "[F]inished editing\n"
                );
            action = (char)(toupper(*(ask_question_string(""))));

            if (action == 'N') {
                new_name = ask_question_string("\nEnter new name:\n");
            }
            else if (action == 'D') {
                new_desc = ask_question_string("\nEnter new description:\n");
            }
            else if (action == 'P') {
                new_price = ask_question_int("\nEnter new price:\n");
            }
            else if (action == 'F') {
                printf("\nMerchandise has been successfully edited.");
            }
            else {
                printf("\nInvalid input\n");
            }
        }
        ioopm_edit_merchandise(warehouse, ((merchandise_t *)result.pointer), new_name, new_desc, new_price);
    }
    else {
        printf("\n%s does not exist (check spelling)", merch);
    }
}


void TUI_inventory_list_stock(ioopm_hash_table_t *warehouse) {
    TUI_inventory_list_merch(warehouse);
    char *merch = ask_question_string("\n\nMerchandise to show stock of:\n");

    elem_t result = { .pointer = NULL };
    if (ioopm_hash_table_lookup(warehouse, (elem_t) { .pointer = merch }, &result)) {
        ioopm_list_t *storage_locations = ((merchandise_t *)result.pointer)->storage_locations;

        if (!ioopm_linked_list_is_empty(storage_locations)) {

            int size = ioopm_linked_list_size(storage_locations);
            ioopm_list_iterator_t *iterator = ioopm_list_iterator(storage_locations);

            printf("\nTotal stock of %s: %d\n\n Stock per shelf:\n\n", ((merchandise_t *)result.pointer)->name, ((merchandise_t *)result.pointer)->total_stock);
            storage_location_t storage_location = *(storage_location_t *)ioopm_iterator_current(iterator).pointer;
            printf("\n%s) %d", storage_location.shelf, storage_location.stock);

            for (int i = 0; i < size; ++i) {
                if (ioopm_iterator_has_next(iterator))
                storage_location = *(storage_location_t *)ioopm_iterator_next(iterator).pointer;
                   printf("\n%s) %d", storage_location.shelf, storage_location.stock);
            }
        }    
    }
    else {
        printf("\n%s does not exist (check spelling)", merch); 
    }
    printf("\n%s is out of stock.", merch);
}


void TUI_inventory_increase_stock(ioopm_hash_table_t *warehouse) {
    TUI_inventory_list_merch(warehouse);
    char *name = ask_question_string("\n\nMerchandise to stock up on");

    elem_t result = { .pointer = NULL };
    if (!ioopm_hash_table_lookup(warehouse, (elem_t) { .pointer = name }, &result)) {
        printf("\n%s does not exits (check spelling)", name);
    }

    // is_shelf funkar inte som den ska

    char *shelf = " ";
    while (!is_shelf(shelf) && !shelf_availible(shelf)) {
        printf("\nShelf format is one capital letter (A-Z) followed by two digits (0-9)");
        shelf = ask_question_string("\nShelf to store in");
    }

    int quantity = 0;
    while(quantity <= 0) {
        printf("\nStock to add must be bigger than 0");
        quantity = ask_question_int("\nAmount of stock to be added");
        }

    ioopm_replenish_stock(warehouse, (merchandise_t *)result.pointer, quantity, shelf);
}

void TUI_cart_add(ioopm_cart_t *cart)
{
    cart_merch_t merch = ioopm_ask_merch();
    ioopm_cart_add(cart, merch);
    bool add_more = ioopm_ask_question_bool("Would you like to add more merchandise?");
    while (add_more)
    {
        cart_merch_t merch = ioopm_ask_merch();
        ioopm_cart_add(cart, merch);
        bool add_more = ioopm_ask_question_bool("Would you like to add more merchandise?");
    }
}

void TUI_cart_remove(ioopm_cart_t *cart)
{
    char *merch_name = ioopm_ask_merch_name(cart);
    int No_merch = ioopm_ask_No_merch(cart, merch_name);
    ioopm_cart_remove(cart, merch_name, No_merch);
    bool remove_more = ioopm_ask_question_bool("Would you like to remove more merchandise?");
    while (remove_more)
    {
        char *merch_name = ioopm_ask_merch_name(cart);
        int No_merch = ioopm_ask_No_merch(cart, merch_name);
        ioopm_cart_remove(cart, merch_name, No_merch);
        bool remove_more = ioopm_ask_question_bool("Would you like to remove more merchandise?");
    }
}

void TUI_cart_get_cost(ioopm_cart_t *cart)
{
    int cost = ioopm_cart_get_cost(cart);
    printf("The cost of all the contents in your cart is %d.%d SEK", cost/100, cost%100);
}

void TUI_cart_list_contents(ioopm_cart_t *cart)
{
    ioopm_list_t *all_merch = ioopm_cart_get_merch(cart);
    ioopm_list_iterator_t *merch_iterator = ioopm_iterator_create(all_merch);
    for (int i = 0; i < ioopm_linked_list_length(all_merch); i++)
    {
        cart_merch_t *current_merch = ioopm_iterator_current(merch_iterator).ptr_v;
        char *name = current_merch->name;
        int pcs = current_merch->pcs;
        printf("%d. %s: %d pcs", i, name, pcs);
        ioopm_iterator_next(merch_iterator);
    }
}

void TUI_inventory_add_merch(ioopm_inventory_t *inventory)
{

}

void TUI_inventory_list_merch(ioopm_inventory_t *inventory)
{

}

void TUI_inventory_remove_merch(ioopm_inventory_t *inventory)
{

}

void TUI_inventory_edit_merch(ioopm_inventory_t *inventory)
{

}

void TUI_inventory_repelenish_merch(ioopm_inventory_t *inventory)
{
    
}

int do_checkout(ioopm_inventory_t *inventory, ioopm_cart_t *cart)
{
    ioopm_list_t *cart_merch = ioopm_cart_get_merch(cart);
    ioopm_inventory_remove_merch_list(inventory, cart_merch);
    ioopm_cart_clear(cart);
    return 0;
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
        "13. Exit the menu.\n";
    
    int[13] admin_options = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
    bool admin_access = ioopm_ask_admin_access();
    while (admin_access)
    {   
        int menu_choice = ioopm_ask_menu(admin_menu, admin_options);
        switch (menu_choice)
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
            TUI_inventory_repelenish_merch(inventory);
            break;

        case 6:
            ioopm_undo_undo(inventory, cart);
            break;

        case 7:
            TUI_cart_add(cart);
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
            return 0;
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
