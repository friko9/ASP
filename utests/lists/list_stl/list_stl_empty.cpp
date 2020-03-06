///////////////////////
// Unit Test	     //
// Element: list_stl //
// Scope: empty list //
///////////////////////

//#include "test_deps.h"

#include "list_stl.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <limits>

using namespace std;
using namespace testing;

//TEST SUITE
//SUBJECT empty list_stl
//RESULT doesnt contain any element
namespace EmptyListTest {
  TEST(EmptyListInt8,ContainsReturnFalseForEntireRange)
  {
    using value_t = int8_t;
    list_stl<value_t> empty_list;
    for( auto test_value : Range(numeric_limits<value_t>::min(),numeric_limits<value_t>::max()) )
      ASSERT_FALSE(empty_list.contains(test_value));
  }
}
