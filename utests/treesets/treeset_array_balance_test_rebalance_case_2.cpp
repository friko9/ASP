#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balance
{
    struct treeset_array_balance_test_rebalance_case_2
	: public treeset_array_balance_test_case
    {
	index_t index;
	side_t side;
	std::vector<node_t> expected_values;
	std::vector<index_t> expected_indexes;
	std::vector<height_t> expected_heights;
	score_t compare(std::vector<node_t>& vals1,std::vector<index_t> &indexes1,std::vector<height_t> &heights1,
			std::vector<node_t>& vals2,std::vector<index_t> &indexes2,std::vector<height_t> &heights2)
	    {
		score_t score = indexes1.size() == indexes2.size();
		for(int i=0; i<indexes1.size(); ++i)
		{
		    bool indexes_null = indexes1[i] == null && indexes2[i] == null;
		    bool index1_ok = indexes1[i] < vals1.size();
		    bool index2_ok = indexes2[i] < vals2.size();
		    bool vals_equal = index1_ok && index2_ok && vals1[indexes1[i]] == vals2[indexes2[i]];
		    score += indexes_null || vals_equal;
		}
		for(int i=0; i<heights1.size(); ++i)
		    score += heights1[i] == heights2[i];
		return score;
	    }
	test_result test()
	    {
		test_plug.rebalance_case_2(container, index, side);
		bool index_size_match = test_plug.get_indexes(container).size() == expected_indexes.size();
		bool heights_size_match = test_plug.get_indexes(container).size() == expected_indexes.size();
		if( index_size_match && heights_size_match )
		    return compare(expected_values,
				   expected_indexes,
				   expected_heights,
				   test_plug.get_values(container),
				   test_plug.get_indexes(container),
				   test_plug.get_heights(container));
		else
		    return score_t(false);
	    }
    };

    struct treesize8_c_l_lr_rebalance_case_2_c_on_left_state_cxlr_lxll_rxc
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{5,-1,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_lr_rebalance_case_2_c_on_left_state_cxlr_lxll_rxc);

    struct treesize16_c_l_lr_rebalance_case_2_c_on_left_state_cxlr_lxll_rxc
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{5,-1,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_lr_rebalance_case_2_c_on_left_state_cxlr_lxll_rxc);

    struct treesize8_c_r_rl_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{3,2,2},{6,1,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_rl_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr);

    struct treesize16_c_r_rl_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{3,2,2},{6,1,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_rl_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr);

    struct treesize16_c_l_r_ll_lr_lrl_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rrxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,1},{5,-5,2},{10,-7,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_lr_lrl_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rrxr);

    struct treesize32_c_l_r_ll_lr_lrl_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rrxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,1},{5,-5,2},{10,-7,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_ll_lr_lrl_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rrxr);

    struct treesize16_c_l_r_ll_lr_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_rlxlrr_rrxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,1},{5,-5,2},{11,-3,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_lr_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_rlxlrr_rrxr);

    struct treesize32_c_l_r_ll_lr_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_rlxlrr_rrxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,1},{5,-5,2},{11,-3,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_ll_lr_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_rlxlrr_rrxr);

    struct treesize16_c_l_r_ll_lr_lrl_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rlxlrr_rrxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,1},{5,-5,2},{10,-7,1},{11,-3,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_lr_lrl_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rlxlrr_rrxr);

    struct treesize32_c_l_r_ll_lr_lrl_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rlxlrr_rrxr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,1},{5,-5,2},{10,-7,1},{11,-3,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_ll_lr_lrl_lrr_rebalance_case_2_c_on_left_state_cxlr_lxl_rxc_llxll_lrxlrl_rlxlrr_rrxr);

    struct treesize16_c_l_r_rl_rr_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_rlxrlr_rrxrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{13,7,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_rl_rr_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_rlxrlr_rrxrr);

    struct treesize32_c_l_r_rl_rr_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_rlxrlr_rrxrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{13,7,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_rl_rr_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_rlxrlr_rrxrr);

    struct treesize16_c_l_r_rl_rr_rll_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rrxrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{12,3,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_rl_rr_rll_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rrxrr);

    struct treesize32_c_l_r_rl_rr_rll_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rrxrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{12,3,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_rl_rr_rll_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rrxrr);

    struct treesize16_c_l_r_rl_rr_rll_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rlxrlr_rrxrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{12,3,1},{13,7,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_rl_rr_rll_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rlxrlr_rrxrr);

    struct treesize32_c_l_r_rl_rr_rll_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rlxrlr_rrxrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{12,3,1},{13,7,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_rl_rr_rll_rlr_rebalance_case_2_c_on_right_state_cxrl_lxc_rxr_llxl_lrxrll_rlxrlr_rrxrr);

    struct treesize16_c_l_ll_llr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{4,-20,2},{9,-15,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-15,2},{4,-20,1},{5,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_ll_llr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl);

    struct treesize32_c_l_ll_llr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{4,-20,2},{9,-15,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-15,2},{4,-20,1},{5,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_llr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl);

    struct treesize16_c_l_lr_lrl_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{5,-5,2},{10,-7,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-7,2},{4,-10,1},{5,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_lr_lrl_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr);

    struct treesize32_c_l_lr_lrl_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{5,-5,2},{10,-7,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-7,2},{4,-10,1},{5,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_lr_lrl_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr);
 
    struct treesize32_c_l_ll_lr_lll_llr_llrl_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrrxlr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{4,-20,3},{5,-5,1},{8,-30,1},{9,-15,2},{18,-17,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-15,3},{4,-20,2},{5,-10,2},{8,-30,1},{9,-17,1},{11,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lll_llr_llrl_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrrxlr);

    struct treesize64_c_l_ll_lr_lll_llr_llrl_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrrxlr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{4,-20,3},{5,-5,1},{8,-30,1},{9,-15,2},{18,-17,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-15,3},{4,-20,2},{5,-10,2},{8,-30,1},{9,-17,1},{11,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lll_llr_llrl_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrrxlr);

    struct treesize32_c_l_ll_lr_lll_llr_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_lrlxllrr_lrrxlr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{4,-20,3},{5,-5,1},{8,-30,1},{9,-15,2},{19,-13,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-15,3},{4,-20,2},{5,-10,2},{8,-30,1},{10,-13,1},{11,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lll_llr_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_lrlxllrr_lrrxlr);

    struct treesize64_c_l_ll_lr_lll_llr_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_lrlxllrr_lrrxlr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{4,-20,3},{5,-5,1},{8,-30,1},{9,-15,2},{19,-13,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-15,3},{4,-20,2},{5,-10,2},{8,-30,1},{10,-13,1},{11,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lll_llr_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_lrlxllrr_lrrxlr);

    struct treesize32_c_l_ll_lr_lll_llr_llrl_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrlxllrrr_lrr_lr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{4,-20,3},{5,-5,1},{8,-30,1},{9,-15,2},{18,-17,1},{19,-13,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-15,3},{4,-20,2},{5,-10,2},{8,-30,1},{9,-17,1},{10,-13,1},{11,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lll_llr_llrl_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrlxllrrr_lrr_lr);

    struct treesize64_c_l_ll_lr_lll_llr_llrl_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrlxllrrr_lrr_lr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{4,-20,3},{5,-5,1},{8,-30,1},{9,-15,2},{18,-17,1},{19,-13,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-15,3},{4,-20,2},{5,-10,2},{8,-30,1},{9,-17,1},{10,-13,1},{11,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lll_llr_llrl_llrr_rebalance_case_2_l_on_left_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrlxllrrr_lrr_lr);

    struct treesize32_c_l_ll_lr_lrl_lrr_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrlr_lrrxlrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{4,-20,1},{5,-5,3},{10,-7,2},{11,-3,1},{21,-6,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-7,3},{4,-10,2},{5,-5,2},{8,-20,1},{10,-6,1},{11,-3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lrl_lrr_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrlr_lrrxlrr);

    struct treesize64_c_l_ll_lr_lrl_lrr_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrlr_lrrxlrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{4,-20,1},{5,-5,3},{10,-7,2},{11,-3,1},{21,-6,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-7,3},{4,-10,2},{5,-5,2},{8,-20,1},{10,-6,1},{11,-3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lrl_lrr_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrlr_lrrxlrr);

    struct treesize32_c_l_ll_lr_lrl_lrr_lrll_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrrxlrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{4,-20,1},{5,-5,3},{10,-7,2},{11,-3,1},{20,-8,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-7,3},{4,-10,2},{5,-5,2},{8,-20,1},{9,-8,1},{11,-3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lrl_lrr_lrll_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrrxlrr);

    struct treesize64_c_l_ll_lr_lrl_lrr_lrll_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrrxlrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{4,-20,1},{5,-5,3},{10,-7,2},{11,-3,1},{20,-8,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-7,3},{4,-10,2},{5,-5,2},{8,-20,1},{9,-8,1},{11,-3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lrl_lrr_lrll_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrrxlrr);

    struct treesize32_c_l_ll_lr_lrl_lrr_lrll_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrlxlrlr_lrrxlrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{4,-20,1},{5,-5,3},{10,-7,2},{11,-3,1},{20,-8,1},{21,-6,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-7,3},{4,-10,2},{5,-5,2},{8,-20,1},{9,-8,1},{10,-6,1},{11,-3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lrl_lrr_lrll_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrlxlrlr_lrrxlrr);

    struct treesize64_c_l_ll_lr_lrl_lrr_lrll_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrlxlrlr_lrrxlrr
	: public treeset_array_balance_test_rebalance_case_2
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{4,-20,1},{5,-5,3},{10,-7,2},{11,-3,1},{20,-8,1},{21,-6,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-7,3},{4,-10,2},{5,-5,2},{8,-20,1},{9,-8,1},{10,-6,1},{11,-3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lrl_lrr_lrll_lrlr_rebalance_case_2_l_on_right_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrlxlrlr_lrrxlrr);
}
