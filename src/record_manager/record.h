/**
 * @file record.h
 *
 * This file defines the record interface.
 * Its implementations will be used to marshall and unmarshall records for and from storage.
 **/

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

size_t calculate_record_size(short num_fields, struct field_info *fields);

void *marshall_record(short num_fields, struct field_info *fields);

struct field_info *unmarshall_record(short num_fields, void *record);
