#include <string.h>
#include <stdio.h>

int string_len(char string[]){
    int i = 0;
 while (string[i] != '\0')
 {
    i++;
 }
 return i;
}

void print(char string[]){
    for (int i = 0; string[i] != '\0'; i++)
    {
        putchar(string[i]);
    } 
}

void println(char string[]){
    for (int i = 0; string[i] != '\0'; i++)
    {
        putchar(string[i]);
    }
    putchar('\n');
}


int main(int argc, char *argv[]){
    char *string = "Bertil";
    int len_1  = string_len(string);
    int len_2 = strlen(string);
    printf("min: %d, inbyggda: %d\n", len_1, len_2);
    println(string);
    return 0;
}