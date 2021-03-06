#include "./sorting_common.h"
#include "includes/asp_sorting/misc_sort.h"
#include "includes/asp_sorting/quick_sort.h"
#include "includes/asp_sorting/stl_sort.h"

#include <iostream>
#include <fstream>

template<typename T>
std::map<std::string,std::function<void(std::vector<T>&)>>
make_subjects()
{
    using subject_t = std::function<void(std::vector<T>&)>;
    return std::map<std::string,subject_t>{
	    //stl_sort.h
	named_pair(stl_qsort_1,T),
	    named_pair(stl_qsort_2,T),
	    named_pair(stl_sort,T),
	    named_pair(stl_sort_indexing,T),
	    //quick_sort.h
	    named_pair(quicksort_enchanced,T),
	    named_pair(quicksort_enchanced_indexing,T),
	    named_pair(quicksort_enchanced_looped,T),
	    //misc_sort.h
	    named_pair(heapsort,T),
	    named_pair(mergesort,T)
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
    std::vector<size_t> dataset_sizes = { 100, 1000, 10000, 100000, 1000000 };
    
    PerformanceTester<int> int_tester { make_subjects<int>(), make_generators_int(), dataset_sizes, repetitions };
    PerformanceTester<long double> ldouble_tester { make_subjects<long double>(), make_generators_ldouble(repetitions), dataset_sizes, repetitions };
    PerformanceTester<T20B> T20B_tester { make_subjects<T20B>(), make_generators_T20B(), dataset_sizes, repetitions };
    PerformanceTester<T128B> T128B_tester { make_subjects<T128B>(), make_generators_T128B(), dataset_sizes, repetitions };

    std::cout<<"test integers"<<std::endl;
    auto result_int = int_tester.run();
    std::cout<<"test doubles"<<std::endl;
    auto result_ldbl = ldouble_tester.run();
    std::cout<<"test T20B"<<std::endl;
    auto result_t20B = T20B_tester.run();
    std::cout<<"test T128B"<<std::endl;
    auto result_t128B = T128B_tester.run();

    print_test_summary(out, { result_int, result_ldbl, result_t20B, result_t128B });
    return 0;
}
