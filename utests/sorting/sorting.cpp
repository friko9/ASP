#include "sorting.h"
#include <utility>

using namespace std;

test_set& sorting::access_test_set()
{
    static test_set singleton;
    return singleton;
}

int main(int argc, char *argv[])
{
    test_set& test = sorting::access_test_set();
    test.run();
    test.summary();
}
