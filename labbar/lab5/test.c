#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int main(void){

    char buf[255];
    int buf_siz = 255;
    read_string(buf, buf_siz);
    int i = 0;
    while (buf[i] != '\0'){
        printf("%d, %c", i, buf[i]);
        i++;
    }

    return 0;
}