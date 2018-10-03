#include "treeset_array_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balancing
{
    struct treeset_array_balancing_test_move_nodes_down
	: public treeset_array_balancing_test_case
    {
	index_t index;
	side_t side;
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
		test_plug.move_nodes_down(container, index, side);
		score_t values_ok = compare(cmp_values, test_plug.get_values(container));
		score_t indexes_ok = compare(cmp_indexes, test_plug.get_indexes(container));
		score_t heights_ok = compare(cmp_heights, test_plug.get_heights(container));
		return values_ok + indexes_ok + heights_ok;
	    }
    };
	
    struct treesize4_c_move_nodes_down_c_on_left_state_lxc_cxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,1}};
		index = 1;
		side = side_t::left;
		result_node_permutations = {{2,1},{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_move_nodes_down_c_on_left_state_lxc_cxnull);

    struct treesize16_c_move_nodes_down_c_on_left_state_lxc_cxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1}};
		index = 1;
		side = side_t::left;
		result_node_permutations = {{2,1},{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_move_nodes_down_c_on_left_state_lxc_cxnull);

    struct treesize4_c_move_nodes_down_c_on_right_state_null
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,1}};
		index = 1;
		side = side_t::right;
		result_node_permutations = {{3,1},{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_move_nodes_down_c_on_right_state_null);

    struct treesize16_c_move_nodes_down_c_on_right_state_null
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1}};
		index = 1;
		side = side_t::right;
		result_node_permutations = {{3,1},{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_move_nodes_down_c_on_right_state_null);

    struct treesize8_c_l_move_nodes_down_l_on_left_state_llxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1}};
		index = 2;
		side = side_t::left;
		result_node_permutations = {{4,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_move_nodes_down_l_on_left_state_llxl_lxnull);

    struct treesize32_c_l_move_nodes_down_l_on_left_state_llxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1}};
		index = 2;
		side = side_t::left;
		result_node_permutations = {{4,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_move_nodes_down_l_on_left_state_llxl_lxnull);

    struct treesize8_c_l_move_nodes_down_l_on_right_state_lrxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1}};
		index = 2;
		side = side_t::right;
		result_node_permutations = {{5,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_move_nodes_down_l_on_right_state_lrxl_lxnull);

    struct treesize32_c_l_move_nodes_down_l_on_right_state_lrxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1}};
		index = 2;
		side = side_t::right;
		result_node_permutations = {{5,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_move_nodes_down_l_on_right_state_lrxl_lxnull);
    
    struct treesize8_c_r_move_nodes_down_r_on_left_state_rlxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{3,1,1}};
		index = 3;
		side = side_t::left;
		result_node_permutations = {{6,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_move_nodes_down_r_on_left_state_rlxr_rxnull);

    struct treesize32_c_r_move_nodes_down_r_on_left_state_rlxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{3,1,1}};
		index = 3;
		side = side_t::left;
		result_node_permutations = {{6,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_r_move_nodes_down_r_on_left_state_rlxr_rxnull);

    struct treesize8_c_r_move_nodes_down_r_on_right_state_rrxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{3,1,1}};
		index = 3;
		side = side_t::right;
		result_node_permutations = {{7,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_move_nodes_down_r_on_right_state_rrxr_rxnull);

    struct treesize32_c_r_move_nodes_down_r_on_right_state_rrxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{3,1,1}};
		index = 3;
		side = side_t::right;
		result_node_permutations = {{7,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_r_move_nodes_down_r_on_right_state_rrxr_rxnull);

    struct treesize8_c_l_r_move_nodes_down_l_on_left_state_llxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 2;
		side = side_t::left;
		result_node_permutations = {{4,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_move_nodes_down_l_on_left_state_llxl_lxnull);

    struct treesize32_c_l_r_move_nodes_down_l_on_left_state_llxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 2;
		side = side_t::left;
		result_node_permutations = {{4,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_move_nodes_down_l_on_left_state_llxl_lxnull);

    struct treesize8_c_l_r_move_nodes_down_l_on_right_state_lrxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 2;
		side = side_t::right;
		result_node_permutations = {{5,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_move_nodes_down_l_on_right_state_lrxl_lxnull);

    struct treesize32_c_l_r_move_nodes_down_l_on_right_state_lrxl_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 2;
		side = side_t::right;
		result_node_permutations = {{5,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_move_nodes_down_l_on_right_state_lrxl_lxnull);
    
    struct treesize8_c_l_r_move_nodes_down_r_on_left_state_rlxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 3;
		side = side_t::left;
		result_node_permutations = {{6,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_move_nodes_down_r_on_left_state_rlxr_rxnull);

    struct treesize32_c_l_r_move_nodes_down_r_on_left_state_rlxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 3;
		side = side_t::left;
		result_node_permutations = {{6,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_move_nodes_down_r_on_left_state_rlxr_rxnull);

    struct treesize8_c_l_r_move_nodes_down_r_on_right_state_rrxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 3;
		side = side_t::right;
		result_node_permutations = {{7,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_move_nodes_down_r_on_right_state_rrxr_rxnull);

    struct treesize32_c_l_r_move_nodes_down_r_on_right_state_rrxr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		index = 3;
		side = side_t::right;
		result_node_permutations = {{7,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_c_l_r_move_nodes_down_r_on_right_state_rrxr_rxnull);    
    
    struct treesize16_full8_move_nodes_down_l_on_left_state_llxl_lllxll_llrxlr_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 2;
		side = side_t::left;
		result_node_permutations = {{4,2},{8,4},{9,5},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_down_l_on_left_state_llxl_lllxll_llrxlr_lxnull);

    struct treesize64_full8_move_nodes_down_l_on_left_state_llxl_lllxll_llrxlr_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 2;
		side = side_t::left;
		result_node_permutations = {{4,2},{8,4},{9,5},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_move_nodes_down_l_on_left_state_llxl_lllxll_llrxlr_lxnull);

    struct treesize16_full8_move_nodes_down_l_on_right_state_lrxl_lrlxll_lrrxlr_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 2;
		side = side_t::right;
		result_node_permutations = {{5,2},{10,4},{11,5},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_down_l_on_right_state_lrxl_lrlxll_lrrxlr_lxnull);

    struct treesize64_full8_move_nodes_down_l_on_right_state_lrxl_lrlxll_lrrxlr_lxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 2;
		side = side_t::right;
		result_node_permutations = {{5,2},{10,4},{11,5},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_move_nodes_down_l_on_right_state_lrxl_lrlxll_lrrxlr_lxnull);


    struct treesize16_full8_move_nodes_down_r_on_left_state_rlxr_rllxrl_rlrxrr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 3;
		side = side_t::left;
		result_node_permutations = {{6,3},{12,6},{13,7},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_down_r_on_left_state_rlxr_rllxrl_rlrxrr_rxnull);

    struct treesize64_full8_move_nodes_down_r_on_left_state_rlxr_rllxrl_rlrxrr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 3;
		side = side_t::left;
		result_node_permutations = {{6,3},{12,6},{13,7},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_move_nodes_down_r_on_left_state_rlxr_rllxrl_rlrxrr_rxnull);

    struct treesize16_full8_move_nodes_down_r_on_right_state_rrxr_rrlxrl_rrrxrr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 3;
		side = side_t::right;
		result_node_permutations = {{7,3},{14,6},{15,7},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_move_nodes_down_r_on_right_state_rrxr_rrlxrl_rrrxrr_rxnull);

    struct treesize64_full8_move_nodes_down_r_on_right_state_rrxr_rrlxrl_rrrxrr_rxnull
	: public treeset_array_balancing_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,1},
			{2,-4,2},{3,4,2},
			{4,-6,1},{5,-2,1},{6,2,1},{7,6,1}};
		index = 3;
		side = side_t::right;
		result_node_permutations = {{7,3},{14,6},{15,7},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_move_nodes_down_r_on_right_state_rrxr_rrlxrl_rrrxrr_rxnull);
    

		

}
