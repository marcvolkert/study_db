#include "../src/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* === Auxiliary Function ===
Generates a random INTEGER.
*/
INTEGER *get_random_INTEGER(void)
{
  void *value = malloc(sizeof(INTEGER));
  *(INTEGER *)value = rand();
  return value;
}

/* === Auxiliary Function ===
Generates a random DOUBLE.
*/
DOUBLE *get_random_DOUBLE(void)
{
  void *value = malloc(sizeof(DOUBLE));
  *(DOUBLE *)value = (DOUBLE)rand() / (DOUBLE)rand();
  return value;
}

/* === Auxiliary Function ===
Generates a random VARCHAR with length in [min, max].
*/
VARCHAR *get_random_VARCHAR_with_length(u_int64_t min_length, u_int64_t max_length)
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
  return value;
}
