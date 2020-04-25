///////////////////////
// Unit Test	     //
// Element: treesets //
// Scope: empty set  //
///////////////////////

#include "treeset_array.h"
#include "treeset_array_balancing.h"
#include "treeset_dynamic.h"
#include "treeset_dynamic_balancing.h"
#include "treeset_stl.h"

#include "utest_treeset.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <limits>

using namespace std;
using namespace testing;

class EmptyTestInt8 : public TestWithParam<tuple<const TreesetObjectT*,int8_t,int8_t>>
{
public:
  using value_t = int8_t;
public:
  void SetUp() override {
    test_obj = get<0>(this->GetParam())->clone();
    range_min = get<1>(this->GetParam());
    range_max = get<2>(this->GetParam());
      }
  void TearDown() override {
    delete test_obj;
  }
public:
  TreesetObjectT* test_obj;
  int8_t range_min;
  int8_t range_max;
};

namespace EmptyTreesetTest {
  //TEST SUITE
  //SUBJECT empty <treeset>
  //INPUT  { treeset, range_min , range_max }
  //RESULT <treeset> doesn't contain any element in inclusive_range [min,max]
  TEST_P(EmptyTestInt8,ContainsReturnFalseForEntireRange)
  {
    for( auto test_value : make_InclusiveRange(range_min, range_max) )
      ASSERT_FALSE(test_obj->contains(test_value));
  }

  auto v_min = numeric_limits<int8_t>::min();
  auto v_max = numeric_limits<int8_t>::max();

  auto test_objects = Values( make_tuple( NEW_TEST_OBJ(treeset_stl<int8_t>), v_min, v_max ),
			      make_tuple( NEW_TEST_OBJ(treeset_array<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_array_balancing<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic_balancing<int8_t>), v_min, v_max) );

  //TEST DATASET
  //DATA insert = Inorder full set
  //DATA remove = [inorder | revorder | shuffled] [full | half with gaps]
  //DATA expect = [empty | half with gaps]
  INSTANTIATE_TEST_CASE_P(Treesets, EmptyTestInt8, test_objects );
}
