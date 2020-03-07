///////////////////////
// Unit Test	     //
// Element: list_stl //
// Scope: empty list //
///////////////////////

//#include "test_deps.h"

#include "list_array.h"
#include "list_array_enchanced.h"
#include "list_array_selforganizing.h"
#include "list_array_sorted.h"
#include "list_array_sorted_warden.h"
#include "list_dynamic.h"
#include "list_stl.h"
#include "list_stlforward.h"

#include "utest_list.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <limits>

using namespace std;
using namespace testing;

class EmptyTestInt8 : public TestWithParam<tuple<const ListObjectT*,int8_t,int8_t>>
{
public:
  using value_t = int8_t;
public:
  void SetUp() override {
    test_obj = get<0>(this->GetParam())->clone();
      }
public:
  ListObjectT* test_obj;
};

namespace EmptyListTest {
  //TEST SUITE
  //SUBJECT empty <list>
  //INPUT  { list, range_min , range_max }
  //RESULT <list> doesn't contain any element in inclusive_range [min,max]
  TEST_P(EmptyTestInt8,ContainsReturnFalseForEntireRange)
  {
    auto min = get<1>(GetParam());
    auto max = get<2>(GetParam());
    for( auto test_value : make_InclusiveRange(min, max) )
      ASSERT_FALSE(test_obj->contains(test_value));
  }
  
  auto v_min = numeric_limits<int8_t>::min();
  auto v_max = numeric_limits<int8_t>::max();  
  auto v_min_1 = numeric_limits<int8_t>::min() + int8_t{1};
  auto v_max_1 = numeric_limits<int8_t>::max() - int8_t{1};

  //TEST DATASET
  //DATA insert = Inorder full set
  //DATA remove = [inorder | revorder | shuffled] [full | half with gaps]
  //DATA expect = [empty | half with gaps]
  INSTANTIATE_TEST_CASE_P(Lists, EmptyTestInt8,
			  Values(
				 make_tuple( NEW_TEST_OBJ(list_stl<int8_t>), v_min, v_max ),
				 make_tuple( NEW_TEST_OBJ(list_stlforward<int8_t>), v_min, v_max),
				 make_tuple( NEW_TEST_OBJ(list_array<int8_t>), v_min, v_max),
				 make_tuple( NEW_TEST_OBJ(list_array_enchanced<int8_t>), v_min, v_max),
				 make_tuple( NEW_TEST_OBJ(list_array_selforganizing<int8_t>), v_min, v_max),
				 make_tuple( NEW_TEST_OBJ(list_array_sorted<int8_t>), v_min, v_max),
				 make_tuple( NEW_TEST_OBJ(list_array_sorted_warden<int8_t>), v_min_1, v_max_1),
				 make_tuple( NEW_TEST_OBJ(list_dynamic<int8_t>), v_min, v_max)
				 ));
}
