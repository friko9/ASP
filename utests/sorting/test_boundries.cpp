///////////////////////////////////////////////
// Unit Test				     //
// Element: sorting function		     //
// Scope: value and lower set-size boundries //
///////////////////////////////////////////////
#include "test_deps.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <limits>
#include <vector>

#ifndef UTEST_FNAME
#define UTEST_FNAME (void)
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

using std::vector;
using std::numeric_limits;
using std::endl;
using namespace testing;

template<typename T>
vector<T> empty_set = {};
template<typename T>
vector<T> array1_zero = {0};
template<typename T>
vector<T> array1_min = {numeric_limits<T>::min()};
template<typename T>
vector<T> array1_max = {numeric_limits<T>::max()};
template<typename T>
vector<T> array2_equal_zero = {0,0};
template<typename T>
vector<T> array2_equal_min = {numeric_limits<T>::min(),numeric_limits<T>::min()};
template<typename T>
vector<T> array2_equal_max = {numeric_limits<T>::max(),numeric_limits<T>::max()};
template<typename T>
vector<T> array3_equal_zero = {0,0,0};
template<typename T>
vector<T> array3_equal_min = {numeric_limits<T>::min(),numeric_limits<T>::min(),numeric_limits<T>::min()};
template<typename T>
vector<T> array3_equal_max = {numeric_limits<T>::max(),numeric_limits<T>::max(),numeric_limits<T>::max()};

class int_array : public TestWithParam<vector<int>>{};
class float_array : public TestWithParam<vector<float>>{};

TEST(empty_int_array, result_sorted)
{
  std::vector<int> s = empty_set<int>;
  UTEST_FNAME(s);
  ASSERT_EQ(s, empty_set<int>)<<"function: "<<STR(UTEST_FNAME)<<endl;
}
TEST(float_empty_array, result_sorted)
{
  std::vector<float> s = empty_set<float>;
  UTEST_FNAME(s);
  ASSERT_EQ(s, empty_set<float>)<<"function: "<<STR(UTEST_FNAME)<<endl;
}
TEST_P(int_array, result_sorted)
{
  vector<int> s = GetParam();
  UTEST_FNAME(s);
  ASSERT_EQ(s, GetParam())<<"function: "<<STR(UTEST_FNAME)<<endl;
}
TEST_P(float_array, result_sorted)
{
  auto s = GetParam();
  UTEST_FNAME(s);
  ASSERT_EQ(s, GetParam())<<"function: "<<STR(UTEST_FNAME)<<endl;
}

INSTANTIATE_TEST_CASE_P(array1, int_array, ValuesIn({ array1_zero<int>,
						      array1_min<int>,
						      array1_max<int>}));
  
INSTANTIATE_TEST_CASE_P(array1, float_array, ValuesIn({array1_zero<float>,
						       array1_min<float>,
						       array1_max<float>}));

INSTANTIATE_TEST_CASE_P(array2, int_array, ValuesIn({array2_equal_zero<int>,
						     array2_equal_min<int>,
						     array2_equal_max<int>}));

INSTANTIATE_TEST_CASE_P(array2, float_array, ValuesIn({array2_equal_zero<float>,
						       array2_equal_min<float>,
						       array2_equal_max<float>}));

INSTANTIATE_TEST_CASE_P(array3, int_array, ValuesIn({array3_equal_zero<int>,
						     array3_equal_min<int>,
						     array3_equal_max<int>}));

INSTANTIATE_TEST_CASE_P(array3, float_array, ValuesIn({array3_equal_zero<float>,
						       array3_equal_min<float>,
						       array3_equal_max<float>}));
