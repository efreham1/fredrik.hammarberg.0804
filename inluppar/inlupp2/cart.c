#include "cart.h"
#include "undo.h"

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
    return cart;
}

void ioopm_cart_destroy(ioopm_cart_t *cart)
{
    ioopm_cart_clear(cart);
    ioopm_hash_table_destroy(cart->contents);
    free(cart);
}

void ioopm_cart_add(ioopm_cart_t *cart, merch_t merch)
{
    merch_t *local_merch = calloc(1, sizeof(merch_t));
    *local_merch = merch;
    elem_t to_insert = {.ptr_v = local_merch};
    if (ioopm_hash_table_lookup(cart->contents, to_insert) == NULL)
    {
        ioopm_hash_table_insert(cart->contents, to_insert, (elem_t) {.int_v=1});
    }
    else
    {
        int No_ = ioopm_hash_table_lookup(cart->contents, to_insert)->int_v;
        ioopm_hash_table_insert(cart->contents, to_insert, (elem_t){.int_v=No_ +1});
    }
}

void ioopm_cart_remove(ioopm_cart_t *cart, char *merch_name, int No_merch)
{

}

int ioopm_cart_get_cost(ioopm_cart_t *cart)
{
    return 1;
}

void clear_merch(elem_t key, elem_t *value, void *extra)
{
    free(key.ptr_v);
}

void ioopm_cart_clear(ioopm_cart_t *cart)
{
    ioopm_hash_table_apply_to_all(cart->contents, clear_merch, NULL);
    ioopm_hash_table_clear(cart->contents);
}

ioopm_hash_table_t *ioopm_cart_get_merch(ioopm_cart_t *cart)
{
    return cart->contents;
}