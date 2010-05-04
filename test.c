
#include "dirent.h"

#include<stdio.h>
#include <stdlib.h>

static char dirent_buffer[ sizeof(struct dirent) + 260 + 1 ] = {0,};

static struct dirent *dirent_r = (struct dirent *)dirent_buffer;

int main(int argc, char **argv) {

	struct dirent *dirent;
	int len,i;
	struct dirent **namelist = NULL;
	DIR* dir = opendir(".");

	len = scandir(".", &namelist, NULL, alphasort);
	for(i=0;i<len;++i) {
		printf("%3d %s %s\n", i+1, namelist[i]->d_type & DT_DIR ? "FOLDER" : "FILE  ", namelist[i]->d_name );
		free(namelist[i]);
	}
	free(namelist);

	printf("============================\n");

	len = scandir(".", &namelist, NULL, versionsort);
	for(i=0;i<len;++i) {
		printf("%3d %s %s\n", i+1, namelist[i]->d_type & DT_DIR ? "FOLDER" : "FILE  ", namelist[i]->d_name );
		free(namelist[i]);
	}
	free(namelist);


	getchar();

	return 0;
}

