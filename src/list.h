#pragma once

#include <cstddef>
#include <string.h>
#include "internal.h"

namespace Roc
{
    template <typename T>
    class List
    {
        T *m_elements;
        size_t m_length;
        size_t m_capacity;

        static size_t alloc_alignment()
        {
            return (alignof(T) > alignof(size_t)) ? alignof(T) : alignof(size_t);
        }

        char *allocation() const
        {
            return (char *)m_elements - List<T>::alloc_alignment();
        }

        size_t allocation_size() const
        {
            return (m_capacity * sizeof(T)) + List<T>::alloc_alignment();
        }

        ptrdiff_t *refcount_ptr() const
        {
            return (ptrdiff_t *)m_elements - 1;
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
                m_elements = NULL;
            }
            else
            {
                size_t alignment = List<T>::alloc_alignment();
                size_t rc_space = alignment;
                size_t rc_offset = rc_space - sizeof(size_t);
                size_t elems_offset = rc_space;
                size_t alloc_size = rc_space + cap * sizeof(T);
                char *alloc = (char *)roc_alloc(alloc_size, (uint32_t)alignment);
                ptrdiff_t *refcount = (ptrdiff_t *)(alloc + rc_offset);
                *refcount = REFCOUNT_ONE;
                m_elements = (T *)(alloc + elems_offset);

                if (elems != NULL)
                {
                    memcpy(m_elements, elems, len * sizeof(T));
                }
            }

            m_length = len;
            m_capacity = cap;
        }

        ~List()
        {
            if (m_elements != NULL)
            {
                for (size_t i = 0; i < m_length; i++)
                    m_elements[i].~T();
                roc_dealloc(allocation(), (uint32_t)List<T>::alloc_alignment());
            }
        }

        size_t length() const
        {
            return m_length;
        }

        size_t capacity() const
        {
            return m_capacity;
        }

        bool is_unique() const
        {
            if (m_elements == NULL)
                return true;
            return *refcount_ptr() == REFCOUNT_ONE;
        }

        /**
         * Increase capacity by at least the requested number of elements (possibly more).
         */
        void reserve(size_t num_extra_elems)
        {
            if (m_elements == NULL)
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
                    List<T>::alloc_alignment());
                if (new_alloc == old_alloc)
                {
                    // We've allocated in place!
                    m_capacity += num_extra_elems;
                }
                else
                {
                    // We got back a different allocation; copy the existing elements
                    // into it. We don't need to change their refcounts because we're
                    // just swapping one reference for another.
                    memcpy(new_alloc, old_alloc, old_alloc_size);
                    roc_dealloc(old_alloc, List<T>::alloc_alignment());
                    m_elements = (T *)((char *)new_alloc + List<T>::alloc_alignment());
                    m_capacity += num_extra_elems;
                }
            }
            else
            {
                // This allocation is shared. We need a new, bigger one.
                // Reduce refcount of the old allocation, and create a new List.
                // The element refcounts don't change, as we're removing one and adding one.
                (*refcount_ptr())--;
                *this = List<T>(m_elements, m_length, m_capacity + num_extra_elems);
            }
        }
    };
};
