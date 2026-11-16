/* Unit tests for lib/ringbuf. Run with: make test-ringbuf */
#include "unity.h"
#include "ringbuf.h"

#define CAP 4u

static uint8_t   storage[CAP];
static ringbuf_t rb;

void setUp(void)
{
    TEST_ASSERT_TRUE(ringbuf_init(&rb, storage, CAP));
}

void tearDown(void) {}

static void test_init_rejects_bad_arguments(void)
{
    ringbuf_t other;
    uint8_t   mem[2];
    TEST_ASSERT_FALSE(ringbuf_init(NULL, mem, 2));
    TEST_ASSERT_FALSE(ringbuf_init(&other, NULL, 2));
    TEST_ASSERT_FALSE(ringbuf_init(&other, mem, 0));
}

static void test_new_buffer_is_empty(void)
{
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
    TEST_ASSERT_FALSE(ringbuf_is_full(&rb));
    TEST_ASSERT_EQUAL_size_t(0, ringbuf_count(&rb));
}

static void test_pop_on_empty_fails(void)
{
    uint8_t out = 0xAA;
    TEST_ASSERT_FALSE(ringbuf_pop(&rb, &out));
    TEST_ASSERT_EQUAL_HEX8(0xAA, out); /* untouched */
}

static void test_push_then_pop_returns_same_byte(void)
{
    uint8_t out = 0;
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 0x42));
    TEST_ASSERT_EQUAL_size_t(1, ringbuf_count(&rb));
    TEST_ASSERT_TRUE(ringbuf_pop(&rb, &out));
    TEST_ASSERT_EQUAL_HEX8(0x42, out);
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
}

static void test_fifo_order(void)
{
    uint8_t out;
    for (uint8_t i = 1; i <= 3; i++) {
        TEST_ASSERT_TRUE(ringbuf_push(&rb, i));
    }
    for (uint8_t i = 1; i <= 3; i++) {
        TEST_ASSERT_TRUE(ringbuf_pop(&rb, &out));
        TEST_ASSERT_EQUAL_UINT8(i, out);
    }
}

static void test_full_at_capacity_and_rejects_push(void)
{
    uint8_t out;
    for (uint8_t i = 0; i < CAP; i++) {
        TEST_ASSERT_TRUE(ringbuf_push(&rb, (uint8_t)(10 + i)));
    }
    TEST_ASSERT_TRUE(ringbuf_is_full(&rb));
    TEST_ASSERT_FALSE(ringbuf_push(&rb, 99));       /* rejected */
    TEST_ASSERT_EQUAL_size_t(CAP, ringbuf_count(&rb));
    TEST_ASSERT_TRUE(ringbuf_pop(&rb, &out));
    TEST_ASSERT_EQUAL_UINT8(10, out);                /* oldest not overwritten */
}

static void test_wraps_around_many_times(void)
{
    uint8_t out;
    uint8_t next_in = 0, next_out = 0;
    /* keep the buffer half full while cycling far past capacity */
    TEST_ASSERT_TRUE(ringbuf_push(&rb, next_in++));
    TEST_ASSERT_TRUE(ringbuf_push(&rb, next_in++));
    for (int i = 0; i < 1000; i++) {
        TEST_ASSERT_TRUE(ringbuf_push(&rb, next_in++));
        TEST_ASSERT_TRUE(ringbuf_pop(&rb, &out));
        TEST_ASSERT_EQUAL_UINT8(next_out++, out);
        TEST_ASSERT_EQUAL_size_t(2, ringbuf_count(&rb));
    }
}

static void test_peek_does_not_remove(void)
{
    uint8_t out = 0;
    TEST_ASSERT_FALSE(ringbuf_peek(&rb, &out));
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 7));
    TEST_ASSERT_TRUE(ringbuf_peek(&rb, &out));
    TEST_ASSERT_EQUAL_UINT8(7, out);
    TEST_ASSERT_EQUAL_size_t(1, ringbuf_count(&rb));
}

static void test_clear_empties_buffer(void)
{
    uint8_t out;
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 1));
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 2));
    ringbuf_clear(&rb);
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
    TEST_ASSERT_FALSE(ringbuf_pop(&rb, &out));
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 3));         /* still usable */
    TEST_ASSERT_TRUE(ringbuf_pop(&rb, &out));
    TEST_ASSERT_EQUAL_UINT8(3, out);
}

static void test_capacity_one_edge_case(void)
{
    ringbuf_t one;
    uint8_t   mem[1];
    uint8_t   out;
    TEST_ASSERT_TRUE(ringbuf_init(&one, mem, 1));
    TEST_ASSERT_TRUE(ringbuf_push(&one, 5));
    TEST_ASSERT_TRUE(ringbuf_is_full(&one));
    TEST_ASSERT_FALSE(ringbuf_push(&one, 6));
    TEST_ASSERT_TRUE(ringbuf_pop(&one, &out));
    TEST_ASSERT_EQUAL_UINT8(5, out);
    TEST_ASSERT_TRUE(ringbuf_is_empty(&one));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_rejects_bad_arguments);
    RUN_TEST(test_new_buffer_is_empty);
    RUN_TEST(test_pop_on_empty_fails);
    RUN_TEST(test_push_then_pop_returns_same_byte);
    RUN_TEST(test_fifo_order);
    RUN_TEST(test_full_at_capacity_and_rejects_push);
    RUN_TEST(test_wraps_around_many_times);
    RUN_TEST(test_peek_does_not_remove);
    RUN_TEST(test_clear_empties_buffer);
    RUN_TEST(test_capacity_one_edge_case);
    return UNITY_END();
}
