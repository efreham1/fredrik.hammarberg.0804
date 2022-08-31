#include "utils.h"
#include <stdlib.h>

int main(void){
    int number = random()%1024;
    char buf[255];
    int buf_siz = 255;
    char *name = ask_question_string("Skriv in ditt namn", buf, buf_siz);
    snprintf(buf, buf_siz, "Du %s, jag tänker på ett tal ... kan du gissa vilket?", name);
    int guess = ask_question_int(buf);




return 0;
}