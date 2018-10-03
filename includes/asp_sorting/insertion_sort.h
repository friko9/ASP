#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <algorithm>
#include <cassert>
#include <vector>

template<typename T>
void insertion_sort_iter(std::vector<T>& v)
{
    const auto its = v.begin();
    const auto ite = v.end();
    for(auto it = its; it<ite; ++it)
 	for(auto it2 = it,it1=it-1; it2!=its && *it2 < *it1; --it1,--it2)
	    std::iter_swap(it2,it1);
 }

template<typename T>
void insertion_sort_iter_bitand(std::vector<T>& v)
{
    assert( v.size() < v.capacity() );
    const auto its = v.begin();
    const auto ite = v.end();
    for(auto it = its; it<ite; ++it)
	for(auto it2 = it,it1=it-1; it2>its & *it2 < *it1; --it1,--it2)
	    std::iter_swap(it2,it1);
}

template<typename T>
void insertion_sort_iter_bitand_mem(std::vector<T>& v)
{
    assert( v.size() < v.capacity() );
    const auto its = v.begin();
    const auto ite = v.end();
    for(auto it = its; it<ite; ++it)
    {
	T mem = *it;
	auto it2 = it;
	for(auto it1 = it-1; it2!=its & mem < *it1; --it1,--it2)
	    *it2 = *it1;
	*it2 = mem;
    }
}

template<typename T>
void insertion_sort_iter_warden_mem(std::vector<T>& v)
{
    T mem;
    v.push_back(std::numeric_limits<T>::max());
    const auto its = v.begin();
    auto it = --v.end();
    while( it > its )
    {
	auto it1 = it;
	auto it2 = --it;
	for( mem = *it2; *it1 < mem; ++it1,++it2)
	    *it2 = *it1;
	*it2 = mem;
    }
    auto it1 = it+1;
    for(mem = *its; *it1 < mem; ++it,++it1)
	*it = *it1;
    *it = mem;
    v.pop_back();
}

template<typename T>
void insertion_sort_iter_warden(std::vector<T>& v)
{
    v.push_back(std::numeric_limits<T>::max());
    const auto its = v.begin();
    auto it = --v.end();
    while( --it > its )
	for(auto it2 = it,it1=it+1; *it1 < *it2; ++it1,++it2)
	    std::iter_swap(it2,it1);
    for(auto it1=it+1; *it1 < *it; ++it,++it1)
	std::iter_swap(it,it1);
    v.pop_back();
}

template<typename T>
void insertion_sort_index(std::vector<T>& v)
{
    const int size = v.size();
    for(int i = 1; i<size; ++i)
	for(auto j=i,k=i-1; j>0 && v[j] < v[k]; --j,--k )
	    std::swap(v[j],v[k]);
}

template<typename T>
void insertion_sort_index_bitand(std::vector<T>& v)
{
    assert( v.size() < v.capacity() );
    const int size = v.size();
    for(int i = 1; i<size; ++i)
	for(auto j=i,k=i-1; j>0 & v[j] < v[k]; --j,--k)
	    std::swap(v[j],v[k]);
}

template<typename T>
void insertion_sort_index_warden(std::vector<T>& v)
{
    const int size = v.size();
    v.push_back(std::numeric_limits<T>::max());
    for(int i = size-2; i>=0; --i)
	for(auto j = i,k=i+1; v[k] < v[j]; ++j,++k)
	    std::swap(v[j],v[k]);
    v.pop_back();
}

#endif
