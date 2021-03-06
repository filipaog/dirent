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

	DIRENT_API
	int readdir_r(DIR *dirp, struct dirent *out, struct dirent **result) {

		int ret = EBADF;

		if(dirp && out && result && (dirp->hnd != -1)) {

			ret = 0;
			
			if(!dirp->end_of_stream) {

				out->d_name = (char*)(out + 1);

				out->d_namlen = strlen(dirp->fileinfo.name);

				strncpy_s(out->d_name, out->d_namlen+1, dirp->fileinfo.name, out->d_namlen+1);

				if(dirp->fileinfo.attrib & _A_SUBDIR)
					out->d_type = DT_DIR;
				else
					out->d_type = DT_REG;

				if(_findnext( dirp->hnd, &(dirp->fileinfo)) != 0)
					dirp->end_of_stream = 1;
			
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

