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

#ifndef _4FD631B9_C404_4ebb_A5E4_4341C3924C06
#define _4FD631B9_C404_4ebb_A5E4_4341C3924C06

#include "dirent.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <io.h>

#ifdef __cplusplus
extern "C" {
#endif

	struct DIR {
		intptr_t hnd;
		struct _finddata_t fileinfo;
		long	telldir;
		char *findstr;
		char end_of_stream;
		struct dirent *g_dirent;
	};

#ifdef __cplusplus
} /*** extern "C" ***/
#endif

#endif /*** _4FD631B9_C404_4ebb_A5E4_4341C3924C06 ***/

