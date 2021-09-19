## 3.2 文件描述符
1. 所有打开的文件都通过文件描述符引用，文件描述符是非负整数。

    1.1 代码示例：

[demo1.1链接](https://gitee.com/zylwi/APUE/blob/master/Chapter-03/section0302/fd.c)

```c
#include "apue.h"
#include <fcntl.h>

int main() {
    int fd;
    char *pathname = "./file1";
    fd = open(pathname, O_RDONLY);
    printf("open file return fd: %d", fd);
    return 0;
}
```


2. 打开一个现有文件或者创建一个文件，内核会向进程返回一个文件描述符。
    
    1. 例如：当读，写一个文件时，使用open或者write返回的文件描述符标识这个文件，并将参数传送给read或者write。
    
    2.1 代码示例：

[demo2.1代码链接](https://gitee.com/zylwi/APUE/blob/master/Chapter-03/section0302/fd_write.c)	

```c
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
```


3. 文件描述符0与进程的标准输入关联，文件描述符1与进程的标准输出关联，文件描述符2与进程的标准错误关联。

	1. 0，1，2已经被标准化，通常替换为常量STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO

    3.1 代码示例：

[demo3.1代码链接](https://gitee.com/zylwi/APUE/blob/master/Chapter-03/section0302/fd_write.c)

```c
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
```
 
	
4. 文件描述符的变化范围是0~OPEN_MAX-1，即每个进程可以打开的文件个数上限。

	1 查看进程描述符上限： unlimit -n

	2 查看系统描述符上限： sysctl -a | grep file-max

        3 **超过文件描述符上限，报错too many open files**

    4.1 代码示例

[4.1代码链接](https://gitee.com/zylwi/APUE/blob/master/Chapter-03/section0302/fd_max.c#)

```c
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
```