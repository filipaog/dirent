

#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	long telldir(DIR *dirp) {

		return dirp->telldir;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

