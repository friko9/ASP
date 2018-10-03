#ifndef UTILS_COMMON_H
#define UTILS_COMMON_H

#include "../common.h"
#include "includes/utils/utils.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <map>
#include <ostream>
#include <vector>

#define named_pair(X,T) std::make_pair(std::string(#X"<")+typeid(T).name()+std::string(">"),(X<T>))

class PerformanceTesterBase
{
public:
    using timer_t = double;
    using timer_map_t = std::map<size_t,timer_t>;
    using result_t = std::map<std::string,timer_map_t>;
    using result_row_t = result_t::value_type;
    using result_cell_t = timer_map_t::value_type;
public:
    PerformanceTesterBase(std::vector<size_t> dataset_sizes, size_t repetitions)
	: priv_dataset_sizes(dataset_sizes),priv_repetitions(repetitions){}
protected:
    std::vector<size_t> priv_dataset_sizes;
    size_t priv_repetitions;
protected:
    static timer_map_t& get_timers( result_row_t& arg){ return arg.second; }
    static timer_t& get_timer( result_cell_t& arg){ return arg.second; }
private:
    void* operator new(size_t) = delete;
    void* operator new(size_t,void*) = delete;
};

template<typename elem_t>
class PerformanceTester : public PerformanceTesterBase
{
public:
    using subject_t = std::function<void(std::vector<elem_t>&)>;
    using generator_t = std::function<elem_t()>;
public:
    PerformanceTester(std::map<std::string,subject_t> subjects,
		      std::map<std::string,generator_t> generators,
		      std::vector<size_t> dataset_sizes,
		      size_t repetitions ) :
	priv_subjects(subjects),priv_generators(generators),
	PerformanceTesterBase(dataset_sizes,repetitions){}
    result_t run();
private:
    std::map<std::string,subject_t> priv_subjects;
    std::map<std::string,generator_t> priv_generators;
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
    for( size_t i = 0; i < priv_repetitions; ++i )
	for( auto generator : priv_generators)
	    for( auto data_size : priv_dataset_sizes )
	    {
		std::vector<elem_t> prepared_data(data_size);
		std::generate(prepared_data.begin(), prepared_data.end(), get_generator(generator));
		for( auto subject : priv_subjects)
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
	    get_timer(timer) /= (timer_t)priv_repetitions;
    return result_table;
}

std::map<std::string,std::function<int()>> make_generators_int();
std::map<std::string,std::function<uint32_t()>> make_generators_uint32t();
std::map<std::string,std::function<double()>> make_generators_double();
void print_test_summary(std::ostream& out,std::vector<PerformanceTesterBase::result_t> results);

template <typename T>
void test_floor_log2_1(std::vector<T> v)
{
    volatile uint32_t retval;
    for( auto x : v )
	retval = floor_log2_1((uint32_t)x);
}

template <typename T>
void test_floor_log2_3(std::vector<T> v)
{
    volatile uint32_t retval;
    for( auto x : v )
	retval = floor_log2_3((uint32_t)x);
}

template <typename T>
void test_floor_log2_std(std::vector<T> v)
{
    volatile uint32_t retval;
    for( auto x : v )
	retval = std::floor(std::log2(x));
}


#endif /*UTILS_COMMON_H*/
