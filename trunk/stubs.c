

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

#ifdef __cplusplus
} /*** extern "C" ***/
#endif

