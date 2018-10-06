#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>
#include <tuple>

namespace test_treeset_array_balance
{
    struct treeset_array_balance_test_remove_node
	: public treeset_array_balance_test_case
    {
	size_t del_index;
	side_t del_side = side_t::left;
	std::vector<node_t> cmp_values;
	std::vector<size_t> cmp_indexes;
	std::vector<height_t> cmp_heights;
	std::vector<std::pair<size_t,size_t>> result_node_permutations;
	void set_expected_result(container_t& container, std::vector<std::pair<size_t,size_t>> index_permutations)
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
		test_plug.remove_node(container, del_index, del_side);
		score_t values_ok = compare(cmp_values, test_plug.get_values(container));
		score_t indexes_ok = compare(cmp_indexes, test_plug.get_indexes(container));
		score_t heights_ok = compare(cmp_heights, test_plug.get_heights(container));
		return values_ok + indexes_ok + heights_ok;
	    }
    };
    
    struct treesize2_c_remove_node_c_state_cxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2;
		data = {{1,0,1}};
		del_index = 1;
		result_node_permutations = {{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize2_c_remove_node_c_state_cxnull);

    struct treesize8_c_remove_node_c_state_cxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,1}};
		del_index = 1;
		result_node_permutations = {{1,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_remove_node_c_state_cxnull);

    struct treesize4_c_l_remove_node_l_state_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1}};
		del_index = 2;
		result_node_permutations = {{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_remove_node_l_state_lxnull);

    struct treesize16_c_l_remove_node_l_state_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{2,-1,1}};
		del_index = 2;
		result_node_permutations = {{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_remove_node_l_state_lxnull);

    struct treesize4_c_l_remove_node_c_state_cxl_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1}};
		del_index = 1;
		result_node_permutations = {{1,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_remove_node_c_state_cxl_lxnull);

    struct treesize16_c_l_remove_node_c_state_cxl_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{2,-1,1}};
		del_index = 1;
		result_node_permutations = {{1,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_remove_node_c_state_cxl_lxnull);

    struct treesize4_c_r_remove_node_c_state_cxr_rxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{3,1,1}};
		del_index = 1;
		result_node_permutations = {{1,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_remove_node_c_state_cxr_rxnull);

    struct treesize16_c_r_remove_node_c_state_cxr_rxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{3,1,1}};
		del_index = 1;
		result_node_permutations = {{1,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_remove_node_c_state_cxr_rxnull);

    struct treesize4_c_l_r_remove_node_l_state_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 2;
		result_node_permutations = {{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_l_state_lxnull);

    struct treesize16_c_l_r_remove_node_l_state_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 2;
		result_node_permutations = {{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_l_state_lxnull);

    struct treesize4_c_l_r_remove_node_l_state_rxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 3;
		result_node_permutations = {{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_l_state_rxnull);

    struct treesize16_c_l_r_remove_node_r_state_rxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 3;
		result_node_permutations = {{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_r_state_rxnull);

    struct treesize4_c_l_r_remove_node_c_on_left_state_cxl_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_c_on_left_state_cxl_lxnull);

    struct treesize16_c_l_r_remove_node_c_on_left_state_cxl_lxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,2},{2,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_c_on_left_state_cxl_lxnull);

    struct treesize4_c_l_r_remove_node_c_on_right_state_cxr_rxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_c_on_right_state_cxr_rxnull);

    struct treesize16_c_l_r_remove_node_c_on_right_state_cxr_rxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,2},{2,-1,1},{3,1,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,3},{3,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_c_on_right_state_cxr_rxnull);

    struct treesize8_c_l_r_ll_rr_remove_node_l_state_lxll_llxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 2;
		result_node_permutations = {{2,4},{4,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_l_state_lxll_llxnull);

    struct treesize16_c_l_r_ll_rr_remove_node_l_state_lxll_llxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 2;
		result_node_permutations = {{2,4},{4,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_l_state_lxll_llxnull);

    struct treesize8_c_l_r_ll_rr_remove_node_r_state_rxrr_rrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 3;
		result_node_permutations = {{3,7},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_r_state_rxrr_rrxnull);

    struct treesize16_c_l_r_ll_rr_remove_node_r_state_rxrr_rrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 3;
		result_node_permutations = {{3,7},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_r_state_rxrr_rrxnull);

    struct treesize8_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_llxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,2},{2,4},{4,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_llxnull);

    struct treesize16_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_llxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,2},{2,4},{4,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_llxnull);

    struct treesize8_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_rxrr_rrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,3},{3,7},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_rxrr_rrxnull);

    struct treesize16_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_rxrr_rrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-1,2},{3,1,2},{4,-2,1},{7,2,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,3},{3,7},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_rxrr_rrxnull);

    struct treesize8_c_l_r_lr_rl_remove_node_l_state_lxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 2;
		result_node_permutations = {{2,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_l_state_lxlr_lrxnull);

    struct treesize16_c_l_r_lr_rl_remove_node_l_state_lxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 2;
		result_node_permutations = {{2,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_l_state_lxlr_lrxnull);

    struct treesize8_c_l_r_lr_rl_remove_node_r_state_rxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 3;
		result_node_permutations = {{3,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_r_state_rxrl_rlxnull);

    struct treesize16_c_l_r_lr_rl_remove_node_r_state_rxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 3;
		result_node_permutations = {{3,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_r_state_rxrl_rlxnull);

    struct treesize8_c_l_r_lr_rl_remove_node_c_on_left_state_cxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_c_on_left_state_cxlr_lrxnull);

    struct treesize16_c_l_r_lr_rl_remove_node_c_on_left_state_cxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_c_on_left_state_cxlr_lrxnull);

    struct treesize8_c_l_r_lr_rl_remove_node_c_on_right_state_cxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_c_on_right_state_cxrl_rlxnull);

    struct treesize16_c_l_r_lr_rl_remove_node_c_on_right_state_cxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{5,-1,1},{6,1,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_c_on_right_state_cxrl_rlxnull);

    struct treesize8_full8_remove_node_l_on_left_state_lxll_llxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 2;
		del_side = side_t::left;
		result_node_permutations = {{2,4},{4,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_l_on_left_state_lxll_llxnull);

    struct treesize16_full8_remove_node_l_on_left_state_lxll_llxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 2;
		del_side = side_t::left;
		result_node_permutations = {{2,4},{4,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_l_on_left_state_lxll_llxnull);

    struct treesize8_full8_remove_node_l_on_right_state_lxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 2;
		del_side = side_t::right;
		result_node_permutations = {{2,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_l_on_right_state_lxlr_lrxnull);

    struct treesize16_full8_remove_node_l_on_right_state_lxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 2;
		del_side = side_t::right;
		result_node_permutations = {{2,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_l_on_right_state_lxlr_lrxnull);

    struct treesize8_full8_remove_node_r_on_left_state_rxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 3;
		del_side = side_t::left;
		result_node_permutations = {{3,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_r_on_left_state_rxrl_rlxnull);

    struct treesize16_full8_remove_node_r_on_left_state_rxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 3;
		del_side = side_t::left;
		result_node_permutations = {{3,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_r_on_left_state_rxrl_rlxnull);

    struct treesize8_full8_remove_node_r_on_right_state_rxrr_rrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 3;
		del_side = side_t::right;
		result_node_permutations = {{3,7},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_r_on_right_state_rxrr_rrxnull);

    struct treesize16_full8_remove_node_r_on_right_state_rxrr_rrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 3;
		del_side = side_t::right;
		result_node_permutations = {{3,7},{7,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_r_on_right_state_rxrr_rrxnull);

    struct treesize8_full8_remove_node_c_on_left_state_cxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_c_on_left_state_cxlr_lrxnull);

    struct treesize16_full8_remove_node_c_on_left_state_cxlr_lrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,5},{5,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_c_on_left_state_cxlr_lrxnull);

    struct treesize8_full8_remove_node_c_on_right_state_cxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_c_on_right_state_cxrl_rlxnull);

    struct treesize16_full8_remove_node_c_on_right_state_cxrl_rlxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-2,2},{3,2,2},{4,-3,1},{5,-1,1},{6,1,1},{7,3,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,6},{6,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_c_on_right_state_cxrl_rlxnull);

    struct treesize16_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_lrrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-3,3},{3,3,3},{4,-4,1},{5,-2,2},{6,2,2},{7,4,1},{11,-1,1},{12,1,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,11},{11,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_lrrxnull);

    struct treesize32_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_lrrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-3,3},{3,3,3},{4,-4,1},{5,-2,2},{6,2,2},{7,4,1},{11,-1,1},{12,1,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,11},{11,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_lrrxnull);

    struct treesize16_full8_lrr_rll_remove_node_c_on_right_state_cxrll_rllxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-3,3},{3,3,3},{4,-4,1},{5,-2,2},{6,2,2},{7,4,1},{11,-1,1},{12,1,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,12},{12,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_lrr_rll_remove_node_c_on_right_state_cxrll_rllxnull);

    struct treesize32_full8_lrr_rll_remove_node_c_on_right_state_cxrll_rllxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,4},{2,-3,3},{3,3,3},{4,-4,1},{5,-2,2},{6,2,2},{7,4,1},{11,-1,1},{12,1,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,12},{12,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrr_rll_remove_node_c_on_right_state_cxrll_rllxnull);

    struct treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr_lrllxnull_lrlrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{3,10,4},{4,-20,1},{5,-5,3},{6,5,3},{7,20,1},
			{10,-7,2},{13,7,2},{20,-8,1},{21,-6,1},{26,6,1},{27,8,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,5},{5,10},{10,20},{11,21},{20,null},{21,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr_lrllxnull_lrlrxnull);

    struct treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr_lrllxnull_lrlrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{3,10,4},{4,-20,1},{5,-5,3},{6,5,3},{7,20,1},
			{10,-7,2},{13,7,2},{20,-8,1},{21,-6,1},{26,6,1},{27,8,1}};
		del_index = 1;
		del_side = side_t::left;
		result_node_permutations = {{1,5},{5,10},{10,20},{11,21},{20,null},{21,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr_lrllxnull_lrlrxnull);

    struct treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr_rlrlxnull_rlrrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0,5},{2,-10,4},{3,10,4},{4,-20,1},{5,-5,3},{6,5,3},{7,20,1},
			{10,-7,2},{13,7,2},{20,-8,1},{21,-6,1},{26,6,1},{27,8,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,6},{6,13},{12,26},{13,27},{26,null},{27,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr_rlrlxnull_rlrrxnull);

    struct treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr_rlrlxnull_rlrrxnull
	: public treeset_array_balance_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0,5},{2,-10,4},{3,10,4},{4,-20,1},{5,-5,3},{6,5,3},{7,20,1},
			{10,-7,2},{13,7,2},{20,-8,1},{21,-6,1},{26,6,1},{27,8,1}};
		del_index = 1;
		del_side = side_t::right;
		result_node_permutations = {{1,6},{6,13},{12,26},{13,27},{26,null},{27,null}};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr_rlrlxnull_rlrrxnull);
}
