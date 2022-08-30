#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int count = 0;
    for (int i = atoi(argv[2]); i <= atoi(argv[1])*atoi(argv[2]); i += atoi(argv[2]))
    {
        for (int k = 1; k <= i; k++)
        {
            printf("*");
            count++;
        }
        
        printf("\n");
    }
    
    printf("Totalt: %d\n", count);

    return 0;
}