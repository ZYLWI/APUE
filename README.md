# UNIX环境高级编程-3

#### 介绍
UNIX环境高级编程，书中习题以及练习

#### 下载书中代码并编译
Centos7：
yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
yum install libbsd libbsd-devel
make
cp ./include/apue.h /usr/include/
cp ./lib/libapue.a /usr/local/lib/

#### 使用示例
$ cat fd.c
#include "apue.h"
#include <fcntl.h>

int main() {
    int fd;
    char *pathname = "./file1";
    fd = open(pathname, O_RDONLY);
    printf("%d", fd);
    return 0;
}
$ gcc fd.c -lapue
$ ./a.out
3