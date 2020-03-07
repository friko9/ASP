///////////////////////////////////////
// Unit Test			     //
// Element: list_stl		     //
// Scope: insert/contains large sets //
///////////////////////////////////////

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
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;
using namespace testing;

template <typename T>
class PopulateTest
  : public TestWithParam <tuple <tuple<const ListObjectT*,
				       typename T::value_type,
				       typename T::value_type>,
				 T>>
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
  void populate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj->insert(x);});
  }
public:
  ListObjectT* test_obj;
  value_t range_min;
  value_t range_max;
};

using PopulateTestInt16 = PopulateTest<Pretty<int16_t,vector>>;

namespace InsertionTest_ {
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set }
  //RESULT list contains listed elements after inorder insertion
  TEST_P(PopulateTestInt16,ContainsInserted)
  {
    auto& insert = get<1>(GetParam());
    auto& expect = insert;

    EXPECT_NO_THROW( populate_test_obj(insert) );

    for( auto test_val : expect )
      ASSERT_TRUE(test_obj->contains(test_val))<<"Populated list_stl doesn't contain: "<<test_val<<endl;
  }
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set }
  //RESULT list doesn't contain not listed elements after inorder insertion
  TEST_P(PopulateTestInt16,DoesntContainNotInserted)
  {
    auto& insert = get<1>(GetParam());
    auto expect = insert;

    EXPECT_NO_THROW( populate_test_obj(insert) );
    
    sort(expect.begin(),expect.end());

    auto expect_begin = expect.begin();
    for( auto i : make_InclusiveRange(range_min, range_max) )
      {
  	auto it = find(expect_begin, expect.end(), i);
  	if( it != expect.end() )
  	  expect_begin = it;
  	else
  	  ASSERT_FALSE(test_obj->contains(i))<<"Populated list_stl contains: "<<i<<endl;
      }
  }
  
  using value_t = PopulateTestInt16::value_t;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();  
  constexpr value_t v_min_1 = numeric_limits<value_t>::min() + value_t {1};

  auto test_objects = Values( make_tuple( NEW_TEST_OBJ(list_stl<int16_t>), v_min, v_max ),
			      make_tuple( NEW_TEST_OBJ(list_stlforward<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(list_array<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(list_array_enchanced<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(list_array_selforganizing<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(list_array_sorted<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(list_array_sorted_warden<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(list_dynamic<int16_t>), v_min, v_max)  );

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

