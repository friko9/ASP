#ifndef HASHMAPS_COMMON_H
#define HASHMAPS_COMMON_H

#include "../common.h"
#include "includes/utils/utils.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

#define named_tester_pair(Container,Populator,Tester,T) std::make_pair(std::string(#Container"_"#Populator"_"#Tester"<")+typeid(T).name()+std::string(">"),std::make_shared<tester_t<Container,Populator,Tester,T>>())

template <typename elem_t>
class tester_base
{
public:
    virtual void populate(const std::vector<elem_t>& data) = 0;
    virtual void test(const std::vector<elem_t>& data) = 0;
    virtual tester_base* clone() = 0;
};

template <template<typename Tx> typename ContainerT,
	  template<typename Tx> typename PopulatorF,
	  template<typename Tx> typename TesterF,
	  typename T>
class tester_t : public tester_base<T>
{
    ContainerT<T> priv_container;
public:
    tester_t(tester_t&) = default;
    tester_t() = default;
    void populate(const std::vector<T>& data)
	{
	    PopulatorF<ContainerT<T>> populator;
	    for( auto x : data )
		populator(priv_container,x);
	}
    void test(const std::vector<T>& data)
	{
	    TesterF<ContainerT<T>> tester;
	    for( auto x : data )
		tester(priv_container,x);
	}
    tester_t* clone()
	{ return new tester_t { *this }; }
};

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
class PerformanceTester
    : public PerformanceTesterBase
{
public:
    using subject_t = std::shared_ptr<tester_base<elem_t>>;
    using populator_t = std::function<elem_t()>;
    using testset_generator_t = std::function<elem_t()>;
public:
    PerformanceTester(std::map<std::string,subject_t> subjects,
		      std::map<std::string,populator_t> populators,
		      std::map<std::string,testset_generator_t> testset_generators,
		      std::vector<size_t> dataset_sizes,
		      size_t repetitions ) :
	priv_subjects(subjects),priv_testset_generators(testset_generators),priv_populators(populators),
	PerformanceTesterBase(dataset_sizes,repetitions){}
    result_t run();
private:
    std::map<std::string,subject_t> priv_subjects;
    std::map<std::string,populator_t> priv_populators;
    std::map<std::string,testset_generator_t> priv_testset_generators;
private:
    template< typename T2>
    static std::string get_name(std::pair<const std::string,T2> arg)
	{ return arg.first; }
    static populator_t& get_populator(std::pair<const std::string,populator_t>& arg)
	{ return arg.second; }
    static testset_generator_t& get_testset_generator(std::pair<const std::string,testset_generator_t>& arg)
	{ return arg.second; }
    static subject_t& get_subject(std::pair<const std::string,subject_t>& arg)
	{ return arg.second; }
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
	for( auto data_size : priv_dataset_sizes )
	    for( auto populator : priv_populators)
	    {
		std::vector<elem_t> prepared_population(data_size);
		std::generate(prepared_population.begin(), prepared_population.end(), get_populator(populator));
		for( auto generator : priv_testset_generators)
		{
		    std::vector<elem_t> prepared_data(data_size);
		    std::generate(prepared_data.begin(), prepared_data.end(), get_testset_generator(generator));
		    for( auto subject : priv_subjects)
		    {
			std::vector<elem_t> data {prepared_data};
			data.reserve(data.size()+1);
			auto subject_under_test = get_subject(subject)->clone();
			subject_under_test->populate(prepared_population);
			auto t1 = std::chrono::high_resolution_clock::now();
			subject_under_test->test(data);
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<timer_t,std::micro> d = t2-t1;

			std::string test_name = get_name(subject)+"_"+get_name(populator)+"_"+get_name(generator);
			result_table[test_name][data_size] += d.count();
		    }
		}
	    }
    
    for( auto& result_row : result_table )
	for( auto& timer : get_timers(result_row) )
	    get_timer(timer) /= (timer_t)priv_repetitions;
    return result_table;
}

template <typename ContainerT>
struct NullPopulator
{
    using elem_t = typename ContainerT::elem_t;
    void operator ()(ContainerT& c,elem_t x){ }
};

template <typename ContainerT>
struct InsertPopulator
{
    using elem_t = typename ContainerT::elem_t;
    void operator ()(ContainerT& c,elem_t x){ c.insert(x); }
};

template <typename ContainerT>
struct InsertTester
{
    using elem_t = typename ContainerT::elem_t;
    void operator ()(ContainerT& c,elem_t x){ c.insert(x); }
};

template <typename ContainerT>
struct ContainsTester
{
    using elem_t = typename ContainerT::elem_t;
    void operator ()(ContainerT& c,elem_t x){ c.contains(x); }
};

template <typename ContainerT>
struct RemoveTester
{
    using elem_t = typename ContainerT::elem_t;
    void operator ()(ContainerT& c,elem_t x){ c.remove(x); }
};

template <typename T>
struct echohash
{
    using hash_t = typename std::vector<T>::size_type;
    hash_t operator() (const T x) noexcept { return (hash_t)x; }
};

template <size_t size>
struct echohash<BigT<size>>
{
    using hash_t = typename std::vector<BigT<size>>::size_type;
    hash_t operator() (const BigT<size>& x) noexcept { return (hash_t)x.val; }
};

template <typename T>
struct linRehash
{
    using hash_t = typename std::vector<T>::size_type;
    hash_t operator() (const T x, const hash_t h){ return h+1; }
};

template <typename T>
struct pow2Rehash
{
    using hash_t = typename std::vector<T>::size_type;
    // delta(x^2) = 2mem + 1 = 2(mem+1) - 1;
    hash_t operator() (const T x, const hash_t h){ return h + 2*++mem -1; }
private:
    hash_t mem = 0;
};

std::map<std::string,std::function<int()>> make_generators_int();
std::map<std::string,std::function<T20B()>> make_generators_T20B();
std::map<std::string,std::function<T128B()>> make_generators_T128B();
std::map<std::string,std::function<double()>> make_generators_double();
void print_test_summary(std::ostream& out,std::vector<PerformanceTesterBase::result_t> results);

extern std::vector<size_t> dataset_sizes;

#endif /*HASHMAPS_COMMON_H*/
