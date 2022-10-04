#include <stdbool.h>

int do_checkout(inventory_t *inventory, cart_t *cart)
{
    ioopm_list_t *cart_merch = ioopm_cart_get_merch(cart);
    if(ioopm_inventory_remove_merch_list(cart_merch)==1) return 1;
    if(ioopm_cart_clear(cart)==1) return 1;
    return 0;
}

int event_loop(inventory_t *inventory, cart_t *cart)
{
    bool admin_access = ioopm_ask_admin_access();
    while (admin_access)
    {   
        char menu_choice = ioopm_ask_admin_menu();
        switch (menu_choice)
        {
        case 'A':
            if(ioopm_inventory_add_merch(inventory)==1) return 1;
            break;
        
        case 'L':
            if(ioopm_inventory_list_merch(inventory)==1) return 1;
            break;

        case 'D':
            if(ioopm_inventory_remove_merch(inventory)==1) return 1;
            break;

        case 'E':
            if(ioopm_inventory_edit_merch(inventory)==1) return 1;
            break;

        case 'R':
            if(ioopm_inventory_repelenish_merch(inventory)==1) return 1;
            break;

        case 'U':
            if(ioopm_undo(inventory, cart)==1) return 1;
            break;

        case 'Q':
            return 0;
        }
    }

    bool user_access = ioopm_ask_user_access();

    while (user_access)
    {
        char menu_choice = ioopm_ask_user_menu();
        switch (menu_choice)
        {
        case 'A':
            if(ioopm_cart_add(cart)==1) return 1;
            break;

        case 'R':
            if(ioopm_cart_remove(cart)==1) return 1;
            break;

        case 'L':
            if(ioopm_inventory_list_merch(cart)==1) return 1;
            break;

        case 'C':
            if(ioopm_cart_get_cost(cart)==1) return 1;
            break;

        case 'O':
            if(do_checkout(inventory, cart)==1) return 1;
            break;
        
        case 'U':
            if(ioopm_undo(inventory, cart)==1) return 1;
            break;

        case 'Q':
            return 0;
        }
    }
}

int main(void)
{
    inventory_t *inventory = ioopm_inventory_load();
    cart_t *cart = ioopm_cart_create();
    if (event_loop(inventory, cart)==1)return 1;
    ioopm_inventory_save(inventory);
    return 0; 
}