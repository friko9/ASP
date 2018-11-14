#ifndef LIST_ARRAY_ENCHANCED_H
#define LIST_ARRAT_ENCHANCED_H

#include "../utils/utils.h"

#include <cassert>
#include <vector>

template <typename T>
class list_array_enchanced
{
    friend TestPlug<list_array_enchanced<T>>;
    using index_t = typename std::vector<T>::size_type;
    static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value );
public:
    using elem_t = T;
private:
    index_t size()
	{ return elems.size(); }
    index_t find(T x)
	{
	    index_t node = next[head];
	    while( node != tail && elems[node] != x )
		node = next[node];
	    return node;
	}
    void move_elem(index_t src,index_t dst)
	{
	    assert(src < size());
	    assert(dst < size());
	    assert(src != head);
	    assert(src != tail);
	    assert(dst != head);
	    assert(dst != tail);
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
    list_array_enchanced()
	{
	    elems.push_back(T());
	    elems.push_back(T());
	    prev.push_back(index_t(head));
	    prev.push_back(index_t(tail));
	    next.push_back(index_t(head));
	    next.push_back(index_t(tail));
	}
    void insert(T x)
	{
	    index_t node = size();
	    index_t node_next = next[head];
	    index_t node_prev = head;
	    next.push_back(node_next);
	    prev.push_back(node_prev);
	    elems.push_back(x);

	    next[node_prev] = node;
	    prev[node_next] = node;
	}
    bool contains(T x)
	{
	    return find(x) != tail;
	}
    void remove(T x)
	{
	    index_t node = find(x);
	    if( node != tail )
	    {
		index_t last = size()-1;
		exclude_elem(node);
		move_elem(last,node);
		elems.pop_back();
		prev.pop_back();
		next.pop_back();
	    }
	}
private:
    std::vector<T> elems;
    std::vector<index_t> next,prev;
    static constexpr index_t head = 1, tail = 0;
};

#endif /*LIST_ARRAT_ENCHANCED_H*/
