#ifndef LIST_ARRAY_SORTED_H
#define LIST_ARRAY_SORTED_H

#include <vector>

template <typename T>
class list_array_sorted
{
    friend TestPlug<list_array_sorted<T>>;
    std::vector<T> elems;
    std::vector<int> next,prev;
    int head = null, tail = null;
    int find(T x)
	{
	    int n = head;
	    while( n!= null && elems[n] < x )
		n=next[n];
	    return n;
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
	    int n = elems.size();
	    int n_next = find(x);
	    int n_prev = (n_next != null)? prev[n_next] : tail;

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
	    int n = find(x);
	    return n != null && elems[n] == x;
	}
    void remove(T x)
	{
	    int last = elems.size()-1;
	    int n = find(x);
	    if( n == null || elems[n] != x ) return;
	    exclude_elem(n);
	    move_elem(last,n);
	    elems.pop_back();
	    prev.pop_back();
	    next.pop_back();
	}	    
};

#endif /*LIST_ARRAY_SORTED_H*/
