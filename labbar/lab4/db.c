#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct item
{
    char *name;
    char *desc;
    int price;
    char *shelf;
};
typedef struct item item_t;


void print_item(item_t *item){
    printf("Name: %s\nDesc: %s\nPrice: %d SEK\nShelf: %s\n", item->name, item->desc, item->price, item->shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf){
    item_t item = {.name = name, .desc = desc, .price = price, .shelf = shelf};
    return item;
}

