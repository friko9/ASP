#ifndef HASHSET_STL_H
#define HASHSET_STL_H

#include "includes/utils/utils.h"

#include <unordered_set>

template <typename T>
class hashset_stl
{
    friend TestPlug<hashset_stl<T>>;
    using It = typename std::unordered_set<T>::iterator;
    std::unordered_set<T> s;
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
};
#endif /*HASHSET_STL_H*/
