

#include <errno.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

#ifndef _DF4A9F29_043F_44a4_BB11_49AC14C8BCC4
#define _DF4A9F29_043F_44a4_BB11_49AC14C8BCC4

#ifdef __cplusplus
extern "C" {
#endif

	#define DIRENT_EXPORTS /* DELETE ME */

	#if defined(DIRENT_EXPORTS)
		#define DIRENT_API __declspec(dllexport)
	#else
		#define DIRENT_API __declspec(dllimport)
	#endif

	typedef struct DIR DIR;

	struct dirent {

		long d_ino;						/* POSIX.1-2001 */
		char *d_name;					/* POSIX.1-2001 */

		#define _DIRENT_HAVE_D_TYPE 1
		#define DT_BLK		0x01		/* This is a block device. */
		#define DT_CHR		0x02		/* This is a character device. */
		#define DT_DIR		0x04		/* This is a directory. */
		#define DT_FIFO		0x08		/* This is a named pipe (FIFO). */
		#define DT_LNK		0x10		/* This is a symbolic link. */
		#define DT_REG		0x20		/* This is a regular file. */
		#define DT_SOCK		0x40		/* This is a Unix domain socket. */
		#define DT_UNKNOWN	0x00		/* The file type is unknown. */

		unsigned char d_type;			/* BSD AND LINUX EXTENSION */

		#define _DIRENT_HAVE_D_NAMLEN 1
		unsigned short int d_namlen;	/* EXTENSION */
	};

	DIRENT_API
	int closedir(DIR *dirp);

	/*****
		dirfd()
		BSD Extension ( 4.3 )
		feature test macro ( _BSD_SOURCE || _SVID_SOURCE )
	*****/
	#if defined(_BSD_SOURCE) || defined(_SVID_SOURCE)
		DIRENT_API
		int dirfd(DIR *dirp);
	#endif /*** BSD 4.3 EXTENSION ***/

	DIRENT_API
	DIR *opendir(const char *dirname);

	/*****
		readdir()
		conforming to SVr4, 4.3BSD, POSIX.1-2001.
	*****/
	DIRENT_API
	struct dirent *	readdir(DIR *dirp);

	DIRENT_API
	int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);

	
	/*****
		rewinddir()
		conforming to SVr4, 4.3BSD, POSIX.1-2001.
	*****/
	DIRENT_API
	void rewinddir(DIR *dirp);

	/*****
		seekdir()
		conforming to 4.3BSD, POSIX.1-2001
		feature test macro ( _BSD_SOURCE || _SVID_SOURCE || _XOPEN_SOURCE )
	*****/
	#if defined(_BSD_SOURCE) || defined(_SVID_SOURCE) || defined(_XOPEN_SOURCE)
		DIRENT_API
		void seekdir(DIR *dirp, long loc);
	#endif 

	/*****
		telldir()
		conforming to 4.3BSD, POSIX.1-2001
		feature test macro ( _BSD_SOURCE || _SVID_SOURCE || _XOPEN_SOURCE )
	*****/
	#if defined(_BSD_SOURCE) || defined(_SVID_SOURCE) || defined(_XOPEN_SOURCE)
		DIRENT_API
		long telldir(DIR *dirp);
	#endif


#ifdef __cplusplus
} /*** extern "C" ***/
#endif

#endif /*** _DF4A9F29_043F_44a4_BB11_49AC14C8BCC4 ***/

