## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = -Iinclude \
              -std=c89 \
              -pedantic \
              -Wall -Wno-missing-braces -Wextra \
              -Wno-missing-field-initializers -Wformat=2 -Wswitch-default \
              -Wswitch-enum -Wcast-align -Wpointer-arith -Wbad-function-cast \
              -Wstrict-overflow=5 -Wstrict-prototypes -Winline -Wundef \
              -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code \
              -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 \
              -Wredundant-decls -Wold-style-definition -Werror

SRCDIR = src

bin_PROGRAMS = circ

circ_SOURCES = src/main.c src/irc/connection.c

circ_LDADD = ${circ_LIBS}
