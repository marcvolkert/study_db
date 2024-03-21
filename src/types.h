/* Description: This file contains the definition of the database data types. */

#include <stdint.h>

// INTEGER: 8 bytes
typedef int64_t INTEGER;
// DOUBLE: 8 bytes
typedef double DOUBLE;
// VARCHAR: char array with null terminator (like normal C string)
typedef char *VARCHAR;

// Type IDs
typedef uint8_t type_id;

#define INTEGER_TYPE (type_id)0
#define DOUBLE_TYPE (type_id)1
#define VARCHAR_TYPE (type_id)2
