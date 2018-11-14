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

AM_CPPFLAGS = \
	-I$(top_srcdir)/savr-lib/include \
	-I$(top_builddir)/savr-lib/include

AM_CFLAGS = \
	-pedantic \
	-Wformat-security \
	-W -Wall \
	-Werror \
	-Wpointer-arith \
	-Winit-self \
	-Wformat=2 \
	-Wcast-align \
	-Wlogical-op \
	-Wshadow \
	-fvisibility=hidden \
	-Wl,-O1 \
	-Wl,--discard-all \
	-Wl,--no-undefined \
	-mmcu=$(MCU) \
	-Os \
	-mcall-prologues \
	-std=c89

check_PROGRAMS = \
	test_dummy \
	test_ringbuffer

#
# test_dummy
#
test_dummy_SOURCES = \
	$(top_srcdir)/savr-tests/test_dummy.c \
	$(top_srcdir)/savr-tests/test.h

test_dummy_LDADD = \
	$(top_builddir)/savr-lib/libsavr.la

#
# test_ringbuffer
#
test_ringbuffer_SOURCES = \
	$(top_srcdir)/savr-tests/test_ringbuffer.c \
	$(top_srcdir)/savr-tests/test.h

test_ringbuffer_LDADD = \
	$(top_builddir)/savr-lib/libsavr.la

%.hex: %
	$(AM_V_GEN)avr-objcopy -O ihex $< $@

TESTS = ${check_PROGRAMS:=.hex}

TEST_EXTENSIONS = .hex

HEX_LOG_COMPILER = ./test-compiler.sh

CLEANFILES = \
	${check_PROGRAMS:=.hex}

MAINTAINERCLEANFILES = \
	Makefile.in

