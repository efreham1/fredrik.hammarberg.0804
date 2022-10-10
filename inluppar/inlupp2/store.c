#include <stdbool.h>
#include "cart.h"
#include "ask.h"

int do_checkout(ioopm_inventory_t *inventory, ioopm_cart_t *cart)
{
    ioopm_hash_table_t *cart_merch = ioopm_cart_get_merch(cart);
    ioopm_inventory_remove_merch_list(cart_merch);
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
        "7. Exit the menu.\n";
    
    char* admin_options = "1234567";
    bool admin_access = ioopm_ask_admin_access();
    while (admin_access)
    {   
        char menu_choice = ioopm_ask_menu(admin_menu, admin_options);
        switch (menu_choice)
        {
        case 1:
            ioopm_inventory_add_merch(inventory);
            break;
        
        case 2:
            ioopm_inventory_list_merch(inventory);
            break;

        case 3:
            ioopm_inventory_remove_merch(inventory);
            break;

        case 4:
            ioopm_inventory_edit_merch(inventory);
            break;

        case 5:
            ioopm_inventory_repelenish_merch(inventory);
            break;

        case 6:
            ioopm_undo(inventory, cart);
            break;

        case 7:
            return 0;
        }
    }

    char *user_menu =
        "------------------User menu------------------\n"
        "Please chose an option by typing its number:\n"
        "1. Add merchandise to your cart.\n"
        "2. List all merchandise in the store.\n"
        "3. Remove merchandise from your cart.\n"
        "4. Get the cost of your cart's contents.\n"
        "5. List the cart's contents.\n"
        "6. CLear the cart's contents.\n"
        "7. Checkout your cart.\n"
        "8. Undo the previous action.\n"
        "9. Exit the menu.\n";
    
    char* user_options = "123456789";

    bool user_access = ioopm_ask_user_access();

    while (user_access)
    {
        char menu_choice = ioopm_ask_menu(user_menu, user_options);
        switch (menu_choice)
        {
        case 1:
            ioopm_TUI_cart_add(cart);
            break;

        case 2:
            ioopm_inventory_list_merch(inventory);
            break;

        case 3:
            ioopm_TUI_cart_remove(cart);
            break;

        case 4:
            ioopm_TUI_cart_get_cost(cart);
            break;

        case 5:
            ioopm_TUI_cart_list_contents(cart);
            break;

        case 6:
            ioopm_cart_clear(cart);
            break;

        case 7:
            do_checkout(inventory, cart);
            break;
        
        case 8:
            ioopm_undo(inventory, cart);
            break;

        case 9:
            return 0;
        }
    }
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