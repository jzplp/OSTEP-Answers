#include<stdlib.h>
#include<stdio.h>
int main()
{
	int * p = (int *)malloc(100*sizeof(int));
	p[1] = 10;
	p[90] = 20;
	free(p);
	printf("%d %d\n", p[1],p[90]);
	return 0;
}