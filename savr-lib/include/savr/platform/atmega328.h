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
#ifndef SAVR_PLATFORM_ATMEGA328_H
#define SAVR_PLATFORM_ATMEGA328_H

/* SPI */
#define SPI_MOSI_DDR   DDRB
#define SPI_MOSI_PORT  PORTB
#define SPI_MOSI_PIN   PINB
#define SPI_MOSI_BIT   3

#define SPI_MISO_DDR   DDRB
#define SPI_MISO_PORT  PORTB
#define SPI_MISO_PIN   PINB
#define SPI_MISO_BIT   4

#define SPI_SCK_DDR   DDRB
#define SPI_SCK_PORT  PORTB
#define SPI_SCK_PIN   PINB
#define SPI_SCK_BIT   5

#endif /* SAVR_PLATFORM_ATMEGA328_H */
