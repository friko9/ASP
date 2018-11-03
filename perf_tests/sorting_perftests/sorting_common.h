#ifndef SORTING_COMMON_H
#define SORTING_COMMON_H

#include "../common.h"
#include <algorithm>
#include <chrono>
#include <functional>
#include <map>
#include <ostream>
#include <vector>

#define named_pair(X,T) std::make_pair(std::string(#X"<")+typeid(T).name()+std::string(">"),(X<T>))

class BasicPerformanceTester
{
public:
    using timer_t = double;
    using timer_map_t = std::map<size_t,timer_t>;
    using result_t = std::map<std::string,timer_map_t>;
    using result_row_t = result_t::value_type;
    using result_cell_t = timer_map_t::value_type;
public:
    BasicPerformanceTester(std::vector<size_t> dataset_sizes, size_t repetitions)
	: int_dataset_sizes(dataset_sizes),int_repetitions(repetitions){}
protected:
    std::vector<size_t> int_dataset_sizes;
    size_t int_repetitions;
protected:
    static timer_map_t& get_timers( result_row_t& arg){ return arg.second; }
    static timer_t& get_timer( result_cell_t& arg){ return arg.second; }
private:
    void* operator new(size_t) = delete;
    void* operator new(size_t,void*) = delete;
};

template<typename elem_t>
class PerformanceTester : public BasicPerformanceTester
{
public:
    using subject_t = std::function<void(std::vector<elem_t>&)>;
    using generator_t = std::function<elem_t()>;
public:
    PerformanceTester(std::map<std::string,subject_t> subjects,
		      std::map<std::string,generator_t> generators,
		      std::vector<size_t> dataset_sizes,
		      size_t repetitions ) :
	int_subjects(subjects),int_generators(generators),
	BasicPerformanceTester(dataset_sizes,repetitions){}
    result_t run();
private:
    std::map<std::string,subject_t> int_subjects;
    std::map<std::string,generator_t> int_generators;
private:
    template< typename T2>
    static std::string get_name(std::pair<const std::string,T2> arg){ return arg.first; }
    static generator_t& get_generator(std::pair<const std::string,generator_t>& arg){ return arg.second; }
    static subject_t& get_subject(std::pair<const std::string,subject_t>& arg){ return arg.second; }
private:
    void* operator new(size_t) = delete;
    void* operator new(size_t,void*) = delete;
};

template<typename elem_t>
typename PerformanceTester<elem_t>::result_t
PerformanceTester<elem_t>::run()
{
    result_t result_table;
    for( size_t i = 0; i < int_repetitions; ++i )
	for( auto generator : int_generators)
	    for( auto data_size : int_dataset_sizes )
	    {
		std::vector<elem_t> prepared_data(data_size);
		std::generate(prepared_data.begin(), prepared_data.end(), get_generator(generator));
		for( auto subject : int_subjects)
		{
		    std::vector<elem_t> data {prepared_data};
		    data.reserve(data.size()+1);
		    auto subject_under_test = get_subject(subject);
		    auto t1 = std::chrono::high_resolution_clock::now();
		    subject_under_test(data);
		    auto t2 = std::chrono::high_resolution_clock::now();
		    std::chrono::duration<timer_t,std::micro> d = t2-t1;

		    std::string test_name = get_name(subject)+"_"+get_name(generator);
		    result_table[test_name][data_size] += d.count();
		}
	    }
    for( auto& result_row : result_table )
	for( auto& timer : get_timers(result_row) )
	    get_timer(timer) /= (timer_t)int_repetitions;
    return result_table;
}

std::map<std::string,std::function<int()>> make_generators_int();
std::map<std::string,std::function<long double()>> make_generators_ldouble(size_t repetitions);
std::map<std::string,std::function<T20B()>> make_generators_T20B();
std::map<std::string,std::function<T128B()>> make_generators_T128B();
void print_test_summary(std::ostream& out,std::vector<BasicPerformanceTester::result_t> results);

#endif /*SORTING_COMMON_H*/
