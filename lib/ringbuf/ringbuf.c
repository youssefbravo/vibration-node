/*
 * ringbuf.c - fixed-size byte FIFO on caller-provided storage.
 *
 * Not interrupt-safe yet: push and pop both modify `count`.
 */
#include "ringbuf.h"

bool ringbuf_init(ringbuf_t *rb, uint8_t *storage, size_t capacity)
{
    if (rb == NULL || storage == NULL || capacity == 0) {
        return false;
    }

    rb->buf      = storage;
    rb->capacity = capacity;
    rb->head     = 0;
    rb->tail     = 0;
    rb->count    = 0;
    return true;
}

bool ringbuf_push(ringbuf_t *rb, uint8_t byte)
{
    if (rb->count == rb->capacity) {
        return false;               /* full: keep the oldest data */
    }

    rb->buf[rb->head] = byte;
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count++;
    return true;
}

bool ringbuf_pop(ringbuf_t *rb, uint8_t *out)
{
    if (rb->count == 0) {
        return false;
    }

    *out = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count--;
    return true;
}

bool ringbuf_peek(const ringbuf_t *rb, uint8_t *out)
{
    if (rb->count == 0) {
        return false;
    }

    *out = rb->buf[rb->tail];
    return true;
}

bool ringbuf_is_empty(const ringbuf_t *rb)
{
    return rb->count == 0;
}

bool ringbuf_is_full(const ringbuf_t *rb)
{
    return rb->count == rb->capacity;
}

size_t ringbuf_count(const ringbuf_t *rb)
{
    return rb->count;
}

void ringbuf_clear(ringbuf_t *rb)
{
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;
}