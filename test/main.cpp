#include "str.h"
#include "alloc.h"
#include <cstdio>

// Single translation unit compilation. Include all the source files here.
#include "alloc.cpp"
#include "str.cpp"

int main()
{
    test_str_len();
    return 0;
}
