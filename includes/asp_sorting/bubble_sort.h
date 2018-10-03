#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <algorithm>
#include <vector>

template<typename T>
void bubble_sort_simple(std::vector<T>& v)
{
    const auto its = v.begin();
    for( auto ite = v.end()-1; ite != its; --ite)
	for(auto it = its; it!=ite; ++it)
	    if( *(it+1) < *it )
		std::iter_swap(it,it+1);
}

template<typename T>
void bubble_sort_lastswap(std::vector<T>& v)
{
    const auto its = v.begin();
    for( auto ite = v.end()-1,last_swp=its; ite != its; ite=last_swp,last_swp=its)
	for(auto it = its; it!=ite; ++it)
	    if( *(it+1) < *it )
	    {
		std::iter_swap(it,it+1);
		last_swp = it;
	    }
}

template<typename T>
void shake_sort_lastswap(std::vector<T>& v)
{
    auto its = v.begin();
    auto ite = v.end()-1;
    auto last_swp = its;
    while(its!=ite)
    {
	for(auto it = its; it < ite; ++it)
	    if( *(it+1) < *it )
	    {
		std::iter_swap(it,it+1);
		last_swp = it;
	    }
	ite = last_swp;
	for(auto it = ite; it > its; --it)
	    if(*it < *(it-1) )
	    {
		std::iter_swap(it,it-1);
		last_swp = it;
	    }
	its = last_swp;
    }
}

#endif /*BUBBLE_SORT_H*/
