/**
 * This file contains tests for the endecoder module.
 **/

#include "../../src/endecoder/endecoder.h"
#include "../random_types.c"
#include "unity.c"

void setUp(void)
{
  srand(time(NULL));
}

void tearDown(void)
{
  // do nothing
}

// Test case 1: encode and decode INTEGER
void test_endecode_INTEGER()
{
  printf("\n=== TEST: Encode and decode INTEGER ===\n");
  INTEGER *value = get_random_INTEGER();
  void *encoded = encode_INTEGER(*value);
  INTEGER decoded = decode_INTEGER(encoded);
  printf("expected: %ld, actual: %ld\n", *value, decoded);
  TEST_ASSERT_EQUAL_INT(decoded, *value);
  free(value);
  free(encoded);
}

// Test case 2: encode and decode DOUBLE
void test_endecode_DOUBLE()
{
  printf("\n=== TEST: Encode and decode DOUBLE ===\n");
  DOUBLE *value = get_random_DOUBLE();
  void *encoded = encode_DOUBLE(*value);
  DOUBLE decoded = decode_DOUBLE(encoded);
  printf("expected: %lf, actual: %lf\n", *value, decoded);
  TEST_ASSERT_EQUAL_DOUBLE(decoded, *value);
}

// Run test cases
int main(void)
{
  UNITY_BEGIN();
  int iterations = 1000;
  for (int i = 0; i < iterations; i++) {
    RUN_TEST(test_endecode_INTEGER);
  }
  for (int i = 0; i < iterations; i++) {
    RUN_TEST(test_endecode_DOUBLE);
  }
  return UNITY_END();
}