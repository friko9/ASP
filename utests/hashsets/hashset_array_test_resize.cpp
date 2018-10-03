#include "hashset_array_test.h"

#include <algorithm>
#include <limits>
#include <cmath>

namespace test_hashset_array
{
    struct hashset_array_test_resize_compare_with_stdhashset
	: public hashset_array_test_case
    {
	size_t size_start, size_end;
	test_result test()
	    {
		test_result result = (size_end > size_start)? size_end-size_start+1 : size_start-size_end+1;;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<size_t>( result,
					    size_start,
					    size_end,
					    [this,&failed_list](size_t size) -> bool {
						
						test_plug.resize(container,size);

						 if( test_plug.get_vMap(container).size() < size )
						     return false;
						auto hash_max = test_plug.get_hashMax(container);
						 for( int i =2; i < std::sqrt(hash_max)+1; ++i)
						     if( hash_max%i == 0 ) return false;
						for( int i = std::numeric_limits<elem_t>::min(); i< std::numeric_limits<elem_t>::max(); ++i)
						{
						    bool cmp_result = this->testhashset.count(i) != 0;
						    bool result = this->container.contains(i);
						    if( cmp_result ^ result )
						    {
							failed_list->add_failed(i);
							return false;
						    }
						}
						return true;
					    });
		return result;
	    }
	virtual void setup_data() = 0;
	void configure()
	    {
		setup_data();
		for( auto x : data )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    
    struct empty_resize_up_all_vals_return_empty
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		size_start = 0;
		size_end = 32;
	    }
	void setup_data(){}
	test_result run(){ return test(); }
	
    };
    ENABLE_TEST(access_test_set(),empty_resize_up_all_vals_return_empty);

    struct empty_resize_down_all_vals_return_empty
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		size_start = 32;
		size_end = 0;
	    }
	void setup_data(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_resize_down_all_vals_return_empty);

    struct populated_inorder_resize_up_compare_with_stdhashset
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t val =data.back(), i =1; data.back() <= val; val +=i, ++i )
		    data.push_back(val);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		size_start = primes[floor_log2(data.size())+1]+1;
		size_end = data.size()*32;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_up_compare_with_stdhashset);
    
    struct populated_inorder_resize_down_compare_with_stdhashset
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t val =data.back(), i =1; data.back() <= val; val +=i, ++i )
		    data.push_back(val);
		data.push_back(std::numeric_limits<elem_t>::max());

		size_start = data.size()*32;
		size_end = primes[floor_log2(data.size())+1]+1;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_down_compare_with_stdhashset);

    struct populated_noorder_resize_up_compare_with_stdhashset
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t val =data.back(), i =1; data.back() <= val; val +=i, ++i )
		    data.push_back(val);
		data.push_back(std::numeric_limits<elem_t>::max());
		random_shuffle(data.begin(),data.end());

		size_start = primes[floor_log2(data.size())+1]+1;
		size_end = data.size()*32;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_up_compare_with_stdhashset);

    struct populated_noorder_resize_down_compare_with_stdhashset
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t val =data.back(), i =1; data.back() <= val; val +=i, ++i )
		    data.push_back(val);
		data.push_back(std::numeric_limits<elem_t>::max());
		random_shuffle(data.begin(),data.end());

		size_start = data.size()*32;
		size_end = primes[floor_log2(data.size())+1]+1;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_down_compare_with_stdhashset);

    struct populated_revorder_resize_up_compare_with_stdhashset
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t val =data.back(), i =1; data.back() <= val; val +=i, ++i )
		    data.push_back(val);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::reverse(data.begin(), data.end());

		size_start = primes[floor_log2(data.size())+1]+1;
		size_end = data.size()*32;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_up_compare_with_stdhashset);

    struct populated_revorder_resize_down_compare_with_stdhashset
	: public hashset_array_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t val =data.back(), i =1; data.back() <= val; val +=i, ++i )
		    data.push_back(val);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::reverse(data.begin(), data.end());

		size_start = data.size()*32;
		size_end = primes[floor_log2(data.size())+1]+1;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_down_compare_with_stdhashset);
}
