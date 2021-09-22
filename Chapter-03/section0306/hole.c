#include "apue.h"
#include <fcntl.h>

char buf1[] = "hello world";
char buf2[] = "HELLO WORLD";

int main() {
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("create error");

    if ((write(fd, buf1, 11) != 11))
        err_sys("buf1 write error");
    // offset now = 11

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    // offset now 16384

    if (write(fd, buf2, 11) != 11)
        err_sys("buf2 write error");
    // offset now = 16395
    return 0;
}
