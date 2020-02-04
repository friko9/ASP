/////////////////////////////////////////////////////////////
// Unit Test						   //
// Element: sorting function				   //
// Scope: small data sets - different combination of input //
/////////////////////////////////////////////////////////////
#include "test_deps.h"

#include "tuple.h"
#include "gtest/gtest.h"
#include <vector>
#include <algorithm>

#ifndef UTEST_FNAME
#define UTEST_FNAME (void)
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

using std::ostream;
using std::tuple;
using std::vector;
using std::endl;

using namespace testing;

template<typename T>
using array4 = tuple<T,T,T,T>;

class int_array4 : public TestWithParam<array4<int>>{};
class float_array4 : public TestWithParam<array4<float>>{};

TEST_P(int_array4, result_sorted)
{
  vector<int> s = to_vector(GetParam());
  vector<int> sorted = s;
  stable_sort(begin(sorted),end(sorted));
  UTEST_FNAME(s);
  ASSERT_EQ(s,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}
TEST_P(float_array4, result_sorted)
{
  vector<float> s = to_vector(GetParam());
  vector<float> sorted = s;
  stable_sort(begin(sorted),end(sorted));
  UTEST_FNAME(s);
  ASSERT_EQ(s,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}

INSTANTIATE_TEST_CASE_P(array4_sorted_combination, int_array4,
			Combine( Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4),
				 Values(1, 2, 3, 4)
				 ));

