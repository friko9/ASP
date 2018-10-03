#ifndef TREESET_ARRAY_BALANCING_TEST_H
#define TREESET_ARRAY_BALANCING_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_treesets/treeset_array_balancing.h"

#include <functional>
#include <set>
#include <tuple>
#include <vector>

template<typename T>
struct TestPlug<treeset_array_balancing<T>>
{
    using treeset_t = treeset_array_balancing<T>;
    using node_t = typename std::pair<T,size_t>;
    using side_t = typename treeset_t::side_t;
    using height_t = typename treeset_t::height_t;
    using index_t = typename treeset_t::index_t;
    using vindex_t = typename treeset_t::vindex_t;
    static constexpr size_t null = treeset_t::null;
    static constexpr size_t root = treeset_t::root;

    std::vector<node_t>& get_values(treeset_t& arg) { return arg.values; }
    std::vector<size_t>& get_indexes(treeset_t& arg) { return arg.indexes; }
    std::vector<height_t>& get_heights(treeset_t& arg) { return arg.heights; }

    index_t find(treeset_t& arg, T x) { return arg.find(x); }
    void update_node_height(treeset_t& arg, index_t node){ arg.update_node_height(node); }
    index_t traverse_last(treeset_t& arg, index_t node, side_t side){ return arg.traverse_last(node,side); }
    void remove_value(treeset_t& arg, vindex_t node){ arg.remove_value(node); }
    index_t remove_node(treeset_t& arg, index_t node, side_t side){ return arg.remove_node(node,side); }
    void move_nodes_up(treeset_t& arg, index_t src){ arg.move_nodes_up(src); }
    void move_nodes_down(treeset_t& arg, index_t src,side_t side){ arg.move_nodes_down(src,side); }
    void move_nodes_side(treeset_t& arg, index_t src,index_t dst){ arg.move_nodes_side(src,dst); }
    void rebalance_case_1(treeset_t& arg, index_t node, side_t side){ arg.rebalance_case_1(node,side); }
    void rebalance_case_2(treeset_t& arg, index_t node, side_t side){ arg.rebalance_case_2(node,side); }
    void rebalance(treeset_t& arg, index_t node){ arg.rebalance(node); }
};

namespace test_treeset_array_balancing
{
    test_set& access_test_set();

    struct treeset_array_balancing_test_case : test_case
    {
    	using elem_t = int8_t;
	using container_t = treeset_array_balancing<elem_t>;
	using TestPlug_t = TestPlug<container_t>;
	using node_t = typename TestPlug_t::node_t;
	using side_t = typename TestPlug_t::side_t;
	using index_t = typename TestPlug_t::index_t;
	using vindex_t = typename TestPlug_t::vindex_t;
	using height_t = typename TestPlug_t::height_t;
	using data_t = std::vector<std::tuple<size_t,elem_t,height_t>>;
	size_t null = TestPlug_t::null;
	size_t root = TestPlug_t::root;
	
	TestPlug_t test_plug;
	std::set<elem_t> testtreeset;
	container_t container;
	
	data_t data;
	size_t tree_size;
    public:
	virtual void setup_data(){};
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
	    score_t& operator +=(score_t arg)
	    {
		this->score += arg.score;
		this->max_score += arg.max_score;
		return *this;
	    }
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
	template<typename T>
	score_t compare(const std::vector<T>& v1, const std::vector<T>& v2)
	{
	    score_t score = v1.size() == v2.size();
	    if(v1.size() != v2.size())
		return score;
	    for(auto it1 = v1.begin(),it2 = v2.begin(); it1 != v1.end(); ++it1,++it2)
		score += *it1 == *it2;
	    return score;
	};
	std::tuple<std::vector<node_t>,std::vector<size_t>,std::vector<height_t>>
	make_data(size_t tree_size, data_t data)
	    {
		std::vector<node_t> values;
		std::vector<size_t> indexes(tree_size,null);
		std::vector<height_t> heights(tree_size,0);
		for(int j=0; j<data.size(); ++j)
		{
		    indexes[std::get<0>(data[j])] = j;
		    heights[std::get<0>(data[j])] = std::get<2>(data[j]);
		    values.push_back( {std::get<1>(data[j]),std::get<0>(data[j])} );
		    testtreeset.insert(std::get<1>(data[j]));
		}
		return std::make_tuple(values,indexes,heights);
	    }
    };
    inline treeset_array_balancing_test_case::score_t operator +(treeset_array_balancing_test_case::score_t left,
						       treeset_array_balancing_test_case::score_t right)
    {return {left.score+right.score,left.max_score+right.max_score}; }
}
#endif /*TREESET_ARRAY_BALANCING_TEST_H*/

