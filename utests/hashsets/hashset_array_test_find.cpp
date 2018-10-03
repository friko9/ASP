#include "hashset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_hashset_array
{
    struct hashset_array_test_find_compare_with_stdhashset : public hashset_array_test_case
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
						auto vals = this->test_plug.get_vals(container);
						auto find_res = this->test_plug.find(container, el);
						bool cmp_contains = this->testhashset.count(el) != 0;
						bool contains = find_res != null && vals.at(vmap.at(find_res)) == el;
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
    
    struct empty_find_all_vals_return_end : public hashset_array_test_case
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
						bool result = test_plug.find(container,el) == null;
						if( !result )
						    failed_list->add_failed(el);
						return result;
					    });
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_full_norehash_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 1, 2, 3, 4, 5, 6, 7 };
		std::vector<index_t> vmap = { 6, 0, 1, 2, 3, 4, 5 };
		std::vector<index_t> cntr = { 1, 1, 1, 1, 1, 1, 1 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 0;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;

		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_full_norehash_find_compare_with_stdhashset);

    struct populated_half_norehash_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 1, 3, 5, 7 };
		std::vector<index_t> vmap = { 3, 0,null, 1,null, 2,null,null };
		std::vector<index_t> cntr = { 1, 1, 0, 1, 0, 1, 0, 0 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_norehash_find_compare_with_stdhashset);

    struct populated_full_rehash_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 0, 2, 3, 4, 7, 8, 9 };
		std::vector<index_t> vmap = { 0, 4, 1, 2, 3, 5, 6 };
		std::vector<index_t> cntr = { 2, 1, 2, 1, 1, 0, 0 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 0;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;

		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_full_rehash_find_compare_with_stdhashset);

    struct populated_half_rehash_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 0, 14, 2, 7 };
		std::vector<index_t> vmap = { 0, 1, 2, 3,null,null,null,null };
		std::vector<index_t> cntr = { 3, 0, 1, 0, 0, 0, 0, 0 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_rehash_find_compare_with_stdhashset);

    struct populated_noorder_rehashed_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 0, 14, 7, 1 };
		std::vector<index_t> vmap = { 0, 1, 2, 3,null,null,null,null };
		std::vector<index_t> cntr = { 3, 1, 0, 0, 0, 0, 0, 0 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_rehashed_find_compare_with_stdhashset);

    struct populated_half_rehash_wind_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 13, 6, 2, 20 };
		std::vector<index_t> vmap = {null,1,2, 3,null,null, 0,null };
		std::vector<index_t> cntr = { 0, 0, 1, 0, 0, 0, 3, 0 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_rehash_wind_find_compare_with_stdhashset);

    struct populated_half_rehash_nullseparated_find_compare_with_stdhashset : public hashset_array_test_find_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> vals = { 13, 6, 2, 20 };
		std::vector<index_t> vmap = { 2,1,null,3,null,null, 0,null};
		std::vector<index_t> cntr = { 0, 0, 1, 0, 0, 0, 3, 0 };

		test_plug.get_vCnt(container) = cntr;
		test_plug.get_vals(container) = vals;
		test_plug.get_vMap(container) = vmap;
		
		test_plug.get_Counter(container) = 4;
		test_plug.get_hashMax(container) = 7;
		test_plug.get_maxLoad(container) = 1.0f;
		
		for( auto x : vals )
		    testhashset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_half_rehash_nullseparated_find_compare_with_stdhashset);
}
