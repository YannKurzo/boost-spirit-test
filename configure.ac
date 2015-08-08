# ------------------------------------------------
# Init
# ------------------------------------------------

AC_INIT([boost_autoconf], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE(
    [-Wall -Werror foreign]
)
AC_PROG_CXX
AC_LANG(C++)

AX_BOOST_BASE([1.58.0]) 

AC_CONFIG_HEADERS(
    [autoConfig.h]
)
AC_CONFIG_FILES(
    [Makefile
    src/Makefile]
)


# ------------------------------------------------
# Check for header files for getch
# ------------------------------------------------

#AC_CHECK_HEADERS(
#    [conio.h],
#    [ AC_DEFINE([ HAVE_CONIO ], [ 1 ]) ],
#    [ AC_DEFINE([ HAVE_CONIO ], [ 0 ]) ]
#)

#AC_CHECK_HEADERS(
#    [sys/ioctl.h],
#    [ AC_DEFINE([ HAVE_IOCTL ], [ 1 ]) ],
#    [ AC_DEFINE([ HAVE_IOCTL ], [ 0 ]) ]
#)

# ------------------------------------------------
# Check if mpfr library is installed
# ------------------------------------------------

#AC_SEARCH_LIBS(
#    [mpfr_init],
#    [mpfr],
#    [ mpfrInstalled=true; ],
#    [ mpfrInstalled=false; ]
#)
# Pass to Makefile.am
#AM_CONDITIONAL([MPFRINSTALLED], [test x$mpfrInstalled = xtrue])
     
# ------------------------------------------------
# Output
# ------------------------------------------------

AC_OUTPUT

