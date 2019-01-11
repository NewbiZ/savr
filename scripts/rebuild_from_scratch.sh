#!/bin/bash -eu

if [ ! -f "$PWD/configure.ac" ]
then
    echo "Please run this script from the root savr directory"
    exit 1
fi
rm -rf $PWD/install
make clean maintainer-clean
"$PWD/autogen.sh"
"$PWD/configure" --build=x86_64-unknown-linux-gnu --host=avr --with-mcu-freq=8000000 --prefix="$PWD/install"
make clean all check install
