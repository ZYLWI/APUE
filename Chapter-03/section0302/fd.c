#include "apue.h"
#include <fcntl.h>

int main() {
    int fd;
    char *pathname = "./file1";
    fd = open(pathname, O_RDONLY);
    printf("open file return fd: %d", fd);
    return 0;
}
