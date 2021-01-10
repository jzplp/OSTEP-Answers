#include<stdlib.h>
int main()
{
	int * p = (int *)malloc(100*sizeof(int));
	free(p+50);
	return 0;
}