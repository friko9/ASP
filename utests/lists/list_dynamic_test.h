#ifndef LIST_DYNAMIC_TEST_H
#define LIST_DYNAMIC_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_lists/list_dynamic.h"

#include <functional>
#include <vector>
#include <list>

template<typename T>
struct TestPlug<list_dynamic<T>>
{
    node<T>& getHead(list_dynamic<T>& arg) { return arg.head; }
};

namespace test_list_dynamic
{
    test_set& access_test_set();
    
    struct list_dynamic_test_case : test_case
    {
	using elem_t = int8_t;
	std::vector<elem_t> data;
	std::list<elem_t> testlist;
	TestPlug<list_dynamic<elem_t>> test_plug;
	list_dynamic<elem_t> container;
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
#endif /*LIST_DYNAMIC_TEST_H*/
