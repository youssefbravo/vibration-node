/*
 * ringbuf.c - YOUR IMPLEMENTATION GOES HERE.
 *
 * Every function below is a stub so the project compiles. Replace each
 * TODO with real code until `make test-ringbuf` reports 0 failures.
 *
 * Hints (read only if stuck):
 *   - Indices wrap: next = (i + 1) % capacity, or compare with capacity.
 *   - Keeping `count` makes full/empty trivial. Without it, head == tail is
 *     ambiguous; one classic fix is to waste one slot.
 */
#include "ringbuf.h"

bool ringbuf_init(ringbuf_t *rb, uint8_t *storage, size_t capacity)
{
    (void)rb; (void)storage; (void)capacity;
    return false; /* TODO */
}

bool ringbuf_push(ringbuf_t *rb, uint8_t byte)
{
    (void)rb; (void)byte;
    return false; /* TODO */
}

bool ringbuf_pop(ringbuf_t *rb, uint8_t *out)
{
    (void)rb; (void)out;
    return false; /* TODO */
}

bool ringbuf_peek(const ringbuf_t *rb, uint8_t *out)
{
    (void)rb; (void)out;
    return false; /* TODO */
}

bool ringbuf_is_empty(const ringbuf_t *rb)
{
    (void)rb;
    return false; /* TODO */
}

bool ringbuf_is_full(const ringbuf_t *rb)
{
    (void)rb;
    return false; /* TODO */
}

size_t ringbuf_count(const ringbuf_t *rb)
{
    (void)rb;
    return 0; /* TODO */
}

void ringbuf_clear(ringbuf_t *rb)
{
    (void)rb;
    /* TODO */
}
