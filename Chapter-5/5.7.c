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
