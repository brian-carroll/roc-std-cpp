#pragma once

#include "internal.h"
#include "list.h"

namespace Roc
{

    template <typename K, typename V>
    struct DictItemKeyFirst
    {
        K key;
        V value;
    };

    template <typename K, typename V>
    struct DictItemValueFirst
    {
        V value;
        K key;
    };

    template <typename K, typename V>
    const bool LAYOUT_KEY_FIRST = __alignof__(K) >= __alignof__(V);

    /*
     * Roc is constructing these values according to its memory layout rules.
     * Specifically:
     *
     * 1. fields with the highest alignment go first
     * 2. then fields are sorted alphabetically
     *
     * Taken together, these mean that if we have a value with higher alignment
     * than the key, it'll be first in memory. Otherwise, the key will be first.
     * Fortunately, the total amount of memory doesn't change, so we can use a
     * union and disambiguate by examining the alignment of the key and value.
     *
     * However, note that this only makes sense while we're storing KV pairs
     * contiguously in memory. If we separate them at some point, we'll need to
     * change this implementation drastically!
     */
    template <typename K, typename V>
    union DictItem
    {
        DictItemKeyFirst<K, V> key_first;
        DictItemValueFirst<K, V> value_first;

        DictItem(K key, V value)
        {
            if (LAYOUT_KEY_FIRST<K, V>)
            {
                key_first = {
                    .key = key,
                    .value = value,
                };
            }
            else
            {
                value_first = {
                    .value = value,
                    .key = key,
                };
            }
        }

        K *key() const
        {
            return LAYOUT_KEY_FIRST<K, V>
                       ? &key_first.key
                       : &value_first.key;
        }

        V *value() const
        {
            return LAYOUT_KEY_FIRST<K, V>
                       ? &key_first.value
                       : &value_first.value;
        }
    };

    template <typename K, typename V>
    class Dict
    {
        List<DictItem<K, V>> list;
    };
};