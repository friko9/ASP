#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct treeset_array_test_find_compare_with_stdtreeset
	: public treeset_array_test_case
    {
	test_result test()
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
    };
    
    struct empty_find_all_vals_return_end
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_c_v0_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = { {1,0} };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_v0_find_compare_with_stdtreeset);

    struct populated_c_vmin_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = { {1,std::numeric_limits<elem_t>::min()} };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_vmin_find_compare_with_stdtreeset);

    struct populated_c_vmax_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = { {1,std::numeric_limits<elem_t>::max()} };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_vmax_find_compare_with_stdtreeset);

    struct populated_rmr_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 1024;
		data = {{1,10},{3,20},{7,30},{15,40},{31,50},{63,60},{127,70},{255,80},{511,90},{1023,100}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_find_compare_with_stdtreeset);

    struct populated_lml_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 1024;
		data = {{1,-10},{2,-20},{4,-30},{8,-40},{16,-50},{32,-60},{64,-70},{128,-80},{256,-90},{512,-100}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_lml_find_compare_with_stdtreeset);

    struct populated_c_l_ll_llr_llrr_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,120},{2,100},{4,0},{9,50},{19,70}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_llr_llrr_find_compare_with_stdtreeset);

    struct populated_c_r_rr_rrl_rrll_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,-120},{3,-100},{7,0},{14,-50},{28,-70}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rr_rrl_rrll_find_compare_with_stdtreeset);

    struct populated_c_l_r_ll_lr_lll_llr_llll_lllr_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-50},{3,50},{4,-80},{5,-30},{8,-100},{9,-60},{16,-120},{17,-90}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lll_llr_llll_lllr_find_compare_with_stdtreeset);

    struct populated_c_l_r_rl_rr_rrl_rrr_rrrl_rrrr_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-50},{3,50},{6,30},{7,80},{14,60},{15,100},{30,90},{31,120}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rr_rrl_rrr_rrrl_rrrr_find_compare_with_stdtreeset);


    struct populated_c_l_r_ll_lr_rl_rr_find_compare_with_stdtreeset
	: public treeset_array_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-20},{3,20},{4,-30},{5,-10},{6,10},{7,30}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_rl_rr_find_compare_with_stdtreeset);
}
