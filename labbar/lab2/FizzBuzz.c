#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){


    for (int i = 1; i <= 20; i++){
        bool tag = true;
        if (i%3==0){
            printf("Fizz");
            tag = false;
        }
        if (i%5==0){
            printf("Buzz");
            tag = false;
        }
        if (tag){
            printf("%d", i);
        }
        printf(", ");

    }
    
    
    
    return 0;
}