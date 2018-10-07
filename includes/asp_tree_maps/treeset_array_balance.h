#ifndef TREESET_ARRAY_BALANCE_H
#define TREESET_ARRAY_BALANCE_H

#include "includes/utils/utils.h"

#include <cmath>
#include <cassert>

namespace std{
    template <typename T> 
    class test_vector : public std::vector<T>
    {
    public:
	using vector<T>::vector;
	T& operator [](size_t i)
	    {
		return this->at(i);
	    }
    };
}

template <typename T>
class treeset_array_balance
{
    friend TestPlug<treeset_array_balance<T>>;
    enum class side_t { left, right };
    using height_t = uint8_t;
    static constexpr size_t null = std::numeric_limits<size_t>::max();
    static constexpr size_t root = 1;
    std::test_vector<std::pair<T,size_t>> values;
    std::test_vector<size_t> indexes;
    std::test_vector<height_t> heights;
    size_t find(T x)
	{
	    size_t i = root;
	    while( i < indexes.size() && indexes[i] != null && x != values[indexes[i]].first )
		i = i*2 + ( values[indexes[i]].first < x );
	    return i;
	}
    void update_node_height(size_t node)
	{
	    int max_h = (node*2+1 < indexes.size())? std::max(heights[node*2],heights[node*2+1]) : 0;
	    heights[node] = 1 + max_h;
	}
    size_t traverse_last(size_t i, side_t side)
	{
	    while( i < indexes.size() && indexes[i] != null )
		i = i*2 + (side == side_t::right);
	    return i/2;
	}
    void remove_value(size_t val_i)
	{
	    assert(val_i < values.size());
	    size_t backtrack_i = values.back().second;
	    std::swap( values[val_i], values.back() );
	    if( backtrack_i != null )
		indexes[backtrack_i] = val_i;
	    values.pop_back();
	}
    void move_nodes_up(size_t index)
	{ // :/ O(N^2)
	    size_t destination = index/2;
	    size_t chunk_size = 1;
	    for(;index < indexes.size(); chunk_size *=2,destination *=2, index *=2)
	    {
		std::copy(indexes.begin()+index,indexes.begin()+index+chunk_size,indexes.begin()+destination);
		std::copy(heights.begin()+index,heights.begin()+index+chunk_size,heights.begin()+destination);
		for(int i=destination,e=destination+chunk_size; i<e; i++)
		    if ( indexes[i] != null )
			values[indexes[i]].second = i;
	    }
	    std::fill(indexes.begin()+destination, indexes.begin()+destination+chunk_size, size_t(null));
	    std::fill(heights.begin()+destination, heights.begin()+destination+chunk_size, 0);
	}
    void move_nodes_down(size_t index,side_t side)
	{ // :/ O(N^2)
	    int h = (int)std::log2(indexes.size()) - (int)std::log2(index) - 1;
	    if( h == 0 ) return;
	    size_t chunk_size = 1 << (h-1);
	    size_t destination = (index << h);
	    size_t source = destination/2;
	    destination += (side == side_t::right)? chunk_size : 0;
	    for(;chunk_size > 0; chunk_size /=2,destination /=2, source /=2)
	    {
		std::copy(heights.begin()+source,heights.begin()+source+chunk_size,heights.begin()+destination);
		std::copy(indexes.begin()+source,indexes.begin()+source+chunk_size,indexes.begin()+destination);
		for(int i=destination,e=destination+chunk_size; i<e; i++)
		    if ( indexes[i] != null )
			values[indexes[i]].second = i;
	    }
	    indexes[index] = null;
	    heights[index] = 0;
	}
    void move_nodes_side(size_t src,size_t dst)
	{ // :/ O(N^2)
	    size_t chunk_size =1;
	    if(dst == src) return;
	    for(; src<indexes.size() && dst < indexes.size(); chunk_size *=2, src *=2, dst *=2)
	    {
		std::copy(heights.begin()+src,heights.begin()+src+chunk_size,heights.begin()+dst);
		std::fill(heights.begin()+src, heights.begin()+src+chunk_size, 0);
		std::copy(indexes.begin()+src,indexes.begin()+src+chunk_size,indexes.begin()+dst);
		std::fill(indexes.begin()+src, indexes.begin()+src+chunk_size, size_t(null));
		for(int i=dst,e=dst+chunk_size; i<e; ++i)
		    if ( indexes[i] != null )
			values[indexes[i]].second = i;
	    }
	    for(;dst < indexes.size(); chunk_size *=2, dst *=2)
	    {
		std::fill(indexes.begin()+dst, indexes.begin()+dst+chunk_size, size_t(null));
		std::fill(heights.begin()+dst, heights.begin()+dst+chunk_size, 0);
	    }
	}
    size_t remove_node(size_t index, side_t side = side_t::left)
	{
	    size_t index_left = index*2;
	    size_t index_right = index*2 + 1;
	    
	    if( index_left >= indexes.size() )
	    {
		indexes[index] = null;
		heights[index] = 0;
	    }
	    else if ( index_right >= indexes.size() )
	    {
		indexes[index] = indexes[index_left];
		heights[index] = heights[index_left];
		if( indexes[index] != null )
		    values[indexes[index]].second = index;
	    }
	    else if( indexes[index_left] == null)
		move_nodes_up(index_right);
	    else if( indexes[index_right] == null)
		move_nodes_up(index_left);
	    else
	    { // complicated both sides removal
		bool right_node = side == side_t::right;
		size_t trav_start = index*2 + right_node;
		size_t swp = traverse_last( trav_start, (right_node)?side_t::left : side_t::right );
	
		indexes[index] = indexes[swp];
		heights[index] = heights[swp];
		values[indexes[swp]].second = index;
		return remove_node(swp);
	    }
	    return index;
	}
    void move_node(size_t src,size_t dst)
	{
	    indexes[dst] = indexes[src];
	    heights[dst] = heights[src];
	    indexes[src] = null;
	    heights[src] = 0;
	    if( indexes[dst] != null )
		values[indexes[dst]].second = dst;
	}
    void rebalance_case_1(size_t index, side_t side)
	{
	    bool is_side_left = side == side_t::left;
	    side_t ndown_side = (is_side_left)? side_t::right : side_t::left;
	    size_t ndown_index = 2*index + is_side_left;
	    move_nodes_down(ndown_index, ndown_side);
	    move_node(index,ndown_index);
	    size_t newtop_index = 2*index + !is_side_left;
	    move_node(newtop_index,index);
	    size_t nside_src_index = 2*newtop_index + is_side_left;
	    size_t nside_dst_index = (is_side_left)? nside_src_index+1 : nside_src_index-1;
	    move_nodes_side(nside_src_index, nside_dst_index );
	    update_node_height(ndown_index);
	    size_t nup_index = newtop_index*2 + !is_side_left;
	    move_nodes_up(nup_index);
	    update_node_height(index);
	}
    void rebalance_case_2(size_t index, side_t side)
	{
	    bool is_side_left = side == side_t::left;
	    side_t ndown_side = (is_side_left)? side_t::right : side_t::left;
	    size_t ndown_index = 2*index + is_side_left;
	    move_nodes_down(ndown_index, ndown_side);
	    move_node(index,ndown_index);
	    size_t newtop_index = (2*index + !is_side_left)*2 + is_side_left;
	    move_node(newtop_index,index);
	    size_t nside_src_index = 2*newtop_index + is_side_left;
	    size_t nside_dst_index = (is_side_left)? nside_src_index+1 : nside_src_index-1;
	    move_nodes_side(nside_src_index, nside_dst_index );
	    move_nodes_up(nside_dst_index);
	    update_node_height(ndown_index);
	    size_t nup_index = newtop_index*2 + !is_side_left;
	    move_nodes_up(nup_index);
	    update_node_height(newtop_index/2);
	    update_node_height(index);
	}
    void rebalance(size_t index)
    	{
    	    for(; index != 0; index /=2 )
    	    {
		if(indexes[index] != null)
		    update_node_height(index);
		height_t hl = (index*2 < heights.size())? heights[index*2] : 0;
		height_t hr = (index*2+1 < heights.size())? heights[index*2+1] : 0;
    		if( hl > hr+1 )
		{
		    size_t index_left = 2*index;
		    height_t hll = (index_left*2 < heights.size())? heights[index*2] : 0;
		    height_t hlr = (index_left*2+1 < heights.size())? heights[index*2+1] : 0;
    		    if( hll > hlr+1 )
    			rebalance_case_1(index, side_t::left);
    		    else if( hll+1 < hlr )
			rebalance_case_2(index, side_t::left);
    		} else if( hl+1 < hr )
    		{
		    size_t index_right = 2*index+1;
		    height_t hrl = (index_right*2 < heights.size())? heights[index*2] : 0;
		    height_t hrr = (index_right*2+1 < heights.size())? heights[index*2+1] : 0;
    		    if( hrl+1 < hrr )
			rebalance_case_1(index, side_t::right);
    		    else if( hrl > hrr+1 )
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
