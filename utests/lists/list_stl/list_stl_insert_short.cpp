///////////////////////////////////////
// Unit Test			     //
// Element: list_stl		     //
// Scope: insert/contains small sets //
///////////////////////////////////////

//#include "test_deps.h"

#include "list_stl.h"
#include "utest_utils.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;
using namespace testing;

template <typename T>
class List : public TestWithParam<pair<vector<T>,vector<T>>>
{
public:
  using value_t = T;
public:
  list_stl<T> test_obj;
  void populate_test_obj(vector<T> arg)  {
    for( auto x : arg )
      test_obj.insert(x);
  }
};

using InsertionTestInt8 = List<int8_t>;

namespace InsertionTest_ {
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set , check_set }
  //RESULT list contains listed elements after insertion
  TEST_P(InsertionTestInt8,ContainsAfterInsert)
  {
    auto& insert = GetParam().first;
    auto& expect = GetParam().second;
    populate_test_obj(insert);
    
    for( auto test_val : expect )
	ASSERT_TRUE(test_obj.contains(test_val))<<"Populated list_stl doesn't contain: "<<test_val<<endl;
  };

  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set , check_set }
  //RESULT list doesn't contain not listed elements after insertion
  TEST_P(InsertionTestInt8,DoesntContainOtherElements)
  {
    auto& insert = GetParam().first;
    auto expect = GetParam().second;
    populate_test_obj(insert);

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
  };
  
  using value_t = InsertionTestInt8::value_t;
  using pair_t = std::pair<std::vector<value_t>,std::vector<value_t>>;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();  
  //TEST DATASET
  //DATA insert = single elements.
  //DATA expect = single elements.
  INSTANTIATE_TEST_CASE_P(1Element, InsertionTestInt8,
			  Values(pair_t{{0},{0}},
				 pair_t{{v_min},{v_min}},
				 pair_t{{v_max},{v_max}}
				 ));
  //TEST DATASET
  //DATA insert = single elements.
  //DATA expect = repeating elements.
  INSTANTIATE_TEST_CASE_P(1Element2Checks, InsertionTestInt8,
			  Values(pair_t{{0},{0,0}},
				 pair_t{{v_min},{v_min,v_min}},
				 pair_t{{v_max},{v_max,v_max}}
				 ));
  //TEST DATASET
  //DATA insert = repeating elements.
  //DATA expect = single elements.
  INSTANTIATE_TEST_CASE_P(2Elements, InsertionTestInt8,
			  Values(pair_t{{0,0},{0}},
				 pair_t{{v_min,v_min},{v_min}},
				 pair_t{{v_max,v_max},{v_max}}
				 ));
  //TEST DATASET
  //DATA insert = 3 elements different combinations.
  //DATA expect = insert.
  INSTANTIATE_TEST_CASE_P(3Elements, InsertionTestInt8,
			  Values(pair_t{{v_min,1,v_max},{v_min,1,v_max}},
				 pair_t{{v_min,v_max,1},{v_min,1,v_max}},
				 pair_t{{1,v_min,v_max},{v_min,1,v_max}},
				 pair_t{{1,v_max,v_min},{v_min,1,v_max}},
				 pair_t{{v_max,v_min,1},{v_min,1,v_max}},
				 pair_t{{v_max,1,v_min},{v_min,1,v_max}}
				 ));
}

