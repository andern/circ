## ExampleLib Example: an example of using Automake to link with a library

## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = -Iinclude -Wall

SRCDIR = src

bin_PROGRAMS = circ

circ_SOURCES = 

circ_LDADD = ${circ_LIBS}
