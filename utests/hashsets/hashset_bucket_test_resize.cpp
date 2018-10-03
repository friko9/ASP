#include "hashset_bucket_test.h"

#include <algorithm>
#include <limits>
#include <cmath>

namespace test_hashset_bucket
{
    struct hashset_bucket_test_resize_up_compare_with_stdhashset : public hashset_bucket_test_case
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

    struct hashset_bucket_test_resize_down_compare_with_stdhashset : public hashset_bucket_test_case
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
    
    struct empty_resize_up_all_vals_return_empty : public hashset_bucket_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure(){ /*empty on creation*/ }
    };
    ENABLE_TEST(access_test_set(),empty_resize_up_all_vals_return_empty);

    struct empty_resize_down_all_vals_return_empty : public hashset_bucket_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure(){ /*empty on creation*/ }
    };
    ENABLE_TEST(access_test_set(),empty_resize_down_all_vals_return_empty);

    struct populated_inorder_resize_up_compare_with_stdhashset : public hashset_bucket_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		HashF_echo<elem_t> hash;
		testhashset.insert(std::numeric_limits<elem_t>::min());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testhashset.insert(i);
		testhashset.insert(0);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testhashset.insert(i);
		testhashset.insert(std::numeric_limits<elem_t>::max());	    
		auto& hashset = test_plug.get_vMap(container);
		auto& counter = test_plug.get_Counter(container);
		auto& hash_max = test_plug.get_hashMax(container);
		hashset.resize(128);
		counter = 0;
		hash_max = 127;
		for( auto x : testhashset )
		{
		    index_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_up_compare_with_stdhashset);
    
    struct populated_inorder_resize_down_compare_with_stdhashset : public hashset_bucket_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		HashF_echo<elem_t> hash;
		testhashset.insert(std::numeric_limits<elem_t>::min());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testhashset.insert(i);
		testhashset.insert(0);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testhashset.insert(i);
		testhashset.insert(std::numeric_limits<elem_t>::max());	    
		auto& hashset = test_plug.get_vMap(container);
		auto& counter = test_plug.get_Counter(container);
		auto& hash_max = test_plug.get_hashMax(container);
		hashset.resize(128);
		counter = 0;
		hash_max = 127;
		for( auto x : testhashset )
		{
		    index_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_resize_down_compare_with_stdhashset);

    struct populated_noorder_resize_up_compare_with_stdhashset : public hashset_bucket_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		HashF_echo<elem_t> hash;
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testhashset.insert(i);
		testhashset.insert(std::numeric_limits<elem_t>::min());
		testhashset.insert(0);
		testhashset.insert(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testhashset.insert(i);
		auto& hashset = test_plug.get_vMap(container);
		auto& counter = test_plug.get_Counter(container);
		auto& hash_max = test_plug.get_hashMax(container);
		hashset.resize(128);
		counter = 0;
		hash_max = 127;
		for( auto x : testhashset )
		{
		    index_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_up_compare_with_stdhashset);

    struct populated_noorder_resize_down_compare_with_stdhashset : public hashset_bucket_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		HashF_echo<elem_t> hash;
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testhashset.insert(i);
		testhashset.insert(std::numeric_limits<elem_t>::min());
		testhashset.insert(0);
		testhashset.insert(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testhashset.insert(i);
		auto& hashset = test_plug.get_vMap(container);
		auto& counter = test_plug.get_Counter(container);
		auto& hash_max = test_plug.get_hashMax(container);
		hashset.resize(128);
		counter = 0;
		hash_max = 127;
		for( auto x : testhashset )
		{
		    index_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_resize_down_compare_with_stdhashset);

    struct populated_revorder_resize_up_compare_with_stdhashset : public hashset_bucket_test_resize_up_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		HashF_echo<elem_t> hash;
		testhashset.insert(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::max()-1; i > 0; i-=7)
		    testhashset.insert(i);
		testhashset.insert(0);
		for( int i = -1; i > std::numeric_limits<elem_t>::min(); i-=3)
		    testhashset.insert(i);
		testhashset.insert(std::numeric_limits<elem_t>::min());
		auto& hashset = test_plug.get_vMap(container);
		auto& counter = test_plug.get_Counter(container);
		auto& hash_max = test_plug.get_hashMax(container);
		hashset.resize(128);
		counter = 0;
		hash_max = 127;
		for( auto x : testhashset )
		{
		    index_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_up_compare_with_stdhashset);

    struct populated_revorder_resize_down_compare_with_stdhashset : public hashset_bucket_test_resize_down_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		HashF_echo<elem_t> hash;
		testhashset.insert(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::max()-1; i > 0; i-=7)
		    testhashset.insert(i);
		testhashset.insert(0);
		for( int i = -1; i > std::numeric_limits<elem_t>::min(); i-=3)
		    testhashset.insert(i);
		testhashset.insert(std::numeric_limits<elem_t>::min());
		auto& hashset = test_plug.get_vMap(container);
		auto& counter = test_plug.get_Counter(container);
		auto& hash_max = test_plug.get_hashMax(container);
		hashset.resize(128);
		counter = 0;
		hash_max = 127;
		for( auto x : testhashset )
		{
		    index_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_resize_down_compare_with_stdhashset);
}
