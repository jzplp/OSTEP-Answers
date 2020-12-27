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