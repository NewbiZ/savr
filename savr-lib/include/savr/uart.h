#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <avr/io.h>

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

void uart_init(uint8_t uart, uint16_t baud, size_t buffer_size, uint8_t echo);
void uart_release(uint8_t uart);

size_t uart_read(uint8_t uart, uint8_t* buffer, size_t size);
size_t uart_write(uint8_t uart, const uint8_t* buffer, size_t size);

#endif /* UART_H */
