#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

static struct option longopts[] = {
    {"visualable", no_argument, NULL, 'v'},
    {0, 0, 0, 0}};

int main(int argc, char *argv[])
{

    int opt;
    int v = false;
    while ((opt = getopt_long(argc, argv, "v", longopts, NULL)) != -1)
    {
        switch (opt)
        {
        case 'v':
            v  = true;
            break;
        case 'h':
            fprintf(stdout, "Usage: %s [-v] [file...]\n", argv[0]);
            exit(0);
        case '?':
            fprintf(stderr, "Usage: %s [-v] [file...]\n", argv[0]);
            exit(1);
        }
    }

    int i;

    for (i = optind; i < argc; i++)
    {

        FILE *f;
        int c;

        f = fopen(argv[i], "r");
        if (!f)
        {
            perror(argv[i]);
            exit(1);
        }
        while ((c = fgetc(f)) != EOF)
        {

            if (v)
            {

                switch (c)
                {
                case '\t':
                    putchar('\\');
                    putchar('t');
                    break;
                case '\n':
                    putchar('$');
                    putchar('\n');
                    break;
                default:
                    if (putchar(c) < 0)
                        exit(1);
                    break;
                }
            }
            else
            {
                if (putchar(c) < 0)
                    exit(1);
            }
        }
        fclose(f);
    }

    exit(0);
}