#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(int fd,const char *path);
static void die(const char *s);

int main(int argc, char *argv[]){
    int i;
    int fd;

    if( argc == 1 ){

        do_cat(STDIN_FILENO, "stdin");

    } else {
        
        for (i = 1; i < argc; i++) {
            fd = open(argv[i], O_RDONLY);
            if (fd < 0) die(argv[i]);
            do_cat(fd, argv[i]);
        }
        close(fd);
    }


    return 0;
}

#define BUFSIZE 2048

static void do_cat(int fd, const char *path){

    unsigned  char buf[BUFSIZE];
    int c;

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