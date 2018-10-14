#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct populated_c_exclude_single_node_c_on_left_return_c_null_state_empty
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { nullptr, nullptr, nullptr, data[0], 1 };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == nullptr;
		bool root_ok = new_root == nullptr;
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok);
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_exclude_single_node_c_on_left_return_c_null_state_empty);

    struct populated_c_exclude_single_node_c_on_right_return_c_null_state_empty
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { nullptr, nullptr, nullptr, data[0], 1 };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == nullptr;
		bool root_ok = new_root == nullptr;
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok);
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_exclude_single_node_c_on_right_return_c_null_state_empty);

    struct populated_c_r_exclude_single_node_c_on_right_return_c_r_null_state_cxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 2 };
		node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == nullptr;
		bool root_ok = new_root == node_r;
		node_cmp_t node_cmp = test_node(root_ok, node_r, {nullptr,nullptr,nullptr,data[1],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok) + node_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_exclude_single_node_c_on_right_return_c_r_null_state_cxr);
    
    struct populated_c_r_exclude_single_node_r_on_right_return_c_c_right_state_cxc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 2 };
		node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_r, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,data[0],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok) + node_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_exclude_single_node_r_on_right_return_c_c_right_state_cxc);

    struct populated_c_l_exclude_single_node_c_on_left_return_c_l_null_state_cxl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 2 };
		node_l->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == nullptr;
		bool root_ok = new_root == node_l;
		node_cmp_t node_cmp = test_node(root_ok, node_l, {nullptr,nullptr,nullptr,data[1],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok) + node_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_exclude_single_node_c_on_left_return_c_l_null_state_cxl);
    
    struct populated_c_l_exclude_single_node_l_on_left_return_l_c_left_state_cxc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, nullptr, nullptr, data[0], 2 };
		node_l->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_l, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,data[0],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok) + node_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_exclude_single_node_l_on_left_return_l_c_left_state_cxc);

    struct populated_c_l_r_exclude_single_node_l_on_left_return_l_c_left_state_cxc_rxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 2 };
		node_l->up = node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_l, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {nullptr,node_r,nullptr,data[0],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + node_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_exclude_single_node_l_on_left_return_l_c_left_state_cxc_rxr);

    struct populated_c_l_r_exclude_single_node_r_on_right_return_r_c_right_state_cxc_lxl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 2 };
		node_l->up = node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_r, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,nullptr,nullptr,data[0],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + node_cmp + node_l_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_exclude_single_node_r_on_right_return_r_c_right_state_cxc_lxl);

    struct populated_c_l_r_ll_exclude_single_node_l_on_left_return_l_c_left_state_cxc_lxll_rxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { node_ll, nullptr, nullptr, data[1], 2 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		node_ll->up = node_l;
		node_l->up = node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_l, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_ll,node_r,nullptr,data[0],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_ll, {nullptr,nullptr,node,data[3],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_exclude_single_node_l_on_left_return_l_c_left_state_cxc_lxll_rxr);

    struct populated_c_l_r_lr_exclude_single_node_l_on_right_return_l_c_left_state_cxc_lxlr_rxr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 2 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		node_lr->up = node_l;
		node_l->up = node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_l, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_lr,node_r,nullptr,data[0],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_lr, {nullptr,nullptr,node,data[3],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_lr_exclude_single_node_l_on_right_return_l_c_left_state_cxc_lxlr_rxr);

    struct populated_c_l_r_rl_exclude_single_node_r_on_left_return_r_c_right_state_cxc_lxl_rxrl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { node_rl, nullptr, nullptr, data[2], 2 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		node_rl->up = node_r;
		node_l->up = node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_r, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,node_rl,nullptr,data[0],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rl, {nullptr,nullptr,node,data[3],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_exclude_single_node_r_on_left_return_r_c_right_state_cxc_lxl_rxrl);

    struct populated_c_l_r_rr_exclude_single_node_r_on_right_return_r_c_right_state_cxc_lxl_rxrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, node_rr, nullptr, data[2], 2 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		node_rr->up = node_r;
		node_l->up = node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_single_node(container, node_r, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool rebalance_ok = rebalance == node;
		bool root_ok = new_root == node;
		node_cmp_t node_cmp = test_node(root_ok, node, {node_l,node_rr,nullptr,data[0],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rr, {nullptr,nullptr,node,data[3],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rr_exclude_single_node_r_on_right_return_r_c_right_state_cxc_lxl_rxrr);
}
