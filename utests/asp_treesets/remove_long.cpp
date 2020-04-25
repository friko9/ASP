//////////////////////////////////////////////
// Unit Test				    //
// Element: treesets			    //
// Scope: insert/remove/contains large sets //
//////////////////////////////////////////////

#include "treeset_array.h"
#include "treeset_array_balancing.h"
#include "treeset_dynamic.h"
#include "treeset_dynamic_balancing.h"
#include "treeset_stl.h"

#include "utest_treeset.h"
#include "utest.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <vector>
#include <ostream>
#include <iterator>

using namespace std;
using namespace testing;

template <typename T>
class PopulateRemoveTest
  : public TestWithParam <tuple <tuple<const TreesetObjectT*,
				       typename T::value_type,
				       typename T::value_type>,
				 tuple<T,T,T>>>
{
public:
  using value_t = typename T::value_type;
public:
  void SetUp() override {
    test_obj = get<0>(get<0>(this->GetParam()))->clone();
    range_min = get<1>(get<0>(this->GetParam()));
    range_max = get<2>(get<0>(this->GetParam()));
  }
  void TearDown() override {
    delete test_obj;
  }
  void populate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj->insert(x);});
  }
  void depopulate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj->remove(x);});
  }
public:
  TreesetObjectT* test_obj;
  value_t range_min;
  value_t range_max;
};

using PopulateRemoveTestInt16 = PopulateRemoveTest<Pretty<int16_t,vector>>;

namespace EmptyRemovalTest_ {
  //TEST SUITE
  //SUBJECT empty treeset
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT treeset contains treeseted elements after insertion
  TEST_P(PopulateRemoveTestInt16,ContainsAllTest)
  {
    auto& insert = get<0>(get<1>(GetParam()));
    auto& remove = get<1>(get<1>(GetParam()));
    auto& expect = get<2>(get<1>(GetParam()));

    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );

    for( auto test_val : expect )
      ASSERT_TRUE(test_obj->contains(test_val))<<"Populated set doesn't contain: "<<test_val<<endl;
  }

  //TEST SUITE
  //SUBJECT empty treeset
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT treeset doesn't contain not treeseted elements after insertion
  TEST_P(PopulateRemoveTestInt16,DoesntContainOtherTest)
  {
    auto& insert = get<0>(get<1>(GetParam()));
    auto& remove = get<1>(get<1>(GetParam()));
    auto expect = get<2>(get<1>(GetParam()));

    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );

    sort(expect.begin(),expect.end());

    auto expect_begin = expect.begin();
    for( auto i : make_InclusiveRange(range_min, range_max) )
      {
	auto it = find(expect_begin, expect.end(), i);
	if( it != expect.end() )
	  expect_begin = it;
	else
	  ASSERT_FALSE(test_obj->contains(i))<<"Populated set contains: "<<i<<endl;
      }
  }

  using value_t = PopulateRemoveTestInt16::value_t;
  using pretty_t = Pretty<value_t,vector>;
  using tuple_t = tuple<pretty_t,pretty_t,pretty_t>;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();
  constexpr value_t v_min_1 = numeric_limits<value_t>::min() + value_t{1};
  constexpr value_t v_max_1 = numeric_limits<value_t>::max() - value_t{1};

  auto test_objects = Values( make_tuple( NEW_TEST_OBJ(treeset_stl<int16_t>), v_min, v_max ),
			      make_tuple( NEW_TEST_OBJ(treeset_array_balancing<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic<int16_t>), v_min, v_max),
			      make_tuple( NEW_TEST_OBJ(treeset_dynamic_balancing<int16_t>), v_min, v_max) );

  //TEST DATASET
  //DATA insert = Inorder full set
  //DATA remove = [inorder | revorder | shuffled] [full | half with gaps]
  //DATA expect = [empty | half with gaps]
  INSTANTIATE_TEST_CASE_P(FullInorder, PopulateRemoveTestInt16,
			  Combine( test_objects,
				   Values(
					  tuple_t{make_Pretty( make_InclusiveRange(v_min, v_max) ),
						  make_Pretty( make_InclusiveRange(v_min, v_max) ),
						  {}},
					  tuple_t{make_Pretty( make_InclusiveRange(v_min, v_max) ),
						    make_Pretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) },
					  tuple_t{make_Pretty( make_InclusiveRange(v_min, v_max) ),
						    make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    {} },
					  tuple_t{make_Pretty( make_InclusiveRange(v_min, v_max) ),
						    make_ReversePretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) },
					  tuple_t{make_Pretty( make_InclusiveRange(v_min, v_max) ),
						    make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    {}},
					  tuple_t{make_Pretty( make_InclusiveRange(v_min, v_max) ),
						    make_ShuffledPretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) }
					  )));
  //TEST DATASET
  //DATA insert = Reverse-order full set
  //DATA remove = [inorder | revorder | shuffled] [full | half with gaps]
  //DATA expect = [empty | half with gaps]
  INSTANTIATE_TEST_CASE_P(FullReverseOrder, PopulateRemoveTestInt16,
			  Combine( test_objects,
				   Values(
					  tuple_t{make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						  make_Pretty( make_InclusiveRange(v_min, v_max) ),
						  {}},
					  tuple_t{make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    make_Pretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) },
					  tuple_t{make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    {} },
					  tuple_t{make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    make_ReversePretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) },
					  tuple_t{make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    {}},
					  tuple_t{make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    make_ShuffledPretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) }
					  )));
  //TEST DATASET
  //DATA insert = Shuffled full set
  //DATA remove = [inorder | revorder | shuffled] [full | half with gaps]
  //DATA expect = [empty | half with gaps]
  INSTANTIATE_TEST_CASE_P(FullShuffledOrder, PopulateRemoveTestInt16,
			  Combine( test_objects,
				   Values(
					  tuple_t{make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						  make_Pretty( make_InclusiveRange(v_min, v_max) ),
						  {}},
					  tuple_t{make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    make_Pretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) },
					  tuple_t{make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    make_ReversePretty( make_InclusiveRange(v_min, v_max) ),
						    {} },
					  tuple_t{make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    make_ReversePretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) },
					  tuple_t{make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    {}},
					  tuple_t{make_ShuffledPretty( make_InclusiveRange(v_min, v_max) ),
						    make_ShuffledPretty( make_InclusiveRange(v_min_1, v_max, value_t{2})),
						    make_Pretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) }
					  )));
}
