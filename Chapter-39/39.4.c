#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<assert.h>
#include<sys/stat.h>

void readTotal(const char * sdir) {
	DIR * dp = opendir(sdir);
	assert(dp != NULL);
	struct dirent *d;
	while((d = readdir(dp)) != NULL) {
		if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
			continue;
		printf("%s/%s\n", sdir, d->d_name);
		char filestr[200] = "";
		strcat(filestr, sdir);
		strcat(filestr, "/");
		strcat(filestr, d->d_name);
		struct stat st;
		stat(filestr, &st);
		if(S_ISDIR(st.st_mode))
			readTotal(filestr);
	}
}

int main(int argc, char * argv[]) {
	char * sdir = ".";
	if(argc > 1) 
		sdir = argv[1];
	readTotal(sdir);
	return 0;
}
