#include "treeset_array_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balancing
{
    struct treeset_array_balancing_test_move_nodes_side
	: public treeset_array_balancing_test_case
    {
	index_t source;
	size_t destination;
	std::vector<node_t> cmp_values;
	std::vector<index_t> cmp_indexes;
	std::vector<height_t> cmp_heights;
	std::vector<std::pair<index_t,index_t>> result_node_permutations;
	void set_expected_result(container_t& container, std::vector<std::pair<index_t,index_t>> index_permutations)
	    {
		auto values = test_plug.get_values(container);
		auto indexes = test_plug.get_indexes(container);
		auto heights = test_plug.get_heights(container);
		cmp_values = values;
		cmp_indexes = indexes;
		cmp_heights = heights;
		for( auto p : index_permutations )
		{
		    if( p.first >= indexes.size() )
			throw std::runtime_error("Wrong indexing");
		    cmp_indexes[p.first] = (p.second != null)? indexes[p.second] : null;
		    cmp_heights[p.first] = (p.second != null)? heights[p.second] : 0;
		    if( p.second != null )
			cmp_values[indexes[p.second]].second  = p.first;
		}
	    }
	void configure()
	    {
		setup_data();
		std::tie(test_plug.get_values(container),
			 test_plug.get_indexes(container),
			 test_plug.get_heights(container))
		    = make_data(tree_size,data);
		set_expected_result(container,result_node_permutations);
	    }
	test_result test()
	    {
		test_plug.move_nodes_side(container, source, destination);
		score_t values_ok = compare(cmp_values, test_plug.get_values(container));
		score_t indexes_ok = compare(cmp_indexes, test_plug.get_indexes(container));
		score_t heights_ok = compare(cmp_heights, test_plug.get_heights(container));
		return values_ok + indexes_ok + heights_ok;
	    }
    };

    struct treesize4_c_l_move_nodes_side_l_on_l_state_not_changed
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
 		tree_size = 4;
		data = {{1,0,2},{2,-1,1}};
		source = 2;
		destination = 2;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_move_nodes_side_l_on_l_state_not_changed);
    
    struct treesize4_c_l_move_nodes_side_l_on_r_state_lxnull_rxl
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
 		tree_size = 4;
		data = {{1,0,2},{2,-1,1}};
		source = 2;
		destination = 3;
		result_node_permutations = {{2,null},{3,2}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_move_nodes_side_l_on_r_state_lxnull_rxl);

    struct treesize8_c_l_move_nodes_side_l_on_r_state_lxnull_rxl
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
 		tree_size = 8;
		data = {{1,0,2},{2,-1,1}};
		source = 2;
		destination = 3;
		result_node_permutations = {{2,null},{3,2}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_move_nodes_side_l_on_r_state_lxnull_rxl);

    struct treesize4_c_r_move_nodes_side_r_on_r_state_not_changed
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{3,1,1}};
		source = 3;
		destination = 3;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_move_nodes_side_r_on_r_state_not_changed);

    struct treesize4_c_r_move_nodes_side_r_on_l_state_lxr_rxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{3,1,1}};
		source = 3;
		destination = 2;
		result_node_permutations = {{2,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_move_nodes_side_r_on_l_state_lxr_rxnull);

    struct treesize8_c_r_move_nodes_side_r_on_l_state_lxr_rxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{3,1,1}};
		source = 3;
		destination = 2;
		result_node_permutations = {{2,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_move_nodes_side_r_on_l_state_lxr_rxnull);

    struct treesize4_c_l_r_move_nodes_side_l_on_l_state_not_changed
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		source = 2;
		destination = 2;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_side_l_on_l_state_not_changed);

    struct treesize4_c_l_r_move_nodes_side_l_on_r_state_lxnull_rxl
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		source = 2;
		destination = 3;
		result_node_permutations = {{3,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_side_l_on_r_state_lxnull_rxl);

    struct treesize8_c_l_r_move_nodes_side_l_on_r_state_lxnull_rxl
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		source = 2;
		destination = 3;
		result_node_permutations = {{3,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_move_nodes_side_l_on_r_state_lxnull_rxl);

    struct treesize4_c_l_r_move_nodes_side_r_on_r_state_not_changed
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		source = 3;
		destination = 3;
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_side_r_on_r_state_not_changed);

    struct treesize4_c_l_r_move_nodes_side_r_on_l_state_lxr_rxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		source = 3;
		destination = 2;
		result_node_permutations = {{2,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_side_r_on_l_state_lxr_rxnull);

    struct treesize8_c_l_r_move_nodes_side_r_on_l_state_lxr_rxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		source = 3;
		destination = 2;
		result_node_permutations = {{2,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_move_nodes_side_r_on_l_state_lxr_rxnull);

    struct treesize8_full8_move_nodes_side_l_on_r_state_lxnull_llxnull_lrxnull_rxl_rlxll_rrxlr
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 2;
		destination = 3;
		result_node_permutations = {{2,null},{3,2},
					    {4,null},{5,null},{6,4},{7,5}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_move_nodes_side_l_on_r_state_lxnull_llxnull_lrxnull_rxl_rlxll_rrxlr);

    struct treesize16_full8_move_nodes_side_l_on_r_state_lxnull_llxnull_lrxnull_rxl_rlxll_rrxlr
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 2;
		destination = 3;
		result_node_permutations = {{2,null},{3,2},
					    {4,null},{5,null},{6,4},{7,5}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_side_l_on_r_state_lxnull_llxnull_lrxnull_rxl_rlxll_rrxlr);

    struct treesize8_full8_move_nodes_side_r_on_l_state_lxr_llxrl_lrxrr_rxnull_rlxnull_rrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 3;
		destination = 2;
		result_node_permutations = {{2,3},{3,null},
					    {4,6},{5,7},{6,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_move_nodes_side_r_on_l_state_lxr_llxrl_lrxrr_rxnull_rlxnull_rrxnull);

    struct treesize16_full8_move_nodes_side_r_on_l_state_lxr_llxrl_lrxrr_rxnull_rlxnull_rrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 3;
		destination = 2;
		result_node_permutations = {{2,3},{3,null},
					    {4,6},{5,7},{6,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_side_r_on_l_state_lxr_llxrl_lrxrr_rxnull_rlxnull_rrxnull);

    struct treesize8_full8_move_nodes_side_ll_on_r_state_llxnull_rxll_rlxnull_rrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 4;
		destination = 3;
		result_node_permutations = {{3,4},{4,null},{6,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_move_nodes_side_ll_on_r_state_llxnull_rxll_rlxnull_rrxnull);

    struct treesize16_full8_move_nodes_side_ll_on_r_state_llxnull_rxll_rlxnull_rrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 4;
		destination = 3;
		result_node_permutations = {{3,4},{4,null},{6,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_side_ll_on_r_state_llxnull_rxll_rlxnull_rrxnull);

    struct treesize8_full8_move_nodes_side_lr_on_r_state_lrxnull_rxlr_rlxnull_rrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 5;
		destination = 3;
		result_node_permutations = {{3,5},{5,null},{6,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_move_nodes_side_lr_on_r_state_lrxnull_rxlr_rlxnull_rrxnull);

    struct treesize16_full8_move_nodes_side_lr_on_r_state_lrxnull_rxlr_rlxnull_rrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 5;
		destination = 3;
		result_node_permutations = {{3,5},{5,null},{6,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_side_lr_on_r_state_lrxnull_rxlr_rlxnull_rrxnull);

    struct treesize8_full8_move_nodes_side_rl_on_l_state_rlxnull_lxrl_llxnull_lrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 6;
		destination = 2;
		result_node_permutations = {{2,6},{4,null},{5,null},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_move_nodes_side_rl_on_l_state_rlxnull_lxrl_llxnull_lrxnull);

    struct treesize16_full8_move_nodes_side_rl_on_l_state_rlxnull_lxrl_llxnull_lrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 6;
		destination = 2;
		result_node_permutations = {{2,6},{4,null},{5,null},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_side_rl_on_l_state_rlxnull_lxrl_llxnull_lrxnull);

    struct treesize8_full8_move_nodes_side_rr_on_l_state_rrxnull_lxrr_llxnull_lrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 7;
		destination = 2;
		result_node_permutations = {{2,7},{4,null},{5,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_move_nodes_side_rr_on_l_state_rrxnull_lxrr_llxnull_lrxnull);

    struct treesize16_full8_move_nodes_side_rr_on_l_state_rrxnull_lxrr_llxnull_lrxnull
	: public treeset_array_balancing_test_move_nodes_side
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		source = 7;
		destination = 2;
		result_node_permutations = {{2,7},{4,null},{5,null},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_side_rr_on_l_state_rrxnull_lxrr_llxnull_lrxnull);
}
