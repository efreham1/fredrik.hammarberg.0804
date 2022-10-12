#include "general_TUI.h"
#include "ask.h"

merch_t ioopm_ask_merch()
{
    return (merch_t) {.description = "a"};
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

int ioopm_ask_menu(char *menu, char *options)
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