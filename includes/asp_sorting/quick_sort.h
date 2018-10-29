#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <cmath>

template<typename It>
void quicksort_h(It its,It ite)
{
    using T = typename It::value_type;
    T pivot;
    int i=0;
    // left < pivot; pivot <= right
    if(ite-its <= 1) return;
    auto it1 = its;
    auto it2 = ite-1;
    if(it2-it1 == 1)
    {
	if( *it2 < *it1){ std::iter_swap(it1,it2);}
	return;
    }
f_start:
    pivot = it1[i++];
    while(true)
    {
	while( *it1 < pivot ) ++it1;
	while( it2 > it1 && pivot <= *it2) --it2;
	if(it1 >= it2) break;
	std::iter_swap(it1,it2);
    }
    if(its==it1) goto f_start;
    quicksort_h(its,it1);
    quicksort_h(it1,ite);
}

template<typename T>
inline void quicksort(std::vector<T>& v)
{
    quicksort_h(v.begin(),v.end());
}

template<typename It>
void quicksort_enchanced_sort_iter(const It its,const It ite)
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

template<typename It>
void quicksort_enchanced_h(It its,It ite)
{
    using T = typename It::value_type;
    using dist_t = typename It::difference_type;
    for(dist_t width = ite-its; width>50; width = ite-its )
    {
	dist_t qwidth= width>>2;
	It it1 =its,it2 =ite-1;
	int i=0,correction=2;
	for(;true; ++i)
	{
	    int step2 = ((it2-it1)>>1);
	    int step1 = step2>>1;
	    T pivot = std::max(std::min(it1[i],it1[step1+i]),std::min(it1[step2+i],*it2));
	    do{
		while( *it1 < pivot ) ++it1;
		while( pivot <= *it2) --it2;
		std::iter_swap(it1,it2);
	    }while( it1 < it2);
	    std::iter_swap(it1,it2);
	    if( !--correction) break;
	    
	    dist_t w_l = it1-its;
	    dist_t w_r = ite-it1;
	    if( (width>>1)-w_l > qwidth ) it2=ite-1;
	    else if( (width>>1)-w_r > qwidth ) it1=its;
	    else break;
	}
	quicksort_enchanced_h(it1,ite);
	ite=it1;
    }
    // for(auto it = its; it != ite; ++it)
    // {
    // 	const auto mem = *it;
    // 	auto it1 = it,it2=it-1;
    // 	for(;it1>its && mem < *it2;--it1,--it2)
    // 	    *it1 = *it2;
    // 	*it1 = mem;
    // }
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
	auto mem = *it;
	auto it1 = it;
	for(;it1!=its && *mem < **(it1-1);--it1)
	    *it1 = *(it1-1);
	*it1 = mem;
    }
}

template<typename It>
void quicksort_enchanced_indexing_h(It its,It ite)
{
    using T = typename std::remove_pointer<typename It::value_type>::type;
    if( ite-its < 50 )
	return quicksort_enchanced_sort_iter_indexing(its,ite);
    // left < pivot; pivot <= right
    It prev_it1,prev_it2;
    It it1 = its;
    It it2 = ite-1;
    It piv_it;
    T pivot;
f_start:
//    piv_it = it1+(it2-it1)/2;
//    pivot = **piv_it;
//    iter_swap(piv_it,it2);
    prev_it1 = it1;
    prev_it2 = it2;
    pivot = **it2;
    while(true)
    {
	while( **it1 < pivot ) it1++;
	while( it1 < it2 && pivot <= **it2) it2--;
	if(it1 == it2) break;
	std::iter_swap(it1,it2);
    }
    if((it1-its)*3 < ite-its ){ std::iter_swap(it1,prev_it2);it2=prev_it2;goto f_start;}
    if((ite-it1)*3 < ite-its ){ --it2;it1=prev_it1; goto f_start;}

    quicksort_enchanced_indexing_h(its,it1);
    quicksort_enchanced_indexing_h(it1,ite);
}

template<typename T>
void quicksort_enchanced_indexing(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    std::vector<T*> vp(v.size());
    std::vector<T> vres(v.size());
    T* x = v.data();
    for(auto it=vp.begin(),ite=vp.end();it!=ite;++it) *it = x++;
    quicksort_enchanced_indexing_h(vp.begin(),vp.end());
    auto itv=vres.begin();
    for(auto it = vp.begin(); it != vp.end(); ++it,++itv) *itv = **it;
    v = move(vres);
}

template<typename T>
void quicksort_enchanced_looped(std::vector<T>& v)
{
    using iter = typename std::vector<T>::iterator;
    if(v.size()*sizeof(T) < 200 )
	return quicksort_enchanced_sort_iter(v.begin(),v.end());
    std::vector<std::pair<iter,iter>> stack;
    stack.reserve(std::log2(v.size())+1);
    iter its=v.begin();
    iter ite=v.end();
    while(true)
    {
	int i=5;
	T pivot;
	if( (ite-its)*sizeof(T) < 200 )
	{
	    quicksort_enchanced_sort_iter(its,ite);
	    if(stack.empty()) return;
	    tie(its,ite) = stack.back();
	    stack.pop_back();
	    continue;
	}
	auto it1 = its;
	auto it2 = ite-1;
	quicksort_enchanced_sort_iter(it1,it1+10);
    f_start:
	pivot = it1[i++];
	while(true)
	{
	    while( *it1 < pivot ) it1++;
	    while( pivot <= *it2) it2--;
	    if(it1 >= it2) break;
	    std::iter_swap(it1,it2);
	}
	//if((it1-its)*2<(ite-its)) goto f_start;
	if(it1==its) goto f_start;
	stack.emplace_back(it1,ite);
	ite = it1;
    }
}

#endif /*QICK_SORT_H*/
