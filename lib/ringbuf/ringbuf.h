/*
 * ringbuf.h - fixed-size byte ring buffer (FIFO).
 *
 * EXERCISE (Step 1): implement every function in ringbuf.c so that
 * `make test-ringbuf` passes. Do NOT use malloc: the caller owns the storage.
 *
 * Later (Step 2) you will reuse this exact module to buffer UART bytes that
 * arrive in an interrupt, so think about which fields an ISR writes and
 * which fields the main loop writes.
 */
#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *buf;      /* storage provided by the caller            */
    size_t   capacity; /* number of bytes the buffer can hold       */
    size_t   head;     /* index where the next byte is written      */
    size_t   tail;     /* index where the next byte is read         */
    size_t   count;    /* number of bytes currently stored          */
} ringbuf_t;

/* Set up an empty buffer on top of `storage` (capacity bytes).
 * Returns false if rb or storage is NULL, or capacity is 0. */
bool ringbuf_init(ringbuf_t *rb, uint8_t *storage, size_t capacity);

/* Append one byte. Returns false (and changes nothing) if the buffer is full.
 * A full buffer must NOT overwrite the oldest data. */
bool ringbuf_push(ringbuf_t *rb, uint8_t byte);

/* Remove the oldest byte into *out. Returns false if the buffer is empty. */
bool ringbuf_pop(ringbuf_t *rb, uint8_t *out);

/* Look at the oldest byte without removing it. Returns false if empty. */
bool ringbuf_peek(const ringbuf_t *rb, uint8_t *out);

bool   ringbuf_is_empty(const ringbuf_t *rb);
bool   ringbuf_is_full(const ringbuf_t *rb);
size_t ringbuf_count(const ringbuf_t *rb);

/* Drop all stored bytes (capacity and storage stay the same). */
void ringbuf_clear(ringbuf_t *rb);

#endif /* RINGBUF_H */
