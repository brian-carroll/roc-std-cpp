#pragma once

#include <cstddef>
#include <string.h>
#include "alloc.h"

namespace Roc
{
    template <typename T>
    class List
    {
        T *elements;
        size_t length;
        size_t capacity;

        static size_t alignment()
        {
            return (alignof(T) > alignof(size_t)) ? alignof(T) : alignof(size_t);
        }

        char *allocation()
        {
            return (char *)elements - List<T>::alignment();
        }

        size_t allocation_size()
        {
            return (capacity * sizeof(T)) + List<T>::alignment();
        }

        ptrdiff_t *refcount_ptr()
        {
            return (ptrdiff_t *)elements - 1;
        }

    public:
        List(const T *elems = NULL, size_t len = 0, size_t cap = 0)
        {
            if (elems == NULL)
                len = 0;
            if (len > cap)
                cap = len;

            if (cap == 0)
            {
                elements = NULL;
            }
            else
            {
                size_t alignment = List<T>::alignment();
                size_t rc_space = alignment;
                size_t rc_offset = rc_space - sizeof(size_t);
                size_t elems_offset = rc_space;
                size_t alloc_size = rc_space + cap;
                char *alloc = (char *)roc_alloc(alloc_size, (uint32_t)alignment);
                ptrdiff_t *refcount = (ptrdiff_t *)(alloc + rc_offset);
                *refcount = REFCOUNT_ONE;
                elements = alloc + elems_offset;

                if (elems != NULL)
                {
                    memcpy(elements, elems, len * sizeof(T));
                }
            }

            length = len;
            capacity = cap;
        }

        ~List()
        {
            if (elements != NULL)
            {
                for (size_t i = 0; i < length; i++)
                    elements[i].~T();
                roc_dealloc(allocation(), (uint32_t)List<T>::alignment());
            }
        }

        bool is_unique()
        {
            if (elements == NULL)
                return true;
            return *refcount_ptr() == REFCOUNT_ONE;
        }

        /**
         * Increase capacity by at least the requested number of elements (possibly more).
         */
        void reserve(size_t num_extra_elems)
        {
            if (elements == NULL)
            {
                *this = List<T>(NULL, 0, num_extra_elems);
            }
            else if (is_unique())
            {
                char *old_alloc = allocation();
                size_t old_alloc_size = allocation_size();
                char *new_alloc = (char *)roc_realloc(
                    old_alloc,
                    old_alloc_size + num_extra_elems,
                    old_alloc_size,
                    List<T>::alignment());
                if (new_alloc == old_alloc)
                {
                    // We've allocated in place!
                    capacity += num_extra_elems;
                }
                else
                {
                    // We got back a different allocation; copy the existing elements
                    // into it. We don't need to increment their refcounts because
                    // The existing allocation that references to them is now gone and
                    // no longer referencing them.
                    memcpy(new_alloc, old_alloc, old_alloc_size);
                    roc_dealloc(old_alloc, List<T>::alignment());
                    elements = (T *)((char *)new_alloc + List<T>::alignment());
                    capacity += num_extra_elems;
                }
            }
            else
            {
                // This allocation is shared. We need a new, bigger one.
                // Reduce refcount of the old allocation, and create a new List.
                // The element refcounts don't change, as we're removing one and adding one.
                (*refcount_ptr())--;
                *this = List<T>(elements, length, capacity + num_extra_elems);
            }
        }
    };
};
