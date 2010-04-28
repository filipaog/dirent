

#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	struct dirent *	readdir(DIR *dirp) {

		struct dirent *out = NULL;

		if(dirp)
			if(dirp->hnd != -1)
				if((out = (struct dirent*)malloc(sizeof *out))) {

					out->d_namlen = strlen(dirp->fileinfo.name);

					if((out->d_name = (char*)malloc( out->d_namlen +1))) {

						strncpy_s(out->d_name, out->d_namlen+1, dirp->fileinfo.name, out->d_namlen+1);

						if(dirp->fileinfo.attrib & _A_NORMAL)
							out->d_type = DT_DIR;
						else
							out->d_type = DT_REG;

						if(_findnext( dirp->hnd, &(dirp->fileinfo)) == 0) {
					
							++(dirp->telldir);
							return out;
						}
					}
				}
		
		if(out)
			free(out->d_name);

		free(out);

		return NULL;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

