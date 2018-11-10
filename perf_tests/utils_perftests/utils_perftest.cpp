#include "./utils_common.h"

#include <iostream>
#include <fstream>

template<typename T>
std::map<std::string,std::function<void(std::vector<T>&)>>
make_subjects()
{
    using subject_t = std::function<void(std::vector<T>&)>;
    return std::map<std::string,subject_t>{
	named_pair(test_floor_log2_1,T),
	    named_pair(test_floor_log2_3,T),
	    named_pair(test_floor_log2_std,T),
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
    std::vector<size_t> dataset_sizes = { 40, 4000, 400000 };
    
    PerformanceTester<int> int_tester { make_subjects<int>(), make_generators_int(), dataset_sizes, repetitions };
    PerformanceTester<uint32_t> uint32t_tester { make_subjects<uint32_t>(), make_generators_uint32t(), dataset_sizes, repetitions };
    PerformanceTester<double> double_tester { make_subjects<double>(), make_generators_double(), dataset_sizes, repetitions };

    std::cout<<"test integers"<<std::endl;
    auto result_int = int_tester.run();
    std::cout<<"test uint32_t"<<std::endl;
    auto result_uint32t = double_tester.run();
    std::cout<<"test doubles"<<std::endl;
    auto result_dbl = double_tester.run();

    print_test_summary(out, { result_int, result_uint32t, result_dbl });
    return 0;
}
