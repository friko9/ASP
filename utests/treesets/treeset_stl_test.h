#ifndef TREESET_STL_TEST_H
#define TREESET_STL_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_treesets/treeset_stl.h"

#include <functional>
#include <set>
#include <vector>

template<typename T>
struct TestPlug<treeset_stl<T>>
{
    using It = typename treeset_stl<T>::It;
    std::set<T>& getS(treeset_stl<T>& arg) { return arg.s; }
};

namespace test_treeset_stl
{
    test_set& access_test_set();

    struct treeset_stl_test_case : test_case
    {
    	using elem_t = int8_t;
	using TestPlug_t = TestPlug<treeset_stl<elem_t>>;
	using It = typename TestPlug_t::It;
	TestPlug_t test_plug;
	std::vector<elem_t> data;
	std::set<elem_t> testtreeset;
	treeset_stl<elem_t> container;
    public:
	virtual void setup_data(){};
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
#endif /*TREESET_STL_TEST_H*/
