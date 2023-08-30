#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

bool is_number(char *str){
    size_t len = strlen(str);
    int start = 0;
    if (str[0] == '-' && strlen(str) > 1){
        start = 1;
    }
    for (int i = start; i < len; i++){
        if (!isdigit(str[i])){
            return false;
        }
    }
    
    return true;
}

int main(int argc, char *argv[]){

    if (argc > 1 && is_number(argv[1])){
        if (atoi(argv[1]) < 0){
            printf("%s is negative and therefore not allowed\n", argv[1]);
        }
        else{
            printf("%s is a number\n", argv[1]);
        }
    }
    else{
        if (argc > 1){
            printf("%s is not a number\n", argv[1]);
        }
        else{
            printf("Please provide a command line argument!\n");
        }
    }
    return 0;
}