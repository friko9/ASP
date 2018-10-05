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
    enum class side_t { left, right };
    static constexpr size_t null = std::numeric_limits<size_t>::max();
    static constexpr size_t root = 1;
    std::vector<std::pair<T,size_t>> values;
    std::vector<size_t> indexes;

    size_t find(T x)
	{
	    size_t i = root;
	    while( i < indexes.size() && indexes[i] != null && x != values[indexes[i]].first )
		i = i*2 + ( values[indexes[i]].first < x );
	    return i;
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
	    values[val_i] = values.back();
	    indexes[backtrack_i] = val_i;
	    values.pop_back();
	}
    void move_nodes_up(size_t index)
	{ // :/ O(N^2)
	    assert(index > 1);
	    size_t destination = index/2;
	    size_t chunk_size = 1;
	    for(;index < indexes.size(); chunk_size *=2,destination *=2, index *=2)
	    {
		std::copy(indexes.begin()+index,indexes.begin()+index+chunk_size,indexes.begin()+destination);
		for(int i=destination,e=destination+chunk_size; i<e; i++)
		    if ( indexes[i] != null )
			values[indexes[i]].second = i;
	    }
	    std::fill(indexes.begin()+destination, indexes.begin()+destination+chunk_size, size_t(null));
	}
    void remove_node(size_t index, side_t side = side_t::left)
	{
	    size_t index_left = index*2;
	    size_t index_right = index*2 + 1;
	    
	    if( index_left >= indexes.size() )
		indexes[index] = null;
	    else if ( index_right >= indexes.size() )
	    {
		indexes[index] = indexes[index_left];
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
		values[indexes[swp]].second = index;
		remove_node(swp);
	    }
	}
 public:
    treeset_array(): indexes(16,size_t(null))
	{}
    void insert(T x)
	{
	    size_t index = find(x);
	    if(index >= indexes.size())
		indexes.resize( 4*indexes.size(),size_t(null) );
	    if( indexes[index] == null )
	    {
		indexes[index] = values.size();
		values.push_back(std::make_pair(x,index));
	    }
	}
    bool contains(T x)
	{
	    size_t i = find(x);
	    return i < indexes.size() && indexes[i] != null;
	}
    void remove(T x)
	{
	    size_t index = find(x);
	    if( index >= indexes.size() || indexes[index] == null ) return;
	    remove_value( indexes[index] );
	    remove_node(index, ((index%3)%2)? side_t::right : side_t::left );
	}
};

#endif /*TREESET_ARRAY_H*/

