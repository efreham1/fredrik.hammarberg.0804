#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){

    int numbers[] = {
        3,
        5
    };

    char *words[] = {
        "Fizz",
        "Buzz"
    };

    const int size = 2;

    for (int i = 1; i <= 20; i++){
        char *output = "";
        bool flag = true;
        for (int k = 0; k < size; k++){
            if(i%numbers[k]==0){
                char *tmp = strcat(output, words[k]);
                output = tmp;
                printf("%s\n", output);
                flag = false;
            }
        }
        if (flag){
            printf("%d\n", i);
        }
        else{
            printf("%s\n", output);
        }

    }
    
    
    
    return 0;
}