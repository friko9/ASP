#ifndef HASHSET_STL_H
#define HASHSET_STL_H

#include "includes/utils/utils.h"

#include <unordered_set>

template <typename T>
class hashset_stl
{
    friend TestPlug<hashset_stl<T>>;
    using It = typename std::unordered_set<T>::iterator;
public:
    using elem_t = T;
public:
    void insert(elem_t x)
	{
	    s.insert(x);
	}
    bool contains(elem_t x)
	{
	    return s.find(x) != s.end();
	}
    void remove(elem_t x)
	{
	    auto it = s.find(x);
	    if(it == s.end()) return;
	    s.erase(it);
	}
private:
    std::unordered_set<elem_t> s;
};
#endif /*HASHSET_STL_H*/
