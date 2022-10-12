#include "cart.h"
#include "undo.h"

struct cart
{
    ioopm_list_t *contents;
    int cost;
};

bool eq_cart_merch(elem_t a, elem_t b)
{
    cart_merch_t *merch_a = a.ptr_v;
    char *name_a = merch_a->name;
    cart_merch_t *merch_b = b.ptr_v;
    char *name_b = merch_b->name;
    return strcmp(name_a, name_b)==0;
}

ioopm_cart_t *ioopm_cart_create()
{
    ioopm_cart_t *cart = calloc(1, sizeof(ioopm_cart_t));
    cart->contents = ioopm_linked_list_create(eq_cart_merch);
    cart->cost = 0;
    return cart;
}

void ioopm_cart_destroy(ioopm_cart_t *cart)
{
    ioopm_cart_clear(cart);
    ioopm_linked_list_destroy(cart->contents);
    free(cart);
}

void ioopm_cart_add(ioopm_cart_t *cart, cart_merch_t merch)
{
    
}

void ioopm_cart_remove(ioopm_cart_t *cart, char *merch_name, int No_merch)
{

}

int ioopm_cart_get_cost(ioopm_cart_t *cart)
{
    return 1;
}

void ioopm_cart_clear(ioopm_cart_t *cart)
{
    
}

ioopm_list_t *ioopm_cart_get_merch(ioopm_cart_t *cart)
{
    return cart->contents;
}