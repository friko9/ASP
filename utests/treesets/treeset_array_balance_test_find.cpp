#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balance
{
    struct treeset_array_balance_test_find_compare_with_stdtreeset : public treeset_array_balance_test_case
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
						auto find_res = test_plug.find(container, el);
						auto vals = test_plug.get_values(container);
						auto indexes = test_plug.get_indexes(container);
						bool cmp_contains = this->testtreeset.count(el) != 0;
						bool found = find_res < indexes.size() && indexes[find_res] != null;
						bool contains =  found && vals[indexes[find_res]].first == el ;
						if( cmp_contains ^ contains )
						{
						    failed_list->add_failed(el);
						    return false;
						}
						return true;
					    });
		return result;
	    }
	void configure()
	    {
		setup_data();
		std::tie(test_plug.get_values(container),
			 test_plug.get_indexes(container),
			 test_plug.get_heights(container))
		    = make_data(tree_size,data);
	    }
    };
    
    struct empty_find_all_vals_return_end : public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	void configure(){}
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()+1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    std::numeric_limits<elem_t>::min(),
					    std::numeric_limits<elem_t>::max(),
					    [this,&failed_list](elem_t el) -> bool {
						auto find_res = test_plug.find(container, el);
						auto indexes = test_plug.get_indexes(container);
						bool result = find_res >= indexes.size() || indexes[find_res] == null;
						if( !result )
						    failed_list->add_failed(el);
						return result;
					    });
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_c_v0_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = { {1,0,1} };
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_v0_find_compare_with_stdtreeset);

    struct populated_c_vmin_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = { {1,std::numeric_limits<elem_t>::min(),1} };
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_vmin_find_compare_with_stdtreeset);

    struct populated_c_vmax_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = { {1,std::numeric_limits<elem_t>::max(),1} };
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_vmax_find_compare_with_stdtreeset);

    struct populated_rmr_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 1024;
		data = {{1,10,10},{3,20,9},{7,30,8},{15,40,7},{31,50,6},{63,60,5}
			,{127,70,4},{255,80,3},{511,90,2},{1023,100,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_find_compare_with_stdtreeset);

    struct populated_lml_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 1024;
		data = {{1,-10,10},{2,-20,9},{4,-30,8},{8,-40,7},{16,-50,6},{32,-60,5}
			,{64,-70,4},{128,-80,3},{256,-90,2},{512,-100,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lml_find_compare_with_stdtreeset);

    struct populated_c_l_ll_llr_llrr_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,120,5},{2,100,4},{4,0,3},{9,50,2},{19,70,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_llr_llrr_find_compare_with_stdtreeset);

    struct populated_c_r_rr_rrl_rrll_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,-120,5},{3,-100,4},{7,0,3},{14,-50,2},{28,-70,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rr_rrl_rrll_find_compare_with_stdtreeset);

    struct populated_c_l_r_ll_lr_lll_llr_llll_lllr_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5}
			,{2,-50,4},{3,50,1}
			,{4,-80,3},{5,-30,1}
			,{8,-100,2},{9,-60,1}
			,{16,-120,1},{17,-90,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lll_llr_llll_lllr_find_compare_with_stdtreeset);

    struct populated_c_l_r_rl_rr_rrl_rrr_rrrl_rrrr_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5}
			,{2,-50,1},{3,50,4}
			,{6,30,1},{7,80,3}
			,{14,60,1},{15,100,2}
			,{30,90,1},{31,120,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rr_rrl_rrr_rrrl_rrrr_find_compare_with_stdtreeset);


    struct populated_c_l_r_ll_lr_rl_rr_find_compare_with_stdtreeset
	: public treeset_array_balance_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,3}
			,{2,-20,2},{3,20,2}
			,{4,-30,1},{5,-10,1},{6,10,1},{7,30,1}};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_rl_rr_find_compare_with_stdtreeset);
}
