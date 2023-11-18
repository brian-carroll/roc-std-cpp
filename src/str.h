#include <cstddef>
#include <cstdint>
#include <string.h>
#include "alloc.h"

namespace Roc
{
    #define SMALL_STRING_SIZE sizeof(struct roc_big_str)
    #define REFCOUNT_SIZE sizeof(size_t)

    struct roc_big_str
    {
        char *bytes;
        size_t length;
        size_t capacity;
    };

    class Str
    {
        union
        {
            struct roc_big_str big;
            char small[SMALL_STRING_SIZE];
        };

    public:
        Str(const char *cstr, size_t requested_capacity)
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
                       ? small[SMALL_STRING_SIZE - 1] & 0x7f
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
