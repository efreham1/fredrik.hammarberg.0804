#include "general_TUI.h"
#include "ask.h"


void ioopm_ask_cart_merch(ioopm_inventory_t *inventory, char **merch_name, int *cost, int *pieces)
{
    
}

char *ioopm_ask_merch_name(ioopm_cart_t *cart)
{
    return "A";
}

int ioopm_ask_No_merch(ioopm_cart_t *cart, char *merch_name)
{
    return 5;
}

bool ioopm_ask_question_bool(char *question)
{
    return true;
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

void ioopm_ask_new_inventory_merch(ioopm_hash_table_t *warehouse, char **name, char **desc, int *price)
{

}

char *ioopm_ask_existing_inventory_merch(ioopm_hash_table_t *warehouse)
{
    return "test";
}

char *ioopm_ask_shelf()
{
    return "test";
}

int ioopm_ask_question_u_int(char *question)
{
    return ioopm_ask_question_u_int(question);
}

char *ioopm_ask_question_string(char *question)
{
    return ioopm_ask_question_string(question);
}

int ioopm_ask_question_int(char *question)
{
    return ioopm_ask_question_int(question);
}