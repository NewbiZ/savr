Simple AVR
==========

Build
-----

Typical installation instructions:

    $ ./autogen.sh
    $ ./configure --build=x86_64-unknown-linux-gnu --host=avr --prefix=$PWD/install
    $ make
    $ make check
    $ make install

Usage
-----

Once installed, the recommended procedure to include and link against `savr` is
the use of `pkg-config`.

Each platform has its own `savr` library in a separate directory under
`${prefix}/lib/savr` (e.g. `/usr/lib/savr/atmega328`), while the include
directory structure is common for all builds (pre-processor is used to include
the proper files).

To build and link against `savr`, you just have to provide `pkg-config` with
your target MCU, and it will provide you with all the proper compiler and
linker flags.

    $ avr-gcc -mmcu=atmega328 program.c -o program.o $(pkg-config --define-variable=mcu=atmega328 --cflags --libs savr)
    $ avr-objcopy -O ihex program.o program.hex

For this to work, make sure that `${prefix}/lib/pkgconfig` is in your
`PKG_CONFIG_PATH` environment variable. That should be the case if you
installed `savr` is a standard location.

Dependencies
------------
savr:
- avr-gcc

tests:
- avrlibc
- simavr

Authors
-------
- Aurelien Vallee <vallee.aurelien@gmail.com>

Licensed under MIT/X
--------------------
Copyright (C) 2016 Aurelien Vallee

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
