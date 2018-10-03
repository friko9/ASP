#include "hashset_array_test.h"

#include <algorithm>
#include <limits>
#include <cmath>

namespace test_hashset_array
{
    struct hashset_array_test_resize_up_compare_with_stdhashset : public hashset_array_test_case
    {
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max();
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    1,
					    std::numeric_limits<elem_t>::max(),
					    [this,&failed_list](elem_t size) -> bool {
						
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
    };

    struct hashset_array_test_resize_down_compare_with_stdhashset : public hashset_array_test_case
    {
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max();
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    std::numeric_limits<elem_t>::max(),
					    1,
					    [this,&failed_list](elem_t size) -> bool {
						
						test_plug.resize(container,size);

						if( test_plug.get_vMap(container).size() < size )
						    return false;
						auto hash_max = test_plug.get_hashMax(container);
						for( int i =2; i < std::sqrt(hash_max)+1; ++i)
						    if( hash_max%i == 0 ) return false;
						for( int el = std::numeric_limits<elem_t>::min(); el< std::numeric_limits<elem_t>::max(); ++el)
						{
						    bool cmp_result = this->testhashset.count(el) != 0;
						    bool result = this->container.contains(el);
						    if( cmp_result ^ result )
						    {
							failed_list->add_failed(el);
							return false;
						    }
						}
						return true;
					    });
		return result;
	    }
    };
    
    struct empty_resize_up_all_vals_return_empty : public hashset_array_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure(){ /*empty on creation*/ }
    };
    ENABLE_TEST(access_test_set(),empty_resize_up_all_vals_return_empty);

    struct empty_resize_down_all_vals_return_empty : public hashset_array_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure(){ /*empty on creation*/ }
    };
    ENABLE_TEST(access_test_set(),empty_resize_down_all_vals_return_empty);

    struct populated_inorder_resize_up_compare_with_stdhashset : public hashset_array_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());	    

		for( auto x : testhashset )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_up_compare_with_stdhashset);
    
    struct populated_inorder_resize_down_compare_with_stdhashset : public hashset_array_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());	    

		for( auto x : testhashset )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_down_compare_with_stdhashset);

    struct populated_noorder_resize_up_compare_with_stdhashset : public hashset_array_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());	    

		std::random_shuffle(data.begin(), data.end());
		for( auto x : testhashset )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_up_compare_with_stdhashset);

    struct populated_noorder_resize_down_compare_with_stdhashset : public hashset_array_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());	    

		std::random_shuffle(data.begin(), data.end());
		for( auto x : testhashset )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_down_compare_with_stdhashset);

    struct populated_revorder_resize_up_compare_with_stdhashset : public hashset_array_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());	    

		std::reverse(data.begin(), data.end());
		for( auto x : testhashset )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_up_compare_with_stdhashset);

    struct populated_revorder_resize_down_compare_with_stdhashset : public hashset_array_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());	    

		std::reverse(data.begin(), data.end());
		for( auto x : testhashset )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_down_compare_with_stdhashset);
}
