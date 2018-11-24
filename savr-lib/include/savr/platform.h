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
#   define SAVR_MCU atmega328
#   include <savr/atmega328/atmega328.pinout.h>
#elif defined(__AVR_ATmega2560__)
#   define SAVR_MCU atmega2560
#   include <savr/atmega2560/atmega2560.pinout.h>
#else
#   pragma GCC error "Unsupported MCU"
#endif

/* Try to guess the number of UART available on the MCU.
 * It is highly suggested to use the constants UART0, UART1, UART2 and UART3
 * to access the different UARTs, as they will statically assert that the
 * UARTs are supported for this MCU. For instance, prefer:
 *     uart_init(UART1, ...);
 * to
 *     uart_init(1, ...);
 */
#ifndef MAX_UART
#   if defined(UBRR3)
#       define UART0 0
#       define UART1 1
#       define UART2 2
#       define UART3 3
#       define MAX_UART 4
#   elif defined(UBRR2)
#       define UART0 0
#       define UART1 1
#       define UART2 2
#       define MAX_UART 3
#   elif defined(UBRR1)
#       define UART0 0
#       define UART1 1
#       define MAX_UART 2
#   elif defined(UBRR0)
#       define UART0 0
#       define MAX_UART 1
#   endif
#endif /* MAX_UART */

#ifndef MAX_UART
#    pragma GCC error "MAX_UART not defined and failed to guess it"
#endif

/* Platform-specific definitions than cannot be otherwise guessed */
#define PLATFORM_HEADER_PATH(X) <savr/platform/X.h>
#define PLATFORM_HEADER(X) PLATFORM_HEADER_PATH(X)

/* Pinout helpers */
#define PIN_DDR(P)  *__pinout[P][0]
#define PIN_PORT(P) *__pinout[P][1]
#define PIN_PIN(P)  *__pinout[P][2]
#define PIN_BIT(P)  BIT_##P
#define PIN_BV(P)   __pinbv[P]

extern volatile uint8_t* const __pinout[PIN_COUNT][3];
extern const uint8_t __pinbv[PIN_COUNT];

#endif  /* SAVR_PLATFORM_H */
