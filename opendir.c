
#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	DIR *opendir(const char *dirname) {

		DIR *dir=NULL;
		int  dirname_len = 0;

		if(!dirname)
			return NULL;

		if(!dirname[0])
			return NULL;

		if((dir = (DIR*)malloc(sizeof *dir)) == NULL)
			return NULL;

		dir->hnd = -1;

		dirname_len = strlen(dirname);

		if((dir->findstr = (char*)malloc(dirname_len + 3))) {
			
				strncpy_s(dir->findstr, dirname_len, dirname,dirname_len);

				if(dir->findstr[dirname_len-1] == '\\' || dir->findstr[dirname_len-1] == '/')
					strcat_s(dir->findstr,dirname_len + 3,"*");
				else
					strcat_s(dir->findstr,dirname_len + 3,"\\*");

				dir->hnd = _findfirst( dir->findstr, &(dir->fileinfo));
			}
		
		if(dir && (dir->hnd != -1))
			return dir;

		if(dir) {
			free(dir->findstr);
			free(dir);
		}

		return NULL;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

