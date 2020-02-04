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

using std::vector;
using std::endl;
using std::numeric_limits;

using namespace testing;

class LargeArray : public Test
{
  using testT = uint16_t;
  static vector<testT> input;
protected:
  static void SetUpTestSuite()
  {
    ASSERT_NO_THROW(input.reserve(numeric_limits<testT>::max()))<<"Not enough memory";
    for(uint i=0; i<numeric_limits<testT>::max();++i)
      input.push_back(i);    
  }
  void SetUp()
  {
    ASSERT_NO_THROW(data.reserve(numeric_limits<testT>::max()))<<"Not enough memory";
    copy(begin(input),end(input),back_inserter(data));
  }
  const vector<testT>& sorted = input;
  vector<testT> data;
};
vector<LargeArray::testT> LargeArray::input;

TEST_F(LargeArray, sorted_result_sorted)
{
  bubble_sort_lastswap(data);
  ASSERT_EQ(data,sorted)<<"In: "<<sorted<<"\n result: "<<data<<endl;
}

TEST_F(LargeArray, revsorted_result_sorted)
{
  using T = decltype(data)::value_type;
  sort(begin(data),end(data),[](T a,T b){ return a > b; });
  bubble_sort_lastswap(data);
  ASSERT_EQ(data,sorted)<<"In: "<<sorted<<"\n result: "<<data<<endl;
}

TEST_F(LargeArray, shuffled_result_sorted)
{
  random_shuffle(begin(data),end(data));
  bubble_sort_lastswap(data);
  ASSERT_EQ(data,sorted)<<"In: "<<sorted<<"\n result: "<<data<<endl;
}
