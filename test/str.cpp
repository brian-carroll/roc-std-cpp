#include "str.h"
#include "alloc.h"
#include "lib/simpletest.h"
#include <cstdio>

DEFINE_TEST_G(TestLength, Str)
{
    Roc::Str s("hello");
	TEST_EQ(s.length(), 5);
}
