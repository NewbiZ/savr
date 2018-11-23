#!/bin/bash

PINOUT_FILE="$1"

echo "/*"
echo " * This header was automatically generated. Do not include it directly"
echo " * in your application, as it is not protected for multiple inclusions."
echo " * Use <savr/platform.h> instead, that will automatically select the "
echo " * proper pinout definition based on your controller."
echo " */"
echo

PIN_COUNT=$(wc -l < "$PINOUT_FILE")

echo "#define PIN_COUNT $PIN_COUNT"

I=0
while read -r PIN_LINE
do
    read -ra PIN_DESC <<<"$PIN_LINE"
    DDR="${PIN_DESC[0]}"
    PORT="${PIN_DESC[1]}"
    PIN="${PIN_DESC[2]}"
    BIT="${PIN_DESC[3]}"
    IFS=, read -ra NAMES <<<"${PIN_DESC[4]}"

    for NAME in "${NAMES[@]}"
    do
        NAME="PIN_$NAME"
        echo "/* $NAME */"
        echo "#define $NAME      $I"
        echo "#define DDR_$NAME  $DDR"
        echo "#define PORT_$NAME $PORT"
        echo "#define PIN_$NAME  $PIN"
        echo "#define BIT_$NAME  $BIT"
        echo "#define BV_$NAME   _BV($BIT)"
        echo
    done

    let I++
done < "$PINOUT_FILE"
