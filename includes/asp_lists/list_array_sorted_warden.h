#ifndef LIST_ARRAY_SORTED_WARDEN_H
#define LIST_ARRAY_SORTED_WARDEN_H

#include "../utils/utils.h"

#include <cassert>
#include <limits>
#include <vector>

template <typename T>
class list_array_sorted_warden
{
    friend TestPlug<list_array_sorted_warden<T>>;
    using index_t = typename std::vector<T>::size_type;
    static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value );
    static constexpr index_t head = 1, tail = 0;
    static constexpr T min = std::numeric_limits<T>::min();
    static constexpr T max = std::numeric_limits<T>::max();
private:
    std::vector<T> elems;
    std::vector<index_t> next,prev;

private:
    index_t size()
	{ return elems.size(); }
    index_t find(T x)
	{
	    index_t node = head;
	    while( elems[node] < x )
		node=next[node];
	    return node;
	}
    void move_elem(index_t src,index_t dst)
	{
	    assert(src < size());
	    assert(dst < size());
	    assert( src != head );
	    assert( src != tail );
	    assert( dst != head );
	    assert( dst != tail );
	    if(src == dst) return;
	    index_t& src_prev_next = next[prev[src]];
	    index_t& src_next_prev = prev[next[src]];
	    src_prev_next = dst;
	    src_next_prev = dst;

	    elems[dst] = std::move(elems[src]);
	    next[dst] = next[src];
	    prev[dst] = prev[src];
	}
    void exclude_elem(index_t node)
	{
	    assert( node < size());
	    assert( node != head );
	    assert( node != tail );
	    index_t& node_prev_next = next[prev[node]];
	    index_t& node_next_prev = prev[next[node]];
	    node_next_prev = prev[node];
	    node_prev_next = next[node];
	}
public:
    list_array_sorted_warden()
	{
	    elems.push_back(T(max));
	    elems.push_back(T(min));
	    prev.push_back(index_t(head));
	    prev.push_back(index_t(tail));
	    next.push_back(index_t(head));
	    next.push_back(index_t(tail));
	}
    void insert(T x)
	{
	    assert( x != max);
	    assert( x != min);
	    index_t node = elems.size();
	    index_t node_next = find(x);
	    index_t node_prev = prev[node_next];
	    next.push_back(node_next);
	    prev.push_back(node_prev);
	    elems.push_back(x);

	    next[node_prev] = node;
	    prev[node_next] = node;
	}
    bool contains(T x)
	{
	    assert( x != max);
	    assert( x != min);
	    index_t n = find(x);
	    return elems[n] == x;
	}
    void remove(T x)
	{
	    assert( x != max);
	    assert( x != min);
	    index_t node = find(x);
	    if( elems[node] == x )
	    {
		index_t last = elems.size()-1;
		exclude_elem(node);
		move_elem(last,node);
		elems.pop_back();
		prev.pop_back();
		next.pop_back();
	    }
	}	    
};

#endif /*LIST_ARRAY_SORTED_WARDEN_H*/
