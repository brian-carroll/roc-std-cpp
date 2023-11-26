#include "roc_std.h"
#include "lib/simpletest.h"

namespace Roc {

DEFINE_TEST_G(I64Str, Dict)
{
    Dict<I64, Str> dict;

    // I64 elems[5] = {I64(1), I64(2), I64(3), I64(4), I64(5)};
    // size_t len = sizeof(elems) / sizeof(elems[0]);
    // Roc::List<I64> list(elems, len);
    // TEST(list.length() == len);
    // TEST(list.capacity() == len);
}

};
