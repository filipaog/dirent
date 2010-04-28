

#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	int closedir(DIR *dirp) {

		int err = -1;
		if(dirp) {
			err = _findclose(dirp->hnd);
			free(dirp->findstr);
			free(dirp);
		}
		return err;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

