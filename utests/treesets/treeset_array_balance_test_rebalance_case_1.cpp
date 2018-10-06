#include "treeset_array_balance_test.h"

#include <algorithm>
#include <limits>
/*
namespace test_treeset_array_balance
{
        struct treeset_array_balance_test_rebalance_case_1
	: public treeset_array_balance_test_case
    {
	size_t index;
	side_t side;
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
		test_plug.update_node_height(container, index);
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

    struct treesize8_c_l_ll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc
	: public treeset_array_balance_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{2,-1,2},{4,-2,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1}{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_l_ll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc);

    struct treesize16_c_l_ll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc
	: public treeset_array_balance_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{2,-1,2},{4,-2,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,-1,2},{2,-2,1}{3,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_ll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc);

    struct treesize8_c_r_rr_rebalance_case_1_c_on_right_return_r_state_cxr_lxc_rxrr
	: public treeset_array_balance_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,3},{3,1,2},{7,2,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1}{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_r_rr_rebalance_case_1_c_on_right_return_r_state_cxr_lxc_rxrr);

    struct treesize16_c_r_rr_rebalance_case_1_c_on_right_return_r_state_cxr_lxc_rxrr
	: public treeset_array_balance_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,3},{3,1,2},{7,2,1}};
		index = 1;
		side = side_t::right;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1}{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_rr_rebalance_case_1_c_on_right_return_r_state_cxr_lxc_rxrr);
    
    // TODO
    struct populated_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr
    	: public treeset_array_balance_test_move_nodes_down
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{1,0,4},{2,-10,3},{3,10,1},{4,-20,2},{5,-5,2},{8,-30,1}};
		index = 1;
		side = side_t::left;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,1,2},{2,0,1}{3,2,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr);
	: public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_ll,*node_lr,*node_lll;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -100 };
		node_lll = new node_t { nullptr, nullptr, nullptr, data[5], 1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[4], 1 };
		node_ll = new node_t { node_lll, nullptr, nullptr, data[3], 2 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3 };
		node = new node_t { node_l, node_r, nullptr, data[0], 4 };
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lll->up = node_ll;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_1(container, node_l, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_l;
		bool root_ok = root == node_l;
		node_cmp_t root_cmp = test_node( root_ok, node_l, {node_ll,node,nullptr,data[1], 3} );
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node_ll, {node_lll,nullptr,node_l,data[3], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node, {node_lr,node_r,node_l,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_lll, {nullptr,nullptr,node_ll,data[5], 1});
		node_cmp_t node_rl_cmp = test_node( node_r_cmp.left_ok, node_lr, {nullptr,nullptr,node,data[4], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});
		delete res;

		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_r_cmp + node_l_cmp
		    + node_ll_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lll_rebalance_case_1_c_on_left_return_l_state_cxl_lxll_rxc_llxlll_rlxlr_rrxr);
    
    struct populated_c_l_r_rr_rl_rrr_rebalance_case_1_c_on_right_return_r_state_cxr_lxc_rxrr_llxl_lrxrl_rrxrrr
	: public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rr,*node_rl,*node_rrr;
	void configure()
	    {
		data = { 0, -50, 50, 20, 70, 100 };
		node_rrr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rr = new node_t { nullptr, node_rrr, nullptr, data[4], 2};
		node_rl = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[2], 3};
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		node_l->up = node_r->up = node;
		node_rr->up = node_rl->up = node_r;
		node_rrr->up = node_rr;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_1(container, node_r, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_r;
		bool root_ok = root == node_r;
		node_cmp_t root_cmp = test_node( root_ok, node_r, {node,node_rr,nullptr,data[2], 3} );
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node, {node_l,node_rl,node_r,data[0], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node_rr, {nullptr,node_rrr,node_r,data[4], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rl, {nullptr,nullptr,node,data[3], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rrr, {nullptr,nullptr,node_rr,data[5], 1});
		delete res;
		
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_r_cmp + node_l_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rr_rl_rrr_rebalance_case_1_c_on_right_return_r_state_cxr_lxc_rxrr_llxl_lrxrl_rrxrrr);

    struct populated_c_l_ll_lll_rebalance_case_1_l_on_left_return_ll_state_cxc_lxll_rxl_llxlll
	: public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_ll;
	void configure()
	    {
		data = { 0, -1, -2 };
		node_ll = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, nullptr, nullptr, data[1], 2};
		node = new node_t { node_l, nullptr, nullptr, data[0], 3};
		root = new node_t { node, nullptr, nullptr, 99, 4};
		node->up = root;
		node_l->up = node;
		node_ll->up = node_l;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_1(container, node_l, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_l;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_l,nullptr,nullptr,99, root->height} );
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_l, {node_ll,node,root,data[1], 2} );
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node, {nullptr,nullptr,node_l,data[0], 1});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[2], 1});
		delete res;

		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lll_rebalance_case_1_l_on_left_return_ll_state_cxc_lxll_rxl_llxlll);

    struct populated_c_l_lr_lrr_rebalance_case_1_l_on_right_return_lr_state_cxc_lxlr_llxl_lrxlrr
	: public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { nullptr, node_rr, nullptr, data[1], 2};
		node = new node_t { nullptr, node_r, nullptr, data[0], 3};
		root = new node_t { node, nullptr, nullptr, 99, 4};
		node->up = root;
		node_r->up = node;
		node_rr->up = node_r;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_1(container, node_r, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_r;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_r,nullptr,nullptr,99, root->height} );
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_r, {node,node_rr,root,data[1], 2} );
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[2], 1});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node, {nullptr,nullptr,node_r,data[0], 1});
		delete res;

		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_lr_lrr_rebalance_case_1_l_on_right_return_lr_state_cxc_lxlr_llxl_lrxlrr);

    struct populated_c_l_ll_lr_lll_llr_llll_rebalance_case_1_l_on_left_return_ll_state_cxc_lxll_llxlll_lrxl_lllxllll_lrlxllr_lrrxlr
	: public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_ll,*node_lr,*node_lll;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -100 };
		node_lll = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { nullptr, nullptr, nullptr, data[4], 1};
		node_ll = new node_t { node_lll, nullptr, nullptr, data[3], 2};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lll->up = node_ll;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_1(container, node_l, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_l;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_l,nullptr,nullptr,99, root->height} );
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_l, {node_ll,node,root,data[1], 3} );
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node_ll, {node_lll,nullptr,node_l,data[3], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node, {node_lr,node_r,node_l,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_lll, {nullptr,nullptr,node_ll,data[5], 1});
		node_cmp_t node_rl_cmp = test_node( node_r_cmp.left_ok, node_lr, {nullptr,nullptr,node,data[4], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});
		delete res;

		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp + node_l_cmp
		    + node_ll_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lll_llr_llll_rebalance_case_1_l_on_left_return_ll_state_cxc_lxll_llxlll_lrxl_lllxllll_lrlxllr_lrrxlr);
    struct populated_c_l_ll_lr_lrr_lrl_lrrr_rebalance_case_1_l_on_right_return_lr_state_cxc_lxlr_llxl_lrxlrr_lllxll_llrxlrl_lrrxlrrr
	: public treeset_array_balance_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rr,*node_rl,*node_rrr;
	void configure()
	    {
		data = { 0, -50, 50, 20, 70, 100 };
		node_rrr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rr = new node_t { nullptr, node_rrr, nullptr, data[4], 2};
		node_rl = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[2], 3};
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_rr->up = node_rl->up = node_r;
		node_rrr->up = node_rr;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_1(container, node_r, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_r;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_r,nullptr,nullptr,99, root->height} );
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_r, {node,node_rr,root,data[2], 3} );
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node, {node_l,node_rl,node_r,data[0], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node_rr, {nullptr,node_rrr,node_r,data[4], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rl, {nullptr,nullptr,node,data[3], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rrr, {nullptr,nullptr,node_rr,data[5], 1});
		delete res;
		
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp + node_l_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrr_lrl_lrrr_rebalance_case_1_l_on_right_return_lr_state_cxc_lxlr_llxl_lrxlrr_lllxll_llrxlrl_lrrxlrrr);
}
*/
