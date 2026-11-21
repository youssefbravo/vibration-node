/*
 * bitops.h - bit and bit-field helpers for memory-mapped registers.
 *
 * Arguments may be evaluated more than once; don't pass expressions
 * with side effects (e.g. BIT_SET(reg, i++)).
 */
#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

#define BIT(n)              (1u << (n))

#define BIT_SET(reg, n)     do { (reg) |=  BIT(n); } while (0)
#define BIT_CLR(reg, n)     do { (reg) &= ~BIT(n); } while (0)
#define BIT_TGL(reg, n)     do { (reg) ^=  BIT(n); } while (0)
#define BIT_GET(reg, n)     (((reg) >> (n)) & 1u)

/* width: 1..31, pos + width <= 32 */
#define FIELD_MASK(width)   ((1u << (width)) - 1u)

/* Single read-modify-write: the register never sees a half-updated field. */
#define FIELD_WRITE(reg, pos, width, val)                             \
    do {                                                              \
        (reg) = ((reg) & ~(FIELD_MASK(width) << (pos)))               \
              | (((val) & FIELD_MASK(width)) << (pos));               \
    } while (0)

#define FIELD_READ(reg, pos, width)   (((reg) >> (pos)) & FIELD_MASK(width))

#endif /* BITOPS_H */