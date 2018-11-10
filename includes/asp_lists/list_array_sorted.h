#ifndef LIST_ARRAY_SORTED_H
#define LIST_ARRAY_SORTED_H

#include "../utils/utils.h"

#include <cassert>
#include <vector>

template <typename T>
class list_array_sorted
{
public:
    using elem_t = T;
    using index_t = typename std::vector<T>::size_type;
    static constexpr index_t null =
	(std::is_signed<index_t>::value)? std::numeric_limits<index_t>::min() : std::numeric_limits<index_t>::max();
private:
    friend TestPlug<list_array_sorted<T>>;
    static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value );
private:
    std::vector<T> elems;
    std::vector<index_t> next,prev;
    index_t head = null, tail = null;
private:
    index_t size()
	{ return elems.size(); }
    index_t find(T x)
	{
	    index_t node = head;
	    while( node != null && elems[node] < x )
		node=next[node];
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
    void insert(T x)
	{
	    index_t n = elems.size();
	    index_t n_next = find(x);
	    index_t n_prev = (n_next != null)? prev[n_next] : tail;

	    next.push_back(n_next);
	    prev.push_back(n_prev);
	    elems.push_back(x);

	    if(n_prev != null)
		next[n_prev] = n;
	    else
		head = n;
	    if(n_next != null)
		prev[n_next] = n;
	    else
		tail = n;
	}
    bool contains(T x)
	{
	    index_t n = find(x);
	    return n != null && elems[n] == x;
	}
    void remove(T x)
	{
	    index_t last = elems.size()-1;
	    index_t n = find(x);
	    if( n == null || elems[n] != x ) return;
	    exclude_elem(n);
	    move_elem(last,n);
	    elems.pop_back();
	    prev.pop_back();
	    next.pop_back();
	}	    
};

#endif /*LIST_ARRAY_SORTED_H*/
