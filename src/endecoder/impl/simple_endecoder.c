/**
 * This file implements the endecoder interface (endecoder.h).
 * It contains easy implementations of the encode and decode functions for INTEGER and DOUBLE types.
 **/

#include "../endecoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INTEGER is simply encoded as ASCII string
void *encode_INTEGER(INTEGER value)
{
    void *encoded = malloc(sizeof(INTEGER));
    sprintf(encoded, "%ld", value);
    return encoded;
}

// Reverse of encode_INTEGER
INTEGER decode_INTEGER(void *encoded)
{
    return atoll(encoded);
}


// convert DOUBLE to byte array and turn it into ASCII string
void *encode_DOUBLE(DOUBLE value)
{
    union {
        DOUBLE d;
        char c[sizeof(DOUBLE)];
    } u;
    u.d = value;
    void *encoded = malloc(sizeof(DOUBLE));
    sprintf(encoded, "%2x", value);
}

// Reverse of encode_DOUBLE
DOUBLE decode_DOUBLE(void *encoded)
{
    union {
        DOUBLE d;
        char c[sizeof(DOUBLE)];
    } u;
    sscanf(encoded, "%2x", &u.d);
    return u.d;
}