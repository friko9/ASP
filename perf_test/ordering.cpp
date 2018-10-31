#include "asp_lists.h"

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
bool is_unsorted(std::vector<T>& v)
{
    if(v.size() <= 1) return false;
    for(auto it1=v.begin(),it2=it1+1;it2!=v.end();++it1,++it2)
	if( *it2 < *it1 ) return true;
    return false;
}


std::array<int,8> sizes = {10,20,30,40,60,100,1000,10000};
std::map<string,void(*)(std::vector<int> &)> int_map;
std::map<string,void(*)(std::vector<long double> &)> ldouble_map;
std::map<string,void(*)(std::vector<T20B> &)> T20B_map;
map<string,array<double,sizes.size()>> t_map;

template<typename T,typename M>
void initialize(M& map)
{
    // map.insert( f_pair(stl_sort_indexing,T) );
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
		chrono::duration<double,std::micro> d = t2-t1;
		t_map[f.first+"_"+distr.first][i] += d.count();
		if(is_unsorted(v)) cerr<<f.first<<"~bad\n";
	    }
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