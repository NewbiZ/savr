#!/bin/bash

PINOUT_FILE="$1"

echo "/*"
echo " * This source file was automatically generated. Do not use it directly"
echo " * in your application."
echo " */"
echo
echo "#include <savr/platform.h>"
echo
echo "volatile uint8_t* const __pinout[PIN_COUNT][3] = {"

while read -r LINE
do
    read -ra LINE_DESC <<<"$LINE"
    SECTION="${LINE_DESC[0]}"
    case "$SECTION" in
        \[pinout\])
            DDR="${LINE_DESC[1]}"
            PORT="${LINE_DESC[2]}"
            PIN="${LINE_DESC[3]}"
            IFS=, read -ra NAMES <<<"${LINE_DESC[5]}"

            echo "    { &$DDR, &$PORT, &$PIN }, /* ${NAMES[@]} */"
            ;;
    esac
done < <(awk '/\[[^]]*\]/ {a=$1; next} NF {gsub("=", " = "); print a" "$0}' "$PINOUT_FILE")
echo "};"
echo

echo "const uint8_t __pinbv[PIN_COUNT] = {"
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

            echo "    BV_PIN_$NAMES, /* ${NAMES[@]} */"
            ;;
        \[uart\])
            MAX_UART="${LINE_DESC[2]}"
            ;;
    esac
done < <(awk '/\[[^]]*\]/ {a=$1; next} NF {gsub("=", " = "); print a" "$0}' "$PINOUT_FILE")
echo "};"
echo

UART_I=0
echo "volatile uint16_t* const __ubrr[MAX_UART] = {"
while [[ $UART_I < $MAX_UART ]]
do
    echo "    &UBRR${UART_I},"
    let UART_I++;
done
echo "};"
echo

UART_I=0
echo "volatile uint8_t* const __ucsr[MAX_UART][3] = {"
while [[ $UART_I < $MAX_UART ]]
do
    echo "    { &UCSR${UART_I}A, &UCSR${UART_I}B, &UCSR${UART_I}C },"
    let UART_I++;
done
echo "};"
echo

UART_I=0
echo "volatile uint8_t* const __udr[MAX_UART] = {"
while [[ $UART_I < $MAX_UART ]]
do
    echo "    &UDR${UART_I},"
    let UART_I++;
done
echo "};"
echo

UART_I=0
echo "const uint8_t __rxc[MAX_UART] = {"
while [[ $UART_I < $MAX_UART ]]
do
    echo "    RXC${UART_I},"
    let UART_I++;
done
echo "};"
echo

UART_I=0
echo "const uint8_t __udre[MAX_UART] = {"
while [[ $UART_I < $MAX_UART ]]
do
    echo "    UDRE${UART_I},"
    let UART_I++;
done
echo "};"
