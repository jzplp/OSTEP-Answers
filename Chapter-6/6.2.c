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