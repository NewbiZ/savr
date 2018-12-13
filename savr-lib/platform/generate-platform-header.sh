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

PIN_I=0
while read -r LINE
do
    read -ra LINE_DESC <<<"$LINE"
    SECTION="${LINE_DESC[0]}"
    case "$SECTION" in
        \[pinout\])
            DDR="${LINE_DESC[1]}"
            PORT="${LINE_DESC[2]}"
            PIN="${LINE_DESC[3]}"
            BIT="${LINE_DESC[4]}"
            IFS=, read -ra NAMES <<<"${LINE_DESC[5]}"

            for NAME in "${NAMES[@]}"
            do
                NAME="PIN_$NAME"
                echo "/* $NAME */"
                echo "#define $NAME      $PIN_I"
                echo "#define DDR_$NAME  $DDR"
                echo "#define PORT_$NAME $PORT"
                echo "#define PIN_$NAME  $PIN"
                echo "#define BIT_$NAME  $BIT"
                echo "#define BV_$NAME   _BV($BIT)"
                echo
            done

            let I++
            ;;
        \[uart\])
            MAX_UART="${LINE_DESC[2]}"
            echo "#define MAX_UART $MAX_UART"
            echo
            for UARTN in $(seq 0 $(( $MAX_UART - 1 )))
            do
                echo "#define UART${UARTN} ${UARTN}"
            done
            echo
            ;;
    esac
done < <(awk '/\[[^]]*\]/ {a=$1; next} NF {gsub("=", " = "); print a" "$0}' "$PINOUT_FILE")
