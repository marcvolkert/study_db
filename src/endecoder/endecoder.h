/**
 * This file specifies the interface for the endecoder module.
 * It contains the function signatures for encoding and decoding values of non-char types.
 **/

#include "../types.h"

/*
* Takes a value of type INTEGER and encodes it into a byte array.
* @param value the value to encode
* @return the encoded value
*/
void *encode_INTEGER(INTEGER value);

/*
* Takes a byte array and decodes it into a value of type INTEGER.
* @param encoded the byte array to decode
* @return the decoded value
*/
INTEGER decode_INTEGER(void *encoded);

/*
* Takes a value of type DOUBLE and encodes it into a byte array.
* @param value the value to encode
* @return the encoded value
*/
void *encode_DOUBLE(DOUBLE value);

/*
* Takes a byte array and decodes it into a value of type DOUBLE.
* @param encoded the byte array to decode
* @return the decoded value
*/
DOUBLE decode_DOUBLE(void *encoded);
