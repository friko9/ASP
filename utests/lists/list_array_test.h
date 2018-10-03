#ifndef LIST_ARRAY_TEST_H
#define LIST_ARRAY_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_lists/list_array.h"

#include <functional>
#include <list>
#include <utility>

template<typename T>
struct TestPlug<list_array<T>>
{
    int& get_Head(list_array<T>& arg) { return arg.head; }
    int& get_Tail(list_array<T>& arg) { return arg.tail; }
    std::vector<T>& get_Elems(list_array<T>& arg) { return arg.elems; }
    std::vector<int>& get_Nexts(list_array<T>& arg) { return arg.next; }
    std::vector<int>& get_Prevs(list_array<T>& arg) { return arg.prev; }
    int find(list_array<T>& arg, T x) { return arg.find(x); }
    void move_elem(list_array<T>& arg,int src,int dst) { arg.move_elem(src,dst); }
    void exclude_elem(list_array<T>& arg,int n) { arg.exclude_elem(n); }
};

namespace test_list_array
{
    test_set& access_test_set();
    
    struct list_array_test_case : test_case
    {
    	using elem_t = int8_t;
	static constexpr int null = list_array<elem_t>::null;
	std::vector<elem_t> data;
	std::list<elem_t> testlist;
	TestPlug<list_array<elem_t>> test_plug;
	list_array<elem_t> container;
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
#endif /*LIST_ARRAY_TEST_H*/
