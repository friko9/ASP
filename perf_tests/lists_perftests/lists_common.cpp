#include "./lists_common.h"

#include <iomanip>
#include <random>

std::vector<size_t> dataset_sizes = { 10,20,30,50,100, 1000, 10000 };


std::map<std::string,std::function<int()>> make_generators_int()
{
    using generator_t = std::function<int()>;
    auto upward = [i=std::numeric_limits<int>::min()]()mutable{return ++i;};
    auto downward = [i=std::numeric_limits<int>::max()]()mutable{ return --i; };
    auto random = std::bind(std::uniform_int_distribution<int>(),std::default_random_engine());
    return std::map<std::string,generator_t>{
	{"upward__", upward},
	{"downward", downward},
	{"random__", random}
    };
}
std::map<std::string,std::function<double()>> make_generators_double()
{
    using generator_t = std::function<double()>;
    auto upward = [d=0.0l]()mutable{return d+=1.01l;};
    auto downward = [d=0.0l]()mutable{return d-=1.01l;};
    auto random = std::bind(std::uniform_real_distribution<double>(-1e6,1e6),std::default_random_engine());
    return std::map<std::string,generator_t>{
	{"upward__", upward},
	{"downward", downward},
	{"random__", random}
    };
}
std::map<std::string,std::function<T20B()>> make_generators_T20B()
{
    using generator_t = std::function<T20B()>;
    auto upward = [i=std::numeric_limits<int>::min()]()mutable{return T20B(++i);};
    auto downward = [i=std::numeric_limits<int>::max()]()mutable{ return T20B(--i); };
    auto random_int = std::bind(std::uniform_int_distribution<int>(),std::default_random_engine());
    auto random = [random_int]()mutable{ return T20B(random_int());};
    return std::map<std::string,generator_t>{
	{"upward__", upward},
	{"downward", downward},
	{"random__", random}
    };
}

std::map<std::string,std::function<T128B()>> make_generators_T128B()
{
    using generator_t = std::function<T128B()>;
    auto upward = [i=std::numeric_limits<int>::min()]()mutable{return T128B(++i);};
    auto downward = [i=std::numeric_limits<int>::max()]()mutable{ return T128B(--i); };
    auto random_int = std::bind(std::uniform_int_distribution<int>(),std::default_random_engine());
    auto random = [random_int]()mutable{ return T128B(random_int());};
    return std::map<std::string,generator_t>{
	{"upward__", upward},
	{"downward", downward},
	{"random__", random}
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
