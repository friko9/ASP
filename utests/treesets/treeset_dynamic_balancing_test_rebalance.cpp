#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct populated_c_rebalance_c_state_c1 
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { nullptr, nullptr, nullptr, data[0], 0 };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,data[0],1});
		score_t score = score_t(root_ok) + node_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_rebalance_c_state_c1);

    struct populated_c_l_rebalance_l_state_c2_l1
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 0 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 0 };
		node_l->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_l);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,nullptr,nullptr,data[0],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_rebalance_l_state_c2_l1);

    struct populated_c_r_rebalance_r_state_c2_r1
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[1], 0 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 0 };
		node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_r);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {nullptr,node_r,nullptr,data[0],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node,data[1],1});
		score_t score = score_t(root_ok) + node_cmp + node_r_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rebalance_r_state_c2_r1);

    struct populated_c_l_r_ll_rebalance_ll_state_c3_l2_r_ll1
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { node_ll, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 1 };
		node_r->up = node_l->up = node;
		node_ll->up = node_l;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_ll);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,node_r,nullptr,data[0],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {node_ll,nullptr,node,data[1],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2],node_r->height});
		node_cmp_t node_ll_cmp = test_node(node_l_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_ll_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_rebalance_ll_state_c3_l2_r_ll1);

    struct populated_c_l_r_lr_rebalance_lr_state_c3_l2_r_lr1
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 1 };
		node_r->up = node_l->up = node;
		node_lr->up = node_l;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_lr);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,node_r,nullptr,data[0],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,node_lr,node,data[1],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2],node_r->height});
		node_cmp_t node_lr_cmp = test_node(node_l_cmp.right_ok, node_lr, {nullptr,nullptr,node_l,data[3],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_lr_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_lr_rebalance_lr_state_c3_l2_r_lr1);

    struct populated_c_l_r_rl_rebalance_rl_state_c3_l_r2_rl1
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { node_rl, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 1 };
		node_r->up = node_l->up = node;
		node_rl->up = node_r;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_rl);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,node_r,nullptr,data[0],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1],node_l->height});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {node_rl,nullptr,node,data[2],2});
		node_cmp_t node_rl_cmp = test_node(node_r_cmp.right_ok, node_rl, {nullptr,nullptr,node_r,data[3],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_rl_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rebalance_rl_state_c3_l_r2_rl1);

    struct populated_c_l_r_rr_rebalance_rr_state_c3_l_r2_rr1
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -1, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, node_rr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 1 };
		node_r->up = node_l->up = node;
		node_rr->up = node_r;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_rr);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,node_r,nullptr,data[0],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1],node_l->height});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,node_rr,node,data[2],2});
		node_cmp_t node_rr_cmp = test_node(node_r_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_rr_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rr_rebalance_rr_state_c3_l_r2_rr1);

    struct populated_c2_l1_ll_rebalance_ll_state_c2xl_l1xll_r1xc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_ll;
	void configure()
	    {
		data = { 0, -1, -2 };
		node_ll = new node_t { nullptr, nullptr, nullptr, data[2], 0 };
		node_l = new node_t { node_ll, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 2 };
		node_l->up = node;
		node_ll->up = node_l;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_ll);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node_l;
		node_cmp_t node_cmp = test_node(root_ok, node_l, {node_ll,node,nullptr,data[1],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[2],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node, {nullptr,nullptr,node_l,data[0],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c2_l1_ll_rebalance_ll_state_c2xl_l1xll_r1xc);

    struct populated_c2_l1_lr_rebalance_lr_state_c2xlr_l1xl_r1xc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_lr;
	void configure()
	    {
		data = { 0, -2, -1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 1 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 2 };
		node_l->up = node;
		node_lr->up = node_l;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_lr);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node_lr;
		node_cmp_t node_cmp = test_node(root_ok, node_lr, {node_l,node,nullptr,data[2],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node_lr,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node, {nullptr,nullptr,node_lr,data[0],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c2_l1_lr_rebalance_lr_state_c2xlr_l1xl_r1xc);

    struct populated_c2_r1_rl_rebalance_rl_state_c2xrl_l1xc_r1xr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[2], 0 };
		node_r = new node_t { node_rl, nullptr, nullptr, data[1], 1 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 2 };
		node_r->up = node;
		node_rl->up = node_r;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_rl);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node_rl;
		node_cmp_t node_cmp = test_node(root_ok, node_rl, {node,node_r,nullptr,data[2],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node, {nullptr,nullptr,node_rl,data[0],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node_rl,data[1],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c2_r1_rl_rebalance_rl_state_c2xrl_l1xc_r1xr);

    struct populated_c2_r1_rr_rebalance_rr_state_c2xr_l1xc_r1xrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[2], 0 };
		node_r = new node_t { nullptr, node_rr, nullptr, data[1], 1 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 2 };
		node_r->up = node;
		node_rr->up = node_r;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_rr);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node_r;
		node_cmp_t node_cmp = test_node(root_ok, node_r, {node,node_rr,nullptr,data[1],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node, {nullptr,nullptr,node_r,data[0],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[2],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c2_r1_rr_rebalance_rr_state_c2xr_l1xc_r1xrr);

    struct populated_c3_l2_ll1_lr1_rebalance_l_state_c3xl_l1xll_r2xc_rl1xlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_l,*node_lr,*node_ll;
	void configure()
	    {
		data = { 0, -2, -1, -3 };
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { node_ll, node_lr, nullptr, data[1], 2 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 3 };
		node_l->up = node;
		node_ll->up = node_lr->up = node_l;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node_l;
		node_cmp_t node_cmp = test_node(root_ok, node_l, {node_ll,node,nullptr,data[1],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node, {node_lr,nullptr,node_l,data[0],2});
		node_cmp_t node_rl_cmp = test_node(node_r_cmp.left_ok, node_lr, {nullptr,nullptr,node,data[2],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_rl_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c3_l2_ll1_lr1_rebalance_l_state_c3xl_l1xll_r2xc_rl1xlr);


    struct populated_c3_r2_rl1_rr1_rebalance_rr_state_c2xr_l1xc_r1xrr_lr1xrl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*node_rl,*node_rr;
	void configure()
	    {
		data = { 0, 2, 1, 3 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_r = new node_t { node_rl, node_rr, nullptr, data[1], 2 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 3 };
		node_r->up = node;
		node_rl->up = node_rr->up = node_r;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.rebalance(container, node_rr);
		auto new_root = test_plug.get_root(container);
		bool root_ok = new_root == node_r;
		node_cmp_t node_cmp = test_node(root_ok, node_r, {node,node_rr,nullptr,data[1],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node, {nullptr,node_rl,node_r,data[0],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3],1});
		node_cmp_t node_lr_cmp = test_node(node_l_cmp.right_ok, node_rl, {nullptr,nullptr,node,data[2],1});
		score_t score = score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_lr_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c3_r2_rl1_rr1_rebalance_rr_state_c2xr_l1xc_r1xrr_lr1xrl);

}
