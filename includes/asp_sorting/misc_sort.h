#ifndef MISC_SORT_H
#define MISC_SORT_H

#include "includes/utils/utils.h"
#include <cmath>
#include <exception>

template<typename T>
void counting_sort_stlmap(std::vector<T>& v)
{
    std::map<T,unsigned int> m;
    std::vector<T> ret;
    for( T e : v )
	if(++m[e] == 0)
	    throw std::runtime_error("counter overflow");
    for( auto p : m )
	for(int c = p.second;c>0;--c)
	    ret.push_back(p.first);
    v = std::move(ret);
}

template<typename T>
void heapsort(std::vector<T>& v)
{
    int size = v.size();
    const int depth_minus1 = floor_log2(size);
    const int last_layer = (1<<depth_minus1)-1;
    for(int i=last_layer-1; i >= 0; --i)
	for(int j=i,new_j = j*2+1;new_j<size;j=new_j,new_j=j*2+1)
	{
	    if(new_j < size-1)
		new_j += ( v[new_j] < v[new_j+1] );
	    if( v[j] < v[new_j])
		std::swap(v[new_j],v[j]);
	    else
		break;
	}
    // heap is already sorted
    while(--size >= 0)
    {
	std::swap(v[0],v[size]);
	for(int j=0,new_j=1;new_j<size;j=new_j,new_j=j*2+1)
	{
	    if(new_j < size-1)
		new_j += ( v[new_j] < v[new_j+1] );
	    if( v[j] < v[new_j])
		std::swap(v[new_j],v[j]);
	    else
		break;
	}
    }
}

template<typename It>
void mergesort_sort_iter(const It its,const It ite)
{
    for(auto it = its; it != ite; ++it)
    {
	const auto mem = *it;
	auto it1 = it,it2=it-1;
	for(;it1>its && mem < *it2;--it1,--it2)
	    *it1 = *it2;
	*it1 = mem;
    }
}

template<typename T>
void mergesort(std::vector<T>& v)
{
    using It = typename std::vector<T>::iterator;
    using It_offset_t = typename std::iterator_traits<It>::difference_type;
    constexpr It_offset_t block_size = 32;
    
    const It_offset_t size = v.size();
    const It_offset_t nsize = (It_offset_t)1<<(It_offset_t)(floor_log2(size)+1);
    const It_offset_t new_size = std::max( nsize , block_size);
    v.resize(new_size, std::numeric_limits<T>::max());
    const It last_end = v.begin() + size;
    for(It start =v.begin(); start < last_end; start +=block_size)
	mergesort_sort_iter(start,start+block_size);
    
    for( It_offset_t blk = block_size; blk < size; blk *=2)
	for( It its =v.begin(),itm,ite; ite < last_end; its =ite)
	{
	    std::vector<T> tmp(blk*2);
	    itm = its+blk;
	    ite = itm+blk;
	    It it1 = its;
	    It it2 = itm;
	    auto it = tmp.begin();

	    while(true)
	    {
		if( *it1 <= *it2 ) *it++ = *it1++;
		if( it1 == itm ) break;
		if( *it2 <= *it1 ) *it++ = *it2++;
		if( it2 == ite ) { std::copy(it1,itm,it1+blk); break;}
	    }
	    std::copy(tmp.begin(),it,its);

	}
    v.resize(size);
}

template<typename T>
void shell_sort(std::vector<T>& v)
{
    const int size = v.size();
    for(int s=1023; s > 0; --(++s >>= 1))
    {
	if(s>=size) continue;
	for(int start_i = 0; start_i < s; ++start_i)
	    for(int i = start_i; i<size; i+=s)
		for(int j=i,k=i-s; k>=0 && v[j] < v[k]; k-=s,j-=s)
		    std::swap(v[j],v[k]);
    }
}

#endif /*MISC_SORT_H*/
