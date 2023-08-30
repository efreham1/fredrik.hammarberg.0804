#include <stdio.h>

void cat(char *filename)
{
    FILE *f = fopen(filename, "r");
    int c = fgetc(f);
    int row_n = 1;
    fprintf(stdout, "%d\t", row_n);

    while (c != EOF)
    {
        fputc(c, stdout);
        if (c=='\n'){
            row_n++;
            fprintf(stdout, "%d\t", row_n);
        }
        c = fgetc(f);
    }

    fclose(f);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
        cat(argv[i]);
        }
    }

    return 0;
}