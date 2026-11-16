/* Unit tests for lib/bitops. Run with: make test-bitops */
#include "unity.h"
#include "bitops.h"

/* A fake hardware register. `volatile` like the real ones. */
static volatile uint32_t reg;

void setUp(void) { reg = 0; }
void tearDown(void) {}

static void test_bit_values(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x00000001u, BIT(0));
    TEST_ASSERT_EQUAL_HEX32(0x00000020u, BIT(5));
    TEST_ASSERT_EQUAL_HEX32(0x80000000u, BIT(31)); /* signed-shift trap */
}

static void test_set_bit_only_touches_that_bit(void)
{
    reg = 0x0000F000u;
    BIT_SET(reg, 5);
    TEST_ASSERT_EQUAL_HEX32(0x0000F020u, reg);
    BIT_SET(reg, 5); /* setting twice is harmless */
    TEST_ASSERT_EQUAL_HEX32(0x0000F020u, reg);
    BIT_SET(reg, 31);
    TEST_ASSERT_EQUAL_HEX32(0x8000F020u, reg);
}

static void test_clear_bit_only_touches_that_bit(void)
{
    reg = 0xFFFFFFFFu;
    BIT_CLR(reg, 0);
    BIT_CLR(reg, 31);
    TEST_ASSERT_EQUAL_HEX32(0x7FFFFFFEu, reg);
}

static void test_toggle_bit(void)
{
    BIT_TGL(reg, 3);
    TEST_ASSERT_EQUAL_HEX32(0x00000008u, reg);
    BIT_TGL(reg, 3);
    TEST_ASSERT_EQUAL_HEX32(0x00000000u, reg);
}

static void test_get_bit_returns_exactly_0_or_1(void)
{
    reg = 0x80000020u;
    TEST_ASSERT_EQUAL_UINT32(1u, BIT_GET(reg, 5));
    TEST_ASSERT_EQUAL_UINT32(1u, BIT_GET(reg, 31));
    TEST_ASSERT_EQUAL_UINT32(0u, BIT_GET(reg, 4));
}

static void test_field_mask(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x1u, FIELD_MASK(1));
    TEST_ASSERT_EQUAL_HEX32(0x3u, FIELD_MASK(2));
    TEST_ASSERT_EQUAL_HEX32(0xFFu, FIELD_MASK(8));
    TEST_ASSERT_EQUAL_HEX32(0x7FFFFFFFu, FIELD_MASK(31));
}

/* Real example: GPIOA->MODER, pin 5 = bits [11:10], 01 = output */
static void test_field_write_like_gpio_moder(void)
{
    reg = 0xA8000000u;                   /* GPIOA MODER reset value */
    FIELD_WRITE(reg, 10, 2, 1u);
    TEST_ASSERT_EQUAL_HEX32(0xA8000400u, reg);
}

static void test_field_write_replaces_old_value(void)
{
    reg = 0xFFFFFFFFu;
    FIELD_WRITE(reg, 4, 4, 0x5u);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFF5Fu, reg);
}

static void test_field_write_ignores_bits_that_do_not_fit(void)
{
    reg = 0;
    FIELD_WRITE(reg, 8, 2, 0xFFu);       /* only the low 2 bits may land */
    TEST_ASSERT_EQUAL_HEX32(0x00000300u, reg);
}

static void test_field_read(void)
{
    reg = 0x0000A5C0u;
    TEST_ASSERT_EQUAL_HEX32(0xA5u, FIELD_READ(reg, 8, 8));
    TEST_ASSERT_EQUAL_HEX32(0x3u, FIELD_READ(reg, 6, 2));
    TEST_ASSERT_EQUAL_HEX32(0x0u, FIELD_READ(reg, 0, 6));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_bit_values);
    RUN_TEST(test_set_bit_only_touches_that_bit);
    RUN_TEST(test_clear_bit_only_touches_that_bit);
    RUN_TEST(test_toggle_bit);
    RUN_TEST(test_get_bit_returns_exactly_0_or_1);
    RUN_TEST(test_field_mask);
    RUN_TEST(test_field_write_like_gpio_moder);
    RUN_TEST(test_field_write_replaces_old_value);
    RUN_TEST(test_field_write_ignores_bits_that_do_not_fit);
    RUN_TEST(test_field_read);
    return UNITY_END();
}
