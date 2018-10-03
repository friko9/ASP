#include "list_array_test.h"
#include "list_array_enchanced_test.h"
#include "list_array_selforganizing_test.h"
#include "list_array_sorted_test.h"
#include "list_array_sorted_warden_test.h"
#include "list_dynamic_test.h"
#include "list_stl_test.h"
#include "list_stlforward_test.h"

#include <utility>

using namespace std;

test_set& test_list_array::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_array_enchanced::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_array_selforganizing::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_array_sorted::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_array_sorted_warden::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_dynamic::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_stl::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_list_stlforward::access_test_set()
{
    static test_set singleton;
    return singleton;
}

int main()
{
    test_set& test = test_list_stl::access_test_set();
    test << std::move( test_list_stlforward::access_test_set() );
    test << std::move( test_list_dynamic::access_test_set() );
    test << std::move( test_list_array::access_test_set() );
    test << std::move( test_list_array_enchanced::access_test_set() );
    test << std::move( test_list_array_selforganizing::access_test_set() );
    test << std::move( test_list_array_sorted::access_test_set() );
    test << std::move( test_list_array_sorted_warden::access_test_set() );
    test.run();
    test.summary();
}
