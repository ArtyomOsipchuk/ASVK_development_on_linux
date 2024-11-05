#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0], [arto4002@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([src/hh.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_LIB([rhash],[rhash_msg],[],[AC_MSG_ERROR([rhash is needed])])
AC_CHECK_LIB([readline], [readline])

#AC_ARG_ENABLE([readline],
#    AS_HELP_STRING([--no-readline], [Enable force input without readline]),
#    AC_DEFINE(READLINE, [],[Input without readline])
#  )
AC_ARG_WITH([readline],
    [AS_HELP_STRING([--with-readline], [использовать библиотеку readline])],
    [with_readline="$withval"],
    [with_readline="no"])

if test "x$with_readline" = "xyes"; then
    AC_DEFINE([HAVE_READLINE], [1], [Определить, если библиотека readline доступна])
    AC_MSG_NOTICE([Используем библиотеку readline])
    AC_SUBST([READLINE_LIBS], [-lreadline])
else
    AC_MSG_NOTICE([Библиотека readline не будет использоваться])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
