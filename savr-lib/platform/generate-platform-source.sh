#!/bin/bash

PINOUT_FILE="$1"

PIN_COUNT=$(wc -l < "$PINOUT_FILE")

echo "#include <savr/platform.h>"
echo "volatile uint8_t* const __pinout[PIN_COUNT][3] = {"
while read -r PIN_LINE
do
    read -ra PIN_DESC <<<"$PIN_LINE"
    DDR="${PIN_DESC[0]}"
    PORT="${PIN_DESC[1]}"
    PIN="${PIN_DESC[2]}"
    IFS=, read -ra NAMES <<<"${PIN_DESC[4]}"

    echo "    { &$DDR, &$PORT, &$PIN }, /* ${NAMES[@]} */"
done < "$PINOUT_FILE"
echo "};"
echo
echo "const uint8_t __pinbv[PIN_COUNT] = {"
while read -r PIN_LINE
do
    read -ra PIN_DESC <<<"$PIN_LINE"
    DDR="${PIN_DESC[0]}"
    PORT="${PIN_DESC[1]}"
    PIN="${PIN_DESC[2]}"
    BIT="${PIN_DESC[3]}"
    IFS=, read -ra NAMES <<<"${PIN_DESC[4]}"

    echo "    BV_PIN_$NAMES, /* ${NAMES[@]} */"
done < "$PINOUT_FILE"
echo "};"
