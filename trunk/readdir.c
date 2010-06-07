/*******************************************************************************
Copyright (c) 2010, Chris Stones ( chris.stones _AT_ gmail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

	1)Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	2)Redistributions in binary form must reproduce the above copyright notice, 
	  this list of conditions and the following disclaimer in the documentation 
	  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "dirent_intern.h"

#if defined(CROSS_SRC)
    #define strncpy_s(d,dsz,s,ssz) strncpy(d,s,dsz)
    #define strcat_s(d,dsz,s) strcat(d,s)
#endif /*** CROSS_SRC ***/

#ifdef __cplusplus
extern "C" {
#endif

	// win32 debug builds don't zero allocated mem!
	static void* zmalloc(int sz) {

		void* out;
		if((out = malloc(sz)))
			memset(out,0,sz);
		return out;
	}

	DIRENT_API
	struct dirent *	readdir(DIR *dirp) {


		if(dirp)
			if(dirp->hnd != -1)
				if(dirp->end_of_stream) {
					return NULL;
				}
				else if( dirp->g_dirent || (dirp->g_dirent = (struct dirent*)zmalloc(sizeof *(dirp->g_dirent)))) {

					int d_namelen = strlen(dirp->fileinfo.name);

					if( d_namelen > dirp->g_dirent->d_namlen )
						dirp->g_dirent->d_namlen = d_namelen;

					if((dirp->g_dirent->d_name = (char*)realloc( dirp->g_dirent->d_name, dirp->g_dirent->d_namlen +1))) {

						strncpy_s(dirp->g_dirent->d_name, dirp->g_dirent->d_namlen+1, dirp->fileinfo.name, dirp->g_dirent->d_namlen+1);

						if(dirp->fileinfo.attrib & _A_SUBDIR)
							dirp->g_dirent->d_type = DT_DIR;
						else
							dirp->g_dirent->d_type = DT_REG;

						if(_findnext( dirp->hnd, &(dirp->fileinfo)) == -1)
							dirp->end_of_stream = 1; // TODO: check errno
	
						++(dirp->telldir);
						return dirp->g_dirent;
					}
				}

		return NULL;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

