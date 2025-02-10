#include <stdio.h>
#include <stdlib.h>

static void wcl(FILE *f);

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        wcl(stdin);
    }
    else
    {
        int i;
        FILE *f;
        for (i = 1; i < argc; i++)
        {

            f = fopen(argv[i], "r");
            if (!f)
            {
                perror(argv[i]);
                exit(1);
            }
            wcl(f);
            fclose(f);
        }
    }

    exit(0);
}

static void wcl(FILE *f)
{

    unsigned long n;
    int c;
    int prev = '\n';

    n = 0;
    while ((c = getc(f)) != EOF)
    {
        if (c == '\n')
        {
            n++;
        }
        prev = c;
    }
    if (prev != '\n')
    {
        n++;
    }

    printf("%lu\n", n);
}