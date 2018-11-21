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

#include <stdlib.h>

void ringbuffer_init(ringbuffer_t* rb, size_t size) {
    rb->size = 0;
    if ((rb->buffer = (uint8_t*)malloc(size))) {
        rb->size = size;
    }
    rb->head = rb->tail = rb->buffer;
}

void ringbuffer_release(ringbuffer_t* rb) {
    rb->size = 0;
    free((uint8_t*)rb->buffer);
}

size_t ringbuffer_size(const ringbuffer_t* rb) {
    return rb->size;
}

size_t ringbuffer_read(ringbuffer_t* rb, uint8_t* buffer, size_t size) {
    size_t count = 0;
    while ((rb->head != rb->tail) && (count < size)) {
        *buffer++ = *rb->head++;
        ++count;
        if (rb->head >= rb->buffer+rb->size)
            rb->head = rb->buffer;
    }
    return count;
}

size_t ringbuffer_write(ringbuffer_t* rb, const uint8_t* buffer, size_t size) {
    size_t count = 0;
    while (count++ < size) {
        *rb->tail++ = *buffer++;
        if (rb->tail >= rb->buffer+rb->size)
            rb->tail = rb->buffer;
        if (rb->tail == rb->head) {
            ++rb->head;
            if (rb->head >= rb->buffer+rb->size)
                rb->head = rb->buffer;
        }
    }
    return count-1;
}

int ringbuffer_empty(const ringbuffer_t* rb) {
    return rb->head == rb->tail;
}
