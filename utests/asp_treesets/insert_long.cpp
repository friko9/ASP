///////////////////////////////////////
// Unit Test			     //
// Element: treesets		     //
// Scope: insert/contains large sets //
///////////////////////////////////////

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
class PopulateTest
  : public TestWithParam <tuple <tuple<const TreesetObjectT*,
				       typename T::value_type,
				       typename T::value_type>,
				 T>>
{
public:
  using value_t = typename T::value_type;
public:
  void SetUp() override {
    test_obj_ = get<0>(get<0>(this->GetParam()))->clone();
    range_min_ = get<1>(get<0>(this->GetParam()));
    range_max_ = get<2>(get<0>(this->GetParam()));
  }
  void TearDown() override {
    delete test_obj_;
  }
  void populate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj_->insert(x);});
  }
public:
  TreesetObjectT* test_obj_;
  value_t range_min_;
  value_t range_max_;
};

using PopulateTestInt16 = PopulateTest<Pretty<int16_t,vector>>;

namespace InsertionTest_ {
  //TEST SUITE
  //SUBJECT empty set
  //INPUT  { insert_set }
  //RESULT set contains listed elements after inorder insertion
  TEST_P(PopulateTestInt16,ContainsInserted)
  {
    auto& insert = get<1>(GetParam());
    auto& expect = insert;

    EXPECT_NO_THROW( populate_test_obj(insert) );

    for( auto test_val : expect )
      ASSERT_TRUE(test_obj_->contains(test_val))<<"Populated set doesn't contain: "<<test_val<<endl;
  }
  //TEST SUITE
  //SUBJECT empty set
  //INPUT  { insert_set }
  //RESULT set doesn't contain not listed elements after inorder insertion
  TEST_P(PopulateTestInt16,DoesntContainNotInserted)
  {
    auto& insert = get<1>(GetParam());
    auto expect = insert;

    EXPECT_NO_THROW( populate_test_obj(insert) );

    sort(expect.begin(),expect.end());

    auto expect_begin = expect.begin();
    for( auto i : make_InclusiveRange(range_min_, range_max_) )
      {
  	auto it = find(expect_begin, expect.end(), i);
  	if( it != expect.end() )
  	  expect_begin = it;
  	else
  	  ASSERT_FALSE(test_obj_->contains(i))<<"Populated set contains: "<<i<<endl;
      }
  }

  using value_t = PopulateTestInt16::value_t;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();
  constexpr value_t v_min_1 = numeric_limits<value_t>::min() + value_t {1};

  auto test_objects = Values( make_tuple( NEW_TEST_OBJ(treeset_stl<int16_t>), v_min, v_max ),
			      make_tuple( NEW_TEST_OBJ(treeset_array_balancing<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic_balancing<int16_t>), v_min, v_max) );

  //TEST DATASET
  //DATA insert = [inorder|revorder|shuffled] full set
  //DATA expect = [inorder|revorder|shuffled] full set
  INSTANTIATE_TEST_CASE_P(FullSet, PopulateTestInt16,
			  Combine( test_objects,
				   Values( make_Pretty( make_InclusiveRange(v_min, v_max) ),
					   make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
					   make_ShuffledPretty( make_InclusiveRange(v_min, v_max) )
					   )));
  //TEST DATASET
  //DATA insert = [inorder|revorder|shuffled] half set with gaps
  //DATA expect = [inorder|revorder|shuffled] half set with gaps
  INSTANTIATE_TEST_CASE_P(GapsSet, PopulateTestInt16,
			  Combine( test_objects,
				   Values( make_Pretty( make_InclusiveRange(v_min_1, v_max, value_t {2}) ),
					   make_ReversePretty( make_InclusiveRange(v_min_1, v_max, value_t {2}) ),
					   make_ShuffledPretty( make_InclusiveRange(v_min_1, v_max, value_t {2}) )
					   )));
}

