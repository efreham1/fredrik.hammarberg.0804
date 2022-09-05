#include <stdio.h>

void print(char *string){
    while(*string){
        putchar(*string);
        string++;
    }
}

int main(void){
    
    print("Bertil\n");

    return 0;
}