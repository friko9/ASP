#ifndef LIST_ARRAY_SORTED_WARDEN_H
#define LIST_ARRAY_SORTED_WARDEN_H

#include <cassert>
#include <limits>
#include <vector>

template <typename T>
class list_array_sorted_warden
{
    friend TestPlug<list_array_sorted_warden<T>>;
    std::vector<T> elems;
    std::vector<int> next,prev;
    int head = null, tail = null;
    int find(T x)
	{
	    int n;
	    for( n = head; elems[n] < x; n=next[n])
		;
	    return n;
	}
    void move_elem(int src,int dst)
	{
	    assert( src != head );
	    assert( src != tail );
	    assert( dst != head );
	    assert( dst != tail );
	    if(src == dst) return;
	    prev[next[src]] = dst;
	    next[prev[src]] = dst;

	    elems[dst] = std::move(elems[src]);
	    next[dst] = next[src];
	    prev[dst] = prev[src];
	}
    void exclude_elem(int n)
	{
	    assert( n != head );
	    assert( n != tail );
	    prev[next[n]] = prev[n];
	    next[prev[n]] = next[n];
	}
public:
    enum { null = -1 };
    list_array_sorted_warden()
	{
	    elems.push_back(std::numeric_limits<T>::max());
	    elems.push_back(std::numeric_limits<T>::min());
	    prev.push_back(1);
	    prev.push_back(null);
	    next.push_back(null);
	    next.push_back(0);	
	    head = 1;
	    tail = 0;
	}
    void insert(T x)
	{
	    assert( x != std::numeric_limits<T>::max());
	    assert( x != std::numeric_limits<T>::min());
	    int n = elems.size();
	    int n_next = find(x);
	    int n_prev = prev[n_next];
	    
	    next.push_back(n_next);
	    prev.push_back(n_prev);
	    elems.push_back(x);

	    next[n_prev] = n;
	    prev[n_next] = n;
	}
    bool contains(T x)
	{
	    assert( x != std::numeric_limits<T>::max());
	    assert( x != std::numeric_limits<T>::min());
	    int n = find(x);
	    return elems[n] == x;
	}
    void remove(T x)
	{
	    assert( x != std::numeric_limits<T>::max());
	    assert( x != std::numeric_limits<T>::min());
	    int last = elems.size()-1;
	    int n = find(x);
	    if( elems[n] != x ) return;
	    exclude_elem(n);
	    move_elem(last,n);
	    elems.pop_back();
	    prev.pop_back();
	    next.pop_back();
	}	    
};

#endif /*LIST_ARRAY_SORTED_WARDEN_H*/
