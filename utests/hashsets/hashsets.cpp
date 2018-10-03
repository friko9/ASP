#include "hashset_array_test.h"
#include "hashset_bucket_test.h"
#include "hashset_stl_test.h"

#include <utility>

using namespace std;

test_set& test_hashset_array::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_hashset_bucket::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_hashset_stl::access_test_set()
{
    static test_set singleton;
    return singleton;
}

int main()
{
    test_set& lists_test = test_hashset_stl::access_test_set();
    lists_test << std::move( test_hashset_bucket::access_test_set() );
    lists_test << std::move( test_hashset_array::access_test_set() );
    lists_test.run();
    lists_test.summary();
}
