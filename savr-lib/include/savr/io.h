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
#ifndef SAVR_IO_H
#define SAVR_IO_H

#include <stdint.h>

#define LOW  0
#define HIGH 1

#define INPUT  0
#define OUTPUT 1

#define TRISTATE 0
#define PULLUP   1

/* Set pin in input/output mode */
void pin_mode(uint8_t pin, uint8_t direction, uint8_t state);

/* Read or write to a pin */
void pin_write(uint8_t pin, uint8_t value);
uint8_t pin_read(uint8_t pin);

#endif /* SAVR_IO_H */
