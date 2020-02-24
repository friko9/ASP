//////////////////////////////////////////////////////////////////
// Unit Test						        //
// Element: sorting function				        //
// Scope: large data sets - sorted, revsorted, random-shuffeled //
//////////////////////////////////////////////////////////////////
#include "test_deps.h"

#include "utest_tuple.h"
#include "utest_utils.h"

#include <gtest/gtest.h>
#include <vector>
#include <limits>

using namespace std;
using namespace testing;

class LargeArray : public Test
{
  using value_t = uint16_t;
  static vector<value_t> input;
protected:
  static void SetUpTestCase()
  {
    static_assert(is_unsigned<value_t>(),"ERROR: value_t is signed type");
    ASSERT_NO_THROW(input.reserve(numeric_limits<value_t>::max()))<<"Not enough memory";
    for(value_t i=0; i<numeric_limits<value_t>::max();++i)
      input.push_back(i);
  }
  void SetUp()
  {
    static_assert(is_unsigned<value_t>(),"ERROR: value_t is signed type");
    ASSERT_NO_THROW(data.reserve(input.size()))<<"Not enough memory";
    copy(begin(input),end(input),back_inserter(data));
  }
  const vector<value_t>& sorted = input;
  vector<value_t> data;
};
vector<LargeArray::value_t> LargeArray::input;

//TEST SUITE
//SUBJECT UTEST_FNAME sorting function defined in compile-time
//INPUT  sorted large array
//RESULT sorted input array
TEST_F(LargeArray, sorted_result_sorted)
{
  UTEST_FNAME(data);
  ASSERT_EQ(data,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}

//TEST SUITE
//SUBJECT UTEST_FNAME sorting function defined in compile-time
//INPUT  reverse-sorted large array
//RESULT sorted input array
TEST_F(LargeArray, revsorted_result_sorted)
{
  using T = decltype(data)::value_type;

  sort(begin(data),end(data),[](T a,T b){ return a > b; });
  UTEST_FNAME(data);
  ASSERT_EQ(data,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}

//TEST SUITE
//SUBJECT UTEST_FNAME sorting function defined in compile-time
//INPUT  shuffeled large array
//RESULT sorted input array
TEST_F(LargeArray, shuffled_result_sorted)
{
  random_shuffle(begin(data),end(data));
  UTEST_FNAME(data);
  ASSERT_EQ(data,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}
