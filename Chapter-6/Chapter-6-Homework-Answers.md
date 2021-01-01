在虚拟机中可以设置CPU的个数，直接设置为一个内核就能避免多内核CPU测量不准的情况。

* **测量gettimeofdays()连续调用**  
[答案代码 6.1.c](6.1.c)
```C
#include<stdio.h>
#include<sys/time.h>

int main()
{
	struct timeval start,end;
	int i;
	for(i=0;i<10;++i) {	
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		printf("%ld\n", end.tv_usec - start.tv_usec);
		printf("%ld %ld\n", end.tv_usec, start.tv_usec);
	}
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./6.1
0
499384 499384
1
499443 499442
0
499448 499448
0
499452 499452
0
499457 499457
0
499462 499462
0
499467 499467
0
499471 499471
0
499476 499476
0
499480 499480
```
感觉在连续调用的情况下，精度还是挺高的。可以使用这个函数测试。

* **测量系统调用的成本**  
[答案代码 6.2.c](6.2.c)
```C
#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int fd = open("./6.2.c", O_RDONLY);
	int i;
	char buf[10];
	struct timeval start, end;
	if(fd == -1) {
		fprintf(stderr, "file open failed!\n");
		exit(1);
	}
	for(i=0;i<10;++i) {
		gettimeofday(&start, NULL);
		read(fd, buf, 0);
		gettimeofday(&end, NULL);
		printf("%d\n", end.tv_usec - start.tv_usec);
	}	
	close(fd);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./6.2
1
1
1
0
0
1
0
1
0
1
```
看来是系统的调用的耗时太少了。平均不到一微秒。

* **测量上下文切换的成本**  
[答案代码 6.3.c](6.3.c)
```C
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pi1[2];
    int pi2[2];
    char buf1[30], buf2[30];
    int p1 = pipe(pi1);
    int p2 = pipe(pi2);
    long temptime;
    struct timeval start, end;
    int i;
    if (p1 < 0 || p2 < 0)
    {
        fprintf(stderr, "pipe failed");
        exit(1);
    }
    int rc = fork();
    for (i = 0; i < 10; ++i)
    {
        if (rc < 0)
        {
            fprintf(stderr, "fork failed");
            exit(1);
        }
        else if (rc == 0)
        {
            read(pi1[0], buf1, 25);
            gettimeofday(&end, NULL);
            printf("%d\n", end.tv_usec - atol(buf1));
            gettimeofday(&start, NULL);
            sprintf(buf2, "%ld", start.tv_usec);
            write(pi2[1], buf2, 25);
        }
        else
        {
            gettimeofday(&start, NULL);
            sprintf(buf1, "%ld", start.tv_usec);
            write(pi1[1], buf1, 25);
            read(pi2[0], buf2, 25);
            gettimeofday(&end, NULL);
            printf("%d\n", end.tv_usec - atol(buf2));
        }
    }
    return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./6.3
408
5
5
5
5
4
36
8
4
4
14
5
5
5
4
4
13
4
4
165
```
代码中除了上下文切换，还有系统调用，还有字符串转换数字等成本。另外我在tty2运行这个程序，tty1还开着图形界面，还有一些系统进程切换的成本，所以这个数字在浮动。我们按切换少的时间计算，时间大概在4-5微秒。
