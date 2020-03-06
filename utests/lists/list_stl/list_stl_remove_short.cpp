//////////////////////////////////////////////
// Unit Test			            //
// Element: list_stl		            //
// Scope: insert/remove/contains small sets //
//////////////////////////////////////////////

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
class PopulateRemoveTest : public TestWithParam<tuple<T,T,T>>
{
public:
  using value_t = typename T::value_type;
public:
  list_stl<value_t> test_obj;
  void populate_test_obj(vector<value_t> arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj.insert(x);});
  }
  void depopulate_test_obj(vector<value_t> arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj.remove(x);});
  }
};

using PopulateRemoveTestInt8 = PopulateRemoveTest<vector<int8_t>>;

namespace EmptyRemovalTest_ {
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT list contains listed element after insertion
  TEST_P(PopulateRemoveTestInt8,ContainsAllTest)
  {
    auto& insert = get<0>(GetParam());
    auto& remove = get<1>(GetParam());
    auto& expect = get<2>(GetParam());

    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );
    
    for( auto test_val : expect )
      ASSERT_TRUE(test_obj.contains(test_val))<<"Populated list_stl doesn't contain: "<<test_val<<endl;
  }

  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT list doesn't contain not listed elements after insertion
  TEST_P(PopulateRemoveTestInt8,DoesntContainOtherTest)
  {
    auto& insert = get<0>(GetParam());
    auto& remove = get<1>(GetParam());
    auto expect = get<2>(GetParam());
    
    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );
    
    stable_sort(expect.begin(),expect.end());

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
  
  using value_t = PopulateRemoveTestInt8::value_t;
  using tuple_t = tuple<vector<value_t>,vector<value_t>,vector<value_t>>;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();  
  //TEST DATASET
  //DATA insert = empty
  //DATA remove = single elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(0ExR1NEx0E, PopulateRemoveTestInt8,
			  Values(tuple_t{{},{0},{}},
				 tuple_t{{},{v_min},{}},
				 tuple_t{{},{v_max},{}}
				 ));
  //TEST DATASET
  //DATA insert = single elements
  //DATA remove = single elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(1ExR1Ex0E, PopulateRemoveTestInt8,
			  Values(tuple_t{{0},{0},{}},
				 tuple_t{{v_min},{v_min},{}},
				 tuple_t{{v_max},{v_max},{}}
				 ));
  //TEST DATASET
  //DATA insert = single elements
  //DATA remove = single elements
  //DATA expect = single elements
  INSTANTIATE_TEST_CASE_P(1ExR1NEx1E, PopulateRemoveTestInt8,
			  Values(tuple_t{{0},{v_max},{0}},
				 tuple_t{{v_min},{0},{v_min}},
				 tuple_t{{v_max},{v_min},{v_max}}
				 ));
  //TEST DATASET
  //DATA insert = single elements.
  //DATA remove = repeating elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(1ExR2Ex0E, PopulateRemoveTestInt8,
			  Values(tuple_t{{0},{0,0},{}},
				 tuple_t{{v_min},{v_min,v_min},{}},
				 tuple_t{{v_max},{v_max,v_max},{}}
				 ));
  //TEST DATASET
  //DATA insert = repeating elements
  //DATA remove = single elements
  //DATA expect = single elements
  INSTANTIATE_TEST_CASE_P(2ExR1Ex1E, PopulateRemoveTestInt8,
			  Values(tuple_t{{0,0},{0},{0}},
				 tuple_t{{v_min,v_min},{v_min},{v_min}},
				 tuple_t{{v_max,v_max},{v_max},{v_max}}
				 ));
  //TEST DATASET
  //DATA insert = repeating elements
  //DATA remove = repeating elements
  //DATA expect = empty
  INSTANTIATE_TEST_CASE_P(2ExR2Ex0E, PopulateRemoveTestInt8,
			  Values(tuple_t{{0,0},{0,0},{}},
				 tuple_t{{v_min,v_min},{v_min,v_min},{}},
				 tuple_t{{v_max,v_max},{v_max,v_max},{}}
				 ));
}

