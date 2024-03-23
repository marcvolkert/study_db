#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char separator = '\x1E'; // ASCII record separator

/* === Function ===
Takes the number of fields and an array of field_info structs and calculates
the required space for the record. The space is calculated as follows:
- The space required for the data is the sum of the byte sizes of all fields
- The space required for the separators is num_fields
*/
unsigned long int calculate_record_size(short num_fields, struct field_info *fields)
{
    // first, we calculate the space required for the data
    // this is simply the sum of the byte sizes of all fields
    int req_data_space = 0;
    for (short i = 0; i < num_fields; i++)
    {
        req_data_space += fields[i].byte_size;
    }
    // then, we calculate the space required for the separators
    // we need num_fields separators
    int req_separator_space = num_fields;
    // the total space required is the sum of the data space and the separator space
    return req_data_space + req_separator_space;
}

/* === Function ===
Takes a record and marshalls it into a byte array. The byte array
consists of the concatenated field values separated by the separator character.
*/
void *marshall_record(short num_fields, struct field_info *fields)
{
    // calculate the required space for the record
    size_t req_space = calculate_record_size(num_fields, fields);
    void *record = malloc(req_space);
    // write the record
    u_int8_t *curr_pos = record;
    for (short i = 0; i < num_fields; i++)
    {
        // calculate required space for the current field
        size_t curr_byte_size = fields[i].byte_size;
        // copy the field value to the record
        memcpy(curr_pos, fields[i].value, curr_byte_size);
        // move the current position to the next field
        curr_pos += curr_byte_size;
        // add the separator if it's not the last field
        memcpy(curr_pos, &separator, 1);
        curr_pos += 1;
    }
    return record;
}

/* === Function ===
Takes a marshalled record and unmarshalls it into an array of
field_info structs. This is simply the reverse of the marshall function.
*/
struct field_info *unmarshall_record(short num_fields, void *record)
{
    // allocate memory for the fields
    struct field_info *fields = malloc(num_fields * sizeof(struct field_info));
    // field spans from lower_bound to upper_bound
    u_int8_t *lower_bound = record;
    u_int8_t *upper_bound = record;
    for (short i = 0; i < num_fields; i++)
    {
        // find the upper bound of the current field
        while (*upper_bound != separator)
        {
            upper_bound++;
        }
        // calculate the byte size of the current field
        size_t curr_byte_size = upper_bound - lower_bound;
        // allocate memory for the current field value
        fields[i].value = malloc(curr_byte_size);
        // copy the field value to the field_info struct
        memcpy(fields[i].value, lower_bound, curr_byte_size);
        fields[i].byte_size = curr_byte_size;
        // move the lower bound to the next field
        lower_bound = upper_bound + 1;
        // move the upper bound to the next separator
        upper_bound = lower_bound;
    }
    return fields;
}