#include <savr/ringbuffer.h>

#include <avr/interrupt.h>
#include <avr/io.h>

static ringbuffer_t __spi_rx;
static ringbuffer_t __spi_tx;

void spi_init(size_t buffer_size) {
    /* Allocate RX/TX ring buffers */
    ringbuffer_init(&__spi_rx, buffer_size);
    ringbuffer_init(&__spi_tx, buffer_size);

    /* Enable SPI pins and interrupts */
    SPCR |= _BV(SPIE) | _BV(SPE);

    /* Enable all interrupts */
    sei();
}

void spi_config(int data_order, int master, int clock_polarity, int clock_phase) {
    (void)data_order;
    (void)master;
    (void)clock_polarity;
    (void)clock_phase;
}
