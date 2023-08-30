#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    while (a != b){
        if(a>b){
            a+= -b;
        }
        else if(a<b){
            b += -a;
        }
    }

    printf("gcd(%s, %s) = %d\n", argv[1], argv[2], a);

    return 0;
}