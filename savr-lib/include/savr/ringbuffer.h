#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t size;
    volatile uint8_t* head;
    volatile uint8_t* tail;
    uint8_t* buffer;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t* rb, size_t size);
void ringbuffer_release(ringbuffer_t* rb);

size_t ringbuffer_size(const ringbuffer_t* rb);
size_t ringbuffer_read(ringbuffer_t* rb, uint8_t* buffer, size_t size);
size_t ringbuffer_write(ringbuffer_t* rb, const uint8_t* buffer, size_t size);
int ringbuffer_empty(const ringbuffer_t* rb);

#endif /* RINGBUFFER_H */
