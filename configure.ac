#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

CFLAGS="$CFLAGS -Iinclude"

AC_PREREQ([2.68])
AC_INIT([circ], [0.1.0], [Andreas Halle <andern at gmail dot com>])
AM_INIT_AUTOMAKE([1.11 -Wall no-define])

AC_CONFIG_SRCDIR([src])

AC_PROG_CC
AM_PROG_CC_C_O

AC_CHECK_HEADERS([arpa/inet.h])
AC_CHECK_HEADERS([netdb.h])
AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADERS([stdarg.h])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([sys/types.h])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
