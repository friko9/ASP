#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct treeset_array_test_move_nodes_up
	: public treeset_array_test_case
    {
	index_t index;
	std::vector<node_t> cmp_values;
	std::vector<index_t> cmp_indexes;
	std::vector<std::pair<index_t,index_t>> result_node_permutations;
	void set_expected_result(container_t& container, std::vector<std::pair<index_t,index_t>> index_permutations)
	    {
		auto values = test_plug.get_values(container);
		auto indexes = test_plug.get_indexes(container);
		cmp_values = values;
		cmp_indexes = indexes;
		for( auto p : index_permutations )
		{
		    if( p.first >= indexes.size() )
			throw std::runtime_error("Wrong indexing");
		    cmp_indexes[p.first] = (p.second != null)? indexes[p.second] : null;
		    if( p.second != null )
			cmp_values[indexes[p.second]].second  = p.first;
		}
	    }
	void configure()
	    {
		setup_data();
		std::tie(test_plug.get_values(container),
			 test_plug.get_indexes(container))
		    = make_data(tree_size,data);
		set_expected_result(container,result_node_permutations);
	    }
	test_result test()
	    {
		test_plug.move_nodes_up(container, index);
		score_t values_ok = compare(cmp_values, test_plug.get_values(container));
		score_t indexes_ok = compare(cmp_indexes, test_plug.get_indexes(container));
		return values_ok + indexes_ok;
	    }
    };
	
    struct treesize4_c_move_nodes_up_l_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0}};
		index = 2;
		result_node_permutations = {{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_move_nodes_up_l_state_null);

    struct treesize8_c_move_nodes_up_l_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0}};
		index = 2;
		result_node_permutations = {{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_move_nodes_up_l_state_null);

    struct treesize4_c_move_nodes_up_r_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0}};
		index = 3;
		result_node_permutations = {{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_move_nodes_up_r_state_null);

    struct treesize8_c_move_nodes_up_r_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0}};
		index = 3;
		result_node_permutations = {{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_move_nodes_up_r_state_null);

    struct treesize4_c_l_move_nodes_up_l_state_cxl
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1}};
		index = 2;
		result_node_permutations = {{1,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_move_nodes_up_l_state_cxl);

    struct treesize16_c_l_move_nodes_up_l_state_cxl
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1}};
		index = 2;
		result_node_permutations = {{1,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_move_nodes_up_l_state_cxl);

    struct treesize4_c_r_move_nodes_up_r_state_cxr
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{3,1}};
		index = 3;
		result_node_permutations = {{1,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_move_nodes_up_r_state_cxr);

    struct treesize16_c_r_move_nodes_up_r_state_cxr
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{3,1}};
		index = 3;
		result_node_permutations = {{1,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_move_nodes_up_r_state_cxr);
    
    struct treesize4_c_l_r_move_nodes_up_l_state_cxl_lxnull_rxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1},{3,1}};
		index = 2;
		result_node_permutations = {{1,2},{2,null},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_up_l_state_cxl_lxnull_rxnull);

    struct treesize16_c_l_r_move_nodes_up_l_state_cxl_lxnull_rxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1}};
		index = 2;
		result_node_permutations = {{1,2},{2,null},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_move_nodes_up_l_state_cxl_lxnull_rxnull);

    struct treesize4_c_l_r_move_nodes_up_r_state_cxr_lxnull_rxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1},{3,1}};
		index = 3;
		result_node_permutations = {{1,3},{2,null},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_up_r_state_cxr_lxnull_rxnull);

    struct treesize16_c_l_r_move_nodes_up_r_state_cxr_lxnull_rxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1}};
		index = 3;
		result_node_permutations = {{1,3},{2,null},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_move_nodes_up_r_state_cxr_lxnull_rxnull);

    struct treesize16_full16_move_nodes_up_ll_state_lxll_llxlll_lrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 4;
		result_node_permutations = {{2,4},{4,8},{5,9},{8,null},{9,null},{10,null},{11,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_ll_state_lxll_llxlll_lrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize32_full16_move_nodes_up_ll_state_lxll_llxlll_lrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 4;
		result_node_permutations = {{2,4},{4,8},{5,9},{8,null},{9,null},{10,null},{11,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_ll_state_lxll_llxlll_lrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize16_full16_move_nodes_up_lr_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 5;
		result_node_permutations = {{2,5},{4,10},{5,11},{8,null},{9,null},{10,null},{11,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_lr_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize32_full16_move_nodes_up_lr_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 5;
		result_node_permutations = {{2,5},{4,10},{5,11},{8,null},{9,null},{10,null},{11,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_lr_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize16_full16_move_nodes_up_rl_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 6;
		result_node_permutations = {{3,6},{6,12},{7,13},{12,null},{13,null},{14,null},{15,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_rl_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull);

    struct treesize32_full16_move_nodes_up_rl_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 6;
		result_node_permutations = {{3,6},{6,12},{7,13},{12,null},{13,null},{14,null},{15,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_rl_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull);

    struct treesize16_full16_move_nodes_up_rl_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 7;
		result_node_permutations = {{3,7},{6,14},{7,15},{12,null},{13,null},{14,null},{15,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_rl_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull);

    struct treesize32_full16_move_nodes_up_rr_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},
			{2,-4},{3,4},
			{4,-6},{5,-2},{6,2},{7,6},
			{8,-7},{9,-5},{10,-3},{11,-1},{12,1},{13,3},{14,5},{15,7}};
		index = 7;
		result_node_permutations = {{3,7},{6,14},{7,15},{12,null},{13,null},{14,null},{15,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_rr_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull);
}
