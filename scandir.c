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
    #define strcpy_s(d,dsz,s) strncpy(d,s,dsz)
    #define strcat_s(d,dsz,s) strcat(d,s)
#endif /*** CROSS_SRC ***/

#ifdef __cplusplus
extern "C" {
#endif

	// deep copy struct dirent
	static struct dirent* new_dirent(struct dirent** dptr, const struct dirent *src) {

		struct dirent *dirent = NULL;

		if((dirent = (struct dirent *)malloc(sizeof(struct dirent) + src->d_namlen + 1 ))) {
			
			*dirent = *src;
			dirent->d_name = (char*)(dirent + 1);
			strcpy_s(dirent->d_name, dirent->d_namlen+1, src->d_name);
			*dptr = dirent;
		
		}
		return dirent;
	}

	DIRENT_API
	int scandir(const char *dir_str, 
		struct dirent ***namelist,
		int(*filter)(const struct dirent *),
		int(*compar)(const struct dirent **, const struct dirent**) )
	{
		DIR *dir;
		int len=0;
		struct dirent *dirent;

		if(!namelist)
			return -1;

		*namelist = NULL;

		if(!(dir = opendir(dir_str)))
			return -1;
		
		while(dirent = readdir(dir))
			if(filter && !filter(dirent))
				continue;
			else if((*namelist = realloc(*namelist, sizeof(struct dirent*) * (len+1)))==NULL)
				goto exit_err; /* FIXME: leak on ENOMEM*/
			else if(!new_dirent((*namelist) + len, dirent))
				goto exit_err;
			else
				++len;

		if(compar)
			qsort(*namelist,len,sizeof(struct dirent*), (int(*)(const void*,const void*))compar);

		closedir(dir);

		return len;

exit_err:
		
		if(*namelist) {
			for(--len;len>=0;len--)
				free(*((*namelist) + len));
			free( *namelist );
		}

		closedir(dir);
		return -1;
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif

