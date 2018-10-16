#ifndef LIST_ARRAY_ENCHANCED_TEST_H
#define LIST_ARRAY_ENCHANCED_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_lists/list_array_enchanced.h"

#include <functional>
#include <list>
#include <utility>

template<typename T>
struct TestPlug<list_array_enchanced<T>>
{
    using list_t = list_array_enchanced<T>;
    using index_t = typename list_t::index_t;
    index_t get_Head(list_t& arg) { return arg.head; }
    index_t get_Tail(list_t& arg) { return arg.tail; }
    std::vector<T>& get_Elems(list_t& arg) { return arg.elems; }
    std::vector<index_t>& get_Nexts(list_t& arg) { return arg.next; }
    std::vector<index_t>& get_Prevs(list_t& arg) { return arg.prev; }
    index_t find(list_t& arg, T x) { return arg.find(x); }
    void move_elem(list_t& arg,index_t src,index_t dst) { arg.move_elem(src,dst); }
    void exclude_elem(list_t& arg,index_t n) { arg.exclude_elem(n); }
};

namespace test_list_array_enchanced
{
    test_set& access_test_set();
    
    struct list_array_enchanced_test_case
	: public test_case
    {
	using elem_t = int8_t;
	using TestPlug_t = TestPlug<list_array_enchanced<elem_t>>;
	using list_t = typename TestPlug_t::list_t;
	using index_t = typename TestPlug_t::index_t;
    public:
	std::vector<elem_t> data;
	std::list<elem_t> testlist;
	TestPlug_t test_plug;
	list_t container;
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
	struct score_t
	{
	    int score,max_score;
	    score_t(bool test):score(test),max_score(1){}
	    score_t(int s,int max):score(s),max_score(max){}
	    test_result to_test_result()
		{ return {max_score,score }; }
	    operator test_result ()
		{ return to_test_result(); }
	};
	struct node_t
	{
	    index_t prev,next;
	    elem_t val;
	};
	struct node_cmp_t
	{
	    bool val_ok, prev_ok, next_ok;
	    operator score_t()
		{ return {val_ok+prev_ok+next_ok, 3}; }
	};
	node_cmp_t test_node(bool enable, index_t index, node_t cmp)
	    {
		bool val_ok = enable && test_plug.get_Elems(container).at(index) == cmp.val;
		bool prev_ok = enable && test_plug.get_Prevs(container).at(index) == cmp.prev;
		bool next_ok = enable && test_plug.get_Nexts(container).at(index) == cmp.next;
		return { val_ok, prev_ok, next_ok };
	    }
    };
    inline list_array_enchanced_test_case::score_t operator +(list_array_enchanced_test_case::score_t left,
							      list_array_enchanced_test_case::score_t right)
    {return {left.score+right.score,left.max_score+right.max_score}; }
}
#endif /*LIST_ARRAY_ENCHANCED_TEST_H*/
