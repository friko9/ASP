#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balance
{
    struct treeset_array_balance_test_rebalance
	: public treeset_array_balance_test_case
    {
	size_t index;
	std::vector<node_t> expected_values;
	std::vector<size_t> expected_indexes;
	std::vector<height_t> expected_heights;
	score_t compare(std::vector<node_t>& vals1,std::vector<size_t> &indexes1,std::vector<height_t> &heights1,
			std::vector<node_t>& vals2,std::vector<size_t> &indexes2,std::vector<height_t> &heights2)
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


    // TODO
}
