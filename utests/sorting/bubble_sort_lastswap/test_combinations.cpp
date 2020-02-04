////////////////////////////////////////////////////////////////////
// Unit Test		      					  //
// Element: bubble_sort_lastswap				  //
// Scope: small data sets - different combination of input	  //
////////////////////////////////////////////////////////////////////
#include "tuple.h"
#include "bubble_sort.h"
#include "gtest/gtest.h"
#include <vector>
#include <algorithm>

using std::ostream;
using std::tuple;
using std::vector;
using std::endl;

using namespace testing;

template<typename T>
using array5 = tuple<T,T,T,T,T>;

class int_array5 : public TestWithParam<array5<int>>
{};

class float_array5 : public TestWithParam<array5<float>>
{};

TEST_P(int_array5, result_sorted)
{
  auto arg = GetParam();
  vector<int> s = { get<0>(arg), get<1>(arg), get<2>(arg), get<3>(arg), get<4>(arg) };
  vector<int> sorted = s;
  stable_sort(begin(sorted),end(sorted));
  bubble_sort_lastswap(s);
  EXPECT_EQ(s,sorted)<<"In: "<<arg<<"\n result: "<<s<<endl;
}
TEST_P(float_array5, result_sorted)
{
  auto arg = GetParam();
  vector<float> s = { get<0>(arg), get<1>(arg), get<2>(arg), get<3>(arg), get<4>(arg) };
  vector<float> sorted = s;
  stable_sort(begin(sorted),end(sorted));
  bubble_sort_lastswap(s);
  EXPECT_EQ(s,sorted)<<"In: "<<arg<<"\n result: "<<s<<endl;
}

INSTANTIATE_TEST_CASE_P(array5_sorted_combination, int_array5,
			Combine( Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4)
				 ));

