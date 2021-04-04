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
