#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [arto4002@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([src/hh.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_LIB([rhash],[initscr],[],[AC_MSG_ERROR([rhash is needed])])
AC_CHECK_LIB([optional], [readline])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--without-readline], [Enable force input without readline]),
    AC_DEFINE(READLINE, [],[Input without readline])
  )

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
