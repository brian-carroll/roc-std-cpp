#pragma once

#include <cstddef>
#include <string.h>
#include "internal.h"

namespace Roc
{
    struct roc_big_str
    {
        char *bytes;
        size_t length;
        size_t capacity;
    };

    const size_t SMALL_STRING_SIZE = sizeof(struct roc_big_str);
    const size_t SMALL_STRING_MAXLEN = SMALL_STRING_SIZE - 1;
    const size_t REFCOUNT_SIZE = sizeof(size_t);

    class Str
    {
        union
        {
            struct roc_big_str big;
            char small[SMALL_STRING_SIZE];
        };

#ifdef DEBUG
        void debug_representation()
        {
            printf("Roc::Str\n");
            printf("    is_small_str: %s\n", is_small_str() ? "true" : "false");
            printf("    big.bytes: %p\n", big.bytes);
            printf("    big.length: %zu\n", big.length);
            printf("    big.capacity: %zu\n", big.capacity);
            printf("    small: ");
            for (size_t i = 0; i < SMALL_STRING_SIZE; i++)
            {
                printf("%02x ", (unsigned char)small[i]);
            }
            printf("\n");
        }
#endif

    public:
        Str(const char *cstr = "", size_t requested_capacity = 0)
        {
            size_t len = strlen(cstr);

            if (len < SMALL_STRING_SIZE)
            {
                big = {};
                memcpy(small, cstr, len);
                small[SMALL_STRING_SIZE - 1] = len | 0x80;
            }
            else
            {
                size_t capacity = requested_capacity < len ? len : requested_capacity;
                size_t alloc_size = REFCOUNT_SIZE + capacity;
                void *allocation = roc_alloc(alloc_size, REFCOUNT_SIZE);
                ptrdiff_t *refcount = (ptrdiff_t *)allocation;
                *refcount = REFCOUNT_ONE;

                big.bytes = (char *)allocation + REFCOUNT_SIZE;
                big.length = len;
                big.capacity = capacity;
            }
        }

        ~Str()
        {
            if (!is_small_str())
            {
                char *allocation = big.bytes - REFCOUNT_SIZE;
                roc_dealloc(allocation, REFCOUNT_SIZE);
            }
        }

        bool is_small_str()
        {
            return small[SMALL_STRING_SIZE - 1] < 0;
        }

        size_t length()
        {
            return is_small_str()
                       ? (size_t)(small[SMALL_STRING_SIZE - 1] & 0x7f)
                       : big.length;
        }

        size_t capacity()
        {
            return is_small_str()
                       ? SMALL_STRING_SIZE - 1
                       : big.capacity;
        }

        bool is_unique()
        {
            if (is_small_str())
            {
                return true;
            }
            ptrdiff_t *refcount = (ptrdiff_t *)big.bytes - REFCOUNT_SIZE;
            return *refcount == REFCOUNT_ONE;
        }
    };
};
