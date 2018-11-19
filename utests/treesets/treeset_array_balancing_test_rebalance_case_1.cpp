#include "treeset_array_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balancing
{
    struct treeset_array_balancing_test_rebalance_case_1
	: public treeset_array_balancing_test_case
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
		test_plug.rebalance_case_1(container, index, side);
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
	void configure()
	    {
		setup_data();
		std::tie(test_plug.get_values(container),
			 test_plug.get_indexes(container),
			 test_plug.get_heights(container))
		    = make_data(tree_size,data);
	    }
    };

    struct treesize8_c_l_ll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{4,-2,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_ll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc);

    struct treesize16_c_l_ll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-1,2},{4,-2,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_ll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc);

    struct treesize8_c_r_rr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{3,1,2},{7,2,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_rr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr);

    struct treesize16_c_r_rr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{3,1,2},{7,2,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_rr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr);
    
    struct treesize16_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr
    	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,2},{5,-5,1},{8,-30,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-10,3},{2,-20,2},{3,0,2},{4,-30,1},{6,-5,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr);

    struct treesize32_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr
    	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,2},{5,-5,1},{8,-30,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-10,3},{2,-20,2},{3,0,2},{4,-30,1},{6,-5,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr);

    struct treesize16_c_l_r_rr_rl_rrr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr_llxl_lrxrl_rrxrrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,1},{7,20,2},{15,30,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,10,3},{2,0,2},{3,20,2},{4,-10,1},{5,5,1},{7,30,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_rr_rl_rrr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr_llxl_lrxrl_rrxrrr);

    struct treesize32_c_l_r_rr_rl_rrr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr_llxl_lrxrl_rrxrrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,1},{7,20,2},{15,30,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,10,3},{2,0,2},{3,20,2},{4,-10,1},{5,5,1},{7,30,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_rr_rl_rrr_rebalance_case_1_c_on_right_state_cxr_lxc_rxrr_llxl_lrxrl_rrxrrr);

    struct treesize16_c_l_ll_lll_rebalance_case_1_l_on_left_state_cxc_lxll_lrxl_llxlll
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{4,-20,2},{8,-30,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-20,2},{4,-30,1},{5,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_ll_lll_rebalance_case_1_l_on_left_state_cxc_lxll_lrxl_llxlll);

    struct treesize32_c_l_ll_lll_rebalance_case_1_l_on_left_state_cxc_lxll_lrxl_llxlll
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-10,3},{4,-20,2},{8,-30,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-20,2},{4,-30,1},{5,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lll_rebalance_case_1_l_on_left_state_cxc_lxll_lrxl_llxlll);

    struct treesize16_c_l_lr_lrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-20,3},{5,-10,2},{11,-5,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-10,2},{4,-20,1},{5,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_lr_lrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr);

    struct treesize32_c_l_lr_lrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-20,3},{5,-10,2},{11,-5,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,4},{2,-10,2},{4,-20,1},{5,-5,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_lr_lrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr);

    struct treesize32_c_l_ll_lr_lll_llr_llll_rebalance_case_1_l_on_left_state_cxc_lxll_llxlll_lrxl_lllxllll_lrlxllr_lrrxlr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-20,4},{4,-30,3},{5,-10,1},{8,-40,2},{9,-25,1},{16,-50,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-30,3},{4,-40,2},{5,-20,2},{8,-50,1},{10,-25,1},{11,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lll_llr_llll_rebalance_case_1_l_on_left_state_cxc_lxll_llxlll_lrxl_lllxllll_lrlxllr_lrrxlr);

    struct treesize64_c_l_ll_lr_lll_llr_llll_rebalance_case_1_l_on_left_state_cxc_lxll_llxlll_lrxl_lllxllll_lrlxllr_lrrxlr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-20,4},{4,-30,3},{5,-10,1},{8,-40,2},{9,-25,1},{16,-50,1}};
		index = 2;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-30,3},{4,-40,2},{5,-20,2},{8,-50,1},{10,-25,1},{11,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lll_llr_llll_rebalance_case_1_l_on_left_state_cxc_lxll_llxlll_lrxl_lllxllll_lrlxllr_lrrxlr);

    struct treesize32_c_l_ll_lr_lrr_lrl_lrrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr_lllxll_llrxlrl_lrrxlrrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-40,4},{4,-50,1},{5,-30,3},{11,-20,2},{10,-35,1},{23,-10,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-30,3},{4,-40,2},{5,-20,2},{8,-50,1},{9,-35,1},{11,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_ll_lr_lrr_lrl_lrrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr_lllxll_llrxlrl_lrrxlrrr);

    struct treesize64_c_l_ll_lr_lrr_lrl_lrrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr_lllxll_llrxlrl_lrrxlrrr
	: public treeset_array_balancing_test_rebalance_case_1
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-40,4},{4,-50,1},{5,-30,3},{11,-20,2},{10,-35,1},{23,-10,1}};
		index = 2;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,5},{2,-30,3},{4,-40,2},{5,-20,2},{8,-50,1},{9,-35,1},{11,-10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_c_l_ll_lr_lrr_lrl_lrrr_rebalance_case_1_l_on_right_state_cxc_lxlr_llxl_lrxlrr_lllxll_llrxlrl_lrrxlrrr);
}

