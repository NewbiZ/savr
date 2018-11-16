# Copyright (C) 2016 Aurelien Vallee
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Start the configuration phase
# =============================
AC_PREREQ(2.59)

m4_define([AC_SAVR_API_MAJOR], [1])
m4_define([AC_SAVR_API_MINOR], [0])
m4_define([AC_SAVR_API_PATCH], [0])
m4_define([AC_SAVR_API_VERSION], [AC_SAVR_API_MAJOR.AC_SAVR_API_MINOR.AC_SAVR_API_PATCH])

AC_DEFUN([AC_SAVR_ABI_CUR], [0])
AC_DEFUN([AC_SAVR_ABI_REV], [0])
AC_DEFUN([AC_SAVR_ABI_AGE], [0])
AC_DEFUN([AC_SAVR_ABI_VERSION],
         [AC_SAVR_ABI_CUR:AC_SAVR_ABI_REV:AC_SAVR_ABI_AGE])

AC_INIT([savr], [AC_SAVR_API_VERSION],
    [vallee.aurelien@gmail.com], [savr],
    [https://github.com/NewbiZ/savr])

AM_INIT_AUTOMAKE([foreign])
LT_INIT

m4_ifdef([AM_SILENT_RULES], [
    AM_SILENT_RULES([yes])
])

AC_DEFINE(SAVR_API_MAJOR, AC_SAVR_API_MAJOR, [SAVR API major number])
AC_DEFINE(SAVR_API_MINOR, AC_SAVR_API_MINOR, [SAVR API minor number])
AC_DEFINE(SAVR_API_PATCH, AC_SAVR_API_PATCH, [SAVR API patch level])
AC_DEFINE(SAVR_API_VERSION, "AC_SAVR_API_VERSION", [SAVR API version])

AC_DEFINE(SAVR_ABI_CUR, AC_SAVR_ABI_CUR, [SAVR ABI current number])
AC_DEFINE(SAVR_ABI_REV, AC_SAVR_ABI_REV, [SAVR ABI revision number])
AC_DEFINE(SAVR_ABI_AGE, AC_SAVR_ABI_AGE, [SAVR ABI age number])
AC_DEFINE(SAVR_ABI_VERSION, "AC_SAVR_ABI_VERSION", [SAVR ABI version])

# Libtool
# =========
LTVER=AC_SAVR_ABI_VERSION
AC_SUBST(LTVER)

# Check build tools
# =================
AC_PROG_CC
AC_LANG([C])
AC_PROG_LIBTOOL
AM_PROG_CC_C_O

# Documentation
# =============
AC_CHECK_PROG(HAVE_SPHINX, sphinx-build, yes, no)
if test "x$HAVE_SPHINX" = "xno"
then
    AC_MSG_WARN([Sphinx not found - documentation generation disabled])
fi
AM_CONDITIONAL([HAVE_SPHINX], [test "x$HAVE_SPHINX" = "xyes"])

# Cross compilation
# =================
AC_MSG_CHECKING([if target host is avr])
case "$host" in
    avr*)
        AC_MSG_RESULT([yes])
        ;;
    *)
        AC_MSG_RESULT([no])
        AC_MSG_WARN()
        AC_MSG_WARN(savr must be built using an avr cross-compiler.)
        AC_MSG_WARN(Try configuring with:)
        AC_MSG_WARN("$0 --build=$build --host=avr")
        AC_MSG_WARN()
        AC_MSG_ERROR(aborting configure)
        ;;
esac

AC_MSG_CHECKING([if target mcu is compliant])
case "$MCU" in
    atmega*)
        AC_MSG_RESULT([yes])
        ;;
    *)
        AC_MSG_RESULT([no])
        AC_MSG_WARN()
        AC_MSG_WARN(savr must be built for a target mcu.)
        AC_MSG_WARN(Try configuring with:)
        AC_MSG_WARN("$0 --build=$build --host=avr MCU=atmega328")
        AC_MSG_WARN()
        AC_MSG_ERROR(aborting configure)
        ;;
esac

AC_SUBST(MCU)

# Dependencies
# ==================
AC_CONFIG_MACRO_DIR([m4])
PKG_PROG_PKG_CONFIG
PKG_INSTALLDIR

#AX_PKG_CHECK_MODULES([],[],[])

# Finish the configuration phase
# ==============================
AC_CONFIG_FILES([Makefile \
                 savr-bin/Makefile \
                 savr-lib/Makefile \
                 savr-lib/savr.pc \
                 savr-tests/Makefile \
                 savr-docs/Makefile])
AC_CONFIG_FILES([savr-tests/test-compiler.sh], \
                [chmod +x savr-tests/test-compiler.sh])
AC_CONFIG_HEADERS([config.h savr-lib/include/savr/savr.h])

AC_OUTPUT
