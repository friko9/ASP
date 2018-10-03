#ifndef LIST_ARRAY_ENCHANCED_H
#define LIST_ARRAT_ENCHANCED_H

#include <cassert>
#include <vector>

template <typename T>
class list_array_enchanced
{
    friend TestPlug<list_array_enchanced<T>>;
    std::vector<T> elems;
    std::vector<int> next,prev;
    static constexpr int head = 1, tail = 0;
    int find(T x)
	{
	    int n;
	    for( n = next[head]; n != tail && elems[n] != x; n=next[n])
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
    list_array_enchanced()
	{
	    elems.push_back(T());
	    elems.push_back(T());
	    prev.push_back(int(head));
	    prev.push_back(int(tail));
	    next.push_back(int(head));
	    next.push_back(int(tail));
	}
    void insert(T x)
	{
	    int n = elems.size();
	    int n_next = next[head];
	    int n_prev = head;
	    
	    next.push_back(n_next);
	    prev.push_back(n_prev);
	    elems.push_back(x);

	    next[n_prev] = n;
	    prev[n_next] = n;
	}
    bool contains(T x)
	{
	    return find(x) != tail;
	}
    void remove(T x)
	{
	    int last = elems.size()-1;
	    int n = find(x);
	    if( n == tail ) return;
	    exclude_elem(n);
	    move_elem(last,n);
	    elems.pop_back();
	    prev.pop_back();
	    next.pop_back();
	}	    
};

#endif /*LIST_ARRAT_ENCHANCED_H*/
