AC_INIT([bomberguy], [0.2], [olaf@seldiame.net])

AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([-Wall])


AC_EXEEXT
AC_OBJEXT

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC

AC_C_INLINE

AC_FUNC_VPRINTF
AC_CHECK_FUNCS(vsnprintf)
dnl AC_LIB_RPATH

dnl Checks for programs.


dnl Checks for libraries.
dnl Check for SDL
   AM_PATH_SDL(1.1.0,
        :,
        AC_MSG_ERROR(SDL not found. Make sure sdl-config is in your PATH, or specify with --with-sdl-prefix)
    )
    
    CFLAGS="$SDL_CFLAGS $CFLAGS"
	SDL_LIBS="$SDL_LIBS -lpng -ljpeg"
    LIBS="$SDL_LIBS $LIBS"

dnl Checks for header files.


dnl Checks for typedefs, structures, and compiler characteristics.
case "$target" in
    *cygwin* | *mingw32* | *mingw32msvc* )
        CFLAGS="$CFLAGS"
        LIBS="$LIBS -liberty -lwsock32 -lm"
	MINGW32=yes
        ;;
    *solaris* )
	CFLAGS="$CFLAGS"
	LIBS="$LIBS -lsocket -lnsl -lm"
        AC_PATH_X
        AC_PATH_XTRA
        if test x$have_x = xyes; then
            CFLAGS="$CFLAGS $X_CFLAGS"
            SYS_GL_LIBS="$X_LIBS -lGL -lGLU"
        else
            SYS_GL_LIBS="-lGL -lGLU"
        fi
        ;;
    *)
        LIBS="$LIBS -lm"
        AC_PATH_X
        AC_PATH_XTRA
        if test x$have_x = xyes; then
            CFLAGS="$CFLAGS $X_CFLAGS"
        fi
        ;;
esac


dnl Debug ************************************
AC_ARG_ENABLE(debug, [  --disable-debug          Disable Debuging ])
if test x$enable_debug = xno ; then
	CFLAGS="$CFLAGS"
else
	CFLAGS="$CFLAGS -ggdb -O0"
	LDFLAGS="$LDFLAGS -ggdb"
	AC_MSG_WARN(Enable Debuging)
fi

dnl All Warning are Errors ************************
AC_ARG_ENABLE(werror, [  --disable-werror          Disable Warning as Error Treatment ])
if test x$enable_werror = xno ; then
	CFLAGS="$CFLAGS -Wall"
	AC_MSG_WARN(Disable Warning as Error Treatment)
else
	CFLAGS="$CFLAGS -Wall -Werror"
fi


dnl SDL_image library *****************************
AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW, , AC_MSG_ERROR([
*** Unable to find SDL_image libary with PNG support
(http://www.libsdl.org/projects/SDL_image/)
]))


dnl SDL_mixer **********************************
AC_ARG_ENABLE(sdlmixer, [  --disable-sdlmixer      Do not compile with SDL Mixer support ])
AC_ARG_WITH(sdlmixer-prefix, [  --with-sdlmixer-prefix=PFX prefix where SDL_mixer library is installed], sdlmixer_prefix="$withval", sdlmixer_prefix="")
if test x$enable_sdlmixer = xno ; then
     AC_MSG_WARN(Disable SDLMixer support)
	 have_sdl_mixer=no
else
	if test x"$sdlmixer_prefix" != "x"; then
  		SDLMIXER_LIB="-L$sdlmixer_prefix/lib"
  		SDLMIXER_CFLAGS="-I$sdlmixer_prefix/include"
  		LDFLAGS="$SDLMIXER_LIB $LDFLAGS"
  		CFLAGS="$CFLAGS $SDLMIXER_CFLAGS"
	fi

	AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio, have_sdl_mixer="yes", have_sdl_mixer="no" , )

	if test "x$have_sdl_mixer" = "xyes"; then
 		AC_DEFINE(HAVE_SDL_MIXER, [1], [SDL_mixer])
 		LIBS="$LIBS -lSDL_mixer"
	else
 		AC_MSG_WARN([*** libSDL_mixer not found. Make sure you have the development package of SDL_mixer installed - (www.libsdl.org) - or try to use --with-sdlmixer-prefix option])
	fi
fi



dnl Checks for library functions.
dnl Check for rintf and functions like that
AC_MSG_CHECKING(for rintf)
have_rintf=no
AC_TRY_COMPILE([
#include <math.h>
],[
int i; float f; i = rintf (f); 
],[
have_rintf=yes
])
AC_MSG_RESULT($have_rintf)
if test x$have_rintf = xno; then
	AC_CHECK_LIB(m, rintf, have_rintf=yes, have_rintf=no , )
fi

if test x$have_rintf = xyes; then
    	AC_DEFINE(HAVE_RINTF, [1], [if rintf is working here])
fi


dnl Checks for library functions.
dnl Check for rintf and functions like that
AC_MSG_CHECKING(for rint)
have_rint=no
AC_TRY_COMPILE([
#include <math.h>
],[
int i; double f; i = rint (f); 
],[
have_rint=yes
])
AC_MSG_RESULT($have_rint)
if test x$have_rint = xno; then
	AC_CHECK_LIB(m, rint, have_rint=yes, have_rint=no , )
fi

if test x$have_rint = xyes; then
    	AC_DEFINE(HAVE_RINT, [1], [if rint is working here])
fi



dnl Check for powf and functions like that
AC_MSG_CHECKING(for powf)
have_powf=no
AC_TRY_COMPILE([
#include <math.h>
],[
float i; float f = 2; float j = 2; i = powf (f,j); 
],[
have_powf=yes
])
AC_MSG_RESULT($have_powf)
if test x$have_powf = xno; then
	AC_CHECK_LIB(m, powf, have_powf=yes, have_powf=no , )
fi

if test x$have_powf = xyes; then
    	AC_DEFINE(HAVE_POWF, [1], [if powf is working here])
fi

dnl Check for sqrtf and functions like that
AC_MSG_CHECKING(for sqrtf)
have_sqrtf=no
AC_TRY_COMPILE([
#include <math.h>
],[
float i; float f = 2; i = sqrtf (f); 
],[
have_sqrtf=yes
])
AC_MSG_RESULT($have_sqrtf)
if test x$have_sqrtf = xno; then
	AC_CHECK_LIB(m, sqrtf, have_sqrtf=yes, have_sqrtf=no , )
fi

if test x$have_sqrtf = xyes; then
    	AC_DEFINE(HAVE_SQRTF, [1], [if sqrtf is working here])
fi


dnl Check for floorf and functions like that
AC_MSG_CHECKING(for floorf)
have_floorf=no
AC_TRY_COMPILE([
#include <math.h>
],[
int i; float f; i = floorf (f); 
],[
have_floorf=yes
])
AC_MSG_RESULT($have_floorf)
if test x$have_floorf = xno; then
	AC_CHECK_LIB(m, floorf, have_floorf=yes, have_floorf=no , )
fi
if test x$have_floorf = xyes; then
    	AC_DEFINE(HAVE_FLOORF, [1], [if floorf is working here])
fi


dnl Checks for Additional stuffs.



dnl Set PACKAGE SOURCE DIR in config.h.
packagesrcdir=`cd $srcdir && pwd`

dnl Set PACKAGE PREFIX
if test "x${prefix}" = "xNONE"; then
  packageprefix=${ac_default_prefix}
else
  packageprefix=${prefix}
fi

dnl Set PACKAGE DATA & DOC DIR
packagedatadir=share/games/${PACKAGE}
packagedocdir=share/doc/${PACKAGE}

dnl Set PACKAGE DIRS in config.h.
packagepixmapsdir=${packagedatadir}/pixmaps
packagehelpdir=${packagedatadir}/help
packagemenudir=${packagedatadir}

dnl Subst PACKAGE_DATA_DIR.
NO_PREFIX_PACKAGE_DATA_DIR="${packagedatadir}"
AC_SUBST(NO_PREFIX_PACKAGE_DATA_DIR)
PACKAGE_DATA_DIR="${packageprefix}/${packagedatadir}"
AC_SUBST(PACKAGE_DATA_DIR)

dnl Subst PACKAGE_DOC_DIR.
NO_PREFIX_PACKAGE_DOC_DIR="${packagedocdir}"
AC_SUBST(NO_PREFIX_PACKAGE_DOC_DIR)
PACKAGE_DOC_DIR="${packageprefix}/${packagedocdir}"
AC_SUBST(PACKAGE_DOC_DIR)

dnl Subst PACKAGE_PIXMAPS_DIR.
NO_PREFIX_PACKAGE_PIXMAPS_DIR="${packagepixmapsdir}"
AC_SUBST(NO_PREFIX_PACKAGE_PIXMAPS_DIR)
PACKAGE_PIXMAPS_DIR="${packageprefix}/${packagepixmapsdir}"
AC_SUBST(PACKAGE_PIXMAPS_DIR)

dnl Subst PACKAGE_HELP_DIR.
NO_PREFIX_PACKAGE_HELP_DIR="${packagehelpdir}"
AC_SUBST(NO_PREFIX_PACKAGE_HELP_DIR)
PACKAGE_HELP_DIR="${packageprefix}/${packagehelpdir}"
AC_SUBST(PACKAGE_HELP_DIR)

dnl Subst PACKAGE_MENU_DIR.
NO_PREFIX_PACKAGE_MENU_DIR="${packagemenudir}"
AC_SUBST(NO_PREFIX_PACKAGE_MENU_DIR)
PACKAGE_MENU_DIR="${packageprefix}/${packagemenudir}"
AC_SUBST(PACKAGE_MENU_DIR)

AM_CONDITIONAL(MINGW32, test x$MINGW32 = xyes)

AC_DEFINE([PACKAGE_DATA_DIR], ["data/"], [Data dir])
AC_DEFINE([PACKAGE_DOC_DIR], ["doc/"], [Doc dir] )
AC_DEFINE([PACKAGE_PIXMAPS_DIR], ["data/pixmaps"], [Pixmaps dir])
AC_DEFINE([PACKAGE_HELP_DIR], ["help/"], [Help dir])
AC_DEFINE([PACKAGE_MENU_DIR], ["."] , [Menu dir])
AC_DEFINE([PACKAGE_SOURCE_DIR], ["src/"] , [Source dir])

AC_CONFIG_HEADERS(config.h)

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 data/Makefile
 data/pixmaps/Makefile
 data/music/Makefile
 data/gfx/Makefile
 data/player/Makefile
 data/maps/Makefile
 data/tileset/Makefile
 data/tileset/cemetery/Makefile
 data/tileset/classic/Makefile
 data/tileset/cucumber/Makefile
 data/tileset/default/Makefile
 data/tileset/farm/Makefile
 data/tileset/hell/Makefile
 data/tileset/jungle/Makefile
 data/tileset/modern/Makefile
 data/tileset/radioactive/Makefile
 data/tileset/supermario/Makefile
 data/tileset/tricked/Makefile
])

AC_OUTPUT
