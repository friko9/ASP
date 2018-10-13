#ifndef TREESET_ARRAY_H
#define TREESET_ARRAY_H

#include "includes/utils/utils.h"

#include <cassert>
#include <limits>
#include <vector>

template <typename T>
class treeset_array
{
    friend TestPlug<treeset_array<T>>;
    using index_t = typename std::vector<size_t>::size_type;
    using vindex_t = typename std::vector<T>::size_type;
    enum class side_t { left, right };
private:
    static constexpr size_t null = std::numeric_limits<size_t>::max();
    static constexpr size_t root = 1;
    std::vector<std::pair<T,size_t>> values;
    std::vector<size_t> indexes;
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
private:
    index_t size()
	{ return indexes.size(); }
    T& node_value( index_t node )
	{ return values[indexes[node]].first; }
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
    		for(index_t node = dst; node < dst + lsize; ++node )
    		    update_value_to_node_link(node);
    	    }
    	    std::fill(indexes.begin() +dst, indexes.begin() +dst +lsize, index_t(null));
    	}
    void erase_node(index_t node)
	{
	    assert(node_inrange(node));
	    indexes[node] = null;
	}
    void move_node(index_t src,index_t dst)
	{
	    assert( node_inrange(src) );
	    assert( node_inrange(dst) );
	    indexes[dst] = indexes[src];
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
    void resize( index_t new_size )
	{
	    assert( size() < new_size );
	    indexes.resize( new_size, index_t(null) );
	}
    void insert_value( index_t node, T value)
	{
	    assert( node_inrange(node) );
	    indexes[node] = values.size();
	    values.push_back(std::make_pair(value,node));
	}
 public:
    treeset_array(): indexes(16,size_t(null))
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
		side_t side = (node%3 > 1)? side_t::right : side_t::left;
		remove_value( indexes[node] );
		remove_node(node, side);
	    }
	}
};

#endif /*TREESET_ARRAY_H*/

