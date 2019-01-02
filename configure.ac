#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([primes], [1.0], [vmfdez90@gmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign nostdinc -Wall])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG(C++)

# Checks for libraries.

AC_CHECK_LIB([sqlite3], [sqlite3_open_v2], [], [AC_MSG_ERROR(No SQLite3 library found.)])

# Checks for header files.

AC_CHECK_HEADERS([sqlite3.h], [], [AC_MSG_ERROR(No SQLite3 headers found.)])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AC_OUTPUT
