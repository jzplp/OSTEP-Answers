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