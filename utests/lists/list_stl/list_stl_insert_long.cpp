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
vector<T> toInorderVector(const internal::ParamGenerator<T>& arg) {
  return vector<T>(arg.begin(),arg.end());
}

template <typename T>
vector<T> toRandomizedVector(const internal::ParamGenerator<T>& arg) {
  auto array = toInorderVector(arg);
  random_shuffle(array.begin(), array.end());
  return array;
}

template <typename T>
class List : public TestWithParam<vector<T>>
{
public:
  using value_t = T;
public:
  list_stl<T> test_obj;
  template<typename It>
  inline
  void populate_test_obj(It begin,It end)  {
    for_each(begin, end, [this](auto x){test_obj.insert(x);});
  }
};

using InsertionTestInt16 = List<int16_t>;

namespace InsertionTest_ {
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set }
  //RESULT list contains listed elements after inorder insertion
  TEST_P(InsertionTestInt16,ContainsInserted)
  {
    auto& insert = GetParam();
    auto& expect = insert;

    populate_test_obj(insert.begin(),insert.end());

    for( auto test_val : expect )
      ASSERT_TRUE(test_obj.contains(test_val))<<"Populated list_stl doesn't contain: "<<test_val<<endl;
  }
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set }
  //RESULT list doesn't contain not listed elements after inorder insertion
  TEST_P(InsertionTestInt16,DoesntContainNotInserted)
  {
    auto& insert = GetParam();
    auto expect = insert;

    populate_test_obj(insert.begin(),insert.end());
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
  
  using value_t = InsertionTestInt16::value_t;
  using pair_t = std::pair<std::vector<value_t>,std::vector<value_t>>;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();
  //TEST DATASET
  //DATA insert = Range(v_min,v_max).
  INSTANTIATE_TEST_CASE_P(FullSet, InsertionTestInt16,
			  ValuesIn({
				   toInorderVector( Range(v_min, v_max) ),
				   toInorderVector( Range(v_max, v_min, -1) ),
				   toRandomizedVector( Range(v_min, v_max) ),
			    }));
  constexpr value_t v_min_1 = numeric_limits<value_t>::min()+(value_t)1;
  constexpr value_t v_max_1 = numeric_limits<value_t>::max()-(value_t)1;
  //TEST DATASET
  //DATA insert = Range(v_min+1,v_max-1).
  INSTANTIATE_TEST_CASE_P(GapsSet, InsertionTestInt16,
  			  ValuesIn({
				    toInorderVector( Range(v_min_1, v_max_1, 2) ),
				    toInorderVector( Range(v_max_1, v_min_1, -2) ),
				    toRandomizedVector( Range(v_min_1, v_max_1, 2) )
  			    }));
}

