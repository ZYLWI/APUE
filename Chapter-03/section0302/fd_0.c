#include "apue.h"
#include <fcntl.h>

int main() {
    char buf[11] = {};
    if ((read(0, (void *)buf, 11)) < 0) {
        err_sys("read from STDIN_FILENO has been failed");
    }

    printf("read buf:\n%s\n", buf);

    return 0;
}
