#include "general_TUI.h"
#include "ask.h"


cart_merch_t ioopm_ask_merch()
{
    return (cart_merch_t) {.description = "a"};
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

int ioopm_ask_menu(char *menu, ioopm_list_t *options)
{
    return 3;
}

bool ioopm_ask_user_access()
{
    return true;
}

bool ioopm_ask_admin_access()
{
    return true;
}

void ask_new_inventory_merch(ioopm_hash_table_t *warehouse, char **name, char **desc, int *price)
{

}

char *ask_existing_inventory_merch(ioopm_hash_table_t *warehouse)
{
    return "test";
}

char *ask_shelf()
{
    return "test";
}

int ask_question_u_int(char *question)
{
    return ask_question_u_int_(question);
}

char *ask_question_string(char *question)
{
    return ask_question_string_(question);
}

int ask_question_int(char *question)
{
    return ask_question_int_(question);
}