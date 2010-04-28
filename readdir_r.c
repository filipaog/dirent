

#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	int readdir_r(DIR *dirp, struct dirent *out, struct dirent **result) {

		int ret = EBADF;

		if(dirp && entry && result)
			if(dirp->hnd != -1) {

				ret = 0;
			
				out->d_name = out + sizeof *out;

				out->d_namlen = strlen(dirp->fileinfo.name);

				strncpy_s(out->d_name, out->d_namlen+1, dirp->fileinfo.name, out->d_namlen+1);

				if(dirp->fileinfo.attrib & _A_NORMAL)
					out->d_type = DT_DIR;
				else
					out->d_type = DT_REG;

				if(_findnext( dirp->hnd, &(dirp->fileinfo)) == 0) {
			
					++(dirp->telldir);
					*result = out;
					return ret;
				}
			}
		
		if(result)
			*result = NULL;

		return ret;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

