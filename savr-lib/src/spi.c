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
#include <savr/spi.h>
#include <savr/platform.h>

#include <avr/io.h>

void spi_master_init() {
    DDR_PIN_MOSI |= BV_PIN_MOSI | BV_PIN_SCK | BV_PIN_SS;

    /* Enable SPI pins, set master mode  */
    SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPI2X);
}

void spi_master_release() {
    /* TODO: SPI master release */
}

/* Send a single byte */
uint8_t spi_send(uint8_t send) {
    SPDR = send;
    while (!(SPSR & _BV(SPIF)));
    return SPDR;
}

/* Send count bytes, and store the received values in buffer if not NULL */
void spi_sendn(uint8_t send, uint8_t* buffer, size_t count) {
    size_t i;
    uint8_t recv;
    for (i=0; i<count; ++i) {
        recv = spi_send(send);
        if (buffer != NULL)
            buffer[i] = recv;
    }
}

/* Poll until the received value matches the provided mask */
uint8_t spi_poll_until_mask(uint8_t send, uint8_t mask, uint8_t retries) {
    uint8_t recv;
    do {
        recv = spi_send(send);
    } while (retries-- && !(recv & mask));
    return recv;
}

/* Poll until the received value equals the provided value */
uint8_t spi_poll_until_value(uint8_t send, uint8_t value, uint8_t retries) {
    uint8_t recv;
    do {
        recv = spi_send(send);
    } while (retries-- && !(recv == value));
    return recv;
}

/* Poll as long as the received value matches the provided mask */
uint8_t spi_poll_while_mask(uint8_t send, uint8_t mask, uint8_t retries) {
    uint8_t recv;
    do {
        recv = spi_send(send);
    } while (retries-- && (recv & mask));
    return recv;
}

/* Poll as long as the received value equals the provided value */
uint8_t spi_poll_while_value(uint8_t send, uint8_t value, uint8_t retries) {
    uint8_t recv;
    do {
        recv = spi_send(send);
    } while (retries-- && (recv == value));
    return recv;
}
