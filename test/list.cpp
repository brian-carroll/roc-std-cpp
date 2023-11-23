#include "list.h"
#include "internal.h"
#include "lib/simpletest.h"
#include <cstdio>

struct SomeStruct
{
    int64_t a;
    int64_t b;
};

DEFINE_TEST_G(FromArrayI64, List)
{
    int64_t elems[5] = {1, 2, 3, 4, 5};
    size_t len = sizeof(elems) / sizeof(elems[0]);
    Roc::List<int64_t> list(elems, len);
    TEST(list.length() == len);
    TEST(list.capacity() == len);
}

DEFINE_TEST_G(FromArrayOfStruct, List)
{
    SomeStruct elems[5] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    size_t len = sizeof(elems) / sizeof(elems[0]);
    Roc::List<SomeStruct> list(elems, len);
    TEST(list.length() == len);
    TEST(list.capacity() == len);
}

DEFINE_TEST_G(ReserveSmall, List)
{
    Roc::List<SomeStruct> list;
    size_t cap = 42;
    list.reserve(cap);
    TEST_EQ(list.length(), 0);
    TEST_EQ(list.capacity(), cap);
}
