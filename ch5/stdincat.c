#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 2048
#define STDIN STDIN_FILENO
#define STDOUT STDOUT_FILENO

int main(int argc, char *argv[])
{
    unsigned char buf[BUFSIZE];
    int c;

    while ((c = read(STDIN, buf, sizeof buf)) > 0)
    {
        if (write(STDOUT, buf, c) < 0)
        {
            perror("write error");

            return 1;
        }
    }

    return 0;
}
