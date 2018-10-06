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
    static constexpr size_t null = std::numeric_limits<size_t>::max();
    static constexpr size_t root = 1;
    std::test_vector<std::pair<T,size_t>> values;
    std::test_vector<size_t> indexes;
    std::test_vector<uint8_t> heights;
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
    void remove_node(size_t index, side_t side = side_t::left)
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
		remove_node(swp);
	    }
	}
    size_t reballance_case_1(size_t origin)
	{
	    size_t node = origin/2;
	    bool origin_on_right = origin%2;
	    move_nodes_down(node*2+ !origin_on_right, (origin_on_right)? side_t::left : side_t::right);
	    indexes[node*2+!origin_on_right] = indexes[node];
	    values[indexes[node*2+!origin_on_right]].second = node*2+!origin_on_right;
	    size_t src_origin_branch = origin*2+ !origin_on_right;
	    size_t dst_node_branch = src_origin_branch + ((origin_on_right)? -1 : 1);
	    move_nodes_side(src_origin_branch, dst_node_branch );
	    update_node_height(dst_node_branch/2);
	    indexes[node] = indexes[origin];
	    values[indexes[node]].second = node;
	    move_nodes_up(origin*2 + origin_on_right);
	    update_node_height(node);
	    return node;
	}
    size_t reballance_case_2(size_t origin)
	{
	    size_t node = origin/2;
	    bool origin_on_right = origin%2;
	    move_nodes_down( node*2 + !origin_on_right, (origin_on_right)? side_t::left : side_t::right );
	    indexes[node*2+!origin_on_right] = indexes[node];
	    values[indexes[node*2+!origin_on_right]].second = node*2+!origin_on_right;
	    size_t new_top = origin*2 + !origin_on_right;
	    indexes[node] = indexes[new_top];
	    values[indexes[node]].second = node;	    
	    size_t src_origin_branch = new_top*2+ !origin_on_right;
	    size_t dst_node_branch = src_origin_branch + ((origin_on_right)? -1 : 1);
	    if( src_origin_branch <= indexes.size() )
	    {
		move_nodes_side(src_origin_branch, dst_node_branch );
		move_nodes_up(dst_node_branch );
		move_nodes_up( new_top*2 + origin_on_right );
	    }
	    update_node_height(node*2);
	    update_node_height(node*2+1);
	    update_node_height(node);
	    return node;
	}
    void reballance(size_t origin)
	{
	    for( size_t node = origin/2; node != 0; origin = node, node /=2 )
	    {
		size_t node_left = node*2;
		size_t node_right = node*2+1;
		update_node_height(node);
		if( node_right*2+1 >= indexes.size() ) continue;
		if( heights[node_right] - heights[node_left] > 1 )
		{
		    if( heights[node_right*2] < heights[node_right*2+1] )
			reballance_case_1(node_right);
		    else if( heights[node_right*2+1] < heights[node_right*2] )
			reballance_case_2(node_right);
		} else if( heights[node_left] - heights[node_right]  > 1 )
		{
		    if( heights[node_left*2+1] < heights[node_left*2] )
			reballance_case_1(node_left);
		    else if( heights[node_left*2] < heights[node_left*2+1] )
			reballance_case_2(node_left);
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
	    reballance(index);
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
		remove_value( indexes[index] );
		remove_node(index, ((index%3)%2)? side_t::right : side_t::left );
		reballance(index);
	    }
	}
};

#endif /*TREESET_ARRAY_BALANCE_H*/
