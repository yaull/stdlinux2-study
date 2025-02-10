// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <unistd.h>


int len(const char *s) {
    int length = 0;

    while (s[length] != '\0') {
        length++;
    }
    return length;
}
int main(){

    char *s = "hello world";
    int l = len(s);

    write(1, s, l);
}