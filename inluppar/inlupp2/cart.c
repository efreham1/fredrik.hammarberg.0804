#include "cart.h"

struct cart
{
    ioopm_hash_table_t *contents;
    int cost;
};

bool eq_int(elem_t a, elem_t b)
{
    return a.int_v == b.int_v;
}

ioopm_cart_t *ioopm_cart_create()
{
    ioopm_cart_t *cart = calloc(1, sizeof(ioopm_cart_t));
    cart->contents = ioopm_hash_table_create_spec(0.75, 25, hash_function_merch, eq_merch, eq_int, lt_merch);
    cart->cost = 0;
}

void ioopm_cart_destroy(ioopm_cart_t *cart)
{
    ioopm_cart_clear(cart);
    ioopm_hash_table_destroy(cart->contents);
    free(cart);
}

void ioopm_cart_add(ioopm_cart_t *cart, merch_t merch)
{

}

void ioopm_cart_remove(ioopm_cart_t *cart, char *merch_name, int No_merch)
{

}

int ioopm_cart_get_cost(ioopm_cart_t *cart)
{

}

void ioopm_cart_clear(ioopm_cart_t *cart)
{

}

ioopm_hash_table_t *ioopm_cart_get_merch(ioopm_cart_t *cart)
{
    return cart->contents;
}