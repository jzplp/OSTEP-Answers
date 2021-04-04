* **问题 1 答案**  
[答案代码](39.1.c)
```C
#include<stdio.h>
#include<sys/stat.h>
int main(int argc, char * argv[]) {
	if(argc < 2) 
		return 0;
	struct stat st;
	stat(argv[1], &st);
	printf("inode: %d\n", st.st_ino);
	printf("hard link: %d\n", st.st_nlink);
	printf("total size: %d\n", st.st_size);
	printf("blocks: %d\n", st.st_blocks);
	return 0;
}
```
测试
```
[testjz@localhost OS_test]$ gcc -o 39.1 39.1.c
[testjz@localhost OS_test]$ ./39.1 39.1.c
inode: 19149
hard link: 1
total size: 309
blocks: 8
[testjz@localhost OS_test]$ ./39.1 .
inode: 75
hard link: 2
total size: 4096
blocks: 16
[testjz@localhost OS_test]$ echo hello > file
[testjz@localhost OS_test]$ ./39.1 .
inode: 75
hard link: 2
total size: 4096
blocks: 16
```
stat接口看不到什么目录的引用计数，只能看到硬链接。  

* **问题 2 答案**  
[答案代码](39.2.c)
```C
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<assert.h>
#include<sys/stat.h>
int main(int argc, char * argv[]) {
	char * sdir = ".";
	if(argc > 1) 
		sdir = argv[1];
	int flag = 0;
	if(argc > 2 && strcmp(argv[2], "-l") == 0)
		flag = 1;
	DIR * dp = opendir(sdir);
	assert(dp != NULL);
	struct dirent *d;
	while((d = readdir(dp)) != NULL) {
		printf("%s\n", d->d_name);
		if(flag) {
			char filestr[200] = "";
			strcat(filestr, sdir);
			strcat(filestr, "/");
			strcat(filestr, d->d_name);
			struct stat st;
			stat(filestr, &st);
			printf("inode: %d uid: %d mode: %d\n", st.st_ino, st.st_uid, st.st_mode);
		}	
	}
	return 0;
}
```
测试
```
[testjz@localhost OS_test]$ gcc -o 39.2 39.2.c
[testjz@localhost OS_test]$ ./39.2 abc
.
..
p1
p1.c
[testjz@localhost OS_test]$ ./39.2 abc -l
.
inode: 19157 uid: 1000 mode: 16877
..
inode: 75 uid: 1000 mode: 16893
p1
inode: 4186 uid: 1000 mode: 33277
p1.c
inode: 12164 uid: 1000 mode: 33204
```

* **问题 3 答案**  
[答案代码](39.3.c)
```C
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/fcntl.h>
int main(int argc, char *argv[]) {
	assert(argc > 2);
	assert(argv[1][0] == '-');
	int n = atoi(&argv[1][1]);
	assert(n > 0);
	int fd = open(argv[2], O_RDONLY);
	assert(fd >= 0);
	char buf[1025];
	int size;
	int lines = 1;
	while(1) {
		size = read(fd, buf, 1024);
		if(size == 0)
			break;
		int i;
		for(i = 0; i< size; ++i)
			if(buf[i] == '\n')
				lines++;
	}
	lines -= n;
	lseek(fd, 0, SEEK_SET);
	n = 1;
	while(1) {
		size = read(fd, buf, 1024);
		if(size == 0)
			break;
		int i;
		for(i = 0; i< size; ++i) {
			if(n >= lines)
				putchar(buf[i]);
			if(buf[i] == '\n') {
				++n;
			}
		}
	}
	close(fd);
	return 0;
}
```
测试
```
[testjz@localhost OS_test]$ gcc -o 39.2 39.2.c
[testjz@localhost OS_test]$ gcc -o 39.3 39.3.c
[testjz@localhost OS_test]$ ./39.3 -1 39.3.c
}
[testjz@localhost OS_test]$ ./39.3 -3 39.3.c
	close(fd);
	return 0;
}
```

* **问题 4 答案**  
[答案代码](39.4.c)
```C
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<assert.h>
#include<sys/stat.h>

void readTotal(const char * sdir) {
	DIR * dp = opendir(sdir);
	assert(dp != NULL);
	struct dirent *d;
	while((d = readdir(dp)) != NULL) {
		if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
			continue;
		printf("%s/%s\n", sdir, d->d_name);
		char filestr[200] = "";
		strcat(filestr, sdir);
		strcat(filestr, "/");
		strcat(filestr, d->d_name);
		struct stat st;
		stat(filestr, &st);
		if(S_ISDIR(st.st_mode))
			readTotal(filestr);
	}
}

int main(int argc, char * argv[]) {
	char * sdir = ".";
	if(argc > 1) 
		sdir = argv[1];
	readTotal(sdir);
	return 0;
}
```
测试
```
[testjz@localhost OS_test]$ gcc -o 39.3 39.4.c
[testjz@localhost OS_test]$ ./39.4 /home/testjz
/home/testjz/.mozilla
/home/testjz/.mozilla/extensions
/home/testjz/.mozilla/plugins
/home/testjz/.mozilla/firefox
/home/testjz/.mozilla/firefox/1lzwsclw.default
/home/testjz/.mozilla/firefox/1lzwsclw.default/times.json
[testjz@localhost OS_test]$ ./39.4
./2.1.1.c
./common.h
./cpu
./2.2.1.c
```
返回内容太多，后面不列出了

