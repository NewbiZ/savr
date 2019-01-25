/*
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
*/
#ifndef SAVR_PLATFORM_H
#define SAVR_PLATFORM_H

#include <savr/savr.h>
#include <avr/io.h>

/* Guess platform */
#if defined(__AVR_ATmega328__)
#   include <savr/platform/atmega328.pinout.h>
#elif defined(__AVR_ATmega2560__)
#   include <savr/platform/atmega2560.pinout.h>
#else
#   pragma GCC error "Unsupported MCU"
#endif

/* Pinout helpers */
#define PIN_DDR(P)  *__pinout[P][0]
#define PIN_PORT(P) *__pinout[P][1]
#define PIN_PIN(P)  *__pinout[P][2]
#define PIN_BIT(P)  BIT_##P
#define PIN_BV(P)   __pinbv[P]

/* UART helpers */
#define UBRR(U)  *__ubrr[U]
#define UCSRA(U) *__ucsr[U][0]
#define UCSRB(U) *__ucsr[U][1]
#define UCSRC(U) *__ucsr[U][2]
#define UDR(U)   *__udr[U]
#define UDRE(U)  __udre[U]
#define RXC(U)   __rxc[U]

extern volatile uint8_t* const __pinout[PIN_COUNT][3];
extern const uint8_t __pinbv[PIN_COUNT];
extern volatile uint16_t* const __ubrr[MAX_UART];
extern volatile uint8_t* const __ucsr[MAX_UART][3];
extern volatile uint8_t* const __udr[MAX_UART];
extern const uint8_t __udre[MAX_UART];
extern const uint8_t __rxc[MAX_UART];

#endif  /* SAVR_PLATFORM_H */
