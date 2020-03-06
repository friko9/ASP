///////////////////////////////////////
// Unit Test			     //
// Element: list_stl		     //
// Scope: insert/contains large sets //
///////////////////////////////////////

//#include "test_deps.h"

#include "list_stl.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;
using namespace testing;

template <typename T>
class PopulateTest : public TestWithParam<T>
{
public:
  using value_t = typename T::value_type;
public:
  list_stl<value_t> test_obj;
  void populate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj.insert(x);});
  }
};

using PopulateTestInt16 = PopulateTest<Pretty<int16_t,vector>>;

namespace InsertionTest_ {
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set }
  //RESULT list contains listed elements after inorder insertion
  TEST_P(PopulateTestInt16,ContainsInserted)
  {
    auto& insert = GetParam();
    auto& expect = insert;

    EXPECT_NO_THROW( populate_test_obj(insert) );

    for( auto test_val : expect )
      ASSERT_TRUE(test_obj.contains(test_val))<<"Populated list_stl doesn't contain: "<<test_val<<endl;
  }
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set }
  //RESULT list doesn't contain not listed elements after inorder insertion
  TEST_P(PopulateTestInt16,DoesntContainNotInserted)
  {
    auto& insert = GetParam();
    auto expect = insert;

    EXPECT_NO_THROW( populate_test_obj(insert) );
    
    sort(expect.begin(),expect.end());

    auto expect_begin = expect.begin();
    for( auto i = numeric_limits<value_t>::min(); i<numeric_limits<value_t>::max(); ++i)
      {
  	auto it = find(expect_begin, expect.end(), i);
  	if( it != expect.end() )
  	  expect_begin = it;
  	else
  	  ASSERT_FALSE(test_obj.contains(i))<<"Populated list_stl contains: "<<i<<endl;
      }
  }
  
  using value_t = PopulateTestInt16::value_t;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();  
  constexpr value_t v_min_1 = numeric_limits<value_t>::min()+(value_t)1;
  // constexpr value_t v_max_1 = numeric_limits<value_t>::max()-(value_t)1;


  //TEST DATASET
  //DATA insert = [inorder|revorder|shuffled] full set
  //DATA expect = [inorder|revorder|shuffled] full set
  INSTANTIATE_TEST_CASE_P(FullSet, PopulateTestInt16,
  			  Values(  make_Pretty( make_InclusiveRange(v_min, v_max) ),
				   make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
				   make_ShuffledPretty( make_InclusiveRange(v_min, v_max) )
				   ));
  //TEST DATASET
  //DATA insert = [inorder|revorder|shuffled] half set with gaps
  //DATA expect = [inorder|revorder|shuffled] half set with gaps
  INSTANTIATE_TEST_CASE_P(GapsSet, PopulateTestInt16,
  			  Values(  make_Pretty( make_InclusiveRange(v_min_1, v_max, (value_t)2) ),
				   make_ReversePretty( make_InclusiveRange(v_min_1, v_max, (value_t)2) ),
				   make_ShuffledPretty( make_InclusiveRange(v_min_1, v_max, (value_t)2) )
				   ));
}

