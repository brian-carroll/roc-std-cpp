#include "roc_std.h"
#include "lib/simpletest.h"

namespace Roc
{

    DEFINE_TEST_G(I64Str, Dict)
    {
        Dict<I64, Str> dict(5);
        I64 ints[5] = {I64(1), I64(2), I64(3), I64(4), I64(5)};
        Str strs[5] = {Str("1"), Str("2"), Str("3"), Str("4"), Str("5")};
        for (size_t i = 0; i < 5; i++)
        {
            dict.insert(ints[i], strs[i]);
        }
        TEST_EQ(dict.length(), 5);
        TEST_EQ(dict.capacity(), 5);

        for (size_t i = 0; i < 5; i++)
        {
            Str *s = dict.get(&ints[i]);
            TEST_EQ(*s, strs[i]);
        }

        TEST_EQ(dict.length(), 5);
        TEST_EQ(dict.capacity(), 5);
    }

    DEFINE_TEST_G(StrI64, Dict)
    {
        Dict<Str, I64> dict(5);
        I64 ints[5] = {I64(1), I64(2), I64(3), I64(4), I64(5)};
        Str strs[5] = {Str("1"), Str("2"), Str("3"), Str("4"), Str("5")};
        for (size_t i = 0; i < 5; i++)
        {
            dict.insert(strs[i], ints[i]);
        }
        for (size_t i = 0; i < 5; i++)
        {
            I64 *x = dict.get(&strs[i]);
            TEST_EQ(*x, ints[i]);
        }
        TEST_EQ(dict.length(), 5);
        TEST_EQ(dict.capacity(), 5);
    }

    DEFINE_TEST_G(I64I64, Dict)
    {
        Dict<I64, I64> dict(5);
        I64 ints[5] = {I64(1), I64(2), I64(3), I64(4), I64(5)};
        for (size_t i = 0; i < 5; i++)
        {
            dict.insert(ints[i], ints[i]);
        }
        for (size_t i = 0; i < 5; i++)
        {
            I64 *x = dict.get(&ints[i]);
            TEST_EQ(*x, ints[i]);
        }
        TEST_EQ(dict.length(), 5);
        TEST_EQ(dict.capacity(), 5);
    }

};
