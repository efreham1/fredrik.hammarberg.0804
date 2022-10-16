#include "cart.h"

#pragma once

/// @brief Ask in a TUI for a merchandise
/// @return The entered merchandise
cart_merch_t ioopm_ask_merch();

/// @brief Ask for an existing merchandise's name
/// @param cart The cart where the merchandise has to exist
/// @return The retirived name
char *ioopm_ask_merch_name(ioopm_cart_t *cart);

/// @brief Ask for an existing merchandise's amount
/// @param cart The cart where the merchandise has to exist
/// @return The retirived amount of merchandise
int ioopm_ask_No_merch(ioopm_cart_t *cart, char *merch_name);

/// @brief Ask a question which has a yes or no answer
/// @param question The question which will be asked
/// @return The answer yes or no
bool ioopm_ask_question_bool(char *question);

/// @brief Ask for a menu choice
/// @param menu The menu which will be displayed
/// @param options The possible menu options
/// @return The choosed option
int ioopm_ask_menu(char *menu, char *options);

/// @brief See if the user wants user access
/// @return True if user access is granted
bool ioopm_ask_user_access();

/// @brief See if the user wants and can have admin access
/// @return True if admin access is granted
bool ioopm_ask_admin_access();

void ask_new_inventory_merch(inventory->warehouse, &name, &desc, &price);

char *ask_existing_inventory_merch(inventory->warehouse)

char *ask_shelf();

ask_question_u_int(question)