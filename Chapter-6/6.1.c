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
