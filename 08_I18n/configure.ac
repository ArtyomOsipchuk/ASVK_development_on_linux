#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([guess], [1.0], [artos4002@yandex.ru])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_FUNCS([realpath setlocale])
# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile po/Makefile src/Makefile])
AC_OUTPUT
