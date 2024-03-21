#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === Function ===
Takes a record and marshalls it into a byte array. The byte array
starts with an array of offsets, followed by the data.
The offsets array consists of num_fields + 1 elements, which point to the
start of each field in the data section. The last offset points to the
end of the record, i.e. the first byte after the last field.
The data section consists of the concatenated field values.
*/
void *marshall_record(short num_fields, struct field_info *fields)
{
  // first, we calculate the space required for the offset space
  // it should be n (number of fields) times the size of field_offset + 1 (for the last offset pointing to the end of the record)
  // e.g. if we have 256 fields, we need 256 * 4 + 4 = 1028 bytes
  int req_offset_space = num_fields * sizeof(field_offset) + sizeof(field_offset);
  // then, we calculate the space required for the data
  // this is simply the sum of the byte sizes of all fields
  int req_data_space = 0;
  for (short i = 0; i < num_fields; i++)
  {
    req_data_space += fields[i].byte_size;
  }
  // allocate space for the record
  int req_space = req_offset_space + req_data_space;
  void *record = malloc(req_space);
  // write the offsets and the data
  // first, we write the regular offsets for the fields and the data
  field_offset curr_offset = req_offset_space;
  for (short i = 0; i < num_fields; i++)
  {
    // assign the offset to i-th field
    *((field_offset *)record + i) = curr_offset;
    // write the data to the position pointed to by the offset
    memcpy((u_int8_t *)record + curr_offset, fields[i].value, fields[i].byte_size);
    // move the current offset to the next position
    curr_offset += fields[i].byte_size;
  }
  // then, we write the last offset, which points to the end of the record
  *((field_offset *)record + num_fields) = curr_offset;
  return record;
}

/* === Function ===
Takes a marshalled record and unmarshalls it into an array of
field_info structs. This is simply the reverse of the marshall function.
*/
struct field_info *unmarshall_record(short num_fields, void *record)
{
  // reserve space for the field_info structs
  struct field_info *fields = malloc(num_fields * sizeof(struct field_info));
  // variable to keep track of the current offset, i.e. the pointer to the start of the i-th field
  field_offset *curr_offset = (field_offset *)record;
  // now, we can read the read the data and byte sizes for each field
  for (short i = 0; i < num_fields; i++)
  {
    fields[i].byte_size = *(curr_offset + 1) - *curr_offset;
    fields[i].value = malloc(fields[i].byte_size);
    memcpy(fields[i].value, (u_int8_t *)record + *curr_offset, fields[i].byte_size); // copy the data of the i-th field
    curr_offset++;
  }
  return fields;
}