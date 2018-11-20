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
#include <savr/ringbuffer.h>

#include <avr/interrupt.h>

static ringbuffer_t __uart_rx[MAX_UART];
static ringbuffer_t __uart_tx[MAX_UART];
static uint8_t __echo[MAX_UART];

void uart_init(uint8_t uart, uint16_t baud, size_t buffer_size, uint8_t echo) {
    uint16_t ubrr_value;
    volatile uint16_t* ubrr_register;
    volatile uint8_t* ucsra;
    volatile uint8_t* ucsrb;
    volatile uint8_t* ucsrc;

    switch (uart) {
#if MAX_UART >= 1
        case UART0:
            ubrr_register = &UBRR0;
            ucsra = &UCSR0A;
            ucsrb = &UCSR0B;
            ucsrc = &UCSR0C;
#endif /* MAXUART >= 1 */
#if MAX_UART >= 2
        case UART1:
            ubrr_register = &UBRR1;
            ucsra = &UCSR1A;
            ucsrb = &UCSR1B;
            ucsrc = &UCSR1C;
#endif /* MAXUART >= 2 */
#if MAX_UART >= 3
        case UART2:
            ubrr_register = &UBRR2;
            ucsra = &UCSR2A;
            ucsrb = &UCSR2B;
            ucsrc = &UCSR2C;
#endif /* MAXUART >= 3 */
#if MAX_UART >= 4
        case UART3:
            ubrr_register = &UBRR3;
            ucsra = &UCSR3A;
            ucsrb = &UCSR3B;
            ucsrc = &UCSR3C;
#endif /* MAXUART >= 4 */
    }

    /* Allocate RX/TX ring buffers */
    ringbuffer_init(&__uart_rx[uart], buffer_size);
    ringbuffer_init(&__uart_tx[uart], buffer_size);

    /* Remember echo flag */
    __echo[uart] = echo;

    /* Compute UART speed */
    ubrr_value = (F_CPU + 8UL * baud) / (16UL * baud) - 1UL;
    *ubrr_register = ubrr_value;

    /* Disable 2x mode */
    *ucsra &= ~_BV(U2X0);

    /* Enable 8bit data */
    *ucsrc = _BV(UCSZ01) | _BV(UCSZ00);

    /* Enable RX and TX pins for UART */
    *ucsrb = _BV(RXEN0) | _BV(TXEN0);

    /* Enable UART interrupts */
    *ucsrb |= _BV(RXCIE0) | _BV(UDRIE0);

    /* Enable all interrupts */
    sei();
}

void uart_release(uint8_t uart) {
    (void)uart;
    /* TODO */
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
    }

/* Generate interrupt service routines for all available UARTS.
 * Note: On MCUs with a single UART, the "0" suffix should not appear in
 *       symbols.
 */
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

size_t uart_read(uint8_t uart, uint8_t* buffer, size_t size) {
    /* Read received bytes from the RX rinf buffer */
    size_t sz;
    cli();
    sz = ringbuffer_read(&__uart_rx[uart], buffer, size);
    sei();
    return sz;
}

size_t uart_write(uint8_t uart, const uint8_t* buffer, size_t size) {
    /* Write sent bytes to the TX ring buffer */
    size_t sz;
    cli();
    sz = ringbuffer_write(&__uart_tx[uart], buffer, size);
    sei();
    return sz;
}
