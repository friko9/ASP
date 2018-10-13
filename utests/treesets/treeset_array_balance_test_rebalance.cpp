#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balance
{
    struct treeset_array_balance_test_rebalance
	: public treeset_array_balance_test_case
    {
	index_t index;
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
		test_plug.rebalance(container, index);
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
    
    struct treesize2_c_rebalance_c_state_c1 
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2;
		data = {{1,0,99}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize2_c_rebalance_c_state_c1);

    struct treesize8_c_rebalance_c_state_c1 
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_rebalance_c_state_c1);

    struct treesize4_c_l_rebalance_l_state_c2_l1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{2,-1,99}};
		index = 2;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{2,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_rebalance_l_state_c2_l1);

    struct treesize8_c_l_rebalance_l_state_c2_l1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-1,99}};
		index = 2;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{2,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_rebalance_l_state_c2_l1);

    struct treesize4_c_r_rebalance_r_state_c2_r1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{3,1,99}};
		index = 3;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{3,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_rebalance_r_state_c2_r1);

    struct treesize8_c_r_rebalance_r_state_c2_r1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{3,1,99}};
		index = 3;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{3,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_rebalance_r_state_c2_r1);

    struct treesize8_c_l_r1_ll_rebalance_ll_state_c3_l2_r1_ll1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-1,99},{3,1,1},{4,-2,99}};
		index = 4;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-1,2},{3,1,1},{4,-2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r1_ll_rebalance_ll_state_c3_l2_r1_ll1);

    struct treesize16_c_l_r1_ll_rebalance_ll_state_c3_l2_r1_ll1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,99},{2,-1,99},{3,1,1},{4,-2,99}};
		index = 4;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-1,2},{3,1,1},{4,-2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r1_ll_rebalance_ll_state_c3_l2_r1_ll1);

    struct treesize8_c_l_r1_lr_rebalance_lr_state_c3_l2_r1_lr1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-2,99},{3,1,1},{5,-1,99}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-2,2},{3,1,1},{5,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r1_lr_rebalance_lr_state_c3_l2_r1_lr1);

    struct treesize16_c_l_r1_lr_rebalance_lr_state_c3_l2_r1_lr1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,99},{2,-2,99},{3,1,1},{5,-1,99}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-2,2},{3,1,1},{5,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r1_lr_rebalance_lr_state_c3_l2_r1_lr1);

    struct treesize8_c_l1_r_rl_rebalance_lr_state_c3_l1_r2_rl1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-2,1},{3,2,1},{6,1,99}};
		index = 6;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-2,1},{3,2,2},{6,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l1_r_rl_rebalance_lr_state_c3_l1_r2_rl1);

    struct treesize16_c_l1_r_rl_rebalance_lr_state_c3_l1_r2_rl1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,99},{2,-2,1},{3,2,1},{6,1,99}};
		index = 6;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-2,1},{3,2,2},{6,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l1_r_rl_rebalance_lr_state_c3_l1_r2_rl1);

    struct treesize8_c_l1_r_rr_rebalance_rr_state_c3_l1_r2_rr1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-2,1},{3,2,1},{7,4,99}};
		index = 7;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-2,1},{3,2,2},{7,4,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l1_r_rr_rebalance_rr_state_c3_l1_r2_rr1);

    struct treesize16_c_l1_r_rr_rebalance_rr_state_c3_l1_r2_rr1
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,99},{2,-2,1},{3,2,1},{7,4,99}};
		index = 7;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,3},{2,-2,1},{3,2,2},{7,4,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l1_r_rr_rebalance_rr_state_c3_l1_r2_rr1);
    //rebalance case 1
    struct treesize8_c2_l1_ll1_rebalance_ll_state_c2xl_l1xll_r1xc
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{4,-2,1}};
		index = 4;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c2_l1_ll1_rebalance_ll_state_c2xl_l1xll_r1xc);

    struct treesize8_c3_l2_ll1_rebalance_c_state_c2xl_l1xll_r1xc
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{4,-2,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c3_l2_ll1_rebalance_c_state_c2xl_l1xll_r1xc);

    struct treesize8_c2_r1_rr1_rebalance_rr_state_c2xr_l1xc_r1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{3,1,1},{7,2,1}};
		index = 7;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c2_r1_rr1_rebalance_rr_state_c2xr_l1xc_r1xrr);

    struct treesize8_c3_r2_rr1_rebalance_c_state_c2xr_l1xc_r1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,4},{3,1,3},{7,2,2}};
		index = 7;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c3_r2_rr1_rebalance_c_state_c2xr_l1xc_r1xrr);

    struct treesize16_c3_l2_r1_ll1_lr1_lll1_rebalance_lll_state_c3xl_l2xll_r2xc_ll1xlll_rl1xlr_rr1xr
    	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-10,2},{3,10,1},{4,-20,1},{5,-5,1},{8,-30,1}};
		index = 8;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-10,3},{2,-20,2},{3,0,2},{4,-30,1},{6,-5,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c3_l2_r1_ll1_lr1_lll1_rebalance_lll_state_c3xl_l2xll_r2xc_ll1xlll_rl1xlr_rr1xr);

    struct treesize16_c4_l3_r2_ll2_lr1_lll1_rebalance_r_state_c3xl_l2xll_r2xc_ll1xlll_rl1xlr_rr1xr
    	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,2},{4,-20,2},{5,-5,1},{8,-30,1}};
		index = 3;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-10,3},{2,-20,2},{3,0,2},{4,-30,1},{6,-5,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l3_r2_ll2_lr1_lll1_rebalance_r_state_c3xl_l2xll_r2xc_ll1xlll_rl1xlr_rr1xr);

    struct treesize16_c3_l1_r2_rr1_rl1_rrr1_rebalance_rrr_state_c3xr_l2xc_r2xrr_ll1xl_lr1xrl_rr1xrrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-10,1},{3,10,2},{6,5,1},{7,20,1},{15,30,1}};
		index = 15;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,10,3},{2,0,2},{3,20,2},{4,-10,1},{5,5,1},{7,30,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c3_l1_r2_rr1_rl1_rrr1_rebalance_rrr_state_c3xr_l2xc_r2xrr_ll1xl_lr1xrl_rr1xrrr);

    struct treesize16_c4_l2_r3_rr2_rl1_rrr1_rebalance_l_state_c3xr_l2xc_r2xrr_ll1xl_lr1xrl_rr1xrrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,2},{3,10,3},{6,5,1},{7,20,2},{15,30,1}};
		index = 2;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,10,3},{2,0,2},{3,20,2},{4,-10,1},{5,5,1},{7,30,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l2_r3_rr2_rl1_rrr1_rebalance_l_state_c3xr_l2xc_r2xrr_ll1xl_lr1xrl_rr1xrrr);
    //rebalance case 2
    struct treesize8_c2_l1_lr1_rebalance_lr_state_c2xlr_l1xll_r1xc
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-2,1},{5,-1,1}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c2_l1_lr1_rebalance_lr_state_c2xlr_l1xll_r1xc);

    struct treesize8_c3_l2_lr1_rebalance_c_state_c2xlr_l1xll_r1xc
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{5,-1,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1},{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c3_l2_lr1_rebalance_c_state_c2xlr_l1xll_r1xc);

    struct treesize8_c2_r1_rl1_rebalance_rl_state_c2xrl_l1xc_r1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{3,2,1},{6,1,1}};
		index = 6;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c2_r1_rl1_rebalance_rl_state_c2xrl_l1xc_r1xr);

    struct treesize8_c3_r2_rl1_rebalance_c_state_c2xrl_l1xc_r1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{3,2,2},{6,1,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1},{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c3_r2_rl1_rebalance_c_state_c2xrl_l1xc_r1xr);

    struct treesize16_c3_l2_r1_ll1_lr1_lrl1_rebalance_lrl_state_c3xlr_l2xl_r2xc_ll1xll_lr1xlrl_rr1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-10,2},{3,10,1},{4,-20,1},{5,-5,1},{10,-7,1}};
		index = 10;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c3_l2_r1_ll1_lr1_lrl1_rebalance_lrl_state_c3xlr_l2xl_r2xc_ll1xll_lr1xlrl_rr1xr);

    struct treesize16_c4_l3_r2_ll1_lr2_lrl1_rebalance_r_state_c3xlr_l2xl_r2xc_ll1xll_lr1xlrl_rr1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,2},{4,-20,1},{5,-5,2},{10,-7,1}};
		index = 3;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l3_r2_ll1_lr2_lrl1_rebalance_r_state_c3xlr_l2xl_r2xc_ll1xll_lr1xlrl_rr1xr);

    struct treesize16_c3_l2_r1_ll1_lr2_lrr1_rebalance_lrr_state_c3xlr_l2xl_r2xc_ll1xll_rl1xlrr_rr1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-10,2},{3,10,1},{4,-20,1},{5,-5,2},{11,-3,1}};
		index = 11;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c3_l2_r1_ll1_lr2_lrr1_rebalance_lrr_state_c3xlr_l2xl_r2xc_ll1xll_rl1xlrr_rr1xr);

    struct treesize16_c4_l3_r2_ll1_lr2_lrr1_rebalance_r_state_c3xlr_l2xl_r2xc_ll1xll_rl1xlrr_rr1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,2},{4,-20,1},{5,-5,2},{11,-3,1}};
		index = 3;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l3_r2_ll1_lr2_lrr1_rebalance_r_state_c3xlr_l2xl_r2xc_ll1xll_rl1xlrr_rr1xr);

    struct treesize16_c4_l3_r2_ll1_lr2_lrl1_lrr1_rebalance_r_state_c3xlr_l2xl_r2xc_ll1xll_lr1xlrl_rl1xlrr_rr1xr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,2},{4,-20,1},{5,-5,2},{10,-7,1},{11,-3,1}};
		index = 3;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-5,3},{2,-10,2},{3,0,2},{4,-20,1},{5,-7,1},{6,-3,1},{7,10,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l3_r2_ll1_lr2_lrl1_lrr1_rebalance_r_state_c3xlr_l2xl_r2xc_ll1xll_lr1xlrl_rl1xlrr_rr1xr);

    struct treesize16_c3_l1_r2_rl1_rr1_rlr1_rebalance_rlr_state_c3xrl_l2xc_r2xr_ll1xl_rl1xrlr_rr1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-10,1},{3,10,2},{6,5,1},{7,20,1},{13,7,1}};
		index = 13;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c3_l1_r2_rl1_rr1_rlr1_rebalance_rlr_state_c3xrl_l2xc_r2xr_ll1xl_rl1xrlr_rr1xrr);

    struct treesize16_c4_l1_r3_rl2_rr1_rlr1_rebalance_l_state_c3xrl_l2xc_r2xr_ll1xl_rl1xrlr_rr1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{13,7,1}};
		index = 2;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l1_r3_rl2_rr1_rlr1_rebalance_l_state_c3xrl_l2xc_r2xr_ll1xl_rl1xrlr_rr1xrr);

    struct treesize16_c3_l1_r2_rl1_rr1_rll1_rebalance_rll_state_c3xrl_l2xc_r2xr_ll1xl_lr1xrll_rr1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-10,1},{3,10,2},{6,5,1},{7,20,1},{12,3,1}};
		index = 12;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c3_l1_r2_rl1_rr1_rll1_rebalance_rll_state_c3xrl_l2xc_r2xr_ll1xl_lr1xrll_rr1xrr);

    struct treesize16_c4_l1_r3_rl2_rr1_rll1_rebalance_l_state_c3xrl_l2xc_r2xr_ll1xl_lr1xrll_rr1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{12,3,1}};
		index = 2;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l1_r3_rl2_rr1_rll1_rebalance_l_state_c3xrl_l2xc_r2xr_ll1xl_lr1xrll_rr1xrr);

    struct treesize16_c4_l1_r3_rl2_rr1_rll1_rlr1_rebalance_case_2_l_state_c3xrl_l2xc_r2xr_ll1xl_lr1xrll_rl1xrlr_rr1xrr
	: public treeset_array_balance_test_rebalance
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,1},{3,10,3},{6,5,2},{7,20,1},{12,3,1},{13,7,1}};
		index = 2;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,5,3},{2,0,2},{3,10,2},{4,-10,1},{5,3,1},{6,7,1},{7,20,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c4_l1_r3_rl2_rr1_rll1_rlr1_rebalance_case_2_l_state_c3xrl_l2xc_r2xr_ll1xl_lr1xrll_rl1xrlr_rr1xrr);


}
