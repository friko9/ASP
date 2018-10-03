#ifndef HASHSET_STL_TEST_H
#define HASHSET_STL_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_hashmaps/hashset_stl.h"

#include <functional>
#include <unordered_set>
#include <vector>

template<typename T>
struct TestPlug<hashset_stl<T>>
{
    using It = typename hashset_stl<T>::It;
    std::unordered_set<T>& getS(hashset_stl<T>& arg) { return arg.s; }
};

namespace test_hashset_stl
{
    test_set& access_test_set();

    struct hashset_stl_test_case : test_case
    {
    	using elem_t = int8_t;
	using TestPlug_t = TestPlug<hashset_stl<elem_t>>;
	using It = typename TestPlug_t::It;
	TestPlug_t test_plug;
	std::vector<elem_t> data;
	std::unordered_set<elem_t> testhashset;
	hashset_stl<elem_t> container;
    public:
	template<typename It>
	static void compare_test_range( test_result& result,
	 				It first,
	 				It last,
	 				std::function<bool(It)> test_f )
	    {
		bool inc = first < last;
		do
		    if ( test_f(first) )
			++result;
		while ( first != last && (( inc && (++first,true)) || ( !inc && (--first,true))) );
	    }
    };
}
#endif /*HASHSET_STL_TEST_H*/
