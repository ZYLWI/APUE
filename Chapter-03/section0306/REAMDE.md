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
