#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(int fd,const char *path);
static void die(const char *s);
static void print_int(int num);

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
    int counter = 0;

    for (;;) {
        c = read(fd, buf, sizeof buf);
        if(c < 0) die(path);
        if(c==0) break;

        for (int i=0; i < BUFSIZE; i++){
            if (buf[i] == '\n') {
                counter++;
            }
        }
       print_int(counter);
    }
}

static void print_int(int num) {
    char buf[12];
    int i = 0;

    if ( num < 0) {
        write(STDOUT_FILENO, "-",1);
        num = -num;
    }

    do {
        buf[i++] = '0' + (num % 10);
        num /= 10;
    } while( num > 0);

    while(i > 0){
        write(STDOUT_FILENO, &buf[--i], 1);
    }
    
    write(STDOUT_FILENO, "\n", 1);
}

static void die(const char *s){
    perror(s);

    exit(1);
}
