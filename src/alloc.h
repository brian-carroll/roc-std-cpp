#ifndef ROC_ALLOC_H
#define ROC_ALLOC_H

#include <cstddef>
#include <cstdint>

#define REFCOUNT_ONE ((ptrdiff_t)1 << (sizeof(ptrdiff_t) * 8 - 1))

void *roc_alloc(size_t size, uint32_t alignment);
void *roc_realloc(void *ptr, size_t new_size, size_t old_size, size_t alignment);
void roc_dealloc(void *ptr, uint32_t alignment);
void roc_panic(const char *message, uint32_t _tag_id);
void *roc_memset(void *ptr, int value, size_t num_bytes);

#endif
