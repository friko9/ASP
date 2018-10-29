#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <algorithm>
#include <vector>

template<typename T>
void selection_sort_stlmin(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    const auto ite = v.end();
    for( auto it = v.begin(); it != ite; ++it)
	std::iter_swap(it,std::min_element(it,ite));
}

template<typename T>
void selection_sort_iter(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    const auto ite = v.end();
    for( auto it = v.begin(); it != ite; ++it)
    {
	auto min_it = it;
	for( auto it2 = it+1; it2 != ite; ++it2)
	    if( *it2 < *min_it )
		min_it = it2;
	std::iter_swap(it,min_it);
    }
}

template<typename T>
void selection_sort_index(std::vector<T>& v)
{
    int size = v.size();
    if(size <= 1) return;
    for( int i=0; i<size; ++i)
    {
	auto min_i = i;
	for( auto j = i+1; j < size; ++j)
	    if( v[j] < v[min_i] )
		min_i = j;
	std::swap(v[i],v[min_i]);
    }
}

#endif /*SELECTION_SORT_H*/
