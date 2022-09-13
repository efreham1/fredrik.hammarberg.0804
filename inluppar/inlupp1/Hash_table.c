#include "Hash_table.h"

typedef struct hash_table ioopm_hash_table_t;

struct hash_table{
    int number; //TODO funkar inte alls
};

//Create a new hash table
ioopm_hash_table_t *ioopm_hash_table_create(void){
    ioopm_hash_table_t result = {.number=1}; //TODO funkar inte alls
    return &result;
}

//Delete a hash table and free its memory
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht){
    //TODO funkar inte alls
}

//add key => value entry in hash table ht
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value){
    //TODO funkar inte alls
}

//lookup value for key in hash table ht
char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key){
    return "Tjena"; //TODO funkar inte alls
}

//remove any mapping from key to a value
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key){
    return "tjo bish"; //TODO funkar inte alls
}