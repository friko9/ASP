#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "includes/utils/utils.h"
#include <cmath>
#include <iterator>
#include <cstdint>
#include <vector>
#include <tuple>
#include <algorithm>

template<typename It>
void quicksort_h(It its,It ite)
{
    using T = typename It::value_type;
    auto it1 = its;
    auto it2 = std::prev(ite);
    if( it1 == it2 ) return;
    T pivot = *it1;    
    while(true)
    {
	while( it2 != its && pivot <= *it2 ) --it2;
	if( it1 == it2 || std::next(it2) == it1 ) break;
	std::iter_swap(it1,it2);
	while( *it1 < pivot ) ++it1;
    }
    if(it1 == its) ++it1;
    quicksort_h(its,it1);
    quicksort_h(it1,ite);
}

template<typename T>
inline void quicksort(std::vector<T>& v)
{
  if(v.empty()) return;
  quicksort_h(v.begin(),v.end());
}

template<typename It>
void quicksort_enchanced_sort_iter(const It its,const It ite)
{
    for(auto it = its; it != ite; ++it)
    {
	const auto mem = std::move(*it);
	auto it2 = it;
	for(auto it1 = std::prev(it); it2 != its && mem < *it1; --it1,--it2)
	    *it2 =std::move(*it1);
	*it2 = std::move(mem);
    }
}

template<typename It>
void quicksort_enchanced_h(It its,It ite)
{
    using T = typename It::value_type;
    using dist_t = typename It::difference_type;
    for(dist_t width = ite-its; width>50; width = ite-its )
    {
	dist_t qwidth =width/4;
	It it1 =its,it2 =std::prev(ite);
	dist_t pivot_offset =0;
	uint_fast8_t corrections_left =3;
	for(; true; ++pivot_offset)
	{
	    dist_t mid_point = (it2-it1)/2;
	    T pivot = it1[mid_point + pivot_offset];
	    while(true)
	    {
		while( *it1 < pivot ) ++it1;
		while( it2 != its && pivot <= *it2 ) --it2;
		if( it1 == it2 || std::next(it2) == it1 ) break;
		std::iter_swap(it1,it2);
	    }
	    if( --corrections_left == 0 ) break;
	    dist_t width_left = it1-its;
	    dist_t width_right = ite-it1;
	    if( width_left < qwidth ) it2 = std::prev(ite);
	    else if( width_right < qwidth ) it1 =its;
	    else break;
	}
	if(it1 == its) ++it1;
	quicksort_enchanced_h(it1,ite);
	ite =it1;
    }
    quicksort_enchanced_sort_iter(its,ite);
}

template<typename T>
void quicksort_enchanced(std::vector<T>& v)
{
    if( v.size()<=50 )
	return quicksort_enchanced_sort_iter(v.begin(),v.end());
    quicksort_enchanced_h(v.begin(),v.end());
}

template<typename It>
void quicksort_enchanced_sort_iter_indexing(It its,It ite)
{
    for(auto it = its; it != ite; ++it)
    {
	const auto mem_ptr = *it;
	auto it1 =it, it2 =std::prev(it);
	for( ; it1 > its && *mem_ptr < **it2; --it1,--it2)
	    *it1 =*it2;
	*it1 =mem_ptr;
    }
}

template<typename It>
void quicksort_enchanced_indexing_h(It its,It ite)
{
    using T = typename std::remove_pointer<typename It::value_type>::type;
    using dist_t = typename It::difference_type;
    for(dist_t width = ite-its; width>50; width = ite-its )
    {
	dist_t qwidth =width/4;
	It it1 =its,it2 =std::prev(ite);
	dist_t pivot_offset =0;
	uint_fast8_t corrections_left =3;
	for(;true; ++pivot_offset)
	{
	    dist_t mid_point = (it2-it1)/2;
	    T pivot = *it1[mid_point + pivot_offset];
	    while(true)
	    {
		while( **it1 < pivot ) ++it1;
		while( it2 != its && pivot <= **it2 ) --it2;
		if( it1 == it2 || std::next(it2) == it1 ) break;
		std::iter_swap(it1,it2);
	    }
	    if( --corrections_left == 0) break;
	    dist_t width_left = it1-its;
	    dist_t width_right = ite-it1;
	    if( width_left < qwidth ) it2 =std::prev(ite);
	    else if( width_right < qwidth) it1 =its;
	    else break;
	}
	if(it1 == its) ++it1;
	quicksort_enchanced_indexing_h(it1,ite);
	ite =it1;
    }
    quicksort_enchanced_sort_iter_indexing(its,ite);
}

template<typename T>
void quicksort_enchanced_indexing(std::vector<T>& v)
{
    std::vector<T> vres;
    std::vector<T*> vp(v.size());
    vres.reserve(v.size());
    std::generate(vp.begin(),vp.end(), [ptr = v.data()]() mutable { return ptr++; });
    quicksort_enchanced_indexing_h(vp.begin(),vp.end());
    for( auto it : vp )
	vres.emplace_back(std::move(*it));
    std::swap(v,vres);
}


template<typename T>
void quicksort_enchanced_looped(std::vector<T>& v)
{
    using It = typename std::vector<T>::iterator;
    using dist_t = typename It::difference_type;
    It its =v.begin();
    It ite =v.end();

    std::vector<std::pair<It,It>> stack;
    stack.reserve(floor_log2(v.size())+1);

    while(true)
    {
	for(dist_t width = ite-its; width > 50; width = ite-its )
	{
	    dist_t qwidth =width/4;
	    It it1 =its, it2 =std::prev(ite);
	    dist_t pivot_offset =0;
	    uint_fast8_t corrections_left =3;
	    for(; true; ++pivot_offset)
	    {
		dist_t mid_point = (it2-it1)/2;
		T pivot = it1[mid_point + pivot_offset];
		while(true)
		{
		    while( *it1 < pivot ) ++it1;
		    while( it2 != its && pivot <= *it2 ) --it2;
		    if( it1 == it2 || it1 == std::next(it2) ) break;
		    std::iter_swap(it1,it2);
		}
		if( --corrections_left == 0 ) break;
		dist_t width_left = it1-its;
		dist_t width_right = ite-it1;
		if( width_left < qwidth ) it2 = std::prev(ite);
		else if( width_right < qwidth ) it1 =its;
		else break;
	    }
	    if(it1 == its) ++it1;
	    stack.emplace_back(it1,ite);
	    ite =it1;
	}
	quicksort_enchanced_sort_iter(its,ite);
	if(stack.empty()) break;
	std::tie(its,ite) = stack.back();
	stack.pop_back();
    }
}
#endif /*QICK_SORT_H*/
