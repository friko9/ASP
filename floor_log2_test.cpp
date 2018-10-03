#include "./utils/utils.h"
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <iomanip>

int floor_log2_2(int x)
{
    return log2(x);
}

#define f_pair(X) std::make_pair(string(#X),(X))

std::array<int,10> sizes = {10,20,30,40,60,100,1000,10000,100000,1000000};
std::map<std::string,std::array<double,sizes.size()>> t_map;
std::map<std::string,int(*)(int)> m;

template<typename G>
void test(std::map<std::string,int(*)(int)> map,G distr,int repetitions)
{
    using ullong = unsigned long long;
    for(int r=0;r<repetitions;++r)
	for (int i=0; i<sizes.size() ; ++i)
	{
	    std::vector<int> vec(sizes[i]);
	    std::generate(vec.begin(), vec.end(),distr.second);
	    std::cerr<<sizes[i]<<std::endl;
	    for( auto f : map)
	    {
		std::cerr<<f.first<<std::endl;
		std::vector<int> v {vec};
		auto t1 = std::chrono::high_resolution_clock::now();
		for( auto x : v )
		    f.second(x);
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double,std::micro> d = t2-t1;
		t_map[f.first+"_"+distr.first][i] += d.count();
	    }
	}
}

using namespace std;
int main(int argc, char *argv[])
{
    auto rand_int = bind(uniform_int_distribution<int>(),std::default_random_engine());

    m.insert(f_pair(floor_log2_1));
    m.insert(f_pair(floor_log2_2));
    m.insert(f_pair(floor_log2_3));
    int args[] = {1,2,3,4,5,6,7,8,9,10,123,1234,12345,123456,1234567,12345678,
		  123456789,1073741824};
    int ans[] = {0,1,1,2,2,2,2,3,3,3,6,10,13,16,20,23,26,30};

    test(m,make_pair("rand_int",rand_int),1);

    string::size_type maxw = 0;
    for ( auto f : t_map)
	maxw = std::max(f.first.size(),maxw);
    
    cout<<"\n--------------------------------------------\n\n";
    cout << setw(maxw) << "Results in µs";
    for (int i=0; i<sizes.size(); ++i)
	cout << setw(13) << sizes[i];
    cout<<'\n';
    for ( auto f : t_map)
    {
	cout << setw(maxw) << f.first << ':';
	for ( auto t : f.second )
	    cout << setw(13) << t;
	cout << "\n";
    }


    for( auto f : m)
	for(int i=0;i<sizeof(args)/sizeof(int);++i)
	{
	    int res = f.second(args[i]);
	    if ( res != ans[i] )
		cout<<"bad:"<<f.first<<'('<<args[i]<<")="<<res<<"[ not "
		    <<ans[i]<<']'<<endl;
	}
    return 0;
}
