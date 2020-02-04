////////////////////////////////////////////////////////////////////
// Unit Test		      					  //
// Element: bubble_sort_lastswap				  //
// Scope: large data sets - sorted, revsorted, random-shuffeled	  //
////////////////////////////////////////////////////////////////////
#include "tuple.h"
#include "bubble_sort.h"
#include "gtest/gtest.h"
#include <vector>
#include <limits>

#ifndef UTEST_FNAME
#define UTEST_FNAME (void)
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

using std::vector;
using std::endl;
using std::numeric_limits;

using namespace testing;

class LargeArray : public Test
{
  using testT = uint16_t;
  static vector<testT> input;
protected:
  static void SetUpTestCase()
  {
    ASSERT_NO_THROW(input.reserve(numeric_limits<testT>::max()))<<"Not enough memory";
    for(testT i=0; i<numeric_limits<testT>::max();++i)
      input.push_back(i);
  }
  void SetUp()
  {
    ASSERT_NO_THROW(data.reserve(input.size()))<<"Not enough memory";
    copy(begin(input),end(input),back_inserter(data));
  }
  const vector<testT>& sorted = input;
  vector<testT> data;
};
vector<LargeArray::testT> LargeArray::input;

TEST_F(LargeArray, sorted_result_sorted)
{
  UTEST_FNAME(data);
  ASSERT_EQ(data,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}

TEST_F(LargeArray, revsorted_result_sorted)
{
  using T = decltype(data)::value_type;

  sort(begin(data),end(data),[](T a,T b){ return a > b; });
  UTEST_FNAME(data);
  ASSERT_EQ(data,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}

TEST_F(LargeArray, shuffled_result_sorted)
{
  random_shuffle(begin(data),end(data));
  UTEST_FNAME(data);
  ASSERT_EQ(data,sorted)<<"function: "<<STR(UTEST_FNAME)<<endl;
}
