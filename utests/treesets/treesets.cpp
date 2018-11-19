#include "treeset_array_test.h"
#include "treeset_array_balancing_test.h"
#include "treeset_dynamic_test.h"
#include "treeset_dynamic_balancing_test.h"
#include "treeset_stl_test.h"

#include <utility>

using namespace std;

test_set& test_treeset_stl::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_treeset_dynamic::access_test_set()
{
    // TODO
    // del_subtree.cpp
    static test_set singleton;
    return singleton;
}
test_set& test_treeset_dynamic_balancing::access_test_set()
{
    //TODO
    // del_subtree.cpp
    static test_set singleton;
    return singleton;
}
test_set& test_treeset_array::access_test_set()
{
    static test_set singleton;
    return singleton;
}
test_set& test_treeset_array_balancing::access_test_set()
{
    static test_set singleton;
    return singleton;
}

int main()
{
    test_set& test = test_treeset_stl::access_test_set();
    test << std::move( test_treeset_dynamic::access_test_set() );
    test << std::move( test_treeset_dynamic_balancing::access_test_set() );
    test << std::move( test_treeset_array::access_test_set() );
    test << std::move( test_treeset_array_balancing::access_test_set() );
    test.run();
    test.summary();
}
