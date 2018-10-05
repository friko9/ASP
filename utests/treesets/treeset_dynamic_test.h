#ifndef TREESET_DYNAMIC_TEST_H
#define TREESET_DYNAMIC_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_tree_maps/treeset_dynamic.h"

#include <functional>
#include <set>
#include <vector>

template<typename T>
struct TestPlug<treeset_dynamic<T>>
{
    using treeset_t = treeset_dynamic<T>;
    using node_t = typename treeset_t::node_t;
    using find_res_t = std::pair<node_t*,node_t*>;;
    
    node_t*& get_root(treeset_t& arg) { return arg.root; }

    find_res_t find(treeset_t& arg, T x,node_t* node,node_t* parent) { return arg.find(x,node,parent); }
    node_t* exclude_single_node(treeset_t& arg, node_t* node, node_t* parent, node_t* node_t::*side )
	{ return arg.exclude_single_node(node,parent,side); }
    node_t* exclude_double_node(treeset_t& arg, node_t* node, node_t* parent, node_t* node_t::*side )
	{ return arg.exclude_double_node(node,parent,side); }
};

namespace test_treeset_dynamic
{
    test_set& access_test_set();

    struct treeset_dynamic_test_case : test_case
    {
    	using elem_t = int8_t;
	using container_t = treeset_dynamic<elem_t>;
	using TestPlug_t = TestPlug<container_t>;
	using node_t = typename TestPlug_t::node_t;
	using find_res_t = typename TestPlug_t::find_res_t;
	TestPlug_t test_plug;
	std::vector<elem_t> data;
	std::set<elem_t> testtreeset;
	container_t container;
    public:
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
	struct node_cmp_t
	{
	    bool val_ok, left_ok, right_ok;
	    operator score_t()
		{ return {val_ok+left_ok+right_ok, 3}; }
	};
	node_cmp_t test_node(bool enable, node_t* node, node_t cmp)
	    {
		bool val_ok = enable && node->val == cmp.val;
		bool left_ok = enable && node->left == cmp.left;
		bool right_ok = enable && node->right == cmp.right;
		return { val_ok, left_ok, right_ok };
	    }
    };
    inline treeset_dynamic_test_case::score_t operator +(treeset_dynamic_test_case::score_t left,
							 treeset_dynamic_test_case::score_t right)
    {return {left.score+right.score,left.max_score+right.max_score}; }
}
#endif /*TREESET_DYNAMIC_TEST_H*/
