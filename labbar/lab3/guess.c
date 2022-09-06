#include "utils.h"
#include <stdlib.h>
#include <time.h>

int main(void){
    srand(time(NULL));
    int number = rand()%1024;
    int buf_siz = 255;
    char buf[buf_siz];
    char *name = ask_question_string("Skriv in ditt namn\n");
    snprintf(buf, buf_siz, "Du %s, jag tänker på ett tal ... kan du gissa vilket?\n", name);
    int guess = ask_question_int(buf);
    int i = 0;
    while (guess != number && i < 15){
        if (guess < number){
            print("För litet!\n");
        }
        else{
            print("För stort!\n");
        }
        guess = ask_question_int("");
        i++;
    }
    if (guess == number){
        printf("Bingo!\nDet tog %s %d gissningar att komma fram till %d\n", name, i, number);
    }
    else{
        printf("Nu har du slut på gissningar %s! Jag tänkte på %d!\n", name, number);
    }
    
return 0;
}