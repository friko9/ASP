#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H

#include "includes/utils/utils.h"

#include <cassert>
#include <limits>
#include <vector>
#include <typeinfo>

template <typename T>
class list_array
{
public:
    using elem_t = T;
    using index_t = typename std::vector<T>::size_type;
    static constexpr index_t null =
	(std::is_signed<index_t>::value)? std::numeric_limits<index_t>::min() : std::numeric_limits<index_t>::max();
private:
    friend TestPlug<list_array<T>>;
    static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value );
private:
    std::vector<elem_t> elems;
    std::vector<index_t> next,prev;
    index_t head = null, tail = null;
private:
    index_t size()
	{ return elems.size(); }
    index_t find(elem_t x)
	{
	    index_t node = head;
	    while( node != null && elems[node] != x )
		node = next[node];
	    return node;
	}
    void move_elem(index_t src,index_t dst)
	{
	    assert(src < size());
	    assert(dst < size());
	    if(src == dst) return;
	    index_t& src_prev_next = (prev[src] != null)? next[prev[src]] : head;
	    index_t& src_next_prev = (next[src] != null)? prev[next[src]] : tail;
	    src_prev_next = src_next_prev = dst;
	    elems[dst] = std::move(elems[src]);
	    next[dst] = next[src];
	    prev[dst] = prev[src];
	}
    void exclude_elem(index_t node)
	{
	    assert(node < size());
	    index_t& node_prev_next = (prev[node] != null)? next[prev[node]] : head;
	    index_t& node_next_prev = (next[node] != null)? prev[next[node]] : tail;
	    node_prev_next = next[node];
	    node_next_prev = prev[node];
	}
public:
    void insert(elem_t x)
	{
	    next.push_back(head);
	    if(head != null)
		prev[head] = elems.size();
	    else
		tail = 0;
	    head = size();
	    prev.push_back(index_t(null));
	    elems.push_back(x);
	}
    bool contains(elem_t x)
	{
	    return find(x) != null;
	}
    void remove(elem_t x)
	{
	    int node = find(x);
	    if(node != null)
	    {
		int last = size()-1;
		exclude_elem(node);
		move_elem(last,node);
		elems.pop_back();
		prev.pop_back();
		next.pop_back();
	    }
	}	    
};

#endif /*LIST_ARRAY_H*/
