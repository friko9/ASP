#ifndef LIST_STLFORWARD_TEST_H
#define LIST_STLFORWARD_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_lists/list_stlforward.h"

#include <functional>
#include <vector>
#include <list>

template<typename T>
struct TestPlug<list_stlforward<T>>
{
    using list_t = list_stlforward<T>;
    using It = typename list_t::It;
    std::forward_list<T>& getL(list_stlforward<T>& arg) { return arg.l; }
    It find(list_t& arg, T x) { return arg.find(x); }
};

namespace test_list_stlforward
{
    test_set& access_test_set();
    
    struct list_stlforward_test_case
	: public test_case
    {
	using elem_t = int8_t;
	using TestPlug_t = TestPlug<list_stlforward<elem_t>>;
	using list_t = typename TestPlug_t::list_t;
	using It = typename TestPlug_t::It;
    public:
	std::vector<elem_t> data;
	std::list<elem_t> testlist;
	TestPlug_t test_plug;
	list_t container;
    public:
	virtual void setup_data(){}
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
#endif /*LIST_STLFORWARD_TEST_H*/
