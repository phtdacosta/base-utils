#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "baseutils.h"

// const char _94[] = {
//     ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
//     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
//     ':', ';', '<', '=', '>', '?', '@',
//     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z',
//     '[', '\\', ']', '^', '_', '`',
//     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z',
//     '{', '|', '}', '~'
//     };

const char _62[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

uint64_t uconvb36tob10 (const char* str) {
    uint64_t dec = 0;
    uint8_t len = strlen(str);
    while (*str) {
        ((*str - 0) > 64) ? 
            (dec += (9 + ((*str++ - 0) - 64)) * pow(36, --len)) :
            (dec += ((*str++ - 0) - 48) * pow(36, --len)); 
    }
    return dec;
}

int64_t convb36tob10 (const char* str) {
    int64_t dec = 0;
    uint8_t len = strlen(str);
    bool neg;
    (*str++ == '-') ? (neg = true, len--) : (neg = false);
    while (*str) {
        ((*str - 0) > 64) ? 
            (dec += (9 + ((*str++ - 0) - 64)) * pow(36, --len)) :
            (dec += ((*str++ - 0) - 48) * pow(36, --len)); 
    }
    return (neg) ? (dec - dec - dec) : (dec);
}

uint64_t uconvb62tob10 (const char* str) {
    uint64_t dec = 0;
    uint8_t len = strlen(str);
    while (*str) {
        ((*str - 0) > 96) ? 
            (dec += (9 + ((*str++ - 0) - (96 - 26))) * pow(62, --len)) :
            ( ((*str - 0) > 64) ? (dec += (9 + ((*str++ - 0) - 64)) * pow(62, --len)) : (dec += ((*str++ - 0) - 48) * pow(62, --len)) ); 
    }
    return dec;
}

int64_t convb62tob10 (const char* str) {
    int64_t dec = 0;
    uint8_t len = strlen(str);
    bool neg;
    (*str++ == '-') ? (neg = true, len--) : (neg = false);
    while (*str) {
        ((*str - 0) > 96) ? 
            (dec += (9 + ((*str++ - 0) - (96 - 26))) * pow(62, --len)) :
            ( ((*str - 0) > 64) ? (dec += (9 + ((*str++ - 0) - 64)) * pow(62, --len)) : (dec += ((*str++ - 0) - 48) * pow(62, --len)) ); 
    }
    return (neg) ? (dec - dec - dec) : (dec);
}

uint64_t uatoi (const char* str) {
    uint64_t val = 0;
    while (*str) {
        val = val * 10 + (*str++ - '0');
    }
    return val;
}

static inline uint_fast16_t locatevalue_ (const char* charset_, uint8_t char_) {
    uint_fast16_t ind_ ;
    while ( *charset_ ) {
        if (*charset_ == char_) {
            return ind_;
        } else {
            *charset_++;
            ind_++;
        };
    }
    return -1;
}

char* basetobase (const char* str, uint8_t a, uint8_t b) {
    char* arr = malloc(sizeof(char) * 50); // 50 to ensure a secure margin in case of huge representations
    char* tmp = arr;
    uint64_t aux = 0;
    uint8_t len = strlen(str);
    uint8_t lvl = 0;

    bool neg;
    (*str == '-') ? (neg = true, *str++) : (neg = false);

    // Before enconding to the new requested base, the numeric representation is pre-encoded in decimal
    while ( *str ) {
        ((*str - 0) > 96) ? 
            (aux += (9 + ((*str++ - 0) - (96 - 26))) * pow(a, --len)) :
            ( ((*str - 0) > 64) ? (aux += (9 + ((*str++ - 0) - 64)) * pow(a, --len)) : (aux += ((*str++ - 0) - 48) * pow(a, --len)) ); 
    }

    // Successive divisions to find the new numeric representation
    while (aux >= b) {
        ++lvl;
        // *arr++ = aux % b;
        // C = A – B * (A / B)
        *arr++ = aux - b * (aux / b);
        aux = aux / b;
    }
    *arr = aux;
    lvl++;

    // Creates a new specialized array where the new representation will be stored and checks if the number will be negative
    // The +1 is for adding the '\0' character at the end of the function to avoid trash characters
    char* rep = malloc(sizeof(char) * (lvl + 1));
    char* res = rep;
    if (neg) {
        (*rep++ = '-');
        lvl++;
    }

    // Reverses the array, replacing each decimal value by the corresponding value given by a "charset lookup table"
    while (lvl > 0) {
        *rep++ = _62[tmp[--lvl]];
    }
    *rep = '\0';

    // Cleans the space used to store the support variable array 
    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }

    return res;
}

char* basetobasecustom (const char* str, uint8_t a, uint8_t b, const char* charset) {
    char* arr = malloc(sizeof(char) * 50); // 50 to ensure a secure margin in case of huge representations
    char* tmp = arr;
    uint64_t aux = 0;
    uint8_t len = strlen(str);
    uint8_t lvl = 0;

    bool neg;
    (*str == '-') ? (neg = true, *str++) : (neg = false);

    // Before enconding to the new requested base, the numeric representation is pre-encoded in decimal
    uint_fast16_t ind;
    while ( *str ) {
        ind = locatevalue_(charset, *str++);
        if (ind > -1) {
            aux += ind * pow(a, --len);
            *str++;
        } else {
            if (arr != NULL) {
                free(arr);
                arr = NULL;
            }
            return arr;
        } 
    }
    // Successive divisions to find the new numeric representation
    while (aux >= b) {
        ++lvl;
        // *arr++ = aux % b;
        // C = A – B * (A / B)
        *arr++ = aux - b * (aux / b);
        aux = aux / b;
    }
    *arr = aux;
    lvl++;

    // Creates a new specialized array where the new representation will be stored and checks if the number will be negative
    // The +1 is for adding the '\0' character at the end of the function to avoid trash characters
    char* rep = malloc(sizeof(char) * (lvl + 1));
    char* res = rep;
    if (neg) {
        (*rep++ = '-');
        lvl++;
    }

    // Reverses the array, replacing each decimal value by the corresponding value given by a "charset lookup table"
    while (lvl > 0) {
        *rep++ = charset[tmp[--lvl]];
    }
    *rep = '\0';

    // Cleans the space used to store the support variable array 
    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }

    return res;
}