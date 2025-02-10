#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

static void head(FILE *f, long nlines);

#define DEFAULT_N_LIENS 10

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'n'},
    {0, 0, 0, 0}};

int
main(int argc, char *argv[])
{
    int opt;
    long nlines = DEFAULT_N_LIENS;

    while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1)
    {
        switch (opt)
        {
        case 'n':
            nlines = atoi(optarg);
            break;
        case 'h':
            fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
            exit(0);
        case '?':
            fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
            exit(1);
        }
    }
    if (optind == argc)
    {
        head(stdin, nlines);
    }
    else
    {

        int i;
        FILE *f;
        for (i = 2; i < argc; i++)
        {
            f = fopen(argv[i], "r");
            if (!f)
            {
                perror(argv[i]);
                exit(1);
            }
            head(f, nlines);
            fclose(f);
        }
    }
    exit(0);
}

static void head(FILE *f, long nlines)
{

    int c;
    if (nlines < 0)
        return;
    while ((c = getc(f)) != EOF)
    {
        if (putchar(c) < 0)
            exit(1);
        if (c == '\n')
        {
            nlines--;
            if (nlines == 0)
                return;
        }
    }
}