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
    DDR_PIN_MOSI |= BV_PIN_MOSI | BV_PIN_SCK;

    /* Enable SPI pins, set master mode  */
    SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}

void spi_master_release() {
    /* TODO: SPI master release */
}

void spi_master_readwrite(uint8_t* buffer, size_t size) {
    while (buffer < buffer+size) {
        SPDR = *buffer;
        while (!(SPSR & (_BV(SPIF))));
        *buffer++ = SPDR;
    }
}

void spi_master_write(const uint8_t* buffer, size_t size) {
    while (buffer < buffer+size) {
        SPDR = *buffer++;
        while (!(SPSR & (_BV(SPIF))));
    }
}

void spi_master_read(uint8_t* buffer, size_t size) {
    while (buffer < buffer+size) {
        SPDR = 0;
        while (!(SPSR & (_BV(SPIF))));
        *buffer++ = SPDR;
    }
}
