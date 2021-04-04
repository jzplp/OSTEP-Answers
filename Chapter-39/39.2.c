#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<assert.h>
#include<sys/stat.h>
int main(int argc, char * argv[]) {
	char * sdir = ".";
	if(argc > 1) 
		sdir = argv[1];
	int flag = 0;
	if(argc > 2 && strcmp(argv[2], "-l") == 0)
		flag = 1;
	DIR * dp = opendir(sdir);
	assert(dp != NULL);
	struct dirent *d;
	while((d = readdir(dp)) != NULL) {
		printf("%s\n", d->d_name);
		if(flag) {
			char filestr[200] = "";
			strcat(filestr, sdir);
			strcat(filestr, "/");
			strcat(filestr, d->d_name);
			struct stat st;
			stat(filestr, &st);
			printf("inode: %d uid: %d mode: %d\n", st.st_ino, st.st_uid, st.st_mode);
		}	
	}
	return 0;
}
