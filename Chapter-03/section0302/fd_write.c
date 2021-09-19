#include "apue.h"
#include <fcntl.h>

int main() {
    int fd;
    int len;

    if ((fd = creat("file.fd_write", FILE_MODE)) < 0) {
        err_sys("create error");
    }

    if ((len = write(fd, "hello world", 11)) != 11) {
        err_sys("write file has been failed");
    }

    printf("write file return length: %d", len);

    return 0;
}
