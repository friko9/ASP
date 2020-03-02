//////////////////////////////////////////////
// Unit Test				    //
// Element: list_stl			    //
// Scope: insert/remove/contains large sets //
//////////////////////////////////////////////

//#include "test_deps.h"

#include "list_stl.h"
#include "utest_utils.h"
#include "utest_tuple.h"
#include "utest_pretty.h"
#include "utest_inclusive_range.h"

#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <vector>
#include <ostream>
#include <iterator>

using namespace std;
using namespace testing;
template<typename T>
struct std::iterator_traits<testing::internal::ParamIterator<T> >
{
  using difference_type = typename testing::internal::ParamIterator<T>::difference_type;
  using value_type = typename testing::internal::ParamIterator<T>::value_type;
  using pointer = void;
  using reference = typename testing::internal::ParamIterator<T>::reference;
  using iterator_category = std::forward_iterator_tag;
};

template <typename T>
class PopulateRemoveTest : public TestWithParam<tuple<T,T,T>>
{
public:
  using value_t = typename T::value_type;
public:
  list_stl<value_t> test_obj;
  void populate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj.insert(x);});
  }
  void depopulate_test_obj(const T& arg)  {
    for_each(arg.begin(), arg.end(), [this](auto x){test_obj.remove(x);});
  }
};

using PopulateRemoveTestInt16 = PopulateRemoveTest<Pretty<int16_t,vector>>;

namespace EmptyRemovalTest_ {
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT list contains listed elements after insertion
  TEST_P(PopulateRemoveTestInt16,ContainsAllTest)
  {
    auto insert = get<0>(GetParam());
    auto remove = get<1>(GetParam());
    auto expect = get<2>(GetParam());

    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );
    
    for( auto test_val : expect )
      ASSERT_TRUE(test_obj.contains(test_val))<<"Populated list_stl doesn't contain: "<<test_val<<endl;
  }
  
  //TEST SUITE
  //SUBJECT empty list_stl
  //INPUT  { insert_set, remove_set , check_set }
  //RESULT list doesn't contain not listed elements after insertion
  TEST_P(PopulateRemoveTestInt16,DoesntContainOtherTest)
  {
    auto insert = get<0>(GetParam());
    auto remove = get<1>(GetParam());
    auto expect = get<2>(GetParam());
    
    EXPECT_NO_THROW( populate_test_obj(insert) );
    EXPECT_NO_THROW( depopulate_test_obj(remove) );
    
    sort(expect.begin(),expect.end());

    auto expect_begin = expect.begin();
    for( auto i = numeric_limits<value_t>::min(); i<numeric_limits<value_t>::max(); ++i)
      {
	auto it = find(expect_begin, expect.end(), i);
	if( it != expect.end() )
	  expect_begin = it;
	else
	  ASSERT_FALSE(test_obj.contains(i))<<"Populated list_stl contains: "<<i<<endl;
      }
  }

  using value_t = PopulateRemoveTestInt16::value_t;
  using pretty_t = Pretty<value_t,vector>;
  using tuple_t = tuple<pretty_t,pretty_t,pretty_t>;
  // using tuple_t = array<pretty_t,3>;
  constexpr value_t v_min = numeric_limits<value_t>::min();
  constexpr value_t v_max = numeric_limits<value_t>::max();  
  constexpr value_t v_min_1 = numeric_limits<value_t>::min()+(value_t)1;
  constexpr value_t v_max_1 = numeric_limits<value_t>::max()-(value_t)1;
  //TEST DATASET
  //DATA insert = empty
  //DATA remove = single elements
  //DATA expect = empty.
  INSTANTIATE_TEST_CASE_P(FullInorder, PopulateRemoveTestInt16,
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
					   make_ShuffledPretty( make_InclusiveRange(v_min, v_max_1, value_t{2})) }
				 ));
  //TEST DATASET
  //DATA insert = empty
  //DATA remove = single elements
  //DATA expect = empty.
  // INSTANTIATE_TEST_CASE_P(FullRevorder, PopulateRemoveTestInt16,
  // 			  Values(
  // 				 tuple_t{ make_ReversePretty( Range(v_min, v_max) ),
  // 				 	  make_Pretty( Range(v_min, v_max) ),
  // 				 	  {}},
  // 				 tuple_t{ make_ReversePretty( Range(v_min, v_max) ),
  // 				 	   make_Pretty( Range(v_min_1, v_max, 2)),
  // 				 	   make_Pretty( Range(v_min, v_max_1, 2)) },
  // 				 tuple_t{ make_ReversePretty( Range(v_min, v_max) ),
  // 				 	   make_ReversePretty( Range(v_min, v_max) ),
  // 				 	   {} },
  // 				 tuple_t{ make_ReversePretty( Range(v_min, v_max) ),
  // 				 	   make_ReversePretty( Range(v_min_1, v_max, 2)),
  // 				 	   make_Pretty( Range(v_min, v_max_1, 2)) },
  // 				 tuple_t{ make_ReversePretty( Range(v_min, v_max) ),
  // 				 	   make_ShuffledPretty( Range(v_min, v_max) ),
  // 				 	   {}},
  // 				 tuple_t{ make_ReversePretty( Range(v_min, v_max) ),
  // 				 	   make_ShuffledPretty( Range(v_min, v_max_1, 2)),
  // 				 	   make_ShuffledPretty( Range(v_min_1, v_max, 2)) }
  // 				 ));
  //TEST DATASET
  //DATA insert = empty
  //DATA remove = single elements
  //DATA expect = empty.
  // INSTANTIATE_TEST_CASE_P(FullRandOrder, PopulateRemoveTestInt16,
  // 			  Values(
  // 				 tuple_t{ make_ShuffledPretty( Range(v_min, v_max) ),
  // 					  make_Pretty( Range(v_min, v_max) ),
  // 					  {} },
  // 				 tuple_t{ make_ShuffledPretty( Range(v_min, v_max) ),
  // 					   make_Pretty( Range(v_min, v_max_1, 2)),
  // 					   make_Pretty( Range(v_min_1, v_max, 2)) },
  // 				 tuple_t{ make_ShuffledPretty( Range(v_min, v_max) ),
  // 					   make_ReversePretty( Range(v_min, v_max, 1) ),
  // 					   {} },
  // 				 tuple_t{ make_ShuffledPretty( Range(v_min, v_max) ),
  // 					   make_ReversePretty( Range(v_min, v_max_1, 2)),
  // 					   make_Pretty( Range(v_min_1, v_max,  2)) },
  // 				 tuple_t{ make_ShuffledPretty( Range(v_min, v_max) ),
  // 					   make_ShuffledPretty( Range(v_min, v_max) ),
  // 					   {}},
  // 				 tuple_t{ make_ShuffledPretty( Range(v_min, v_max) ),
  // 					   make_ShuffledPretty( Range(v_min_1, v_max, 2)),
  // 					   make_ShuffledPretty( Range(v_min, v_max_1, 2)) }
  // 				 ));
}

