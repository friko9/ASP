#ifndef LIST_STLFORWARD_H
#define LIST_STLFORWARD_H

#include "includes/utils/utils.h"

#include <forward_list>

template <typename T>
class list_stlforward
{
public:
    using elem_t = T;
    using It = typename std::forward_list<T>::iterator;
private:
    friend TestPlug<list_stlforward<T>>;
private:
    std::forward_list<T> l;
private:
    It find(T x)
	{
	    const auto ite = l.end();
	    auto it_prev = l.before_begin();
	    auto it = l.begin();
	    while( it != ite && *it != x )
		++it,++it_prev;
	    return it_prev;
	}
public:
    void insert(T x)
	{
	    l.push_front(x);
	}
    bool contains(T x)
	{
	    return next(find(x)) != l.end();
	}
    void remove(T x)
	{
	    auto it = find(x);
	    if(next(it)!=l.end())
		l.erase_after(it);
	}
};

#endif /*LIST_STLFORWARD_H*/
