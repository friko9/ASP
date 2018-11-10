#include "utils_common.h"

#include <iomanip>
#include <random>

std::map<std::string,std::function<int()>> make_generators_int()
{
    using generator_t = std::function<int()>;
    auto vals_lt_100 = [i=0]()mutable{return i = ++i%100;};
    auto vals_gt_1mld = [i=1000000000]()mutable{return ++i;};
    return std::map<std::string,generator_t>{
	{"vals_lt_100 ", vals_lt_100},
	{"vals_gt_1mld", vals_gt_1mld}
    };
}

std::map<std::string,std::function<uint32_t()>> make_generators_uint32t()
{
    uint32_t i =0;    
    using generator_t = std::function<uint32_t()>;
    auto vals_lt_100 = [i]()mutable{return i = ++i%100;};
    auto vals_gt_1mld = [i=1000000000]()mutable{return ++i;};
    return std::map<std::string,generator_t>{
	{"vals_lt100  ", vals_lt_100},
	{"vals_gt_1mld", vals_gt_1mld}
    };
}

std::map<std::string,std::function<double()>> make_generators_double()
{
    using generator_t = std::function<double()>;
    auto vals_lt_100 = [d=0.0]()mutable{return d = std::fmod(d+1.01,100.0);};
    auto vals_gt_1mld = [d=1e9]()mutable{return d+=1.01;};
    return std::map<std::string,generator_t>{
	{"vals_lt_100  ", vals_lt_100},
	{"vals_gt_1mld", vals_gt_1mld}
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
