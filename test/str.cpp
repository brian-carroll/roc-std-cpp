#include "str.h"
#include "alloc.h"
#include <cstdio>

void test_str_len()
{
    Roc::Str s("hello");
    printf("String length is %zd\n", s.length());
}
