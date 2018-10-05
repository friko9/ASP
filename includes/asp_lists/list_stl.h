#ifndef LIST_STL_H
#define LIST_STL_H

#include "includes/utils/utils.h"

#include <list>

template <typename T>
class list_stl
{
    friend TestPlug<list_stl<T>>;
    using It = typename std::list<T>::iterator;
    std::list<T> l;
    It find(T x)
	{
	    const auto ite = l.end();
	    auto it = l.begin();
	    while( it != ite && *it != x )
		++it;
	    return it;
	}
public:
    void insert(T x)
	{
	    l.push_front(x);
	}
    bool contains(T x)
	{
	    return find(x) != l.end();
	}
    void remove(T x)
	{
	    auto it = find(x);
	    if(it!=l.end())
		l.erase(it);
	}
};

#endif /*LIST_STL_H*/
