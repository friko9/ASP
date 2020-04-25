//////////////////////////////////////////////
// Unit Test			            //
// Element: treesets		            //
// Scope: insert/remove/contains small sets //
//////////////////////////////////////////////

#include "treeset_array.h"
#include "treeset_array_balancing.h"
#include "treeset_dynamic.h"
#include "treeset_dynamic_balancing.h"
#include "treeset_stl.h"

#include "utest_treeset.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;
using namespace testing;

template <typename T>
class PopulateRemoveTest
  : public TestWithParam <tuple <tuple<const TreesetObjectT*,
				       typename T::value_type,
				       typename T::value_type>,
				 tuple<T,T,T>>>
{
public:
  using value_t = typename T::value_type;
public:
  void SetUp() override {
    test_obj = get<0>(get<0>(this->GetParam()))->clone();
    range_min = get<1>(get<0>(this->GetParam()));
    range_max = get<2>(get<0>(this->GetParam()));
  }
  void TearDown() override {
    delete test_obj;
  }
  void populate_test_obj(vector<value_t> arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj->insert(x);});
  }
  void depopulate_test_obj(vector<value_t> arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj->remove(x);});
  }
public:
  TreesetObjectT* test_obj;
  value_t range_min;
  value_t range_max;
};

using PopulateRemoveTestInt8 = PopulateRemoveTest<vector<int8_t>>;

namespace EmptyRemovalTest_ {
  //TEST SUITE
  //SUBJECT empty treeset
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT treeset contains treeseted element after insertion
  TEST_P(PopulateRemoveTestInt8,ContainsAllTest)
  {
    auto& insert = get<0>(get<1>(GetParam()));
    auto& remove = get<1>(get<1>(GetParam()));
    auto& expect = get<2>(get<1>(GetParam()));

    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );

    for( auto test_val : expect )
      ASSERT_TRUE(test_obj->contains(test_val))<<"Populated treeset doesn't contain: "<<test_val<<endl;
  }

  //TEST SUITE
  //SUBJECT empty treeset
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT treeset doesn't contain not treeseted elements after insertion
  TEST_P(PopulateRemoveTestInt8,DoesntContainOtherTest)
  {
    auto& insert = get<0>(get<1>(GetParam()));
    auto& remove = get<1>(get<1>(GetParam()));
    auto expect = get<2>(get<1>(GetParam()));

    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );

    stable_sort(expect.begin(),expect.end());

    auto expect_begin = expect.begin();
    for( auto i : make_InclusiveRange(range_min, range_max) )
      {
	auto it = find(expect_begin, expect.end(), i);
	if( it != expect.end() )
	  expect_begin = it;
	else
	  ASSERT_FALSE(test_obj->contains(i))<<"Populated treeset contains: "<<i<<endl;
      }
  }

  using value_t = PopulateRemoveTestInt8::value_t;
  using tuple_t = tuple<vector<value_t>,vector<value_t>,vector<value_t>>;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();

  auto test_objects = Values( make_tuple( NEW_TEST_OBJ(treeset_stl<int8_t>), v_min, v_max ),
			      make_tuple( NEW_TEST_OBJ(treeset_array<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_array_balancing<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic_balancing<int8_t>), v_min, v_max) );

  // A - add, R - remove, E - existing, N - not existing
  // A0xR1Nx0E - empty -> Add 0 elements - Remove 1 Non-existing -> Result 0 Existing
  //TEST DATASET
  //DATA insert = empty
  //DATA remove = single elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(A0xR1Nx0E, PopulateRemoveTestInt8,
			  Combine( test_objects,
				   Values(tuple_t{{},{0},{}},
					  tuple_t{{},{v_min},{}},
					  tuple_t{{},{v_max},{}}
					  )));
  //TEST DATASET
  //DATA insert = single elements
  //DATA remove = single elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(A1xR1Ex0E, PopulateRemoveTestInt8,
			  Combine( test_objects,
				   Values(tuple_t{{0},{0},{}},
					  tuple_t{{v_min},{v_min},{}},
					  tuple_t{{v_max},{v_max},{}}
					  )));
  //TEST DATASET
  //DATA insert = single elements
  //DATA remove = single elements
  //DATA expect = single elements
  INSTANTIATE_TEST_CASE_P(A1xR1Nx1E, PopulateRemoveTestInt8,
			  Combine( test_objects,
				   Values(tuple_t{{0},{v_max},{0}},
					  tuple_t{{v_min},{0},{v_min}},
					  tuple_t{{v_max},{v_min},{v_max}}
					  )));
  //TEST DATASET
  //DATA insert = single elements.
  //DATA remove = repeating elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(A1ExR2Ex0E, PopulateRemoveTestInt8,
			  Combine( test_objects,
				   Values(tuple_t{{0},{0,0},{}},
					  tuple_t{{v_min},{v_min,v_min},{}},
					  tuple_t{{v_max},{v_max,v_max},{}}
					  )));
  //TEST DATASET
  //DATA insert = repeating elements
  //DATA remove = single elements
  //DATA expect = single elements
  INSTANTIATE_TEST_CASE_P(A2ExR1Ex0E, PopulateRemoveTestInt8,
			  Combine( test_objects,
				   Values(tuple_t{{0,0},{0},{}},
					  tuple_t{{v_min,v_min},{v_min},{}},
					  tuple_t{{v_max,v_max},{v_max},{}}
					  )));
  //TEST DATASET
  //DATA insert = repeating elements
  //DATA remove = repeating elements
  //DATA expect = empty
  INSTANTIATE_TEST_CASE_P(A2ExR2Ex0E, PopulateRemoveTestInt8,
			  Combine( test_objects,
				   Values(tuple_t{{0,0},{0,0},{}},
					  tuple_t{{v_min,v_min},{v_min,v_min},{}},
					  tuple_t{{v_max,v_max},{v_max,v_max},{}}
					  )));
}

