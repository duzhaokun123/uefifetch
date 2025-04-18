#ifndef _ASSERT_H
#define _ASSERT_H
#include <null.h>
#include <fopen_wrap.h>
#include <uefi.h>

#define assert(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "Assertion failed: %s\n", #x); \
            abort(); \
        } \
    } while (0)

#endif
