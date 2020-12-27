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