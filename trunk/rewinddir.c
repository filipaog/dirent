
#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	void rewinddir(DIR *dirp) {

		if(dirp) {
			_findclose(dirp->hnd);
			dirp->hnd = _findfirst(dirp->findstr);
		}
	}
	
#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

