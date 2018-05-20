# base-utils
Cross platform library for conversion between bases in C99

### Overview:
* The initial project intention was to offer specialized functions for conversion into decimal numbers from much bigger bases. (Mainly base 36 and base 62)
* The idea to add more generic functions came up since base conversion is not straightforward in C language at all and there is no high level built-in functions for that purpose.

#### base-utils is currently used on a much bigger project for hash processing.

## Basic usage:
When using the specialized functions, knowing which types will be handled by the application can give the code a good speed boost.

> Over a million iterations, benchmarks shows that the unsigned flavor is 7% faster than the signed one.
```c
    // Unsigned conversion from base 36 to base 10
    uint64_t dec = uconvb36tob10("ab16j901x10");
    // Unsigned conversion from base 62 to base 10
    uint64_t dec = uconvb62tob10("8AmbA1i1KKaTam68");
```

> Only use the signed function if sure that negative representation should be handled as well.
```c
    // Signed conversion from base 36 to base 10
    int64_t dec = convb36tob10("-ab16j901x10");
    // Signed conversion from base 62 to base 10
    int64_t dec = convb62tob10("-8AmbA1i1KKaTam68");
```

> Converting from a base to another can be done using the following function, if both are below base 62
```c
    // Conversion from base 10 to base 2 (It even supports negative representations too!) 
    char* bin = basetobase("10", 10, 2);
```

> Using a custom charset, you can hop between custom base representations easily.
```c
    // Instead of using the default 0 and 1 within base 2,
    // the function will use the given charset to represent the value
    char* num = basetobasecustom("10", 10, 2, "XyZ");
```

> The library comes with a specialized "atoi" function which can run 2.2x faster than the standard implementation (GCC 7.3.0 Windows 8.1)
```c
    // Casts an unsigned char representation of a number into an actual integer
    int i = uatoi('1');
```


### Warnings:
1. **Take care of your representation sizes**, if the representation to be converted is bigger than the biggest C data types *the application will probably crash*.
2. When using the function "basetobase_cc", performance may be poor depending on the length of the custom charset.

### Known issues (Feel free to help!):
Currently there are no known issues.