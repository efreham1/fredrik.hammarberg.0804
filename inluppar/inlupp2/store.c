#include <stdbool.h>
#include "ask.h"
#include "undo.h"
#include "cart.h"
#include "inventory.h"
#include "iterator.h"


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


void TUI_inventory_add_merch(ioopm_inventory_t *inventory) {

    char *name;
    char *desc;
    int price;

    ask_new_inventory_merch(inventory->warehouse, &name, &desc, &price);

    ioopm_inventory_add_merchandise(inventory, name, desc, price);

    if (ioopm_hash_table_has_key(inventory->warehouse, (elem_t) { .ptr_v = name })) {
    printf("\n%s succesfully added to warehouse", name);
    }
    
}

void TUI_inventory_list_merch(ioopm_inventory_t *inventory) {
    ioopm_list_t *merch_list = ioopm_inventory_get_merchandise_list(inventory);
    ioopm_list_iterator_t *iterator = ioopm_list_iterator(merch_list);

    int i = 1;
    while (true)
    {
        printf("\n%d) %s", i, ((char *)ioopm_iterator_current(iterator).ptr_v));
        if (!ioopm_iterator_has_next(iterator)) break;
        ioopm_iterator_next(iterator);
        if (i%20)
        {
            char answer = toupper(*(ask_question_string("\nDo you wish to keep printing merchandise? [y/n]\n")));
            if (answer != 'Y') break;
        }
        i++;
    }

    ioopm_linked_list_destroy(merch_list);
    ioopm_iterator_destroy(iterator);
}


void TUI_inventory_remove_merch(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);

    char *merch_name = ask_existing_inventory_merch(inventory->warehouse);
    ioopm_inventory_remove_merchandise(inventory, merch_name);
}


void TUI_inventory_edit_merch(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);
    char *old_name = ask_existing_inventory_merch(inventory->warehouse);

    elem_t result = { .ptr_v = NULL };

    char *new_name = NULL;
    char *new_desc = NULL;
    int new_price = 0;
    char action;

    while (action != 'F') {
        char *choice = 
            "\nChoose what to edit:\n\n"
            "Edit [n]ame\n"
            "Edit [d]escription\n"
            "Edit [p]rice\n"
            "[F]inished editing\n"
            ;
        switch ((char)(toupper(*(ask_question_string("choice")))))
        {
        case 'N':
            new_name = ask_question_string("\nEnter new name:\n");
            break;
        
        case 'D':
            new_desc = ask_question_string("\nEnter new description:\n");
            break;
        case 'P':
            new_price = ask_question_int("\nEnter new price:\n");
            break;
        case 'F':
            printf("\nMerchandise has been successfully edited.");
            break;
        default:
            printf("\nInvalid input\n");
            break;
        }
    }
    ioopm_inventory_edit_merchandise(inventory, old_name, new_name, new_desc, new_price);
}


void TUI_inventory_show_stock(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);
    char *merch_name = ask_existing_inventory_merch(inventory->warehouse);

        ioopm_list_t *storage_locations = ioopm_inventory_storage_locations_merch(inventory, merch_name);

        if (!ioopm_linked_list_is_empty(storage_locations)) {

            int size = ioopm_linked_list_size(storage_locations);
            ioopm_list_iterator_t *iterator = ioopm_list_iterator(storage_locations);

            printf("\nTotal stock of %s: %d\n\n Stock per shelf:\n\n", merch_name, ioopm_inventory_get_stock(inventory, merch_name));

            while (true)
            {
                storage_location_t storage_location = *(storage_location_t *)ioopm_iterator_current(iterator).ptr_v;
                printf("\n%s) %d", storage_location.shelf, storage_location.stock);
                if (!ioopm_iterator_has_next(iterator)) break;
                ioopm_iterator_has_next(iterator);
            }
            
        }
        else
        {
            printf("\n%s is out of stock.", merch_name);
        }
}


void TUI_inventory_replenish_stock(ioopm_inventory_t *inventory) {
    TUI_inventory_list_merch(inventory);
    char *merch_name = ask_existing_inventory_merch(inventory->warehouse);

    // is_shelf funkar inte som den ska

    char *shelf = ask_shelf();

    int quantity = ask_question_u_int("How much stock would you like to replenish with?");

    ioopm_inventory_replenish_stock(inventory, merch_name, quantity, shelf);
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
    
    int admin_options[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
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
