#include "TUI_cart.h"
#include "ask.h"
#include "cart.h"
#include <stdbool.h>
#include <stdio.h>
#include "iterator.h"

void ioopm_TUI_cart_add(ioopm_cart_t *cart)
{
    merch_t merch = ioopm_ask_merch();
    ioopm_cart_add(cart, merch);
    bool add_more = ioopm_ask_question_bool("Would you like to add more merchandise?");
    while (add_more)
    {
        merch_t merch = ioopm_ask_merch();
        ioopm_cart_add(cart, merch);
        bool add_more = ioopm_ask_question_bool("Would you like to add more merchandise?");
    }
}

void ioopm_TUI_cart_remove(ioopm_cart_t *cart)
{
    char *merch_name = ioopm_ask_merch_name(cart);
    int No_merch = ioopm_ask_No_merch(cart);
    ioopm_cart_remove(cart, merch_name, No_merch);
    bool remove_more = ioopm_ask_question_bool("Would you like to remove more merchandise?");
    while (remove_more)
    {
        char *merch_name = ioopm_ask_merch_name(cart);
        int No_merch = ioopm_ask_No_merch(cart);
        ioopm_cart_remove(cart, merch_name, No_merch);
        bool remove_more = ioopm_ask_question_bool("Would you like to remove more merchandise?");
    }
}

void ioopm_TUI_cart_get_cost(ioopm_cart_t *cart)
{
    int cost = ioopm_cart_get_cost(cart);
    printf("The cost of all the contents in your cart is %d.%d SEK", cost/100, cost%100);
}

void ioopm_TUI_cart_list_contents(ioopm_cart_t *cart)
{
    ioopm_hash_table_t *contents = ioopm_cart_get_merch(cart);
    ioopm_list_t *all_merch = ioopm_hash_table_keys(contents);
    ioopm_list_iterator_t *merch_iterator = ioopm_iterator_create(all_merch);
    for (int i = 0; i < ioopm_linked_list_length(all_merch); i++)
    {
        char *name = ((merch_t *) ioopm_iterator_current(merch_iterator).ptr_v)->name;
        int No_art = ioopm_hash_table_lookup(contents, ioopm_iterator_current(merch_iterator))->int_v;
        printf("%d. %s: %d pcs", i, name, No_art);
        ioopm_iterator_next(merch_iterator);
    }
}