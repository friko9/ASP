#include "hashset_bucket_test.h"

#include <algorithm>
#include <limits>
#include <cmath>

namespace test_hashset_bucket
{
    struct hashset_bucket_test_resize_compare_with_stdhashset
	: public hashset_bucket_test_case
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
					    [this,&failed_list](index_t size) -> bool {
						
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
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		size_start = 1;
		size_end = 1024;
	    }
	void setup_data(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_resize_up_all_vals_return_empty);

    struct empty_resize_down_all_vals_return_empty
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		size_start = 1024;
		size_end = 1;
	    }
	void setup_data(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_resize_down_all_vals_return_empty);

    struct populated_inorder_resize_up_compare_with_stdhashset
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    data.push_back(i);
		data.push_back(0);
		for( elem_t i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		size_start = 1;
		size_end = 1024;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_up_compare_with_stdhashset);
    
    struct populated_inorder_resize_down_compare_with_stdhashset
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::min());
		for( elem_t i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    data.push_back(i);
		data.push_back(0);
		for( elem_t i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		size_start = 1024;
		size_end = 1;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_down_compare_with_stdhashset);

    struct populated_noorder_resize_up_compare_with_stdhashset
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( elem_t i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
		data.push_back(0);
		data.push_back(std::numeric_limits<elem_t>::max());
		for( elem_t i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    data.push_back(i);
		size_start = 1;
		size_end = 1024;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_up_compare_with_stdhashset);

    struct populated_noorder_resize_down_compare_with_stdhashset
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( elem_t i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
		data.push_back(0);
		data.push_back(std::numeric_limits<elem_t>::max());
		for( elem_t i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    data.push_back(i);
		size_start = 1024;
		size_end = 1;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_down_compare_with_stdhashset);

    struct populated_revorder_resize_up_compare_with_stdhashset
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::max());
		for( elem_t i = std::numeric_limits<elem_t>::max()-1; i > 0; i-=7)
		    data.push_back(i);
		data.push_back(0);
		for( elem_t i = -1; i > std::numeric_limits<elem_t>::min(); i-=3)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
		size_start = 1;
		size_end = 1024;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_up_compare_with_stdhashset);

    struct populated_revorder_resize_down_compare_with_stdhashset
	: public hashset_bucket_test_resize_compare_with_stdhashset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data.push_back(std::numeric_limits<elem_t>::max());
		for( elem_t i = std::numeric_limits<elem_t>::max()-1; i > 0; i-=7)
		    data.push_back(i);
		data.push_back(0);
		for( elem_t i = -1; i > std::numeric_limits<elem_t>::min(); i-=3)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
		size_start = 1024;
		size_end = 1;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_down_compare_with_stdhashset);
}
