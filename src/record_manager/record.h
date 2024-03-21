/* The functions prototyped in this file will be used for generating,
 * serializing and deserializing database records. */

#include "../types.h"
#include <stddef.h>

#define MAX_FIELDS 256
#define MAX_VARCHAR_LENGTH 1024

typedef uint8_t field_number;
typedef uint32_t field_offset;

struct field_info
{
  size_t byte_size;
  void *value;
};

void *marshall_record(short num_fields, struct field_info *fields);

struct field_info *unmarshall_record(short num_fields, void *record);
