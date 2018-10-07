#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct populated_c_l_lr_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxll_rxc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_lr;
	void configure()
	    {
		data = { 0, -2, -1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 2 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 3 };
		node_l->up = node;
		node_lr->up = node_l;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_lr;
		bool root_ok = root == node_lr;
		node_cmp_t root_cmp = test_node( root_ok, node_lr, {node_l,node,nullptr,data[2], 2} );
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node, {nullptr,nullptr,node_lr,data[0], 1});
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node_l, {nullptr,nullptr,node_lr,data[1], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_r_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_lr_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxll_rxc);

    struct populated_c_r_rl_rebalance_case_2_c_on_right_return_rl_state_cxrl_lxc_rxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, nullptr, nullptr, data[1], 2};
		node = new node_t { nullptr, node_r, nullptr, data[0], 3};
		node_r->up = node;
		node_rl->up = node_r;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = root == node_rl;
		node_cmp_t root_cmp = test_node( root_ok, node_rl, {node,node_r,nullptr,data[2], 2} );
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node_r, {nullptr,nullptr,node_rl,data[1], 1});
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node, {nullptr,nullptr,node_rl,data[0], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_r_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rl_rebalance_case_2_c_on_right_return_rl_state_cxrl_lxc_rxr);

    struct populated_c_l_r_ll_lr_lrl_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxl_rxc_llxll_lrxlrl_rrxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr,*node_ll,*node_lrl;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -30 };
		node_lrl = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { node_lrl, nullptr, nullptr, data[4], 2};
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lrl->up = node_lr;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_lr;
		bool root_ok = root == node_lr;
		node_cmp_t root_cmp = test_node( root_ok, node_lr, {node_l,node,nullptr,data[4], 3} );
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node_l, {node_ll,node_lrl,node_lr,data[1], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node, {nullptr,node_r,node_lr,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,node_l,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});		
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lrl_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxl_rxc_llxll_lrxlrl_rrxr);

    struct populated_c_l_r_ll_lr_lrr_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxl_rxc_llxll_rlxlrr_rrxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr,*node_ll,*node_lrr;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -10 };
		node_lrr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { nullptr, node_lrr, nullptr, data[4], 2};
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lrr->up = node_lr;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_lr;
		bool root_ok = root == node_lr;
		node_cmp_t root_cmp = test_node( root_ok, node_lr, {node_l,node,nullptr,data[4], 3} );
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node_l, {node_ll,nullptr,node_lr,data[1], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node, {node_lrr,node_r,node_lr,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3], 1});
		node_cmp_t node_rl_cmp = test_node( node_r_cmp.left_ok, node_lrr, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});		
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lrr_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxl_rxc_llxll_rlxlrr_rrxr);

    struct populated_c_l_r_ll_lr_lrl_lrr_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxl_rxc_llxll_lrxlrl_rlxlrr_rrxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr,*node_ll,*node_lrl,*node_lrr;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -10,-30 };
		node_lrl = new node_t { nullptr, nullptr, nullptr, data[6], 1};
		node_lrr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { node_lrl, node_lrr, nullptr, data[4], 2};
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lrr->up = node_lrl->up = node_lr;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto root = test_plug.get_root(container);
		
		bool res_ok = res == node_lr;
		bool root_ok = root == node_lr;
		node_cmp_t root_cmp = test_node( root_ok, node_lr, {node_l,node,nullptr,data[4], 3} );
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node_l, {node_ll,node_lrl,node_lr,data[1], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node, {node_lrr,node_r,node_lr,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,node_l,data[6], 1});
		node_cmp_t node_rl_cmp = test_node( node_r_cmp.left_ok, node_lrr, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});		
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lrl_lrr_rebalance_case_2_c_on_left_return_lr_state_cxlr_lxl_rxc_llxll_lrxlrl_rlxlrr_rrxr);

    struct populated_c_l_r_rl_rr_rlr_rebalance_case_2_c_on_right_return_rl_state_cxrl_lxc_rxr_llxl_rlxrlr_rrxrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl,*node_rr,*node_rlr;
	void configure()
	    {
		data = { 0, 50, -50, 70, 20, 30 };
		node_rlr = new node_t { nullptr, nullptr, nullptr, data[5], 1 };
		node_rl = new node_t { nullptr, node_rlr, nullptr, data[4], 2 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 3 };
		node = new node_t { node_l, node_r, nullptr, data[0], 4 };
		node_l->up = node_r->up = node;
		node_rl->up = node_rr->up = node_r;
		node_rlr->up = node_rl;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = root == node_rl;
		node_cmp_t root_cmp = test_node( root_ok, node_rl, {node,node_r,nullptr,data[4], 3} );
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node, {node_l,nullptr,node_rl,data[0], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node_r, {node_rlr,node_rr,node_rl,data[1], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[2], 1});
		node_cmp_t node_rl_cmp = test_node( node_l_cmp.right_ok, node_rlr, {nullptr,nullptr,node_r,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rr_rlr_rebalance_case_2_c_on_right_return_rl_state_cxrl_lxc_rxr_llxl_rlxrlr_rrxrr);

    struct populated_c_l_r_rl_rr_rll_rebalance_case_2_c_on_right_return_lr_state_cxrl_lxc_rxr_llxl_lrxrll_rrxrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl,*node_rr,*node_rll;
	void configure()
	    {
		data = { 0, 50, -50, 70, 20, 10 };
		node_rll = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rl = new node_t { node_rll, nullptr, nullptr, data[4], 2};
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_l = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		node_l->up = node_r->up = node;
		node_rr->up = node_rl->up = node_r;
		node_rll->up = node_rl;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = root == node_rl;
		node_cmp_t root_cmp = test_node( root_ok, node_rl, {node,node_r,nullptr,data[4], 3});
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node, {node_l,node_rll,node_rl,data[0], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node_r, {nullptr,node_rr,node_rl,data[1], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[2], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rll, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rr_rll_rebalance_case_2_c_on_right_return_lr_state_cxrl_lxc_rxr_llxl_lrxrll_rrxrr);

    struct populated_c_l_r_rl_rr_rll_rlr_rebalance_case_2_c_on_right_return_rl_state_cxrl_lxc_rxr_llxl_lrxrll_rlxrlr_rrxrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl,*node_rr,*node_rll,*node_rlr;
	void configure()
	    {
		data = { 0, 50, -50, 70, 20, 10, 30 };
		node_rlr = new node_t { nullptr, nullptr, nullptr, data[6], 1};
		node_rll = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rl = new node_t { node_rll, node_rlr, nullptr, data[4], 2};
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_l = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		node_l->up = node_r->up = node;
		node_rr->up = node_rl->up = node_r;
		node_rll->up = node_rlr->up = node_rl;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = root == node_rl;
		node_cmp_t root_cmp = test_node( root_ok, node_rl, {node,node_r,nullptr,data[4], 3});
		node_cmp_t node_l_cmp = test_node( root_cmp.left_ok, node, {node_l,node_rll,node_rl,data[0], 2});
		node_cmp_t node_r_cmp = test_node( root_cmp.right_ok, node_r, {node_rlr,node_rr,node_rl,data[1], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[2], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rll, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rl_cmp = test_node( node_r_cmp.left_ok, node_rlr, {nullptr,nullptr,node_r,data[6], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rr_rll_rlr_rebalance_case_2_c_on_right_return_rl_state_cxrl_lxc_rxr_llxl_lrxrll_rlxrlr_rrxrr);
    
    struct populated_c_l_ll_llr_rebalance_case_2_l_on_left_return_llr_state_cxc_lxllr_llxll_lrxl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_lr;
	void configure()
	    {
		data = { 0, -2, -1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 2};
		node = new node_t { node_l, nullptr, nullptr, data[0], 3};
		root = new node_t { node, nullptr, nullptr, 99, 4};
		node->up = root;
		node_l->up = node;
		node_lr->up = node_l;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto new_root = test_plug.get_root(container);
		
		bool res_ok = res == node_lr;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_lr,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_lr, {node_l,node,root,data[2], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node, {nullptr,nullptr,node_lr,data[0], 1});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node_l, {nullptr,nullptr,node_lr,data[1], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_llr_rebalance_case_2_l_on_left_return_llr_state_cxc_lxllr_llxll_lrxl);

    struct populated_c_l_lr_lrl_rebalance_case_2_l_on_right_return_lrl_state_cxc_lxlrl_llxl_lrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, nullptr, nullptr, data[1], 2};
		node = new node_t { nullptr, node_r, nullptr, data[0], 3};
		root = new node_t { node, nullptr, nullptr, 99, 4};
		node->up = root;
		node_r->up = node;
		node_rl->up = node_r;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_rl,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_rl, {node,node_r,root,data[2], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node_r, {nullptr,nullptr,node_rl,data[1], 1});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node, {nullptr,nullptr,node_rl,data[0], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_lr_lrl_rebalance_case_2_l_on_right_return_lrl_state_cxc_lxlrl_llxl_lrxlr);

    struct populated_c_l_ll_lr_lll_llr_llrl_rebalance_case_2_l_on_left_return_llr_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr,*node_ll,*node_lrl;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -30 };
		node_lrl = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { node_lrl, nullptr, nullptr, data[4], 2};
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lrl->up = node_lr;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_lr;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_lr,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_lr, {node_l,node,root,data[4], 3});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node_l, {node_ll,node_lrl,node_lr,data[1], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node, {nullptr,node_r,node_lr,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,node_l,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lll_llr_llrl_rebalance_case_2_l_on_left_return_llr_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrrxlr);

    struct populated_c_l_ll_lr_lll_llr_llrr_rebalance_case_2_l_on_left_return_lr_state_cxc_lxllr_llxll_lrxl_lllxlll_lrlxllrr_lrrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr,*node_ll,*node_lrr;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -10 };
		node_lrr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { nullptr, node_lrr, nullptr, data[4], 2};
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lrr->up = node_lr;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_lr;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_lr,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_lr, {node_l,node,root,data[4], 3});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node_l, {node_ll,nullptr,node_lr,data[1], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node, {node_lrr,node_r,node_lr,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3], 1});
		node_cmp_t node_rl_cmp = test_node( node_l_cmp.right_ok, node_lrr, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lll_llr_llrr_rebalance_case_2_l_on_left_return_lr_state_cxc_lxllr_llxll_lrxl_lllxlll_lrlxllrr_lrrxlr);

    struct populated_c_l_ll_lr_lll_llr_llrl_llrr_rebalance_case_2_l_on_left_return_lr_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrlxllrrr_lrr_lr
     	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr,*node_ll,*node_lrl,*node_lrr;
	void configure()
	    {
		data = { 0, -50, 50, -70, -20, -10,-30 };
		node_lrl = new node_t { nullptr, nullptr, nullptr, data[6], 1};
		node_lrr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_lr = new node_t { node_lrl, node_lrr, nullptr, data[4], 2};
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_ll->up = node_lr->up = node_l;
		node_lrr->up = node_lrl->up = node_lr;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_l, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_lr;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_lr,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_lr, {node_l,node,root,data[4], 3});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node_l, {node_ll,node_lrl,node_lr,data[1], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node, {node_lrr,node_r,node_lr,data[0], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,node_l,data[6], 1});
		node_cmp_t node_rl_cmp = test_node( node_l_cmp.right_ok, node_lrr, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2], 1});
		delete res;
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lll_llr_llrl_llrr_rebalance_case_2_l_on_left_return_lr_state_cxc_lxllr_llxll_lrxl_lllxlll_llrxllrl_lrlxllrrr_lrr_lr);

    struct populated_c_l_ll_lr_lrl_lrr_lrlr_rebalance_case_2_l_on_right_return_rl_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrlr_lrrxlrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl,*node_rr,*node_rlr;
	void configure()
	    {
		data = { 0, 50, -50, 70, 20, 30 };
		node_rlr = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rl = new node_t { nullptr, node_rlr, nullptr, data[4], 2};
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_l = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_rl->up = node_rr->up = node_r;
		node_rlr->up = node_rl;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_rl,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_rl, {node,node_r,root,data[4], 3});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node, {node_l,nullptr,node_rl,data[0], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node_r, {node_rlr,node_rr,node_rl,data[1], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[2], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rlr, {nullptr,nullptr,node_r,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3], 1});
		delete res;

		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_lrr_lrlr_rebalance_case_2_l_on_right_return_rl_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrlr_lrrxlrr);

    struct populated_c_l_ll_lr_lrl_lrr_lrll_rebalance_case_2_l_on_right_return_lr_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrrxlrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl,*node_rr,*node_rll;
	void configure()
	    {
		data = { 0, 50, -50, 70, 20, 10 };
		node_rll = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rl = new node_t { node_rll, nullptr, nullptr, data[4], 2};
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_l = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_rr->up = node_rl->up = node_r;
		node_rll->up = node_rl;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_rl,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_cmp.left_ok, node_rl, {node,node_r,root,data[4], 3});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node, {node_l,node_rll,node_rl,data[0], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node_r, {nullptr,node_rr,node_rl,data[1], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[2], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rll, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3], 1});
		delete res;

		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_lrr_lrll_rebalance_case_2_l_on_right_return_lr_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrrxlrr);

    struct populated_c_l_ll_lr_lrl_lrr_lrll_lrlr_rebalance_case_2_l_on_right_return_rl_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrlxlrlr_lrrxlrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl,*node_rr,*node_rll,*node_rlr;
	void configure()
	    {
		data = { 0, 50, -50, 70, 20, 10, 30 };
		node_rlr = new node_t { nullptr, nullptr, nullptr, data[6], 1};
		node_rll = new node_t { nullptr, nullptr, nullptr, data[5], 1};
		node_rl = new node_t { node_rll, node_rlr, nullptr, data[4], 2};
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1};
		node_l = new node_t { nullptr, nullptr, nullptr, data[2], 1};
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 3};
		node = new node_t { node_l, node_r, nullptr, data[0], 4};
		root = new node_t { node, nullptr, nullptr, 99, 5};
		node->up = root;
		node_l->up = node_r->up = node;
		node_rr->up = node_rl->up = node_r;
		node_rll->up = node_rlr->up = node_rl;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		auto res = test_plug.rebalance_case_2(container, node_r, node);
		auto new_root = test_plug.get_root(container);

		bool res_ok = res == node_rl;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node( root_ok, root, {node_rl,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node( root_ok, node_rl, {node,node_r,root,data[4], 3});
		node_cmp_t node_l_cmp = test_node( node_cmp.left_ok, node, {node_l,node_rll,node_rl,data[0], 2});
		node_cmp_t node_r_cmp = test_node( node_cmp.right_ok, node_r, {node_rlr,node_rr,node_rl,data[1], 2});
		node_cmp_t node_ll_cmp = test_node( node_l_cmp.left_ok, node_l, {nullptr,nullptr,node,data[2], 1});
		node_cmp_t node_lr_cmp = test_node( node_l_cmp.right_ok, node_rll, {nullptr,nullptr,node,data[5], 1});
		node_cmp_t node_rl_cmp = test_node( node_r_cmp.left_ok, node_rlr, {nullptr,nullptr,node_r,data[6], 1});
		node_cmp_t node_rr_cmp = test_node( node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3], 1});
		delete res;
		
		score_t score = score_t(res_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp
		    + node_ll_cmp + node_lr_cmp + node_rl_cmp + node_rr_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_lrr_lrll_lrlr_rebalance_case_2_l_on_right_return_rl_state_cxc_lxlrl_llxl_lrxlr_lllxll_llrxlrll_lrlxlrlr_lrrxlrr);
}
