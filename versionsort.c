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

#ifdef __cplusplus
extern "C" {
#endif

	static __inline int isnum(char c) {
		return c >= '0' && c <= '9' ;
	}

	// position of last '.' or negative.
	static __inline int lastdotpos(const char *c) {

		int n=strlen(c);
		while(--n>=0)
			if(c[n]=='.')
				break;
		return n;
	}

	// (position of last non extension non-numeric) or negative
	static __inline int lastcharpos(const char *c, int n) {

		while(--n>=0)
			if(!isnum(c[n]))
				break;
		return n;
	}


	DIRENT_API
	int versionsort(const void *da, const void *db) {

		int aldp,bldp,alcp,blcp;

		const char *a = (*(const struct dirent **)da)->d_name;
		const char *b = (*(const struct dirent **)db)->d_name;

		aldp=lastdotpos(a);
		bldp=lastdotpos(b);
		alcp=lastcharpos(a,aldp);
		blcp=lastcharpos(b,bldp);

		if((((alcp>=-1) && (alcp != (aldp-1)))) &&
			(((blcp>=-1) && (blcp != (bldp-1)))) &&
				((alcp == blcp)) &&
					((strncmp(a,b,alcp+1)==0))) {
						int l = atoi(a+alcp+1);
						int r = atoi(b+blcp+1);
						
			return l-r;
		}

		return strcmp(a,b);
	}

#ifdef __cplusplus
}	/*** extern "C" ***/
#endif


