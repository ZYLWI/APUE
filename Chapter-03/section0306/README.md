# 3.6 函数lseek

1. 每个打开文件都有一个与其关联的“当前文件偏移量”(`current file offset`)。

2. 通常，读、写都从当前文件偏移处开始，并使偏移量增加所读写的字节数。

3. 打开一个文件时，除非指定`O_APPEND`选项，否则偏移量被设置为0

4. 若lseek成功执行，则返回新的偏移量。此种方法也可以判断涉及的文件是否可以
   设置偏移量。如果文件描述符指向的是管道, FIFO, 或者网络套接字，则lseek返回-1。

```c
#include "apue.h"

int main() {
    // fd: STDIN_FILENO 标准读入
    // 0: 当前偏移位置
    // SEEK_CUR: 当前位置偏移量加0
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) ==  -1) {
        printf("cannot seek \n");
    }
    else {
        printf("seek ok");
    }

    return 0;
}

```

5. 文件当前的偏移量应当是非负数，但是某些设备可能允许负的偏移量，但是对于普通文件
，偏移量一定是非负值。这个思考点比较好：**在比较lseek的返回值应当谨慎，不要测试它
是否小于0，而是测试是否等于-1**

6. lseek仅将当前的文件偏移量记录在内核中，不引起任何IO操作。然后，该偏移量用于下一
个都或者写操作。

7. 文件偏移量可以大于文件的当前长度，在这种情况下，对该文件的下一写将加长该文件，
并在文件中形成一个空洞。**位于文件中但没有写入的字节都被读为0**

8. 文件的空洞并不要求在磁盘上占用存储区，当定位到文件末尾时，对于新写的数据需要分配
磁盘块，但是对于源文件尾端和新开始写位置之间的部分不需要分配磁盘块。

9. 有趣的实验，创建一个空洞文件

```c
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
```

```shell
[root@192 section0306]# ls -l file.hole
-rw-r--r--. 1 root root 16395 Sep 22 23:05 file.hole
[root@192 section0306]# od -c file.hole
0000000   h   e   l   l   o       w   o   r   l   d  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
*
0040000   H   E   L   L   O       W   O   R   L   D
0040013
# 查看占了多少个磁盘块，占了4个
ls -ls lseek_0.c
4 -rw-r--r--. 1 root root 184 Sep 22 22:33 lseek_0.c
```
