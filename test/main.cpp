#include "str.h"
#include "alloc.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

void *roc_alloc(size_t size, uint32_t _alignment)
{
    return malloc(size);
}

void *roc_realloc(void *ptr, size_t new_size, size_t _old_size, size_t _alignment)
{
    return realloc(ptr, new_size);
}

void roc_dealloc(void *ptr, uint32_t _alignment)
{
    free(ptr);
}

void roc_panic(const char *message, uint32_t tag_id)
{
    fprintf(stderr, "%s", message);
    exit(tag_id);
}

void *roc_memset(void *ptr, int value, size_t num_bytes)
{
    return memset(ptr, value, num_bytes);
}

int main()
{
    Roc::Str s("hello");
    printf("String length is %zd\n", s.length());
    return 0;
}
