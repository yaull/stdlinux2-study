#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int main(int argc, char *argv[]){
    int i;

    if( argc <2 ){

        fprintf(stderr, "%s: file name not given\n", argv[0]);
    }

    for (i = 1; i < argc; i++) {
        do_cat(argv[i]);
    }

    return 0;
}

#define BUFSIZE 2048

static void do_cat(const char *path){

    int fd;
    unsigned  char buf[BUFSIZE];
    int c;

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    for (;;) {
        c = read(fd, buf, sizeof buf);
        if(c < 0) die(path);
        if(c==0) break;
        if(write(STDOUT_FILENO, buf,c) < 0) die(path);
    }
}

static void die(const char *s){
    perror(s);

    exit(1);
}