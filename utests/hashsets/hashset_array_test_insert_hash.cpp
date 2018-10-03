#include "hashset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_hashset_array
{
    struct hashset_array_test_insert_hash_compare_with_stdhashset : public hashset_array_test_case
    {
	std::vector<index_t> vmap;
	std::vector<index_t> cntr;
	test_result run()
	    {
		test_result result = 8;
		auto failed_list = std::make_shared<single_failed_list<std::pair<size_t,std::pair<index_t,index_t>>>>();
		result.set_failed( failed_list );

		for( int i = 0; i < data.size(); ++i)
		    test_plug.insert_hash(container,i);
		
		compare_test_range<size_t>( result,
					    0,
					    7,
					    [this,&failed_list](size_t i) -> bool {
						auto vmap_res = test_plug.get_vMap(container).at(i);
						auto cntr_res = test_plug.get_vCnt(container).at(i);
						if( !(vmap_res == vmap[i] && cntr_res == cntr[i]) )
						{
						    failed_list->add_failed(std::make_pair(i,std::make_pair(vmap_res,cntr_res)));
						    return false;
						}
						return true;
					    });
		return result;
	    }
    };

    struct populated_full_norehash_insert_hash_compare_with_stdhashset : public hashset_array_test_insert_hash_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 4, 5, 6, 7 };
		vmap = { 6, 0, 1, 2, 3, 4, 5, null };
		cntr = { 1, 1, 1, 1, 1, 1, 1, 0 };

		test_plug.get_vals(container) = data;
		test_plug.get_vCnt(container) = {0,0,0,0,0,0,0,0};
		test_plug.get_vMap(container) = {null,null,null,null,null,null,null,null};

		test_plug.get_Counter(container) = 0;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_full_norehash_insert_hash_compare_with_stdhashset);

    struct populated_half_norehash_insert_hash_compare_with_stdhashset : public hashset_array_test_insert_hash_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 3, 5, 7 };
		vmap = { 3, 0,null, 1,null, 2,null,null };
		cntr = { 1, 1, 0, 1, 0, 1, 0, 0 };

		test_plug.get_vals(container) = data;
		test_plug.get_vCnt(container) = {0,0,0,0,0,0,0,0};
		test_plug.get_vMap(container) = {null,null,null,null,null,null,null,null};
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : data )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_norehash_insert_hash_compare_with_stdhashset);

    struct populated_full_rehash_insert_hash_compare_with_stdhashset : public hashset_array_test_insert_hash_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 2, 3, 4, 7, 8, 9 };
		vmap = { 0, 4, 1, 2, 3, 5, 6, null };
		cntr = { 2, 1, 2, 1, 1, 0, 0, 0 };

		test_plug.get_vals(container) = data;
		test_plug.get_vCnt(container) = {0,0,0,0,0,0,0,0};
		test_plug.get_vMap(container) = {null,null,null,null,null,null,null,null};
		
		test_plug.get_Counter(container) = 0;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;

		for( auto x : data )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_full_rehash_insert_hash_compare_with_stdhashset);

    struct populated_half_rehash_insert_hash_compare_with_stdhashset : public hashset_array_test_insert_hash_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 14, 2, 7 };
		vmap = { 0, 1, 2, 3,null,null,null,null };
		cntr = { 3, 0, 1, 0, 0, 0, 0, 0 };

		test_plug.get_vals(container) = data;
		test_plug.get_vCnt(container) = {0,0,0,0,0,0,0,0};
		test_plug.get_vMap(container) = {null,null,null,null,null,null,null,null};
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : data )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_rehash_insert_hash_compare_with_stdhashset);

    struct populated_noorder_rehashed_insert_hash_compare_with_stdhashset : public hashset_array_test_insert_hash_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 14, 7, 1 };
		vmap = { 0, 1, 2, 3,null,null,null,null };
		cntr = { 3, 1, 0, 0, 0, 0, 0, 0 };

		test_plug.get_vals(container) = data;
		test_plug.get_vCnt(container) = {0,0,0,0,0,0,0,0};
		test_plug.get_vMap(container) = {null,null,null,null,null,null,null,null};
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : data )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_rehashed_insert_hash_compare_with_stdhashset);

    struct populated_half_rehash_wind_insert_hash_compare_with_stdhashset : public hashset_array_test_insert_hash_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 13, 6, 2, 20 };
		vmap = {1, 3, 2,null,null,null, 0,null };
		cntr = { 0, 0, 1, 0, 0, 0, 3, 0 };

		test_plug.get_vals(container) = data;
		test_plug.get_vCnt(container) = {0,0,0,0,0,0,0,0};
		test_plug.get_vMap(container) = {null,null,null,null,null,null,null,null};
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : data )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_rehash_wind_insert_hash_compare_with_stdhashset);
}
