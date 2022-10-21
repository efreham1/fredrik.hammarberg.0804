#include "general_TUI.h"
#include "ask.h"

bool is_valid_merch(char *str, void *extra)
{
    return ioopm_hash_table_has_key(((ioopm_inventory_t *) extra)->warehouse, (elem_t) {.ptr_v = str});
}

void ioopm_ask_cart_merch(ioopm_inventory_t *inventory, char **merch_name, int *cost, int *pieces)
{
    char *question = "Please enter the name of the merchandise you would like to add to your cart";
    *merch_name = ask_question(question, is_valid_merch, inventory, str_to_str, NULL).str_t;
    *cost = ((inventory_merch_t *) ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = *merch_name})->ptr_v)->price;
    printf("How many %s would you like to add to your cart?", *merch_name);
    *pieces = ask_question_u_int("");
}

bool is_existing_cart_merch(char *str, void *extra)
{
    return ioopm_linked_list_contains(((ioopm_cart_t *) extra)->names, (elem_t) {.ptr_v = str});
}

char *ioopm_ask_existing_cart_merch_name(ioopm_cart_t *cart)
{
    return ask_question("Enter an existing name for a merchandise", is_existing_cart_merch, cart, str_to_str, NULL).str_t;
}

static bool is_menu_choice_list(elem_t value, void *extra)
{
    int i = atoi(((char *) extra));
    
    return i == value.int_v;
}

static bool is_menu_choice(char *str, void *extra)
{
    if(!is_number(str)) return false;
    
    ioopm_list_t *options = (ioopm_list_t*) extra;
    return ioopm_linked_list_any(options, is_menu_choice_list, str);
}

int ioopm_ask_menu(char *menu, ioopm_list_t *options)
{
    return ask_question(menu, is_menu_choice, options, str_to_int, NULL).int_t;
}

bool ioopm_ask_user_access()
{
    return true;
}

bool ioopm_ask_admin_access()
{
    return true;
}

bool is_new_inv_merch(char *str, void *extra)
{
    return !ioopm_hash_table_has_key((ioopm_hash_table_t *) extra, (elem_t) {.ptr_v = str});
}

void ioopm_ask_new_inventory_merch(ioopm_hash_table_t *warehouse, char **name, char **desc, int *price)
{
    *name = ask_question("Enter a unique name for the new merchandise", is_new_inv_merch, warehouse, str_to_str, NULL).str_t;
    *desc = ask_question_string("Enter a description for the merchandise");
    *price = ask_question_u_int("Enter a price in Öre for the merchandise"); 
}

bool is_existing_inv_merch(char *str, void *extra)
{
    return ioopm_hash_table_has_key((ioopm_hash_table_t *) extra, (elem_t) {.ptr_v = str});
}

char *ioopm_ask_existing_inventory_merch(ioopm_hash_table_t *warehouse)
{
    return ask_question("Enter an existing name for a merchandise", is_existing_inv_merch, warehouse, str_to_str, NULL).str_t;
}

char *ioopm_ask_shelf()
{
    return "test";
}

int ioopm_ask_question_u_int(char *question)
{
    return ask_question_u_int(question);
}

char *ioopm_ask_question_string(char *question)
{
    return ask_question_string(question);
}

int ioopm_ask_question_int(char *question)
{
    return ask_question_int(question);
}