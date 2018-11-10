#include "./sorting_common.h"

#include <iomanip>
#include <random>

std::map<std::string,std::function<int()>> make_generators_int()
{
    using generator_t = std::function<int()>;
    auto random = std::bind(std::uniform_int_distribution<int>(),std::default_random_engine());
    auto sorted = [i=0]()mutable{return ++i;};
    auto sorted90 = [i=0,random]()mutable{if(++i%10)return i;else return random();};
    auto sorted99 = [i=0,random]()mutable{if(++i%100)return i;else return random();};
    return std::map<std::string,generator_t>{
	{"random  ", random},
	{"sorted  ", sorted},
	{"sorted90", sorted90},
	{"sorted99", sorted99}
    };
}
std::map<std::string,std::function<long double()>> make_generators_ldouble(size_t repetitions)
{
    using generator_t = std::function<long double()>;
    auto random = std::bind(std::uniform_real_distribution<long double>(),std::default_random_engine());
    auto sorted = [d=0.0l]()mutable{return d+=0.01l;};
    auto sorted90 = [i=4,random,repetitions]()mutable{if(++i%10)return (long double)0.01l*i;else return random()*0.01l*repetitions;};
    auto sorted99 = [i=94,random,repetitions]()mutable{if(++i%100)return (long double)0.01l*i;else return random()*0.01l*repetitions;};
    return std::map<std::string,generator_t>{
	{"random  ", random},
	{"sorted  ", sorted},
	{"sorted90", sorted90},
	{"sorted99", sorted99}
    };
}
std::map<std::string,std::function<T20B()>> make_generators_T20B()
{
    using generator_t = std::function<T20B()>;
    auto rand_int = std::bind(std::uniform_int_distribution<int>(),std::default_random_engine());
    auto random = [rand_int]()mutable{ return T20B(rand_int());};
    auto sorted = [i=0]()mutable{return T20B(++i);};
    auto sorted90 = [i=0,rand_int]()mutable{if(++i%10)return T20B(i);else return T20B(rand_int());};
    auto sorted99 = [i=0,rand_int]()mutable{if(++i%100)return T20B(i);else return T20B(rand_int());};
    return std::map<std::string,generator_t>{
	{"random  ", random},
	{"sorted  ", sorted},
	{"sorted90", sorted90},
	{"sorted99", sorted99}
    };
}

std::map<std::string,std::function<T128B()>> make_generators_T128B()
{
    using generator_t = std::function<T128B()>;
    auto rand_int = std::bind(std::uniform_int_distribution<int>(),std::default_random_engine());
    auto random = [rand_int]()mutable{ return T128B(rand_int());};
    auto sorted = [i=0]()mutable{return T128B(++i);};
    auto sorted90 = [i=0,rand_int]()mutable{if(++i%10)return T128B(i);else return T128B(rand_int());};
    auto sorted99 = [i=0,rand_int]()mutable{if(++i%100)return T128B(i);else return T128B(rand_int());};
    return std::map<std::string,generator_t>{
	{"random  ", random},
	{"sorted  ", sorted},
	{"sorted90", sorted90},
	{"sorted99", sorted99}
    };
}

void print_test_summary(std::ostream& out,std::vector<PerformanceTesterBase::result_t> results)
{
    using row_t = PerformanceTesterBase::result_row_t;
    auto get_name = [](row_t arg){return arg.first;};
    auto get_times = [](row_t arg){return arg.second;};
    using cell_t = PerformanceTesterBase::result_cell_t;
    auto get_datasize = [](cell_t arg){return arg.first;};
    auto get_runtime = [](cell_t arg){return arg.second;};

    size_t max_name_length = 0;
    for( auto result : results )
    {
	auto longest_name = std::max_element(result.begin(), result.end(), [](row_t& v1, row_t& v2){ return v1.first.length() < v2.first.length(); });
	max_name_length = std::max(get_name(*longest_name).length(), max_name_length);
    }
    out<<"\n--------------------------------------------\n\n";
    for(auto result : results)
    {
	out << std::setw(max_name_length) << "Results in µs";
	for( auto cell : get_times(*result.begin()) )
	    out << std::setw(13) << get_datasize(cell);
	out<<'\n';
	for ( auto row : result)
	{
	    out << std::setw(max_name_length) << get_name(row) << ':';
	    for ( auto cell : get_times(row) )
		out << std::setw(13) << get_runtime(cell);
	    out << "\n";
	}
    }
}
