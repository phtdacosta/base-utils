#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "baseutils.h"

const char _94[] = {
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ':', ';', '<', '=', '>', '?', '@',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z',
    '[', '\\', ']', '^', '_', '`',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z',
    '{', '|', '}', '~'
    };

const char _62[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

unsigned long long int uint36to10_ (const char* str_) {
    unsigned long long int aux = 0;
    unsigned char aux_ = strlen(str_);
    while ( *str_ ) {
        ((*str_ - 0) > 64) ? 
            (aux += (9 + ((*str_++ - 0) - 64)) * pow(36, --aux_)) :
            (aux += ((*str_++ - 0) - 48) * pow(36, --aux_)); 
    }
    return aux;
}

signed long long int sint36to10_ (const char* str_) {
    signed long long int aux = 0;
    unsigned char aux_ = strlen(str_);
    bool _;
    (*str_++ == '-') ? (_ = true, aux_--) : (_ = false);
    while ( *str_ ) {
        ((*str_ - 0) > 64) ? 
            (aux += (9 + ((*str_++ - 0) - 64)) * pow(36, --aux_)) :
            (aux += ((*str_++ - 0) - 48) * pow(36, --aux_)); 
    }
    return (_) ? (aux - aux - aux) : (aux);
}

unsigned long long int uint62to10_ (const char* str_) {
    unsigned long long int aux = 0;
    unsigned char aux_ = strlen(str_);
    while ( *str_ ) {
        ((*str_ - 0) > 96) ? 
            (aux += (9 + ((*str_++ - 0) - (96 - 26))) * pow(62, --aux_)) :
            ( ((*str_ - 0) > 64) ? (aux += (9 + ((*str_++ - 0) - 64)) * pow(62, --aux_)) : (aux += ((*str_++ - 0) - 48) * pow(62, --aux_)) ); 
    }
    return aux;
}

signed long long int sint62to10_ (const char* str_) {
    signed long long int aux = 0;
    unsigned char aux_ = strlen(str_);
    bool _;
    (*str_++ == '-') ? (_ = true, aux_--) : (_ = false);
    while ( *str_ ) {
        ((*str_ - 0) > 96) ? 
            (aux += (9 + ((*str_++ - 0) - (96 - 26))) * pow(62, --aux_)) :
            ( ((*str_ - 0) > 64) ? (aux += (9 + ((*str_++ - 0) - 64)) * pow(62, --aux_)) : (aux += ((*str_++ - 0) - 48) * pow(62, --aux_)) ); 
    }
    return (_) ? (aux - aux - aux) : (aux);
}

unsigned long long int atoi_ ( const char* str_ ) {
    unsigned long long int val_ = 0;
    while ( *str_ ) {
        val_ = val_ * 10 + (*str_++ - '0');
    }
    return val_;
}

static inline signed short int locatecharsetval_ (const char* charset_, unsigned char char_) {
    signed short int aux;
    while ( *charset_ ) {
        if (*charset_ == char_) {
            return aux;
        } else {
            *charset_++;
            aux++;
        };
    }
    return -1;
}

char* basetobase (const char* str_, unsigned char a_, unsigned char b_) {
    char* arr_ = malloc(sizeof(char) * 50);
    char* temp_ = arr_;
    unsigned long long int aux = 0;
    unsigned char aux_ = strlen(str_);
    unsigned char aux__ = 0;

    bool neg_;
    (*str_ == '-') ? (neg_ = true, *str_++) : (neg_ = false);

    // Before enconding to the new requested base, the numeric representation is pre-encoded in decimal
    while ( *str_ ) {
        ((*str_ - 0) > 96) ? 
            (aux += (9 + ((*str_++ - 0) - (96 - 26))) * pow(a_, --aux_)) :
            ( ((*str_ - 0) > 64) ? (aux += (9 + ((*str_++ - 0) - 64)) * pow(a_, --aux_)) : (aux += ((*str_++ - 0) - 48) * pow(a_, --aux_)) ); 
    }

    // Successive divisions to find the new numeric representation
    while (aux >= b_) {
        ++aux__;
        // *arr_++ = aux % b_;
        // C = A – B * (A / B)
        *arr_++ = aux - b_ * (aux / b_);
        aux = aux / b_;
    }
    *arr_ = aux;
    aux__++;

    // Creates a new specialized array where the new representation will be stored and checks if the number will be negative
    // The +1 is for adding the '\0' character at the end of the function to avoid trash characters
    char* arr__ = malloc(sizeof(char) * (aux__ + 1));
    char* __ = arr__;
    if (neg_) {
        (*arr__++ = '-');
        aux__++;
    }

    // Reverses the array, replacing each decimal value by the corresponding value given by a "charset lookup table"
    while (aux__ > 0) {
        *arr__++ = _62[temp_[--aux__]];
    }
    *arr__ = '\0';

    // Cleans the space used to store the support variable array 
    // if (arr_ != NULL) {
    //     free(arr_);
    //     arr_ = NULL;
    // }

    return __;
}

char* basetobase_cc (const char* str_, unsigned char a_, unsigned char b_, const char* charset_) {
    char* arr_ = malloc(sizeof(char) * 50);
    char* temp_ = arr_;
    unsigned long long int aux = 0;
    unsigned char aux_ = strlen(str_);
    unsigned char aux__ = 0;

    bool neg_;
    (*str_ == '-') ? (neg_ = true, *str_++) : (neg_ = false);

    // Before enconding to the new requested base, the numeric representation is pre-encoded in decimal
    signed short int val_;
    while ( *str_ ) {
        val_ = locatecharsetval_(charset_, *str_++);
        if (val_ > 0) {
            aux += val_ * pow(a_, --aux_);
            *str_++;
        } else {
            if (arr_ != NULL) {
                free(arr_);
                arr_ = NULL;
            }
            return arr_;
        } 
    }
    // Successive divisions to find the new numeric representation
    while (aux >= b_) {
        ++aux__;
        // *arr_++ = aux % b_;
        // C = A – B * (A / B)
        *arr_++ = aux - b_ * (aux / b_);
        aux = aux / b_;
    }
    *arr_ = aux;
    aux__++;

    // Creates a new specialized array where the new representation will be stored and checks if the number will be negative
    // The +1 is for adding the '\0' character at the end of the function to avoid trash characters
    char* arr__ = malloc(sizeof(char) * (aux__ + 1));
    char* __ = arr__;
    if (neg_) {
        (*arr__++ = '-');
        aux__++;
    }

    // Reverses the array, replacing each decimal value by the corresponding value given by a "charset lookup table"
    while (aux__ > 0) {
        *arr__++ = charset_[temp_[--aux__]];
    }
    *arr__ = '\0';

    // Cleans the space used to store the support variable array 
    // if (arr_ != NULL) {
    //     free(arr_);
    //     arr_ = NULL;
    // }

    return __;
}