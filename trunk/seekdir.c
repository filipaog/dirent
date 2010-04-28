

#include "dirent_intern.h"

#ifdef __cplusplus
extern "C" {
#endif

	DIRENT_API
	void seekdir(DIR *dirp, long loc) {

		if(dirp && (loc >= 0))
			if(dirp->telldir != loc) {

				if(loc>dirp->telldir)
					loc -= dirp->telldir;
				else
					rewinddir(dirp);
				
				while(loc) {
					if(readdir(dirp)==NULL)
						--loc;
					else {
						// FIXME: set errno
						return;
					}
				}
			}
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

