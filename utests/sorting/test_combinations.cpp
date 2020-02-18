/////////////////////////////////////////////////////////////
// Unit Test						   //
// Element: sorting function				   //
// Scope: small data sets - different combination of input //
/////////////////////////////////////////////////////////////
#include "test_deps.h"

#include "utest_tuple.h"
#include "utest_utils.h"

#include <gtest/gtest.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace testing;

template<typename T>
using array4 = tuple<T,T,T,T>;

class int_array4 : public TestWithParam<array4<int>>,
		   public ResultSorted<vector<int>>{};

//TEST SUITE
//SUBJECT UTEST_FNAME sorting function defined in compile-time
//INPUT  4 element array
//RESULT 4 element sorted array
namespace suite_int_array4
{
  TEST_P(int_array4, result_sorted)
  {
    auto test_set = to_vector(GetParam());
    expected_result(test_set);

    UTEST_FNAME(test_set);
    ASSERT_EQ(test_set,expected_result()) <<"function: "<<STR(UTEST_FNAME)<<endl;
  }

  //TEST DATASET
  //DATA All combination of 4 element arrays of values ranging from 1 to 4
  INSTANTIATE_TEST_CASE_P(combinations_1to4, int_array4,
			  Combine( Values(1, 2, 3, 4),
				   Values(1, 2, 3, 4),
				   Values(1, 2, 3, 4),
				   Values(1, 2, 3, 4)
				   ));
}
