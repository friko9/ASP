///////////////////////
// Unit Test	     //
// Element: hashsets //
// Scope: empty set  //
///////////////////////

#include "hashset_array.h"
#include "hashset_bucket.h"
#include "hashset_stl.h"

#include "utest_hashset.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <limits>

using namespace std;
using namespace testing;

class EmptyTestInt8 : public TestWithParam<tuple<const HashsetObjectT*,int8_t,int8_t>>
{
public:
  using value_t = int8_t;
public:
  void SetUp() override {
    test_obj = get<0>(this->GetParam())->clone();
    range_min = get<1>(this->GetParam());
    range_max = get<2>(this->GetParam());
      }
  void TearDown() override {
    delete test_obj;
  }
public:
  HashsetObjectT* test_obj;
  int8_t range_min;
  int8_t range_max;
};

namespace EmptyHashsetTest {
  //TEST SUITE
  //SUBJECT empty <hashset>
  //INPUT  { hashset, range_min , range_max }
  //RESULT <hashset> doesn't contain any element in inclusive_range [min,max]
  TEST_P(EmptyTestInt8,ContainsReturnFalseForEntireRange)
  {
    for( auto test_value : make_InclusiveRange(range_min, range_max) )
      ASSERT_FALSE(test_obj->contains(test_value));
  }

  auto v_min = numeric_limits<int8_t>::min();
  auto v_max = numeric_limits<int8_t>::max();

  template<typename T>
  using hashset_array = hashset_array<T,HashF_echo<T>,RehashF_linear<T>>;
  template<typename T>
  using hashset_bucket = hashset_bucket<T,HashF_echo<T>>;

  auto test_objects = Values( make_tuple( NEW_TEST_OBJ(hashset_stl<int8_t>), v_min, v_max ),
			      make_tuple( NEW_TEST_OBJ(hashset_array<int8_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(hashset_bucket<int8_t>), v_min, v_max));
  
  //TEST DATASET
  //DATA insert = Inorder full set
  //DATA remove = [inorder | revorder | shuffled] [full | half with gaps]
  //DATA expect = [empty | half with gaps]
  INSTANTIATE_TEST_CASE_P(Hashsets, EmptyTestInt8, test_objects );
}
