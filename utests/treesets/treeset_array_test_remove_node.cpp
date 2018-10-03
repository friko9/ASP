#include "treeset_array_test.h"

#include <algorithm>
#include <limits>
#include <tuple>

namespace test_treeset_array
{
    struct treeset_array_test_remove_node
	: public treeset_array_test_case
    {
	size_t del_index;
	side_t del_side = side_t::left;
	std::vector<node_t> expected_values;
	std::vector<size_t> expected_indexes;
	score_t compare(std::vector<node_t>& vals1,std::vector<size_t> &indexes1,
			std::vector<node_t>& vals2,std::vector<size_t> &indexes2)
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
		return score;
	    }
	test_result test()
	    {
		test_plug.remove_node(container, del_index, del_side);
		if( test_plug.get_indexes(container).size() == expected_indexes.size()  )
		    return compare(expected_values,expected_indexes,
				   test_plug.get_values(container),test_plug.get_indexes(container));
		else
		    return score_t(false);
	    }
    };
	
    struct treesize2_c_remove_node_c_state_empty
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2;
		data = {{1,0}};
		del_index = 1;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,decltype(data)());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize2_c_remove_node_c_state_empty);

    struct treesize8_c_remove_node_c_state_null
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0}};
		del_index = 1;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,decltype(data)());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_remove_node_c_state_null);

    struct treesize4_c_l_remove_node_l_state_cxc
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_remove_node_l_state_cxc);

    struct treesize16_c_l_remove_node_l_state_cxc
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_remove_node_l_state_cxc);

    struct treesize4_c_l_remove_node_c_state_cxl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1}};
		del_index = 1;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_remove_node_c_state_cxl);

    struct treesize16_c_l_remove_node_c_state_cxl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1}};
		del_index = 1;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_remove_node_c_state_cxl);

    struct treesize4_c_r_remove_node_c_state_cxr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{3,1}};
		del_index = 1;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_remove_node_c_state_cxr);

    struct treesize16_c_r_remove_node_c_state_cxr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{3,1}};
		del_index = 1;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_remove_node_c_state_cxr);

    struct treesize4_c_l_r_remove_node_l_state_cxc_rxr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_l_state_cxc_rxr);

    struct treesize16_c_l_r_remove_node_l_state_cxc_rxr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_l_state_cxc_rxr);

    struct treesize4_c_l_r_remove_node_l_state_cxc_lxl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 3;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_l_state_cxc_lxl);

    struct treesize16_c_l_r_remove_node_r_state_cxc_lxl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 3;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_r_state_cxc_lxl);

    struct treesize4_c_l_r_remove_node_c_on_left_state_cxl_rxr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_c_on_left_state_cxl_rxr);

    struct treesize16_c_l_r_remove_node_c_on_left_state_cxl_rxr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{3,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_c_on_left_state_cxl_rxr);

    struct treesize4_c_l_r_remove_node_c_on_right_state_cxr_lxl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_remove_node_c_on_right_state_cxr_lxl);

    struct treesize16_c_l_r_remove_node_c_on_right_state_cxr_lxl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_remove_node_c_on_right_state_cxr_lxl);

    struct treesize8_c_l_r_ll_rr_remove_node_l_state_cxc_lxll_rxr_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,1},{7,2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_l_state_cxc_lxll_rxr_rrxrr);

    struct treesize16_c_l_r_ll_rr_remove_node_l_state_cxc_lxll_rxr_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,1},{7,2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_l_state_cxc_lxll_rxr_rrxrr);

    struct treesize8_c_l_r_ll_rr_remove_node_r_state_cxc_lxl_llxll_rxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 3;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1},{3,2},{4,-2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_r_state_cxc_lxl_llxll_rxrr);

    struct treesize16_c_l_r_ll_rr_remove_node_r_state_cxc_lxl_llxll_rxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 3;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1},{3,2},{4,-2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_r_state_cxc_lxl_llxll_rxrr);

    struct treesize8_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_rxr_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{2,-2},{3,1},{7,2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_rxr_rrxrr);

    struct treesize16_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_rxr_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{2,-2},{3,1},{7,2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_c_on_left_state_cxl_lxll_rxr_rrxrr);

    struct treesize8_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_lxl_llxll_rxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-1},{3,2},{4,-2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_lxl_llxll_rxrr);

    struct treesize16_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_lxl_llxll_rxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-1},{3,1},{4,-2},{7,2}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-1},{3,2},{4,-2}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_ll_rr_remove_node_c_on_right_state_cxr_lxl_llxll_rxrr);

    struct treesize8_c_l_r_lr_rl_remove_node_l_state_cxc_lxlr_rxr_rlxlr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1},{3,2},{6,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_l_state_cxc_lxlr_rxr_rlxlr);

    struct treesize16_c_l_r_lr_rl_remove_node_l_state_cxc_lxlr_rxr_rlxlr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 2;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1},{3,2},{6,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_l_state_cxc_lxlr_rxr_rlxlr);

    struct treesize8_c_l_r_lr_rl_remove_node_r_state_cxc_lxl_lrxlr_rxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 3;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,1},{5,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_r_state_cxc_lxl_lrxlr_rxrl);

    struct treesize16_c_l_r_lr_rl_remove_node_r_state_cxc_lxl_lrxlr_rxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 3;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,1},{5,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_r_state_cxc_lxl_lrxlr_rxrl);

    struct treesize8_c_l_r_lr_rl_remove_node_c_on_left_state_cxl_lxlr_rxr_rlxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{2,-2},{3,2},{6,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_c_on_left_state_cxl_lxlr_rxr_rlxrl);

    struct treesize16_c_l_r_lr_rl_remove_node_c_on_left_state_cxl_lxlr_rxr_rlxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{2,-2},{3,2},{6,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_c_on_left_state_cxl_lxlr_rxr_rlxrl);

    struct treesize8_c_l_r_lr_rl_remove_node_c_on_right_state_cxr_lxl_lrxlr_rxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-2},{3,2},{5,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_r_lr_rl_remove_node_c_on_right_state_cxr_lxl_lrxlr_rxrl);

    struct treesize16_c_l_r_lr_rl_remove_node_c_on_right_state_cxr_lxl_lrxlr_rxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{5,-1},{6,1}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-2},{3,2},{5,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_lr_rl_remove_node_c_on_right_state_cxr_lxl_lrxlr_rxrl);

    struct treesize8_full8_remove_node_l_on_left_state_cxc_lxll_lrxlr_rxr_rlxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 2;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-3},{3,2},{5,-1},{6,1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_l_on_left_state_cxc_lxll_lrxlr_rxr_rlxrl_rrxrr);

    struct treesize16_full8_remove_node_l_on_left_state_cxc_lxll_lrxlr_rxr_rlxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 2;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-3},{3,2},{5,-1},{6,1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_l_on_left_state_cxc_lxll_lrxlr_rxr_rlxrl_rrxrr);

    struct treesize8_full8_remove_node_l_on_right_state_cxc_lxlr_llxll_rxr_rlxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 2;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1},{3,2},{4,-3},{6,1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_l_on_right_state_cxc_lxlr_llxll_rxr_rlxrl_rrxrr);

    struct treesize16_full8_remove_node_l_on_right_state_cxc_lxlr_llxll_rxr_rlxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 2;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-1},{3,2},{4,-3},{6,1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_l_on_right_state_cxc_lxlr_llxll_rxr_rlxrl_rrxrr);

    struct treesize8_full8_remove_node_r_on_left_state_cxc_lxl_lrxlr_llxll_rxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 3;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,1},{4,-3},{5,-1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_r_on_left_state_cxc_lxl_lrxlr_llxll_rxrl_rrxrr);

    struct treesize16_full8_remove_node_r_on_left_state_cxc_lxl_lrxlr_llxll_rxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 3;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,1},{4,-3},{5,-1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_r_on_left_state_cxc_lxl_lrxlr_llxll_rxrl_rrxrr);

    struct treesize8_full8_remove_node_r_on_right_state_cxc_lxl_lrxlr_llxll_rxrr_rlxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 3;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,3},{4,-3},{5,-1},{6,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_r_on_right_state_cxc_lxl_lrxlr_llxll_rxrr_rlxrl);

    struct treesize16_full8_remove_node_r_on_right_state_cxc_lxl_lrxlr_llxll_rxrr_rlxrl
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 3;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,0},{2,-2},{3,3},{4,-3},{5,-1},{6,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_r_on_right_state_cxc_lxl_lrxlr_llxll_rxrr_rlxrl);

    struct treesize8_full8_remove_node_c_on_left_state_cxlr_lxl_llxll_rxr_rlxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{2,-2},{3,2},{4,-3},{6,1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_c_on_left_state_cxlr_lxl_llxll_rxr_rlxrl_rrxrr);

    struct treesize16_full8_remove_node_c_on_left_state_cxlr_lxl_llxll_rxr_rlxrl_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,-1},{2,-2},{3,2},{4,-3},{6,1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_c_on_left_state_cxlr_lxl_llxll_rxr_rlxrl_rrxrr);

    struct treesize8_full8_remove_node_c_on_right_state_cxrl_lxl_lrxlr_llxll_rxr_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-2},{3,2},{4,-3},{5,-1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_full8_remove_node_c_on_right_state_cxrl_lxl_lrxlr_llxll_rxr_rrxrr);

    struct treesize16_full8_remove_node_c_on_right_state_cxrl_lxl_lrxlr_llxll_rxr_rrxrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-2},{3,2},{4,-3},{5,-1},{6,1},{7,3}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes) = make_data(tree_size,{{1,1},{2,-2},{3,2},{4,-3},{5,-1},{7,3}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_remove_node_c_on_right_state_cxrl_lxl_lrxlr_llxll_rxr_rrxrr);

    struct treesize16_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_full8_rll
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{11,-1},{12,1}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,{{1,-1},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{12,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_full8_rll);

    struct treesize32_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_full8_rll
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{11,-1},{12,1}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,{{1,-1},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{12,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrr_rll_remove_node_c_on_left_state_cxlrr_full8_rll);

    struct treesize16_full8_lrr_rll_remove_node_c_on_right_state_cxrll_full8_lrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{11,-1},{12,1}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,{{1,1},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{11,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full8_lrr_rll_remove_node_c_on_right_state_cxrll_full8_lrr);

    struct treesize32_full8_lrr_rll_remove_node_c_on_right_state_cxrll_full8_lrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{11,-1},{12,1}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,{{1,1},{2,-3},{3,3},{4,-4},{5,-2},{6,2},{7,4},{11,-1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrr_rll_remove_node_c_on_right_state_cxrll_full8_lrr);

    struct treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-10},{3,10},{4,-20},{5,-5},{6,5},{7,20},{10,-7},{13,7},{20,-8},{21,-6},{26,6},{27,8}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,
				{{1,-5},{2,-10},{3,10},{4,-20},{5,-7},{6,5},{7,20},{10,-8},{11,-6},{13,7},{26,6},{27,8}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr);

    struct treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0},{2,-10},{3,10},{4,-20},{5,-5},{6,5},{7,20},{10,-7},{13,7},{20,-8},{21,-6},{26,6},{27,8}};
		del_index = 1;
		del_side = side_t::left;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,
				{{1,-5},{2,-10},{3,10},{4,-20},{5,-7},{6,5},{7,20},{10,-8},{11,-6},{13,7},{26,6},{27,8}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_left_state_cxlr_lrxlrl_lrlxlrll_lrrxlrlr);

    struct treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-10},{3,10},{4,-20},{5,-5},{6,5},{7,20},{10,-7},{13,7},{20,-8},{21,-6},{26,6},{27,8}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,
				{{1,5},{2,-10},{3,10},{4,-20},{5,-5},{6,7},{7,20},{10,-7},{12,6},{13,8},{20,-8},{21,-6}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr);

    struct treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr
	: public treeset_array_test_remove_node
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 64;
		data = {{1,0},{2,-10},{3,10},{4,-20},{5,-5},{6,5},{7,20},{10,-7},{13,7},{20,-8},{21,-6},{26,6},{27,8}};
		del_index = 1;
		del_side = side_t::right;
		std::tie(expected_values,expected_indexes)
		    = make_data(tree_size,
				{{1,5},{2,-10},{3,10},{4,-20},{5,-5},{6,7},{7,20},{10,-7},{12,6},{13,8},{20,-8},{21,-6}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize64_full8_lrl_rlr_lrll_lrlr_rlrl_rlrr_remove_node_c_on_right_state_cxrl_rlxrlr_rllxrlrl_rlrxrlrr);
}
