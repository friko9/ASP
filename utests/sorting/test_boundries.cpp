///////////////////////////////////////////////
// Unit Test				     //
// Element: sorting function		     //
// Scope: value and lower set-size boundries //
///////////////////////////////////////////////
#include "test_deps.h"

#include "utest_utils.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <limits>
#include <vector>

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

//TEST SUITE
//SUBJECT UTEST_FNAME sorting function defined in compile-time
//INPUT  array<int>
//RESULT sorted input array
namespace suite_int_array {
  TEST_P(int_array, result_sorted)
  {
    vector<int> s = GetParam();
    UTEST_FNAME(s);
    ASSERT_EQ(s, GetParam())<<"function: "<<STR(UTEST_FNAME)<<endl;
  }
  
  //TEST DATASET
  //DATA empty array.  
  INSTANTIATE_TEST_CASE_P(array0, int_array, Values(empty_set<int>));
  
  //TEST DATASET
  //DATA 3 single element arrays with values {0}, {min}, {max}.  
  INSTANTIATE_TEST_CASE_P(array1, int_array, ValuesIn({ array1_zero<int>,
							array1_min<int>,
							array1_max<int>}));
  //TEST DATASET
  //DATA 3 2-element arrays with values {0,0}, {min,min}, {max,max}.
  INSTANTIATE_TEST_CASE_P(array2, int_array, ValuesIn({array2_equal_zero<int>,
						     array2_equal_min<int>,
						     array2_equal_max<int>}));
  //TEST DATASET
  //DATA 3 2-element arrays with values {0,0,0}, {min,min,min}, {max,max,max}.
  INSTANTIATE_TEST_CASE_P(array3, int_array, ValuesIn({array3_equal_zero<int>,
						     array3_equal_min<int>,
						     array3_equal_max<int>}));
}

//TEST SUITE
//SUBJECT UTEST_FNAME sorting function defined in compile-time
//INPUT  array<float>
//RESULT sorted input array
namespace suite_float_array {
  TEST_P(float_array, result_sorted)
  {
    vector<float> s = GetParam();
    UTEST_FNAME(s);
    ASSERT_EQ(s, GetParam())<<"function: "<<STR(UTEST_FNAME)<<endl;
  }
  
  //TEST DATASET
  //DATA empty array.  
  INSTANTIATE_TEST_CASE_P(array0, float_array, Values(empty_set<float>));
  
  //TEST DATASET
  //DATA 3 single element arrays with values {0}, {min}, {max}.  
  INSTANTIATE_TEST_CASE_P(array1, float_array, ValuesIn({ array1_zero<float>,
							array1_min<float>,
							array1_max<float>}));
  //TEST DATASET
  //DATA 3 2-element arrays with values {0,0}, {min,min}, {max,max}.
  INSTANTIATE_TEST_CASE_P(array2, float_array, ValuesIn({array2_equal_zero<float>,
						     array2_equal_min<float>,
						     array2_equal_max<float>}));
  //TEST DATASET
  //DATA 3 2-element arrays with values {0,0,0}, {min,min,min}, {max,max,max}.
  INSTANTIATE_TEST_CASE_P(array3, float_array, ValuesIn({array3_equal_zero<float>,
						     array3_equal_min<float>,
						     array3_equal_max<float>}));
}
