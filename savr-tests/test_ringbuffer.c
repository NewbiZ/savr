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
#include <savr/ringbuffer.h>

#include "test.h"

void test()
{
    uint32_t input, output;
    ringbuffer_t rb;

    ringbuffer_init(&rb, 128);

    if (ringbuffer_size(&rb) != 128)
        test_failure("ringbuffer size after init");

    input = 0xdeadbeef;
    ringbuffer_write(&rb, (const char*)&input, sizeof(input));

    ringbuffer_read(&rb, (char*)&output, sizeof(output));

    ringbuffer_release(&rb);

    if (ringbuffer_size(&rb) != 0)
        test_failure("ringbuffer size after release");

    if (output != 0xdeadbeef)
        test_failure("ringbuffer i/o");
}
