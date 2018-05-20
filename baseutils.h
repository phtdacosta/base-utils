#ifndef BASEUTILS_H
#define BASEUTILS_H

#include <stdint.h>

// Those specialized functions were written to simplify when converting a hash function output into an actual number for any purpose
uint64_t uconvb36tob10 (const char* str);
int64_t convb36tob10 (const char* str);
uint64_t uconvb62tob10 (const char* str);
int64_t convb62tob10 (const char* str);
// This implementation is (more than) twice as faster than the standard function, but only handles unsigned values
uint64_t uatoi (const char* str);
// Those functions greatly improves the use of the library,
// allowing developers to shift between bases (2 up to 62) and using a custom charset within ASCII table (0-255)
char* basetobase (const char* str, uint8_t a, uint8_t b);
char* basetobasecustom (const char* str, uint8_t a, uint8_t b, const char* charset);

#endif