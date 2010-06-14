## you should only need edit these first 4 variables.

# base name of package
NAME=dirent

# Software version
VERSION=0.2

# DLL interface version
INTERFACE=2.0.0

# library dependencies
DEPS =


SVNVERSION=${VERSION}.`svnversion`
PACKAGE=${NAME}
PACKAGE_SO=${NAME}.so.0

CROSS_SRC = alphasort.obj closedir.obj opendir.obj readdir.obj readdir_r.obj rewinddir.obj scandir.obj seekdir.obj stubs.obj telldir.obj versionsort.obj

# sane defaults
CFLAGS  ?= -O2 -g
PREFIX  ?= /usr/local

# Tools
CROSS_CC=i686-mingw32-gcc
CC=gcc
DLLTOOL=i686-mingw32-dlltool


## Rule to cross compile c source
%.obj : %.c
	@echo cross compiling $< 
	@${CROSS_CC} -c  ${CFLAGS} ${CPPFLAGS} -DWIN32 -DDIRENT_EXPORTS -DCROSS_SRC $< -o $@
	
## Rule to compile source
%.o : %.c
	@echo Compiling $<
	@${CC} -fPIC -c ${CFLAGS} ${CPPFLAGS} $< -o $@

win32: ${PACKAGE}.dll ${PACKAGE}.lib ${PACKAGE}.def
	@echo "done."

linux: ${PACKAGE_SO}
	@echo "done."

## Create linux shared object
${PACKAGE_SO} : ${LINUX_SRC}
	@echo linking ${PACKAGE_SO}
	@${CC} ${LDFLAGS} -shared -o ${PACKAGE_SO} ${LINUX_SRC} ${DEPS} -W1

## Create win32 DLL
${PACKAGE}.dll : ${CROSS_SRC}
	@echo linking ${PACKAGE}.dll
	@${CROSS_CC} ${LDFLAGS} -shared -o ${PACKAGE}.dll ${CROSS_SRC} ${DEPS} -W1,--out-implib,${PACKAGE}.lib

## Create win32 import library
${PACKAGE}.lib : ${CROSS_SRC}
	@echo generating import library ${PACKAGE}.lib
	@${DLLTOOL} --dllname ${PACKAGE}.dll ${CROSS_SRC} --output-lib ${PACKAGE}.lib

## Create win32 inport definitions
${PACKAGE}.def : ${CROSS_SRC}
	@echo generating import definition ${PACKAGE}.def
	@${DLLTOOL} --dllname ${PACKAGE}.dll ${CROSS_SRC} --output-def ${PACKAGE}.def

install_win32 : ${PACKAGE}.dll
	@echo "installing ${PACKAGE}.dll to ${PREFIX}/bin"
	@install ${PACKAGE}.dll ${PREFIX}/bin

install_headers :
	@echo "installing headers to ${PREFIX}/include/"
	@install *.h ${PREFIX}/include/

install_win32_dev : install_win32 ${PACKAGE}.lib ${PACKAGE}.def install_headers
	@echo "installing ${PACKAGE}.lib to ${PREFIX}/lib"
	@install ${PACKAGE}.lib ${PREFIX}/lib
	@ln -sf ${PREFIX}/lib/${PACKAGE}.lib ${PREFIX}/lib/${NAME}.a
	@echo "installing ${PACKAGE}.def to ${PREFIX}/lib"
	@install ${PACKAGE}.def ${PREFIX}/lib


install_linux : ${PACKAGE_SO} install_headers
	@echo "installing ${PACKAGE_SO} to ${PREFIX}/lib"
	@install ${PACKAGE_SO} ${PREFIX}/lib
	@ln -sf ${PREFIX}/lib/${PACKAGE_SO} ${PREFIX}/lib/${NAME}.so

install: install_win32_dev
	@echo "installed"

uninstall:
	@rm -fr ${PREFIX}/include/${NAME}-${VERSION}
	@rm -f ${PREFIX}/bin/${PACKAGE}.dll
	@rm -f ${PREFIX}/lib/${PACKAGE}.lib
	@rm -f ${PREFIX}/lib/${PACKAGE}.def
	@rm -f ${PREFIX}/lib/${PACKAGE_SO}

clean:
	@rm -f *.obj
	@rm -f *.dll
	@rm -f *.lib
	@rm -f *.def
	@rm -f *.so*
	@rm -f *.a
	@rm -f *.o

