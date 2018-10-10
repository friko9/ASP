#ifndef TREESET_ARRAY_BALANCE_H
#define TREESET_ARRAY_BALANCE_H

#include "includes/utils/utils.h"

#include <cmath>
#include <cassert>

template <typename T>
class treeset_array_balance
{
    friend TestPlug<treeset_array_balance<T>>;
    using height_t = uint8_t;
    using index_t = size_t;
    enum class side_t { left=0, right=1 };
    static constexpr size_t null = std::numeric_limits<size_t>::max();
    static constexpr size_t root = 1;
    std::vector<std::pair<T,size_t>> values;
    std::vector<size_t> indexes;
    std::vector<height_t> heights;
private:
    side_t flip( side_t side)
	{ return (side == side_t::left)? side_t::right : side_t::left; }
    bool node_exist( index_t node )
	{ return node < indexes.size() && indexes[node] != null; }
    T& node_value( index_t node )
	{ return values[indexes[node]].first; }
    height_t node_height( index_t node )
	{ return node_exist(node)? heights[node] : 0; }
    index_t branch(index_t node, side_t side)
	{ return 2*node + (side == side_t::right); }
    index_t left(index_t node)
	{ return 2*node; }
    index_t right(index_t node)
	{ return 2*node + 1; }
    index_t up(index_t node)
	{ return node/2; }
    size_t find(T x)
	{
	    index_t n = root;
	    while( node_exist(n) && node_value(n) != x )
		n = 2*n + (node_value(n) < x);
	    return n;
	}
    void update_node_height(index_t node)
	{
	    assert( node_exist(node) );
	    height_t hl = node_height( left(node) );
	    height_t hr = node_height( right(node) );
	    heights[node] = 1 + std::max(hl,hr);
	}
    size_t traverse_last(index_t node, side_t side)
	{
	    while( node_exist(node) )
		node = branch(node,side);
	    return up(node);
	}
    void remove_value(index_t val_i)
	{
	    assert(val_i < values.size());
	    index_t swp_node = values.back().second;
	    std::swap( values[val_i], values.back() );
	    if( node_exist(swp_node) )
		indexes[swp_node] = val_i;
	    values.pop_back();
	}
    void update_value_to_node_link(index_t node)
	{
	    if ( node_exist(node) )
		values[indexes[node]].second = node;
	}
    void move_nodes_up(index_t index)
    	{ // :/ O(N^2)
    	    using dist_t = decltype( index-index );
	    index_t dst = up(index);
    	    dist_t size = 1;
    	    for(;index < indexes.size(); size *=2,dst *=2, index *=2)
    	    {
    		std::copy(indexes.begin() +index, indexes.begin() +index +size, indexes.begin() +dst);
    		std::copy(heights.begin() +index, heights.begin() +index +size, heights.begin() +dst);
    		for(index_t node = dst; node < dst + size; ++node )
    		    update_value_to_node_link(node);
    	    }
    	    std::fill(indexes.begin() +dst, indexes.begin() +dst +size, index_t(null));
    	    std::fill(heights.begin() +dst, heights.begin() +dst +size, height_t(0));
    	}
    void move_nodes_down(index_t index,side_t side)
    	{ // :/ O(N^2)
	    using dist_t = decltype( index-index );
    	    auto h = floor_log2(indexes.size()) -floor_log2(index) -1;
    	    if( h == 0 ) return;
	    dist_t size = 1 << (h-1);
    	    index_t dst = (index << h);
	    index_t src = up(dst);
    	    dst += (side == side_t::right)? size : 0;
    	    for(; size > 0; size /=2, dst /=2, src /=2)
    	    {
    		std::copy(heights.begin() +src, heights.begin() +src +size, heights.begin() +dst);
    		std::copy(indexes.begin() +src, indexes.begin() +src +size, indexes.begin() +dst);
    		for(index_t node = dst; node < dst +size; ++node )
    		    update_value_to_node_link(node);
    	    }
    	    indexes[index] = null;
    	    heights[index] = 0;
    	}
    void move_nodes_side(index_t src,size_t dst)
    	{ // :/ O(N^2)
	    using dist_t = decltype( dst - src );
    	    dist_t size = 1;
    	    if(dst == src) return;
    	    for(; src<indexes.size() && dst < indexes.size(); size *=2, src *=2, dst *=2)
    	    {
    		std::copy(heights.begin() +src, heights.begin() +src +size, heights.begin() +dst);
    		std::fill(heights.begin() +src, heights.begin() +src +size, height_t(0));
    		std::copy(indexes.begin() +src, indexes.begin() +src +size, indexes.begin() +dst);
    		std::fill(indexes.begin() +src, indexes.begin() +src +size, index_t(null));
    		for(index_t node = dst; node < dst+size; ++node )
    		    update_value_to_node_link(node);
    	    }
    	    for(;dst < indexes.size(); size *=2, dst *=2)
    	    {
    		std::fill(indexes.begin()+dst, indexes.begin()+dst+size, index_t(null));
    		std::fill(heights.begin()+dst, heights.begin()+dst+size, height_t(0));
    	    }
    	}
    size_t remove_node(size_t index, side_t side = side_t::left)
	{
	    size_t index_left = left(index);
	    size_t index_right = right(index);

	    if( !node_exist(index_left) && !node_exist(index_right) )
		erase_node(index);
	    else if( !node_exist(index_right) )
		move_nodes_up(index_left);
	    else if( !node_exist(index_left) )
		move_nodes_up(index_right);
	    else
	    {
		size_t newtop = traverse_last( branch(index,side), flip(side) );
		move_node(newtop, index);
		return remove_node(newtop);
	    }
	    return index;
	}
    void erase_node(size_t node)
	{
	    indexes[node] = null;
	    heights[node] = 0;
	}
    void move_node(size_t src,size_t dst)
	{
	    indexes[dst] = indexes[src];
	    heights[dst] = heights[src];
	    update_value_to_node_link(dst);
	    erase_node(src);
	}
    void rebalance_case_1(size_t index, side_t side)
	{
	    index_t c = index;
	    index_t l = branch(c, side);
	    index_t r = branch(c, flip(side));
	    index_t lr = branch(l, flip(side));
	    index_t rl = branch(r, side);
	    index_t ll = branch(l, side);
	    move_nodes_down(r, flip(side));
	    move_nodes_side(lr, rl );
	    move_node(c, r);
	    move_node(l, c);
	    move_nodes_up(ll);
	    update_node_height(r);
	    update_node_height(c);
	}
    void rebalance_case_2(size_t index, side_t side)
	{
	    index_t c = index;
	    index_t l = branch(c, side);
	    index_t r = branch(c, flip(side));
	    index_t rl = branch(r, side);
	    index_t lr = branch(l, flip(side));
	    index_t rll = branch(rl, side);
	    index_t lrl = branch(lr, side);
	    index_t lrr = branch(lr, flip(side));
	    move_nodes_down(r, flip(side));
	    move_nodes_side(lrr, rll);
	    move_nodes_up(rll);
	    move_node(c, r);
	    move_node(lr, c);
	    move_nodes_up(lrl);
	    update_node_height(l);
	    update_node_height(r);
	    update_node_height(c);	    
	}
    void rebalance(size_t index)
    	{
    	    for(; index != 0; index /=2 )
    	    {
		if(indexes[index] != null)
		    update_node_height(index);
		height_t hl = (index*2 < heights.size())? heights[index*2] : 0;
		height_t hr = (index*2+1 < heights.size())? heights[index*2+1] : 0;
    		if( hr+1 < hl )
		{
		    size_t index_left = 2*index;
		    height_t hll = (index_left*2 < heights.size())? heights[index_left*2] : 0;
		    height_t hlr = (index_left*2+1 < heights.size())? heights[index_left*2+1] : 0;
    		    if( hlr < hll )
    			rebalance_case_1(index, side_t::left);
    		    else if( hll < hlr )
			rebalance_case_2(index, side_t::left);
    		} else if( hl+1 < hr )
    		{
		    size_t index_right = 2*index+1;
		    height_t hrl = (index_right*2 < heights.size())? heights[index_right*2] : 0;
		    height_t hrr = (index_right*2+1 < heights.size())? heights[index_right*2+1] : 0;
    		    if( hrl < hrr )
			rebalance_case_1(index, side_t::right);
    		    else if( hrr < hrl )
			rebalance_case_2(index, side_t::right);
    		}
    	    }
    	}
 public:
    treeset_array_balance(): indexes(16,size_t(null)), heights(16, 0)
	{}
    void insert(T x)
	{
	    size_t index = find(x);
	    if(index >= indexes.size())
	    {
		indexes.resize( 4*indexes.size(), size_t(null) );
		heights.resize( 4*heights.size(), 0 );
	    }
	    if( indexes[index] == null )
	    {
		indexes[index] = values.size();
		heights[index] = 1;
		values.push_back(std::make_pair(x,index));
	    }
	    rebalance(index/2);
	}
    bool contains(T x)
	{
	    size_t i = find(x);
	    return i < indexes.size() && indexes[i] != null;
	}
    void remove(T x)
	{
	    size_t index = find(x);
	    bool found = index < indexes.size() && indexes[index] != null;
	    if( found )
	    {
		height_t hl = (index*2 < heights.size())? heights[index*2] : 0;
		height_t hr = (index*2+1 < heights.size())? heights[index*2+1] : 0;
		remove_value( indexes[index] );
		index = remove_node(index,(hl<hr)? side_t::right : side_t::left );
		rebalance(index);
	    }
	}
};

#endif /*TREESET_ARRAY_BALANCE_H*/
