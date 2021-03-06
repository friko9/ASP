#ifndef TREESET_STL_H
#define TREESET_STL_H

#include "includes/utils/utils.h"

#include <set>

template <typename T>
class treeset_stl
{
    friend TestPlug<treeset_stl<T>>;
    using It = typename std::set<T>::iterator;
public:
    using elem_t = T;
public:
    void insert(T x)
	{
	    s.insert(x);
	}
    bool contains(T x)
	{
	    return s.find(x) != s.end();
	}
    void remove(T x)
	{
	    auto it = s.find(x);
	    if(it == s.end()) return;
	    s.erase(it);
	}
private:    
    std::set<T> s;
};

#endif /*TREESET_STL_H*/
