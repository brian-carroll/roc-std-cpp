#include "str.h"
#include "alloc.h"
#include <cstdio>

// Single translation unit compilation. Include all the source files here.
#include "lib/simpletest.cpp"
#include "alloc.cpp"
#include "str.cpp"
#include "list.cpp"

char const *groups[] = {
    "Str",
};

int main()
{
    bool pass = true;

    for (auto group : groups)
    {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}
