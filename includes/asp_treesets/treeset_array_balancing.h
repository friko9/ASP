#ifndef TREESET_ARRAY_BALANCING_H
#define TREESET_ARRAY_BALANCING_H

#include "includes/utils/utils.h"

#include <cmath>
#include <cassert>

template <typename T>
class treeset_array_balancing
{
    friend TestPlug<treeset_array_balancing<T>>;
    using height_t = uint8_t;
    using index_t = typename std::vector<size_t>::size_type;
    using vindex_t = typename std::vector<T>::size_type;
    enum class side_t { left, right };
public:
    using elem_t = T;
public:
    treeset_array_balancing(): indexes(16,index_t(null)), heights(16,height_t(0))
	{}
    void insert(T x)
	{
	    size_t node = find(x);
	    if(node >= size())
		resize( 4*size() );
	    if( !node_exist(node) )
		insert_value( node, x );
	}
    bool contains(T x)
	{ return node_exist( find(x) ); }
    void remove(T x)
	{
	    index_t node = find(x);
	    if( node_exist(node) )
	    {
		height_t hl = node_height(left(node));
		height_t hr = node_height(right(node));
		side_t side = (hl < hr)? side_t::right : side_t::left;
		remove_value( indexes[node] );
		node = remove_node(node, side);
		rebalance(node);
	    }
	}
private:
    static side_t flip( side_t side)
	{ return (side == side_t::left)? side_t::right : side_t::left; }
    static index_t branch(index_t node, side_t side)
	{ return 2*node + (side == side_t::right); }
    static index_t left(index_t node)
	{ return 2*node; }
    static index_t right(index_t node)
	{ return 2*node + 1; }
    static index_t up(index_t node)
	{ return node/2; }
    index_t size()
	{ return indexes.size(); }
    T& node_value( index_t node )
	{ return values[indexes[node]].first; }
    height_t node_height( index_t node )
	{ return node_exist(node)? heights[node] : 0; }
    bool value_inrange(vindex_t val_i)
	{ return val_i < values.size(); }
    bool node_inrange(index_t node)
	{ return 0 < node && node < size(); }
    bool node_exist( index_t node )
	{ return node_inrange(node) && indexes[node] != null; }
    size_t find(T value)
	{
	    index_t node = root;
	    assert( node_inrange(node) );
	    while( node_exist(node) && node_value(node) != value )
		node = branch(node, (node_value(node) < value)? side_t::right : side_t::left);
	    return node;
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
	    assert( node_exist(node) );
	    while( node_exist(node) )
		node = branch(node,side);
	    return up(node);
	}
    void remove_value(vindex_t val_i)
	{
	    assert( value_inrange(val_i) );
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
    void move_nodes_up(index_t src)
    	{ // :/ O(N^2)
	    assert( node_inrange(src) );
	    assert( src > 1 );
    	    using dist_t = decltype( src -src );
	    index_t dst = up(src);
    	    dist_t lsize = 1;
    	    for(;src < size(); lsize *=2,dst *=2, src *=2)
    	    {
    		std::copy(indexes.begin() +src, indexes.begin() +src +lsize, indexes.begin() +dst);
    		std::copy(heights.begin() +src, heights.begin() +src +lsize, heights.begin() +dst);
    		for(index_t node = dst; node < dst + lsize; ++node )
    		    update_value_to_node_link(node);
    	    }
    	    std::fill(indexes.begin() +dst, indexes.begin() +dst +lsize, index_t(null));
    	    std::fill(heights.begin() +dst, heights.begin() +dst +lsize, height_t(0));
    	}
    void move_nodes_down(index_t node,side_t side)
    	{ // :/ O(N^2)
	    assert( node_inrange(node) );
	    using dist_t = decltype( node -node );
    	    auto h = floor_log2(size()) -floor_log2(node) -1;
    	    if( h == 0 ) return;
	    dist_t lsize = 1 << (h -1);
    	    index_t dst = (node << h);
	    index_t src = up(dst);
    	    dst += (side == side_t::right)? lsize : 0;
    	    for(; lsize > 0; lsize /=2, dst /=2, src /=2)
    	    {
    		std::copy(heights.begin() +src, heights.begin() +src +lsize, heights.begin() +dst);
    		std::copy(indexes.begin() +src, indexes.begin() +src +lsize, indexes.begin() +dst);
    		for(index_t n = dst; n < dst +lsize; ++n )
    		    update_value_to_node_link(n);
    	    }
    	    indexes[node] = null;
    	    heights[node] = 0;
    	}
    void move_nodes_side(index_t src,index_t dst)
    	{ // :/ O(N^2)
	    assert( node_inrange(src) );
	    assert( node_inrange(dst) );
	    using dist_t = decltype( dst -src );
    	    dist_t lsize = 1;
    	    if(dst == src) return;
    	    for(; src<size() && dst < size(); lsize *=2, src *=2, dst *=2)
    	    {
    		std::copy(heights.begin() +src, heights.begin() +src +lsize, heights.begin() +dst);
    		std::fill(heights.begin() +src, heights.begin() +src +lsize, height_t(0));
    		std::copy(indexes.begin() +src, indexes.begin() +src +lsize, indexes.begin() +dst);
    		std::fill(indexes.begin() +src, indexes.begin() +src +lsize, index_t(null));
    		for(index_t node = dst; node < dst+lsize; ++node )
    		    update_value_to_node_link(node);
    	    }
    	    for(;dst < size(); lsize *=2, dst *=2)
    	    {
    		std::fill(indexes.begin()+dst, indexes.begin()+dst+lsize, index_t(null));
    		std::fill(heights.begin()+dst, heights.begin()+dst+lsize, height_t(0));
    	    }
    	}
    void erase_node(index_t node)
	{
	    assert(node_inrange(node));
	    indexes[node] = null;
	    heights[node] = 0;
	}
    void move_node(index_t src,index_t dst)
	{
	    assert( node_inrange(src) );
	    assert( node_inrange(dst) );
	    indexes[dst] = indexes[src];
	    heights[dst] = heights[src];
	    update_value_to_node_link(dst);
	    erase_node(src);
	}
    size_t remove_node(index_t node, side_t side = side_t::left)
	{
	    assert( node_inrange(node) );
	    index_t node_left = left(node);
	    index_t node_right = right(node);

	    if( !node_exist(node_left) && !node_exist(node_right) )
		erase_node(node);
	    else if( !node_exist(node_right) )
		move_nodes_up(node_left);
	    else if( !node_exist(node_left) )
		move_nodes_up(node_right);
	    else
	    {
		index_t newtop = traverse_last( branch(node,side), flip(side) );
		move_node(newtop, node);
		return remove_node(newtop);
	    }
	    return node;
	}
    void rebalance_case_1(index_t node, side_t side)
	{
	    index_t c = node;
	    index_t l = branch(c, side);
	    index_t r = branch(c, flip(side));
	    index_t lr = branch(l, flip(side));
	    index_t rl = branch(r, side);
	    index_t ll = branch(l, side);
	    assert( node_exist(c) );
	    assert( node_exist(l) );
	    move_nodes_down(r, flip(side));
	    move_nodes_side(lr, rl );
	    move_node(c, r);
	    move_node(l, c);
	    move_nodes_up(ll);
	    update_node_height(r);
	    update_node_height(c);
	}
    void rebalance_case_2(index_t node, side_t side)
	{
	    index_t c = node;
	    index_t l = branch(c, side);
	    index_t r = branch(c, flip(side));
	    index_t rl = branch(r, side);
	    index_t lr = branch(l, flip(side));
	    //	    index_t rll = branch(rl, side);
	    index_t lrl = branch(lr, side);
	    index_t lrr = branch(lr, flip(side));
	    assert( node_exist(c) );
	    assert( node_exist(l) );
	    assert( node_exist(lr) );
	    move_nodes_down(r, flip(side));
	    if ( node_inrange(lrr) )
		move_nodes_side(lrr, rl);
	    move_node(c, r);
	    move_node(lr, c);
	    if ( node_inrange(lrl) )
		move_nodes_up(lrl);
	    update_node_height(l);
	    update_node_height(r);
	    update_node_height(c);	    
	}
    void rebalance(size_t node)
    	{
    	    for(; node != 0; node = up(node) )
    	    {
    		if( !node_exist(node) ) continue;
		update_node_height(node);
    		height_t hl = node_height(left(node));
    		height_t hr = node_height(right(node));
		if( hr+1 < hl || hl+1 < hr )
		{
		    side_t side = (hl < hr)? side_t::right : side_t::left;
		    index_t child = branch(node,side);
		    hl = node_height(branch(child, side));
		    hr = node_height(branch(child, flip(side)));
		    if(hr < hl)
			rebalance_case_1(node, side);
		    else
			rebalance_case_2(node, side);
		}
    	    }
    	}
    void resize( index_t new_size )
	{
	    assert( size() < new_size );
	    indexes.resize( new_size, index_t(null) );
	    heights.resize( new_size, height_t(0) );
	}
    void insert_value( index_t node, T value)
	{
	    assert( node_inrange(node) );
	    indexes[node] = values.size();
	    heights[node] = 1;
	    values.push_back(std::make_pair(value,node));
	    if( node_inrange(up(node)) )
		rebalance(up(node));
	}
private:
    static constexpr index_t null = std::numeric_limits<size_t>::max();
    static constexpr index_t root = 1;
    std::vector<std::pair<T,size_t>> values;
    std::vector<size_t> indexes;
    std::vector<height_t> heights;
};

#endif /*TREESET_ARRAY_BALANCING_H*/
