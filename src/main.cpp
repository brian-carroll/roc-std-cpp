#include "str.h"
#include "alloc.h"
#include <cstdio>

int main()
{
    Roc::Str s("hello");
    printf("String length is %zd\n", s.length());
    return 0;
}
