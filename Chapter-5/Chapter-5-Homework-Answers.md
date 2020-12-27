* **问题 1 答案**  
[答案代码](5.1.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int x = 100;
	printf("x = %d, (pid:%d)\n", x, (int)getpid());
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printf("child x = %d (pid:%d)\n", x, (int)getpid());
		x = 200;
		printf("child after changed x = %d (pid:%d)\n", x, (int)getpid());
	} else {
		printf("parent x = %d (pid:%d)\n", x, (int)getpid());
		x = 300;
		printf("parent after changed x = %d (pid:%d)\n", x, (int)getpid());
	}
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.1
x = 100, (pid:6368)
parent x = 100 (pid:6368)
parent after changed x = 300 (pid:6368)
child x = 100 (pid:6369)
child after changed x = 200 (pid:6369)
```
子进程的变量子一开始与父进程相同。但是实际上父子进程中的同名变量已经不在同一内存区域，实际上是两个变量，因此父子进程的变量值改变不会影响另外一个进程。

* **问题 2 答案**  
[答案代码](5.2.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
	int fd = open("./5.2.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	int rc = fork();
	if (rc < 0) {
		close(fd);
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		char * s = "child write something!\n";
		write(fd, s, strlen(s));
	} else {
		char * s = "parent write something\n";
		write(fd, s, strlen(s));
		wait(NULL);
		close(fd);
	}
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.2
[testjz@localhost OS_test]$ cat 5.2.txt
parent write something
child write something!
```
看起来都可以访问文件描述符并正常写入文件。

* **问题 3 答案**  
[答案代码](5.3.c)
```C
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int rc = vfork();
	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printf("hello\n");
		exit(1);
	} else {
		printf("goodbye\n");
	}
	return 0;
}
```
使用vfork，可以在子进程执行结束后再执行父进程。

* **问题 4 答案**  
[答案代码](5.4.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int flag = 0;
const int MAX = 6;
int main()
{
	char * s = "/bin/ls";
	char * ss = "ls";
	char * s2 = "/";
	char * sv[] = { ss, s2, NULL };
	for(flag = 0;flag < MAX; ++flag) {
		int rc = fork();
		if (rc < 0) {
			fprintf(stderr, "fork failed");
			exit(1);
		} else if (rc == 0) {
			switch(flag) {
			case 0:
				execl(s, ss, s2, NULL);
				break;
			case 1:
				execle(s, ss, s2, NULL);
				break;
			case 2:
				execlp(s, s, s2, NULL);
				break;
			case 3:
				execv(s, sv);
				break;
			case 4:
				execvp(ss, sv);
				break;
			case 5:
				execvpe(ss, sv);
				break;
			default: break;
			}
		} else {
			wait(NULL);
		}
	}
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.4
bin   dev  home  lib64	mnt  proc  run	 srv  tmp  var
boot  etc  lib	 media	opt  root  sbin  sys  usr
bin   dev  home  lib64	mnt  proc  run	 srv  tmp  var
boot  etc  lib	 media	opt  root  sbin  sys  usr
bin   dev  home  lib64	mnt  proc  run	 srv  tmp  var
boot  etc  lib	 media	opt  root  sbin  sys  usr
bin   dev  home  lib64	mnt  proc  run	 srv  tmp  var
boot  etc  lib	 media	opt  root  sbin  sys  usr
bin   dev  home  lib64	mnt  proc  run	 srv  tmp  var
boot  etc  lib	 media	opt  root  sbin  sys  usr
bin   dev  home  lib64	mnt  proc  run	 srv  tmp  var
boot  etc  lib	 media	opt  root  sbin  sys  usr
```
有多种变体是为了要适应不同的调用形式和环境要求。

* **问题 5 答案**  
[答案代码](5.5.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int rc = fork();
	int wc = wait(NULL);
	if(rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printf("child");
	} else {
		printf("parent");
	}
	printf("pid:%d wc:%d rc:%d\n", (int)getpid(), wc, rc);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.5
childpid:14495 wc:-1 rc:0
parentpid:14494 wc:14495 rc:14495
```
父进程使用wait()返回子进程id，子进程由于本身没有子进程，所以返回-1。

* **问题 6 答案**  
[答案代码](5.6.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int rc = fork();
	int wc = waitpid(rc, NULL, 0);
	if(rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printf("child");
	} else {
		printf("parent");
	}
	printf("pid:%d wc:%d rc:%d\n", (int)getpid(), wc, rc);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.6
childpid:14607 wc:-1 rc:0
parentpid:14606 wc:14607 rc:14607
```
waitpid在进程本身有子进程的时候有用。  

* **问题 7 答案**  
[答案代码](5.7.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		close(STDOUT_FILENO);
		printf("output child\n");
	}
	wait(NULL);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.7
[testjz@localhost OS_test]$ 
```
无任何输出。

* **问题 8 答案**  
[答案代码](5.8.c)
```C
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	int pi[2];
	int p = pipe(pi);
	if(p < 0) {
		fprintf(stderr, "pipe failed");
		exit(1);
	}
	int i = 0;
	int rc[2];
	char buf[256];
	for(i=0;i<2;++i) {
		rc[i] = fork();
		if (rc[i] < 0) {
			fprintf(stderr, "fork failed");
			exit(1);
		} else if (rc[i] == 0) {
			switch(i) {
			case 0:
				dup2(pi[1], STDOUT_FILENO);
				puts("child input");
				break;
			case 1:
				dup2(pi[0], STDIN_FILENO);
				gets(buf);
				printf("child0 out (%s) in the child1\n", buf);
				return 2;
			}
			break;
		}
	}
	waitpid(rc[0], NULL, 0);
	waitpid(rc[1], NULL, 0);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./5.8
child0 out (child input) in the child1
```
