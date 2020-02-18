///////////////////////
// Unit Test	     //
// Element: list_stl //
// Scope: empty list //
///////////////////////

//#include "test_deps.h"

#include "list_stl.h"
#include "utest_utils.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;
using namespace testing;

template<typename T>
class EmptyList : public TestWithParam<T>{
public:
  using value_t = T;
  static list_stl<T> empty_list;
};
template<typename T>
list_stl<T> EmptyList<T>::empty_list;

using EmptyListInt = EmptyList<int>;
using EmptyListInt8 = EmptyList<int8_t>;
using EmptyListFloat = EmptyList<float>;
//TEST SUITE
//SUBJECT empty list_stl
//RESULT doesnt contain any element
namespace EmptyListTest {
  TEST_P(EmptyListInt8, ContainsReturnFalse)
  {
    ASSERT_FALSE(empty_list.contains(GetParam()));
  }
  //TEST DATASET
  //DATA all single elements in EmptyListInt8
  using value_t = EmptyListInt8::value_t;
  INSTANTIATE_TEST_CASE_P(range, EmptyListInt8, Range(numeric_limits<value_t>::min(),numeric_limits<value_t>::max()));
}
