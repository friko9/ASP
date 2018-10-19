#include "./floor_log2.h"
#include <iostream>
#include <chrono>
#include <random>
#include <array>
#include <map>
#include <functional>
#include <algorithm>
#include <climits>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <limits>

using namespace std;

#define f_pair(X,T) std::make_pair(string(#X"<")+typeid(T).name()+string(">"),(X<T>))

union T20B
{
    int val;
    char fill[20];
    T20B() = default;
    T20B(const T20B&) = default;
    T20B(T20B&&) = default;
    T20B(T20B&) = default;
    T20B(int x):val(x){}
    bool operator < (const T20B& arg)const{ return val < arg.val;}
    bool operator == (const T20B& arg)const{ return val == arg.val;}
    bool operator != (const T20B& arg)const{ return val != arg.val;}
    bool operator <= (const T20B& arg)const{ return val <= arg.val;}
    T20B& operator = (const T20B& arg) = default;
    T20B& operator = (T20B& arg) = default;
    T20B& operator = (T20B&& arg) = default;
    T20B& operator ++ (){ ++val; return *this;} 
};

namespace std
{
    ostream& operator << (ostream& o,T20B& arg){ o<<arg.val; return o;}

    template <>
    class numeric_limits<T20B> : public numeric_limits<int>
    {    };
}
template<typename T>
void stl_sort(std::vector<T>& v)
{
    sort(v.begin(), v.end());
}

template<typename T>
void stl_stable_sort(std::vector<T>& v)
{
    stable_sort(v.begin(), v.end());
}

template<typename T>
void stl_sort_indexing(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    std::vector<T*> vp(v.size());
    std::vector<T> vres(v.size());
    T* x = v.data();
    for(auto it=vp.begin(),ite=vp.end();it!=ite;++it) *it = x++;
    sort(vp.begin(),vp.end(),[](T* p1,T* p2){ return *p1<*p2;});
    auto itv=vres.begin();
    for(auto it = vp.begin(); it != vp.end(); ++it,++itv) *itv = **it;
    v = move(vres);
}

template<typename T>
void stl_qsort(std::vector<T>& v)
{
    qsort(v.data(), v.size(), sizeof(T), [](const void* a,const void* b)
	  {
	      if(*(T*)a<*(T*)b) return -1;
	      if(*(T*)b<*(T*)a) return 1;
	      return 0;
	  });
}

template<typename T>
void counting_sort_stl(std::vector<T>& v)
{
    map<T,int> m;
    for( T e : v ) ++m[e];
    auto itv=v.begin();
    for( auto p : m )
	for(int c = p.second;c>0;--c,++itv)
	    *itv=c;
}


template<typename T>
void heapsort(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    int size = v.size();
    const int depth_minus1 = (int)log2(size);
    const int last_layer = (1<<depth_minus1)-1;
    for(int i=last_layer-1; i >= 0; --i)
	for(int j=i,new_j = j*2+1;new_j<size;j=new_j,new_j=j*2+1)
	{
	    if(new_j < size-1)
		new_j += ( v[new_j] < v[new_j+1] );
	    if( v[j] < v[new_j])
		swap(v[new_j],v[j]);
	    else
		break;
	}
    // heap is already sorted
    while(--size >= 0)
    {
	swap(v[0],v[size]);
	for(int j=0,new_j=1;new_j<size;j=new_j,new_j=j*2+1)
	{
	    if(new_j < size-1)
		new_j += ( v[new_j] < v[new_j+1] );
	    if( v[j] < v[new_j])
		swap(v[new_j],v[j]);
	    else
		break;
	}
    }
}

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
	if( *it2 < *it1){ iter_swap(it1,it2);}
	return;
    }
f_start:
    pivot = it1[i++];
    while(true)
    {
	while( *it1 < pivot ) ++it1;
	while( it2 > it1 && pivot <= *it2) --it2;
	if(it1 >= it2) break;
	iter_swap(it1,it2);
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
	    T pivot = max(min(it1[i],it1[step1+i]),min(it1[step2+i],*it2));
	    do{
		while( *it1 < pivot ) ++it1;
		while( pivot <= *it2) --it2;
		iter_swap(it1,it2);
	    }while( it1 < it2);
	    iter_swap(it1,it2);
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
    for(auto it = its; it != ite; ++it)
    {
	const auto mem = *it;
	auto it1 = it,it2=it-1;
	for(;it1>its && mem < *it2;--it1,--it2)
	    *it1 = *it2;
	*it1 = mem;
    }
//    quicksort_enchanced_sort_iter(its,ite);
}

template<typename T>
void quicksort_enchanced(std::vector<T>& v)
{
    if( v.size()<=50 )
	return quicksort_enchanced_sort_iter(v.begin(),v.end());
    quicksort_enchanced_h(v.begin(),v.end());
}

template<typename T>
void mergesort(std::vector<T>& v)
{
    using It = typename std::vector<T>::iterator;
    constexpr int block_size = 32;
    
    const int size = v.size();
    const int new_size = max( 1<<(floor_log2_1(size)+1), block_size);
    v.resize(new_size, std::numeric_limits<T>::max());
    const It last_end = v.begin()+size;
    for(It start =v.begin(); start < last_end; start +=block_size)
	quicksort_enchanced_sort_iter(start,start+block_size);
    
    for( int blk = block_size; blk < size; blk *=2)
	for( It its =v.begin(),itm=its+blk,ite=itm+blk; its < last_end; its =ite,itm =its+blk, ite =itm+blk)
	{
	    T tmp [blk*2];
	    It it1 = its;
	    It it2 = its+blk;
	    auto it = tmp;

	    while(true)
	    {
		if( *it1 <= *it2 ) *it++ = *it1++;
		if( it1 == itm ) break;
		if( *it2 <= *it1 ) *it++ = *it2++;
		if( it2 == ite ) { std::copy(it1,itm,it1+blk); break;}
	    }
	    std::copy(tmp,it,its);

	}
    v.resize(size);
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
    using T = typename remove_pointer<typename It::value_type>::type;
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
	iter_swap(it1,it2);
    }
    if((it1-its)*3 < ite-its ){ iter_swap(it1,prev_it2);it2=prev_it2;goto f_start;}
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
    using iter = typename vector<T>::iterator;
    if(v.size()*sizeof(T) < 200 )
	return quicksort_enchanced_sort_iter(v.begin(),v.end());
    vector<pair<iter,iter>> stack;
    stack.reserve(log2(v.size())+1);
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
	    iter_swap(it1,it2);
	}
	//if((it1-its)*2<(ite-its)) goto f_start;
	if(it1==its) goto f_start;
	stack.emplace_back(it1,ite);
	ite = it1;
    }
}

template<typename T>
void radix_sort_std(std::vector<T>& v)
{
    const int size = v.size();
    for(int s=1023; s > 0; --(++s >>= 1))
    {
	if(s>=size) continue;
	for(int start_i = 0; start_i < s; ++start_i)
	    for(int i = start_i; i<size; i+=s)
		for(int j=i,k=i-s; k>=0 && v[j] < v[k]; k-=s,j-=s)
		    swap(v[j],v[k]);
    }
}

template<typename T>
void bubble_sort_simple(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    const auto its = v.begin();
    for( auto ite = v.end()-1; ite != its; --ite)
	for(auto it = v.begin(); it!=ite; ++it)
	    if( *(it+1) < *it )
		iter_swap(it,it+1);
}

template<typename T>
void bubble_sort_lastswap(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    const auto its = v.begin();
    for( auto ite = v.end()-1,last_swp=its; ite != its; ite=last_swp,last_swp=its)
	for(auto it = v.begin(); it!=ite; ++it)
	    if( *(it+1) < *it )
	    {
		iter_swap(it,it+1);
		last_swp = it;
	    }
}

template<typename T>
void shake_sort_lastswap(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    auto its = v.begin();
    auto ite = v.end()-1;
    auto last_swp = its;
    while(its!=ite)
    {
	for(auto it = its; it < ite; ++it)
	    if( *(it+1) < *it )
	    {
		iter_swap(it,it+1);
		last_swp = it;
	    }
	ite = last_swp;
	for(auto it = ite; it > its; --it)
	    if(*it < *(it-1) )
	    {
		iter_swap(it,it-1);
		last_swp = it;
	    }
	its = last_swp;
    }
}

template<typename T>
void selection_sort_stl(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    const auto ite = v.end();
    for( auto it = v.begin(); it != ite; ++it)
	iter_swap(it,min_element(it,ite));
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
	iter_swap(it,min_it);
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
	swap(v[i],v[min_i]);
    }
}

template<typename T>
void insertion_sort_iter(std::vector<T>& v)
{
    const auto its = v.begin();
    const auto ite = v.end();
    for(auto it = its; it<ite; ++it)
 	for(auto it2 = it,it1=it-1; it2!=its && *it2 < *it1; --it1,--it2)
	    iter_swap(it2,it1);
 }

template<typename T>
void insertion_sort_iter_bitand(std::vector<T>& v)
{
    const auto its = v.begin();
    const auto ite = v.end();
    for(auto it = its; it<ite; ++it)
	for(auto it2 = it,it1=it-1; it2>its & *it2 < *it1; --it1,--it2)
	    iter_swap(it2,it1);
}

template<typename T>
void insertion_sort_iter_bitand_mem(std::vector<T>& v)
{
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
    v.push_back(numeric_limits<T>::max());
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
    v.push_back(numeric_limits<T>::max());
    const auto its = v.begin();
    auto it = --v.end();
    while( --it > its )
	for(auto it2 = it,it1=it+1; *it1 < *it2; ++it1,++it2)
	    iter_swap(it2,it1);
    for(auto it1=it+1; *it1 < *it; ++it,++it1)
	iter_swap(it,it1);
    v.pop_back();
}

template<typename T>
void insertion_sort_index(std::vector<T>& v)
{
    const int size = v.size();
    for(int i = 1; i<size; ++i)
	for(auto j=i,k=i-1; j>0 && v[j] < v[k]; --j,--k )
	    swap(v[j],v[k]);
}

template<typename T>
void insertion_sort_index_bitand(std::vector<T>& v)
{
    const int size = v.size();
    for(int i = 1; i<size; ++i)
	for(auto j=i,k=i-1; j>0 & v[j] < v[k]; --j,--k)
	    swap(v[j],v[k]);
}

template<typename T>
void insertion_sort_index_warden(std::vector<T>& v)
{
    const int size = v.size();
    v.push_back(numeric_limits<T>::max());
    for(int i = size-2; i>=0; --i)
	for(auto j = i,k=i+1; v[k] < v[j]; ++j,++k)
	    swap(v[j],v[k]);
    v.pop_back();
}

template<typename T>
bool is_unsorted(std::vector<T>& v)
{
    if(v.size() <= 1) return false;
    for(auto it1=v.begin(),it2=it1+1;it2!=v.end();++it1,++it2)
	if( *it2 < *it1 ) return true;
    return false;
}


std::array<int,8> sizes = {10,20,30,40,60,100,1000,10000};
//std::array<int,10> sizes = {10,20,30,40,60,100,1000,10000,100000,1000000};
std::map<string,void(*)(std::vector<int> &)> int_map;
std::map<string,void(*)(std::vector<long double> &)> ldouble_map;
std::map<string,void(*)(std::vector<T20B> &)> T20B_map;
map<string,array<double,sizes.size()>> t_map;

template<typename T,typename M>
void initialize(M& map)
{
    
    map.insert( f_pair(stl_sort,T) );
    map.insert( f_pair(stl_sort_indexing,T) );
    //map.insert( f_pair(stl_qsort,T) );
    map.insert( f_pair(stl_stable_sort,T) );
    map.insert( f_pair(mergesort,T) );
    map.insert( f_pair(heapsort,T) );
    map.insert( f_pair(quicksort,T) );
    map.insert( f_pair(quicksort_enchanced,T) );
    //map.insert( f_pair(quicksort_enchanced_indexing,T) );
    //map.insert( f_pair(quicksort_enchanced_looped,T) );
    //map.insert( f_pair(insertion_sort_index,T) );
    //map.insert( f_pair(insertion_sort_index_bitand,T) );
    //map.insert( f_pair(insertion_sort_index_warden,T) );
    map.insert( f_pair(insertion_sort_iter,T) );
    map.insert( f_pair(insertion_sort_iter_bitand,T) );
    map.insert( f_pair(insertion_sort_iter_bitand_mem,T) );
    map.insert( f_pair(insertion_sort_iter_warden_mem,T) );
    map.insert( f_pair(insertion_sort_iter_warden,T) );
    //map.insert( f_pair(selection_sort_stl,T) );
    //map.insert( f_pair(selection_sort_iter,T) );
    //map.insert( f_pair(selection_sort_index,T) );
    //map.insert( f_pair(bubble_sort_simple,T) );
    map.insert( f_pair(bubble_sort_lastswap,T) );
    //map.insert( f_pair(shake_sort_lastswap,T) );
    map.insert( f_pair(radix_sort_std,T) );
    //map.insert( f_pair(counting_sort_stl,T) );
}

template<typename T,typename G,typename M>
void test(M& map,G distr,int repetitions)
{
    using ullong = unsigned long long;

    for(int r=0;r<repetitions;++r)
	for (int i=0; i<sizes.size() ; ++i)
	{
	    std::vector<T> vec(sizes[i]);
	    std::generate(vec.begin(), vec.end(),distr.second);
	    cerr<<sizes[i]<<endl;
	    for( auto f : map)
	    {
		cerr<<f.first<<endl;
		std::vector<T> v {vec};
		auto t1 = chrono::high_resolution_clock::now();
		f.second(v);
		auto t2 = chrono::high_resolution_clock::now();
//		cout<<v.front()<<' '<<v.back()<<',';
		chrono::duration<double,std::micro> d = t2-t1;
		t_map[f.first+"_"+distr.first][i] += d.count();
		if(is_unsorted(v)) cerr<<f.first<<"~bad\n";
	    }
//	    cout<<endl;
	}
}
    

int main(int argc, char *argv[])
{
    if(argc  != 2) return -1;
    int repetitions = stoi(argv[1]);
    
    initialize<int>(int_map);
    initialize<long double>(ldouble_map);
    initialize<T20B>(T20B_map);

    auto rand_int = bind(uniform_int_distribution<int>(),std::default_random_engine());
    auto rand_ldouble = bind(uniform_real_distribution<long double>(),std::default_random_engine());
    auto rand_T20B = [&rand_int](){ return T20B(rand_int());};
    test<int>(int_map,make_pair("rand",rand_int),repetitions);
    test<long double>(ldouble_map,make_pair("rand",rand_ldouble),repetitions);
    test<T20B>(T20B_map,make_pair("rand",rand_T20B),repetitions);

    int i=0;
    double d=0;
    auto sorted_int = [i]()mutable{return ++i;};
    auto sorted_ldouble = [d]()mutable{return d+=0.01;};
    auto sorted_T20B = [i]()mutable{return T20B(++i);};
    test<int>(int_map,make_pair("sorted",sorted_int),repetitions);
    test<long double>(ldouble_map,make_pair("sorted",sorted_ldouble),repetitions);
    test<T20B>(T20B_map,make_pair("sorted",sorted_T20B),repetitions);

    auto sorted90_int = [i,&rand_int]()mutable{if(++i%10)return i;else return rand_int();};
    auto sorted90_ldouble = [i,&rand_ldouble,repetitions]()mutable{if(++i%10)return (long double)0.01*i;else return rand_ldouble()*0.01*repetitions;};
    auto sorted90_T20B = [i,&rand_int]()mutable{if(++i%10)return T20B(i);else return T20B(rand_int());};
    test<int>(int_map,make_pair("sorted90",sorted90_int),repetitions);
    test<long double>(ldouble_map,make_pair("sorted90",sorted90_ldouble),repetitions);
    test<T20B>(T20B_map,make_pair("sorted90",sorted90_T20B),repetitions);

    i=94;
    auto sorted99_int = [i,&rand_int]()mutable{if(++i%100)return i;else return rand_int();};
    auto sorted99_ldouble = [i,&rand_ldouble,repetitions]()mutable{if(++i%100)return (long double)0.01*i;else return rand_ldouble()*0.01*repetitions;};
    auto sorted99_T20B = [i,&rand_int]()mutable{if(++i%100)return T20B(i);else return T20B(rand_int());};
    test<int>(int_map,make_pair("sorted99",sorted99_int),repetitions);
    test<long double>(ldouble_map,make_pair("sorted99",sorted99_ldouble),repetitions);
    test<T20B>(T20B_map,make_pair("sorted99",sorted99_T20B),repetitions);

    cout<<"\n--------------------------------------------\n\n";
    cout << setw(50) << "Results in µs";
    for (int i=0; i<sizes.size(); ++i)
	cout << setw(13) << sizes[i];
    cout<<'\n';
    for ( auto f : t_map)
    {
	cout << setw(50) << f.first << ':';
	for ( auto t : f.second )
	    cout << setw(13) << t/(double)repetitions;
	cout << "\n";
    }
    
    return 0;
}
