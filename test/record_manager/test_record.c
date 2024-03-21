#include "../../src/record_manager/record.h"
#include "../../src/types.h"
#include "unity.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* === Auxiliary Function ===
Generates a random INTEGER field.
*/
static struct field_info get_random_integer_field(void)
{
  void *value = malloc(sizeof(INTEGER));
  *(INTEGER *)value = rand();
  struct field_info f = {.byte_size = sizeof(INTEGER), .value = value};
  return f;
}

/* === Auxiliary Function ===
Generates a random DOUBLE field.
*/
static struct field_info get_random_double_field(void)
{
  void *value = malloc(sizeof(DOUBLE));
  *(DOUBLE *)value = (DOUBLE)rand() / (DOUBLE)rand();
  struct field_info f = {.byte_size = sizeof(DOUBLE), .value = value};
  return f;
}

/* === Auxiliary Function ===
Generates a random VARCHAR field with length in [min, max].
*/
static struct field_info get_random_varchar_field_with_length(u_int64_t min_length, u_int64_t max_length)
{
  static const char CHARSET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  int length = rand() % (max_length - min_length + 1) + min_length;
  void *value = malloc(length + 1);
  ((char *)value)[length] = '\0'; // null terminator
  // fill value with random characters
  for (short i = 0; i < length; i++)
  { // -2 to exclude the null terminator
    ((char *)value)[i] = CHARSET[rand() % (sizeof(CHARSET) - 1)];
  }
  struct field_info f = {.byte_size = strlen(value), .value = value};
  return f;
}

/* === Auxiliary Function ===
Generates a random VARCHAR field.
*/
static struct field_info get_random_varchar_field(void)
{
  return get_random_varchar_field_with_length(1, MAX_VARCHAR_LENGTH);
}

void setUp(void)
{
  srand(time(NULL));
}

void tearDown(void)
{
  // clean stuff up here
}

/* === Test Function ===
Tests the marshall and unmarshall functions with a record consisting
of a single INTEGER field.
*/
void test_record_01(void)
{
  printf("\n=== TEST: MARSHALL SINGLE INTEGER FIELD ===\n");
  // record with a single INTEGER field
  short num_fields = 1;
  struct field_info f = get_random_integer_field();
  // marshall and unmarshall the record
  void *marshalled = marshall_record(num_fields, &f);
  struct field_info *unmarshalled = unmarshall_record(num_fields, marshalled);
  // actual and expected values
  size_t expected_byte_size = f.byte_size;
  INTEGER expected_value = *(INTEGER *)f.value;
  size_t actual_byte_size = unmarshalled->byte_size;
  INTEGER actual_value = *(INTEGER *)unmarshalled->value;
  // compare the marshalled and unmarshalled byte sizes
  printf("ASSERTION 1: marshalled and unmarshalled byte size should be equal\n");
  printf("expected_byte_size = %d, actual_byte_size = %zu\n", expected_byte_size, actual_byte_size);
  TEST_ASSERT_EQUAL_INT(expected_byte_size, actual_byte_size);
  // compare the marshalled and unmarshalled values
  printf("ASSERTION 2: marshalled and unmarshalled value should be equal\n");
  printf("expected_value = %d, actual_value = %d\n", expected_value, actual_value);
  TEST_ASSERT_EQUAL_INT(expected_value, actual_value);
  // free memory
  free(marshalled);
  free(unmarshalled);
}

/* === Test Function ===
Tests the marshall and unmarshall functions with a record consisting
of a single DOUBLE field.
*/
void test_record_02(void)
{
  printf("\n=== TEST: MARSHALL SINGLE DOUBLE FIELD ===\n");
  // record with a single DOUBLE field
  short num_fields = 1;
  struct field_info f = get_random_double_field();
  // marshall and unmarshall the record
  void *marshalled = marshall_record(num_fields, &f);
  struct field_info *unmarshalled = unmarshall_record(num_fields, marshalled);
  // actual and expected values
  size_t expected_byte_size = f.byte_size;
  DOUBLE expected_value = *(DOUBLE *)f.value;
  size_t actual_byte_size = unmarshalled->byte_size;
  DOUBLE actual_value = *(DOUBLE *)unmarshalled->value;
  // compare the marshalled and unmarshalled byte sizes
  printf("ASSERTION 1: marshalled and unmarshalled byte size should be equal\n");
  printf("expected_byte_size = %d, actual_byte_size = %zu\n", expected_byte_size, actual_byte_size);
  TEST_ASSERT_EQUAL_INT(expected_byte_size, actual_byte_size);
  // compare the marshalled and unmarshalled values
  printf("ASSERTION 2: marshalled and unmarshalled value should be equal\n");
  printf("expected_value = %f, actual_value = %f\n", expected_value, actual_value);
  TEST_ASSERT_EQUAL_DOUBLE(expected_value, actual_value);
  // free memory
  free(marshalled);
  free(unmarshalled);
}

/* === Test Function ===
Tests the marshall and unmarshall functions with a record consisting
of a single VARCHAR field.
*/
void test_record_03(void)
{
  printf("\n=== TEST: MARSHALL SINGLE VARCHAR FIELD ===\n");
  // record with a single VARCHAR field
  short num_fields = 1;
  struct field_info f = get_random_varchar_field();
  // marshall and unmarshall the record
  void *marshalled = marshall_record(num_fields, &f);
  struct field_info *unmarshalled = unmarshall_record(num_fields, marshalled);
  // actual and expected values
  size_t expected_byte_size = f.byte_size;
  VARCHAR *expected_value = (VARCHAR *)f.value;
  size_t actual_byte_size = unmarshalled->byte_size;
  VARCHAR *actual_value = malloc(actual_byte_size + 1); // +1 for the null terminator
  memcpy((void *)actual_value, unmarshalled->value, actual_byte_size);
  ((char *)actual_value)[actual_byte_size] = '\0'; // null terminator
  // compare the marshalled and unmarshalled byte sizes
  printf("ASSERTION 1: marshalled and unmarshalled byte size should be equal\n");
  printf("expected_byte_size = %d, actual_byte_size = %zu\n", expected_byte_size, actual_byte_size);
  TEST_ASSERT_EQUAL_INT(expected_byte_size, actual_byte_size);
  // compare the marshalled and unmarshalled values
  printf("ASSERTION 2: marshalled and unmarshalled value should be equal\n");
  printf("expected_value = %s, actual_value = %s\n", expected_value, actual_value);
  TEST_ASSERT_EQUAL_STRING(expected_value, actual_value);
  // free memory
  free(marshalled);
  free(unmarshalled);
  free(actual_value);
}

/* === Test Function ===
Tests the marshall and unmarshall functions with a record consisting
of MAX_FIELDS VARCHAR fields with MAX_VARCHAR_LENGTH characters each.
*/
void test_record_04(void)
{
  printf("\n=== TEST: MARSHALL MAX_FIELDS VARCHAR FIELDS ===\n");
  // record with MAX_FIELDS VARCHAR fields
  short num_fields = MAX_FIELDS;
  struct field_info fields[num_fields];
  for (short i = 0; i < num_fields; i++)
  {
    fields[i] = get_random_varchar_field_with_length(MAX_VARCHAR_LENGTH, MAX_VARCHAR_LENGTH);
  }
  // marshall and unmarshall the record
  void *marshalled = marshall_record(num_fields, fields);
  struct field_info *unmarshalled = unmarshall_record(num_fields, marshalled);
  // compare the marshalled and unmarshalled byte sizes
  printf("ASSERTION 1: marshalled and unmarshalled byte size should be equal\n");
  size_t expected_byte_size = 0;
  for (short i = 0; i < num_fields; i++)
  {
    expected_byte_size += fields[i].byte_size;
  }
  size_t actual_byte_size = 0;
  for (short i = 0; i < num_fields; i++)
  {
    actual_byte_size += unmarshalled[i].byte_size;
  }
  printf("expected_byte_size = %d, actual_byte_size = %zu\n", expected_byte_size, actual_byte_size);
  TEST_ASSERT_EQUAL_INT(expected_byte_size, actual_byte_size);
  // compare the marshalled and unmarshalled values
  printf("ASSERTION 2: marshalled and unmarshalled value should be equal\n");
  for (short i = 0; i < num_fields; i++)
  {
    VARCHAR *expected_value = (VARCHAR *)fields[i].value;
    VARCHAR *actual_value = malloc(unmarshalled[i].byte_size + 1); // +1 for the null terminator
    memcpy((void *)actual_value, unmarshalled[i].value, unmarshalled[i].byte_size);
    ((char *)actual_value)[unmarshalled[i].byte_size] = '\0'; // null terminator
    printf("expected_value = %s, actual_value = %s\n", expected_value, actual_value);
    TEST_ASSERT_EQUAL_STRING(expected_value, actual_value);
    free(actual_value);
  }
  // free memory
  free(marshalled);
  free(unmarshalled);
}

/* === Test Function ===
Tests the marshall and unmarshall functions with a record consisting
of a random number of fields.
*/
void test_record_05(void)
{
  printf("\n================== TEST: CREATE RECORD ==================\n");
  short num_fields = rand() % 100 + 1; // between 1 and 100
  printf("generating random record with %d fields... \n", num_fields);
  struct field_info fields[num_fields];
  for (short i = 0; i < num_fields; i++)
  {
    short type = rand() % 3;
    switch (type)
    {
    case 0:
    {
      fields[i] = get_random_integer_field();
      break;
    }
    case 1:
    {
      fields[i] = get_random_double_field();
      break;
    }
    case 2:
    {
      fields[i] = get_random_varchar_field();
      break;
    }
    }
  }
  // marshall and unmarshall the record
  void *marshalled = marshall_record(num_fields, fields);
  struct field_info *unmarshalled = unmarshall_record(num_fields, marshalled);
  // compare the marshalled and unmarshalled byte sizes
  printf("ASSERTION 1: marshalled and unmarshalled byte size should be equal\n");
  size_t expected_byte_size = 0;
  for (short i = 0; i < num_fields; i++)
  {
    expected_byte_size += fields[i].byte_size;
  }
  size_t actual_byte_size = 0;
  for (short i = 0; i < num_fields; i++)
  {
    actual_byte_size += unmarshalled[i].byte_size;
  }
  printf("expected_byte_size = %d, actual_byte_size = %zu\n", expected_byte_size, actual_byte_size);
  TEST_ASSERT_EQUAL_INT(expected_byte_size, actual_byte_size);
  // compare the marshalled and unmarshalled values
  printf("ASSERTION 2: marshalled and unmarshalled value should be equal\n");
  for (short i = 0; i < num_fields; i++)
  {
    if (fields[i].byte_size == 8)
    {
      INTEGER expected_value = *(INTEGER *)fields[i].value;
      INTEGER actual_value = *(INTEGER *)unmarshalled[i].value;
      printf("expected_value = %d, actual_value = %d\n", expected_value, actual_value);
      TEST_ASSERT_EQUAL_INT(expected_value, actual_value);
    }
    else if (fields[i].byte_size == 8)
    {
      DOUBLE expected_value = *(DOUBLE *)fields[i].value;
      DOUBLE actual_value = *(DOUBLE *)unmarshalled[i].value;
      printf("expected_value = %f, actual_value = %f\n", expected_value, actual_value);
      TEST_ASSERT_EQUAL_DOUBLE(expected_value, actual_value);
    }
    else
    {
      VARCHAR *expected_value = (VARCHAR *)fields[i].value;
      VARCHAR *actual_value = malloc(unmarshalled[i].byte_size + 1); // +1 for the null terminator
      memcpy((void *)actual_value, unmarshalled[i].value, unmarshalled[i].byte_size);
      ((char *)actual_value)[unmarshalled[i].byte_size] = '\0'; // null terminator
      printf("expected_value = %s, actual_value = %s\n", expected_value, actual_value);
      TEST_ASSERT_EQUAL_STRING(expected_value, actual_value);
      free(actual_value);
    }
  }
  // free memory
  free(marshalled);
  free(unmarshalled);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_record_01);
  RUN_TEST(test_record_02);
  RUN_TEST(test_record_03);
  RUN_TEST(test_record_04);
  RUN_TEST(test_record_05);
  return UNITY_END();
}