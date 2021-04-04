#include<stdio.h>
#include<sys/stat.h>
int main(int argc, char * argv[]) {
	if(argc < 2) 
		return 0;
	struct stat st;
	stat(argv[1], &st);
	printf("inode: %d\n", st.st_ino);
	printf("hard link: %d\n", st.st_nlink);
	printf("total size: %d\n", st.st_size);
	printf("blocks: %d\n", st.st_blocks);
	return 0;
}
