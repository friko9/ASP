#include "hashset_bucket_test.h"

#include <algorithm>
#include <limits>

namespace test_hashset_bucket
{
    struct hashset_bucket_test_find_compare_with_stdhashset : public hashset_bucket_test_case
    {
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()+1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
				    std::numeric_limits<elem_t>::min(),
				    std::numeric_limits<elem_t>::max(),
				    [this,&failed_list](elem_t el) -> bool {
						auto vmap = this->test_plug.get_vMap(container);
						auto find_res = vmap.at(test_plug.find(container, el));
						bool cmp_contains = this->testhashset.count(el) != 0;
						bool contains = std::find(find_res.begin(),find_res.end(),el) != find_res.end();
						if( cmp_contains ^ contains )
						{
						    failed_list->add_failed(el);
						    return false;
						}
						return true;
					    });
		return result;
	    }
    };
    
    struct empty_find_all_vals_return_end : public hashset_bucket_test_case
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()+1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    std::numeric_limits<elem_t>::min(),
					    std::numeric_limits<elem_t>::max(),
					    [this,&failed_list](elem_t el) -> bool {
						auto vmap = this->test_plug.get_vMap(container);
						auto find_res = vmap.at(test_plug.find(container,el));
						bool result = std::find(find_res.begin(),find_res.end(),el) == find_res.end();
						if( !result )
						    failed_list->add_failed(el);
						return result;
					    });
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_inorder_find_compare_with_stdhashset : public hashset_bucket_test_find_compare_with_stdhashset
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
		    hash_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_find_compare_with_stdhashset);

    struct populated_noorder_find_compare_with_stdhashset : public hashset_bucket_test_find_compare_with_stdhashset
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
		    hash_t h = hash(x);
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_find_compare_with_stdhashset);

    struct populated_revorder_find_compare_with_stdhashset : public hashset_bucket_test_find_compare_with_stdhashset
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
		    hash_t h = hash(x);    
		    hashset.at(h%hash_max).push_front(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_find_compare_with_stdhashset);
}
