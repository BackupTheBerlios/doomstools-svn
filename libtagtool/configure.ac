###############################################################
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([libtagtool], [1.0], [doomsday@mailclub.net])

AC_CONFIG_HEADER(config.h)

# Automake. (needed)
AM_INIT_AUTOMAKE([1.8.2 foreign check-news dist-bzip2 no-dist-gzip])

# needed when we do libtoolize
AM_PROG_LIBTOOL

####################
# checks for options
AC_ARG_ENABLE(debug,
	[  --enable-debug Enable or disable debug symbol generation (default disabled)],
	[enable_debug="$enableval"],
	[enable_debug="no"])

######################
# Checks for libraries.
AC_CHECK_LIB([sqlite3], [sqlite3_open], [SQLITE='yes'], AC_MSG_ERROR([Couldn't find libsqlite3]))
AC_CHECK_LIB([stdtool], [xmalloc], [STDTOOL='yes'], AC_MSG_ERROR([Couldn't find libstdtool]))

# libs headers
AC_CHECK_HEADERS([sqlite3.h])
AC_CHECK_HEADERS([libstdtool.h])

###########
## options :
AC_MSG_CHECKING([for enable-debug])
if test x"$enable_debug" = xyes;
then
 CFGDEBUG=Yes
 CFLAGS="${CFLAGS} -g3"
 CXXFLAGS="${CXXFLAGS} -g3"
else
 CFGDEBUG=No
fi
AC_MSG_RESULT([$CFGDEBUG])


##############################
# define all makefile locations

AC_CONFIG_FILES([Makefile])


##############
# start working

AC_OUTPUT
