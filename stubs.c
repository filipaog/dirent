

#include "dirent_intern.h"

#include<assert.h>

#ifdef __cplusplus
extern "C" {
#endif

	static const char stub = 0;
	

	DIRENT_API
	int dirfd(DIR *dirp) {

		assert(stub);
		return 0;
	}

	DIRENT_API
	struct dirent *	readdir(DIR *dirp) {

		assert(stub);
		return NULL;
	}

	DIRENT_API
	int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result) {

		assert(stub);
		return 0;
	}

#ifdef __cplusplus
} /*** extern "C" ***/
#endif
