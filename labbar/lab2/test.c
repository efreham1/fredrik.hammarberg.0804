#include <stdio.h>
#include <stdbool.h>

int main(void){
    int c;
    while(true){
        c = getchar();
        if (c='\0'){
            printf("FUck you\n");
        }
        printf("%c", c);
    }

    return 0;
}