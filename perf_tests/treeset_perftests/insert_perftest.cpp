#include "./treeset_common.h"
#include "includes/asp_treesets/treeset_array_balancing.h"
#include "includes/asp_treesets/treeset_dynamic_balancing.h"
#include "includes/asp_treesets/treeset_stl.h"

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


template<typename T>
std::map<std::string,std::shared_ptr<tester_base<T>>>
make_subjects()
{
    using subject_t = std::shared_ptr<tester_base<T>>;
    return std::map<std::string,subject_t>{
	named_tester_pair(treeset_array_balancing,NullPopulator,InsertTester,T),
	    named_tester_pair(treeset_dynamic_balancing,NullPopulator,InsertTester,T),
	    named_tester_pair(treeset_stl,NullPopulator,InsertTester,T)
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
	{ make_subjects<int>(), null_generators<int>(), make_generators_int(), dataset_sizes, repetitions };
    PerformanceTester<T20B> T20B_tester =
	{ make_subjects<T20B>(), null_generators<T20B>(), make_generators_T20B(), dataset_sizes, repetitions };
    PerformanceTester<T128B> T128B_tester =
	{ make_subjects<T128B>(), null_generators<T128B>(), make_generators_T128B(), dataset_sizes, repetitions };
    PerformanceTester<double> double_tester =
	{ make_subjects<double>(), null_generators<double>(), make_generators_double(), dataset_sizes, repetitions };

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
