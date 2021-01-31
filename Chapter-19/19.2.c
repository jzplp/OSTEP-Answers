#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>

#define PAGESIZE 4096

int main(int argc, char *argv[])
{
	if(argc != 3) {
		fprintf(stderr, "error parameters!");
		exit(0);
	}
	struct timeval start, end;
	int pageNum = atoi(argv[1]);
	int i,j, num = atoi(argv[2]);
	char arr[PAGESIZE * pageNum];
	
	gettimeofday(&start, NULL);
	for(j=0; j<num; ++j) {
		for(i=0; i<pageNum; ++i) {
			arr[i*4096]=1;
		}
	}
	gettimeofday(&end, NULL);
	printf("%lf %d %d\n", (((double)end.tv_usec - start.tv_usec)/pageNum)/num, end.tv_usec, start.tv_usec);
	return 0;
}