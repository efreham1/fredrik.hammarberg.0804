#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    srand(time(NULL));
    printf("%d\n", rand()%100);
    printf("%d\n", rand()%100);
    printf("%d\n", rand()%100);
    printf("%d\n", rand()%100);

    return 0;
}