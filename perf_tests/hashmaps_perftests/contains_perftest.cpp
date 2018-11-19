#include "./hashmaps_common.h"
#include "includes/asp_hashsets/hashset_array.h"
#include "includes/asp_hashsets/hashset_bucket.h"
#include "includes/asp_hashsets/hashset_stl.h"

#include <iostream>
#include <fstream>
#include <functional>

template<typename T>
std::map<std::string,std::function<T()>> null_generators()
{
    using generator_t = std::function<T()>;
    return std::map<std::string,generator_t>{
	{ "empty", [](){ return T(); } }
    };
}

template <typename T>
using hbucket_echohash = hashset_bucket<T,echohash<T>>;

template <typename T>
using harray_echohash_linRehash = hashset_array<T,echohash<T>,linRehash<T>>;

template <typename T>
using harray_echohash_pow2Rehash = hashset_array<T,echohash<T>,pow2Rehash<T>>;

namespace std
{
    template <size_t S>
    struct hash<BigT<S>> : public hash<int>
    {
	size_t operator()(const BigT<S>& x) const { return (size_t)x.val; }
    };
}


template<typename T>
std::map<std::string,std::shared_ptr<tester_base<T>>>
make_subjects()
{
    using subject_t = std::shared_ptr<tester_base<T>>;
    return std::map<std::string,subject_t>{
	named_tester_pair(hbucket_echohash,InsertPopulator,ContainsTester,T),
	    named_tester_pair(harray_echohash_linRehash,InsertPopulator,ContainsTester,T),
	    named_tester_pair(harray_echohash_pow2Rehash,InsertPopulator,ContainsTester,T),
	    named_tester_pair(hashset_stl,InsertPopulator,ContainsTester,T)
	    };
}

int main(int argc, char *argv[])
{
    std::ofstream fout;
    if(argc  < 2) return -1;
    int arg1 = std::stoi(argv[1]);
    if(arg1 <= 0) return -1;
    if(argc == 3)
    {
	fout.open(argv[2]);
	if(!fout.is_open()) return -2;
    }
    std::ostream& out = (fout.is_open())? fout : std::cout;

    size_t repetitions = arg1;
    
    PerformanceTester<int> int_tester =
	{ make_subjects<int>(), make_generators_int(), make_generators_int(), dataset_sizes, repetitions };
    PerformanceTester<T20B> T20B_tester =
	{ make_subjects<T20B>(), make_generators_T20B(), make_generators_T20B(), dataset_sizes, repetitions };
    PerformanceTester<T128B> T128B_tester =
	{ make_subjects<T128B>(), make_generators_T128B(), make_generators_T128B(), dataset_sizes, repetitions };
    PerformanceTester<double> double_tester =
	{ make_subjects<double>(), make_generators_double(), make_generators_double(), dataset_sizes, repetitions };

    std::cout<<"test integers"<<std::endl;
    auto result_int = int_tester.run();
    std::cout<<"test T20B"<<std::endl;
    auto result_T20B = T20B_tester.run();
    std::cout<<"test T128B"<<std::endl;
    auto result_T128B = T128B_tester.run();
    std::cout<<"test doubles"<<std::endl;
    auto result_dbl = double_tester.run();

    print_test_summary(out, { result_int, result_T20B, result_T128B, result_dbl });
    return 0;
}
