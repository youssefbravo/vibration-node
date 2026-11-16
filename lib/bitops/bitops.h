/*
 * bitops.h - register bit-manipulation macros.
 *
 * EXERCISE (Step 1): replace each stub so `make test-bitops` passes.
 * These are exactly what you will use on real STM32 registers, e.g.
 *     FIELD_WRITE(GPIOA->MODER, 10, 2, 1);   // PA5 = output
 *     BIT_SET(GPIOA->ODR, 5);                // LED on
 *
 * Rules your macros must follow:
 *   - Work on uint32_t values, including bit 31 (watch for signed 1 << 31!).
 *   - Evaluate to/modify `reg` in place for the SET/CLR/TGL/WRITE forms.
 *   - BIT_GET returns exactly 0 or 1.
 *   - FIELD_WRITE must not change any bit outside the field, and must ignore
 *     bits of `val` that do not fit in `width`.
 *   - `width` is 1..31. `pos + width` <= 32.
 *   - Wrap every argument in parentheses inside the macro body.
 *
 * Names are prefixed BIT_/FIELD_ on purpose: ST's CMSIS headers already
 * define SET_BIT/CLEAR_BIT/READ_BIT with different meanings.
 */
#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

/* uint32_t with only bit n set */
#define BIT(n)                          (0u) /* TODO */

#define BIT_SET(reg, n)                 do { (void)(reg); (void)(n); } while (0) /* TODO */
#define BIT_CLR(reg, n)                 do { (void)(reg); (void)(n); } while (0) /* TODO */
#define BIT_TGL(reg, n)                 do { (void)(reg); (void)(n); } while (0) /* TODO */
#define BIT_GET(reg, n)                 (0u) /* TODO: 0 or 1 */

/* `width` low bits set, e.g. FIELD_MASK(3) == 0x7 */
#define FIELD_MASK(width)               (0u) /* TODO */

/* Replace bits [pos, pos+width) of reg with val */
#define FIELD_WRITE(reg, pos, width, val) \
    do { (void)(reg); (void)(pos); (void)(width); (void)(val); } while (0) /* TODO */

/* Extract bits [pos, pos+width) of reg, shifted down to bit 0 */
#define FIELD_READ(reg, pos, width)     (0u) /* TODO */

#endif /* BITOPS_H */
