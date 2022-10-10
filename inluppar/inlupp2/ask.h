#include "common_definitions.h"

merch_t ioopm_ask_merch();

char *ioopm_ask_merch_name(ioopm_cart_t *cart);

int ioopm_ask_No_merch(ioopm_cart_t *cart);

bool ioopm_ask_question_bool(char *question);

int ioopm_ask_menu(char *menu, char *options);

bool ioopm_ask_user_access();

bool ioopm_ask_admin_access();