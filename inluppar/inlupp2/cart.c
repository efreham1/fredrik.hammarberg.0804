#include "cart.h"
#include "undo.h"
#include <string.h>

bool eq_cart_merch(elem_t a, elem_t b)
{
    cart_merch_t *merch_a = a.ptr_v;
    char *name_a = merch_a->name;
    cart_merch_t *merch_b = b.ptr_v;
    char *name_b = merch_b->name;
    return strcmp(name_a, name_b)==0;
}

bool eq_str(elem_t a, elem_t b)
{
    return strcmp(((char *) a.ptr_v), ((char *) b.ptr_v))==0;
}

static cart_merch_t *create_merch(char *merch_name, int cost, int pieces)
{
    cart_merch_t *merch = calloc(1, sizeof(cart_merch_t));
    merch->name = merch_name;
    merch->price = cost;
    merch->pcs = pieces;
    return merch;
}

ioopm_cart_t *ioopm_cart_create()
{
    ioopm_cart_t *cart = calloc(1, sizeof(ioopm_cart_t));
    cart->contents = ioopm_linked_list_create(eq_cart_merch);
    cart->names = ioopm_linked_list_create(eq_str);
    cart->cost = 0;
    return cart;
}

void ioopm_cart_destroy(ioopm_cart_t *cart)
{
    ioopm_cart_clear(cart);
    ioopm_linked_list_destroy(cart->contents);
    ioopm_linked_list_destroy(cart->names);
    free(cart);
}

void ioopm_cart_add(ioopm_cart_t *cart, char *merch_name, int cost, int pieces)
{
    cart_merch_t *merch = create_merch(merch_name, cost, pieces);
    cart->cost += merch->price*merch->pcs;
    ioopm_linked_list_append(cart->contents, (elem_t) {.ptr_v = merch});
    ioopm_linked_list_append(cart->names, (elem_t) {.ptr_v = merch_name});
}

void ioopm_cart_remove(ioopm_cart_t *cart, char *merch_name)
{
    ioopm_list_iterator_t *iter = ioopm_list_iterator(cart->contents);
    int i = 0;
    while (true)
    {
        bool breaking = false;
        if (!ioopm_iterator_has_next(iter))
        {
            breaking = true;
        }
        cart_merch_t *current_merch = ioopm_iterator_current(iter).ptr_v;
        if (strcmp(current_merch->name, merch_name)==0)
        {
            cart->cost += -current_merch->price * current_merch->pcs;
            ioopm_iterator_remove(iter);
            ioopm_linked_list_remove(cart->names, i);
            break;
        }
        else
        {
            ioopm_iterator_next(iter);
            i++;
        }
        
        if (breaking) break;
    }
    
}

int ioopm_cart_get_cost(ioopm_cart_t *cart)
{
    return cart->cost;
}

void free_cart_merch(elem_t *value, void *extra)
{
    free(((cart_merch_t*) value->ptr_v)->name);
    free(value->ptr_v);
}

void ioopm_cart_clear(ioopm_cart_t *cart)
{
    ioopm_linked_list_apply_to_all(cart->contents, free_cart_merch, NULL);
    ioopm_linked_list_clear(cart->contents);
    ioopm_linked_list_clear(cart->names);
    cart->cost = 0;
}

ioopm_list_t *ioopm_cart_get_merch(ioopm_cart_t *cart)
{
    return cart->contents;
}