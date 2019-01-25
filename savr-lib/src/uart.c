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
#include <savr/savr.h>
#include <savr/uart.h>
#include <savr/platform.h>

#ifdef SAVR_ENABLE_UART
#include <savr/ringbuffer.h>
#include <avr/interrupt.h>

static ringbuffer_t __uart_rx[MAX_UART];
static ringbuffer_t __uart_tx[MAX_UART];
#endif /* SAVR_ENABLE_UART */
static uint8_t __echo[MAX_UART];

void uart_init(uint8_t uart, uint16_t baud, size_t buffer_size, uint8_t echo) {
    /* Remember echo flag */
    __echo[uart] = echo;

    /* Compute UART clock divider */
    UBRR(uart) = (F_CPU + 8UL * baud) / (16UL * baud) - 1UL;

    /* Disable 2x mode */
    /* TODO: handle 2x mode and tolerance */
    UCSRA(uart) &= ~_BV(U2X0);

    /* Enable 8bit data */
    UCSRC(uart) = _BV(UCSZ01) | _BV(UCSZ00);

    /* Enable RX and TX pins for UART */
    UCSRB(uart) = _BV(RXEN0) | _BV(TXEN0);

#ifdef SAVR_ENABLE_UART
    /* Allocate RX/TX ring buffers */
    ringbuffer_init(&__uart_rx[uart], buffer_size);
    ringbuffer_init(&__uart_tx[uart], buffer_size);

    /* Enable UART interrupts */
    /* RX will be enabled when there is something to send */
    UCSRB(uart) |= _BV(RXCIE0);

    /* Globally enable interrupts */
    sei();
#else /* SAVR_ENABLE_UART */
    (void)buffer_size;
#endif /* SAVR_ENABLE_UART */
}

void uart_release(uint8_t uart) {
    (void)uart;
    /* TODO: release UART resources */
}

#define ISR_USART_RX(UARTN, VEC, UDR)                           \
    ISR(VEC) {                                                  \
        uint8_t received = UDR;                                 \
        /* Write received byte to the RX ring buffer */         \
        ringbuffer_write(&__uart_rx[UARTN], &received, 1);      \
        if (__echo[UARTN]) {                                    \
            /* Echo received bytes */                           \
            ringbuffer_write(&__uart_tx[UARTN], &received, 1);  \
        }                                                       \
    }

#define ISR_USART_UDRE(UARTN, VEC, UDR)                     \
    ISR(VEC) {                                              \
        uint8_t sent;                                       \
        /* Read sent byte from the TX ring buffer */        \
        if (ringbuffer_read(&__uart_tx[UARTN], &sent, 1))   \
            UDR = sent;                                     \
        /* Nothing to send, disable interrupts until then */\
        else                                                \
            UCSRB(UARTN) &= ~_BV(UDRIE0);                   \
    }

/* Generate interrupt service routines for all available UARTS.
 * On MCUs with a single UART, the "0" suffix should not appear in symbols */
#ifdef SAVR_ENABLE_UART
#if MAX_UART == 1
ISR_USART_RX(0, USART_RX_vect, UDR0)
ISR_USART_UDRE(0, USART_UDRE_vect, UDR0)
#endif /* MAXUART == 1 */
#if MAX_UART >= 2
ISR_USART_RX(0, USART0_RX_vect, UDR0)
ISR_USART_UDRE(0, USART0_UDRE_vect, UDR0)
ISR_USART_RX(1, USART1_RX_vect, UDR1)
ISR_USART_UDRE(1, USART1_UDRE_vect, UDR1)
#endif /* MAXUART >= 2 */
#if MAX_UART >= 3
ISR_USART_RX(2, USART2_RX_vect, UDR2)
ISR_USART_UDRE(2, USART2_UDRE_vect, UDR2)
#endif /* MAXUART >= 3 */
#if MAX_UART >= 4
ISR_USART_RX(3, USART3_RX_vect, UDR3)
ISR_USART_UDRE(3, USART3_UDRE_vect, UDR3)
#endif /* MAXUART >= 4 */
#endif /* SAVR_ENABLE_UART */

size_t uart_read(uint8_t uart, uint8_t* buffer, size_t size) {
    size_t sz;
#ifdef SAVR_ENABLE_UART
    /* Interrupts should be disabled during ringbuffer read/write, since
     * pointer arithmetic on 16b addresses are not atomic on 8b controllers */
    cli();
    /* Read bytes from the RX ring buffer that was enqueued by the ISR */
    sz = ringbuffer_read(&__uart_rx[uart], buffer, size);
    sei();
#else /* SAVR_ENABLE_UART */
    sz = size;
    while (size--) {
        while ((!(UCSRA(uart))) & (1 << RXC(uart)));
        *buffer++ = UDR(uart);
    }
    if (__echo[uart]) {
        uart_write(uart, buffer, size);
    }
#endif /* SAVR_ENABLE_UART */
    return sz;
}

size_t uart_write(uint8_t uart, const uint8_t* buffer, size_t size) {
    size_t sz;
#ifdef SAVR_ENABLE_UART
    /* Interrupts should be disabled during ringbuffer read/write, since
     * pointer arithmetic on 16b addresses are not atomic on 8b controllers */
    cli();
    /* Write bytes to the TX ring buffer that will be dequeued by the ISR */
    sz = ringbuffer_write(&__uart_tx[uart], buffer, size);
    sei();
    UCSRB(uart) |= _BV(UDRIE0);
#else /* SAVR_ENABLE_UART */
    sz = size;
    while (size--) {
        while (!(UCSRA(uart) & (1 << UDRE(uart))));
        UDR(uart) = *buffer++;
    }
#endif /* SAVR_ENABLE_UART */
    return sz;
}
