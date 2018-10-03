#ifndef LIST_ARRAY_SELFORGANIZING_H
#define LIST_ARRAY_SELFORGANIZING_H

#include <vector>

template <typename T>
class list_array_selforganizing
{
    friend TestPlug<list_array_selforganizing<T>>;
    std::vector<T> elems;
    std::vector<int> next,prev;
    int head = null, tail =null;
    int find(T x)
	{
	    int n = head;
	    while( n!= null && elems[n] != x )
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
	    next.push_back(head);
	    if(head != null)
		prev[head]=elems.size();
	    else
		tail = 0;
	    head = elems.size();
	    prev.push_back(null);
	    elems.push_back(x);
	}
    bool contains(T x)
	{
	    int n = find(x);
	    if ( n == null ) return false;
	    if ( n != head )
	    {
		exclude_elem(n);
		next[n] = head;
		prev[n] = null;
		prev[head] = n;
		head = n;
	    }
	    return true;
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

#endif /*LIST_ARRAY_SELFORGANIZING_H*/
