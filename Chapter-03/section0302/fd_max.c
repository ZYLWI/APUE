#include "apue.h"
#include <fcntl.h>

int main() {
    int i;
    int fd;

    for (i = 0; i < 1025; i ++) {
        char filename[10];
        sprintf(filename, "file %d", i);
        if (creat(filename, FILE_MODE) < 0){
            err_sys("create file has been failed");
        }
    }


    return 0;
}
