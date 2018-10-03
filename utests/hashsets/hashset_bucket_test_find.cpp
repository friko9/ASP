#include "hashset_bucket_test.h"

#include <algorithm>
#include <limits>

namespace test_hashset_bucket
{
    struct hashset_bucket_test_find_compare_with_stdhashset
	: public hashset_bucket_test_case
    {
	index_t counter,hash_max,vmap_size;
	test_result test()
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
	virtual void setup_data() = 0;
	void configure()
	    {
		setup_data();
		auto& hashset = test_plug.get_vMap(container);
		test_plug.get_Counter(container) = counter;
		test_plug.get_hashMax(container) = hash_max;
		hashset.resize(vmap_size);
		for( auto x : data )
		{
		    hash_t hash = HashF_echo<elem_t>()(x);
		    hashset.at(hash%hash_max).push_front(x);
		    testhashset.insert(x);
		}
	    }
    };
    
    struct empty_find_all_vals_return_end
	: public hashset_bucket_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure(){}
	void setup_data(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_inorder_find_compare_with_stdhashset
	: public hashset_bucket_test_find_compare_with_stdhashset
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
		counter   = 0;
		hash_max  = 127;
		vmap_size = 128;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_find_compare_with_stdhashset);

    struct populated_noorder_find_compare_with_stdhashset
	: public hashset_bucket_test_find_compare_with_stdhashset
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
		counter   = 0;
		hash_max  = 127;
		vmap_size = 128;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_find_compare_with_stdhashset);

    struct populated_revorder_find_compare_with_stdhashset
	: public hashset_bucket_test_find_compare_with_stdhashset
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
		counter   = 0;
		hash_max  = 127;
		vmap_size = 128;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_find_compare_with_stdhashset);
}
