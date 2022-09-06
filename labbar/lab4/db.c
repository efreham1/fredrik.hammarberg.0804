#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include <time.h>
#include <string.h>

struct item
{
    char *name;
    char *desc;
    int price;
    char *shelf;
};
typedef struct item item_t;


void print_item(item_t *item){
    printf("Name: %s\nDesc: %s\nPrice: %d.%d SEK\nShelf: %s\n", item->name, item->desc, item->price/100, item->price%100, item->shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf){
    item_t item = {.name = name, .desc = desc, .price = price, .shelf = shelf};
    return item;
}

item_t input_item(void){
    print("Enter the info of the item..\n");
    char *name = ask_question_string("Name of item: ");
    char *desc = ask_question_string("Description of the item: ");
    int price = ask_question_int("Price of the item: ");
    char *shelf = ask_question_shelf("Shelf of the item: ");
    item_t item = make_item(name, desc, price, shelf);
    if (item.name == name && item.desc == desc && item.price == price && item.shelf == shelf){
        print("Thank you, your item has been created!\n");
        return item;
    }
    else{
        print("Something went wrong, please try again.\n");
        return input_item();
    }
}

char *magick(char *arr1[], char *arr2[], char *arr3[], int num_ele){
    char *str1 = arr1[rand()%num_ele];
    char *str2 = arr2[rand()%num_ele];
    char *str3 = arr3[rand()%num_ele];
    int str1_len = strlen(str1);
    int str2_len = strlen(str2);
    int str3_len = strlen(str3);

    int tot_len =  str1_len + str2_len + str3_len + 3; //+2 för mellanslag +1 för sluttecken
    char *result = calloc(sizeof(char), tot_len);
    int i = 0;
    for(int j = 0; i<str1_len; i++, j++) result[i]=str1[j];
    result[i] = '-';
    i++;
    for(int j = 0; i<(str2_len+str1_len+1); i++, j++) result[i]=str2[j];
    result[i] = ' ';
    i++;
    for(int j = 0; i<(str3_len+str1_len+str2_len+2); i++, j++) result[i]=str3[j];
    result[i] = '\0';
    return result;

}

void list_db(item_t *items, int no_items){
    for(int i = 0; i<no_items; i++){
        //printf("%d. %s\n", i+1, items[i].name);
        printf("%d.\n", i+1);
        print_item(items+i);
    }
}

void edit_db(item_t *items, int no_items){
    int item_no = 0;
    while (true){
        item_no = ask_question_int("Vilket föremål vill du ändra?\n");
        if (item_no > no_items || item_no < 0){
            printf("Det föremålet finns inte");
        }
        else{
            break;
        }
    }
    items[item_no-1] = input_item();
}

int main(int argc, char *argv[])
{
    srand(time(0));
    char *array1[] = {"röd", "blå", "grön", "lila"}; // TODO: Lägg till!
    char *array2[] = {"glänsandes", "dränkt", "målad", "platterad"}; // TODO: Lägg till!
    char *array3[] = {"gås", "hus", "sten", "universitet"}; // TODO: Lägg till!

    if (argc != 2)
    {
    printf("Usage: %s number\n", argv[0]);
    }
    else
    {
        item_t db[16]; // Array med plats för 16 varor
        int db_siz = 0; // Antalet varor i arrayen just nu

        int items = atoi(argv[1]); // Antalet varor som skall skapas

        if (items > 0 && items <= 16)
        {
            for (int i = 0; i < items; ++i)
            {
            // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
            item_t item = input_item();
            db[db_siz] = item;
            ++db_siz;
            }
        }
        else
        {
            puts("Sorry, must have [1-16] items in database.");
            return 1; // Avslutar programmet!
        }

        for (int i = db_siz; i < 16; ++i)
            {
            char *name = magick(array1, array2, array3, 4); // TODO: Lägg till storlek
            char *desc = magick(array1, array2, array3, 4); // TODO: Lägg till storlek
            int price = rand() % 200000 ;
            char shelf1 = rand() % ('Z'-'A') + 'A';
            char shelf2 = rand() % 10 + '0';
            char shelf3 = rand() % 10 + '0';
            char shelf[] = { shelf1, shelf2, shelf3, '\0'};
            item_t item = make_item(name, desc, price, shelf);

            db[db_siz] = item;
            ++db_siz;
            }

            // Skriv ut innehållet
        list_db(db, db_siz);
        edit_db(db, db_siz);
        list_db(db, db_siz);

    }
    return 0;
}
