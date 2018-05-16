#ifndef SERIALLIB_H
#define SERIALLIB_H

// Those specialized functions were written to simplify when converting a hash function output into an actual number for any purpose
unsigned long long int uint36to10_ (const char* str_);
signed long long int sint36to10_ (const char* str_);
unsigned long long int uint62to10_ (const char* str_);
signed long long int sint62to10_ (const char* str_);
// The standard atoi function is more than 2x slower than this implementation
unsigned long long int atoi_ ( const char* str_ );
// Those functions greatly improves the use of the library, allowing developers to shift between bases using a custom charset
char* basetobase (const char* str_, unsigned char a_, unsigned char b_);
char* basetobase_cc (const char* str_, unsigned char a_, unsigned char b_, const char* charset_);

#endif