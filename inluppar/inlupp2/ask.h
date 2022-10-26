#include "cart.h"
#include "inventory.h"
#include "hash_table.h"

#pragma once

/// @brief Ask in a TUI for a merchandise
/// @return The entered merchandise
void ioopm_ask_cart_merch(ioopm_inventory_t *inventory, char **merch_name, int *cost, int *pieces);

/// @brief Ask for an existing merchandise's name
/// @param cart The cart where the merchandise has to exist
/// @return The retirived name
char *ioopm_ask_existing_cart_merch_name(ioopm_cart_t *cart);

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
int ioopm_ask_menu(char *menu, ioopm_list_t *options);

/// @brief See if the user wants user access
/// @return True if user access is granted
bool ioopm_ask_user_access();

/// @brief See if the user wants and can have admin access
/// @return True if admin access is granted
bool ioopm_ask_admin_access(int password);

void ioopm_ask_new_inventory_merch(ioopm_hash_table_t *warehouse, char **name, char **desc, int *price);

char *ioopm_ask_existing_inventory_merch(ioopm_hash_table_t *warehouse);

char *ioopm_ask_new_shelf(ioopm_list_t *used_shelves);

char *ioopm_ask_old_shelf(ioopm_list_t *used_shelves);

int ioopm_ask_question_u_int(char *question);

char *ioopm_ask_question_string(char *question);

int ioopm_ask_question_int(char *question);

int ioopm_ask_No_stock(ioopm_inventory_t *inventory, char *merch_name, char *shelf);