#ifndef HASHSET_ARRAY_TEST_H
#define HASHSET_ARRAY_TEST_H

#include "includes/utils/utils.h"
#include "includes/asp_test/test_set.h"
#include "includes/asp_hashsets/hashset_array.h"

#include <functional>
#include <unordered_set>
#include <vector>

template<typename T,typename H,typename R>
struct TestPlug<hashset_array<T,H,R>>
{
    using hashset_t = hashset_array<T,H,R>;
    using index_t = typename hashset_t::index_t;
    using hash_t = typename hashset_t::hash_t;

    static constexpr index_t null = hashset_t::null;

    std::vector<T>& get_vals(hashset_t& arg) { return arg.vals; }
    std::vector<index_t>& get_vMap(hashset_t& arg) { return arg.v_map; }
    std::vector<index_t>& get_vCnt(hashset_t& arg) { return arg.v_cnt; }

    float& get_maxLoad(hashset_t& arg) { return arg.max_load; }
    index_t& get_hashMax(hashset_t& arg) { return arg.hash_max; }
    index_t& get_Counter(hashset_t& arg) { return arg.counter; }

    index_t find(hashset_t& arg, T x) { return arg.find(x); }
    void resize(hashset_t& arg,index_t s) { arg.resize(s); }
    void insert_hash(hashset_t& arg,index_t h) { arg.insert_hash(h); }
};

namespace test_hashset_array
{
    test_set& access_test_set();

    template <typename T>
    struct HashF_echo
    {
	int operator ()(T x) const { return int(x);}
    };

    template <typename T>
    struct RehashF_linear
    {
	int operator ()(T x,int h) const { return ++h;}
    };

    struct hashset_array_test_case : test_case
    {
    	using elem_t = int8_t;
	using container_t = hashset_array<elem_t,HashF_echo<elem_t>,RehashF_linear<elem_t>>;
	using TestPlug_t = TestPlug<container_t>;
	using index_t = typename TestPlug_t::index_t;
	using hash_t = typename TestPlug_t::hash_t;

	static constexpr index_t null = TestPlug_t::null;
	
	TestPlug_t test_plug;
	std::vector<elem_t> data;
	std::unordered_set<elem_t> testhashset;
	container_t container;
    public:
	template<typename It>
	static void compare_test_range( test_result& result,
					It first,
					It last,
					std::function<bool(It)> test_f )
	    {
		bool inc = first < last;
		do
		    if ( test_f(first) )
			++result;
		while ( first != last && (( inc && (++first,true)) || ( !inc && (--first,true))) );
	    }
    };    
}
#endif /*HASHSET_ARRAY_TEST_H*/
