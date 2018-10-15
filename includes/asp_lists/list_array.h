#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H

#include "includes/utils/utils.h"
#include <vector>

template <typename T>
class list_array
{
    friend TestPlug<list_array<T>>;
    std::vector<T> elems;
    std::vector<int> next,prev;
    int head = null, tail = null;
    int find(T x)
	{
	    int n = head;
	    while( n != null && elems[n] != x )
		n = next[n];
	    return n;
	}
    void switch_elems(int n1,int n2) // new
	{
	    if(n1 == n2) return;
	    int& n1_prev_next = (prev[n1] != null)? next[prev[n1]] : head;
	    int& n1_next_prev = (next[n1] != null)? prev[next[n1]] : tail;
	    int& n2_prev_next = (prev[n2] != null)? next[prev[n2]] : head;
	    int& n2_next_prev = (next[n2] != null)? prev[next[n2]] : tail;
	    n1_prev_next = n1_next_prev = n2;
	    n2_prev_next = n2_next_prev = n1;
	    std::swap(elems[n1],elems[n2]);
	    std::swap(next[n1],next[n2]);
	    std::swap(prev[n1],prev[n2]);
	}
    void del_elem(int node) // new
	{
	    switch_elems( node, elems.size()-1 );
	    exclude_elem( elems.size()-1 );
	    elems.pop_back();
	    next.pop_back();
	    prev.pop_back();
	}
    void move_elem(int src,int dst)
	{
	    if(src == dst) return;
	    if(next[src] != null)
		prev[next[src]] = dst;
	    else
		tail = dst;
	    if(prev[src] != null)
		next[prev[src]] = dst;
	    else
		head = dst;
	    elems[dst] = std::move(elems[src]);
	    next[dst] = next[src];
	    prev[dst] = prev[src];
	}
    void exclude_elem(int n)
	{
	    if(next[n] != null)
		prev[next[n]] = prev[n];
	    else
		tail = prev[n];
	    if(prev[n] != null)
		next[prev[n]] = next[n];
	    else
		head = next[n];
	}
public:
    enum { null = -1 };
    void insert(T x)
	{
	    next.push_back(head);
	    if(head != null)
		prev[head] = elems.size();
	    else
		tail = 0;
	    head = elems.size();
	    prev.push_back(null);
	    elems.push_back(x);
	}
    bool contains(T x)
	{
	    return find(x) != null;
	}
    void remove(T x)
	{
	    int last = elems.size()-1;
	    int n = find(x);
	    if(n == null) return;
	    exclude_elem(n);
	    move_elem(last,n);
	    elems.pop_back();
	    prev.pop_back();
	    next.pop_back();
	}	    
};

#endif /*LIST_ARRAY_H*/
