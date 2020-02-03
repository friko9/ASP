////////////////////////////////////////////////
// Unit Test				      //
// Element: bubble_sort_lastswap	      //
// Scope: value and lower set-size boundries  //
////////////////////////////////////////////////

#include "bubble_sort.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

template<typename T>
vector<T> empty_set = {};
template<typename T>
vector<T> size1_zero = {0};
template<typename T>
vector<T> size1_min = {std::numeric_limits<T>::min()};
template<typename T>
vector<T> size1_max = {std::numeric_limits<T>::max()};
template<typename T>
vector<T> size2_equal_zero = {0,0};
template<typename T>
vector<T> size2_equal_min = {std::numeric_limits<T>::min(),std::numeric_limits<T>::min()};
template<typename T>
vector<T> size2_equal_max = {std::numeric_limits<T>::max(),std::numeric_limits<T>::max()};
template<typename T>
vector<T> size3_equal_zero = {0,0,0};
template<typename T>
vector<T> size3_equal_min = {std::numeric_limits<T>::min(),std::numeric_limits<T>::min(),std::numeric_limits<T>::min()};
template<typename T>
vector<T> size3_equal_max = {std::numeric_limits<T>::max(),std::numeric_limits<T>::max(),std::numeric_limits<T>::max()};

TEST(utest_int_empty_set, result_sorted)
{
  std::vector<int> s = empty_set<int>;
  EXPECT_NO_THROW(bubble_sort_lastswap(s));
  EXPECT_EQ(s, empty_set<int>);
}

