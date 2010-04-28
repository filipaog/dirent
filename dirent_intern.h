


#include "dirent.h"

#include <errno.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

#ifndef _4FD631B9_C404_4ebb_A5E4_4341C3924C06
#define _4FD631B9_C404_4ebb_A5E4_4341C3924C06

#ifdef __cplusplus
extern "C" {
#endif

	struct DIR {
		intptr_t hnd;
		struct _finddata_t fileinfo;
		char *findstr;
		long	telldir;
	};

#ifdef __cplusplus
} /*** extern "C" ***/
#endif

#endif /*** _4FD631B9_C404_4ebb_A5E4_4341C3924C06 ***/

