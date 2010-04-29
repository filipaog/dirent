
#include "dirent.h"

#include<stdio.h>

static char dirent_buffer[ sizeof(struct dirent) + 260 + 1 ] = {0,};

static struct dirent *dirent_r = (struct dirent *)dirent_buffer;

int main(int argc, char **argv) {

	struct dirent *dirent;
	DIR* dir = opendir(".");
	
	// Dump current directory using readdir ( uses system allocated storage )
	while((dirent = readdir(dir)))
		printf("%3d %s %s\n", telldir(dir), dirent->d_type & DT_DIR ? "FOLDER" : "FILE  ", dirent->d_name );

	rewinddir(dir);

	// Dump current directory using reentrant readdir_r ( uses user allocated storage )
	while(readdir_r(dir, dirent_r, &dirent) == 0)
		printf("%3d %s %s\n", telldir(dir), dirent->d_type & DT_DIR ? "FOLDER" : "FILE  ", dirent->d_name );

	closedir(dir);

	getchar();

	return 0;
}

