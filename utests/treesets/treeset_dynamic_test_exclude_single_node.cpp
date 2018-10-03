#include "treeset_dynamic_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic
{
    struct populated_c_exclude_single_node_c_on_left_return_c_state_empty
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { nullptr, nullptr, data[0] };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node, nullptr, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == nullptr;
		score_t score = score_t(del_node_ok) + score_t(root_ok);
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_exclude_single_node_c_on_left_return_c_state_empty);

    struct populated_c_exclude_single_node_c_on_right_return_c_state_empty
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { nullptr, nullptr, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node, nullptr, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == nullptr;
		score_t score = score_t(del_node_ok) + score_t(root_ok);
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_exclude_single_node_c_on_right_return_c_state_empty);

    struct populated_c_r_exclude_single_node_r_on_right_return_r_state_cxc
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { nullptr, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_r, node, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {nullptr,nullptr,data[0]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_exclude_single_node_r_on_right_return_r_state_cxc);

    struct populated_c_l_exclude_single_node_l_on_left_return_l_state_cxc
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, nullptr, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_l, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {nullptr,nullptr,data[0]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_exclude_single_node_l_on_left_return_l_state_cxc);

    struct populated_c_r_exclude_single_node_c_on_right_return_c_state_cxr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { nullptr, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node, nullptr, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_r;
		node_cmp_t root_cmp  = test_node(root_ok, node_r, {nullptr,nullptr,data[1]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_exclude_single_node_c_on_right_return_c_state_cxr);

    struct populated_c_l_exclude_single_node_c_on_left_return_c_state_cxl
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, nullptr, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node, nullptr, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_l;
		node_cmp_t root_cmp  = test_node(root_ok, node_l, {nullptr,nullptr,data[1]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_exclude_single_node_c_on_left_return_c_state_cxl);

    struct populated_c_l_r_exclude_single_node_l_on_left_return_l_state_cxc_rxr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_l, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {nullptr,node_r,data[0]});
		node_cmp_t node_r_cmp  = test_node(root_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_exclude_single_node_l_on_left_return_l_state_cxc_rxr);

    struct populated_c_l_r_exclude_single_node_r_on_right_return_r_state_cxc_lxl
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_r, node, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {node_l,nullptr,data[0]});
		node_cmp_t node_l_cmp  = test_node(root_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_l_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_exclude_single_node_r_on_right_return_r_state_cxc_lxl);

    struct populated_c_l_r_ll_exclude_single_node_l_on_left_return_l_state_cxc_lxll_rxr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { node_ll, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_l, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {node_ll,node_r,data[0]});
		node_cmp_t node_l_cmp  = test_node(root_cmp.left_ok, node_ll, {nullptr,nullptr,data[3]});
		node_cmp_t node_r_cmp  = test_node(root_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_exclude_single_node_l_on_left_return_l_state_cxc_lxll_rxr);

    struct populated_c_l_r_lr_exclude_single_node_l_on_right_return_l_state_cxc_lxlr_rxr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, node_lr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_l, node, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_l;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {node_lr,node_r,data[0]});
		node_cmp_t node_l_cmp  = test_node(root_cmp.left_ok, node_lr, {nullptr,nullptr,data[3]});
		node_cmp_t node_r_cmp  = test_node(root_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_lr_exclude_single_node_l_on_right_return_l_state_cxc_lxlr_rxr);

    struct populated_c_l_r_rl_exclude_single_node_r_on_left_return_r_state_cxc_lxl_rxrl
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { node_rl, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_r, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {node_l,node_rl,data[0]});
		node_cmp_t node_l_cmp  = test_node(root_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp  = test_node(root_cmp.right_ok, node_rl, {nullptr,nullptr,data[3]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_exclude_single_node_r_on_left_return_r_state_cxc_lxl_rxrl);

    struct populated_c_l_r_rr_exclude_single_node_r_on_right_return_r_state_cxc_lxl_rxrr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -2, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, node_rr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* del_node = test_plug.exclude_single_node(container, node_r, node, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node_r;
		bool root_ok = new_root == node;
		node_cmp_t root_cmp  = test_node(root_ok, node, {node_l,node_rr,data[0]});
		node_cmp_t node_l_cmp  = test_node(root_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp  = test_node(root_cmp.right_ok, node_rr, {nullptr,nullptr,data[3]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rr_exclude_single_node_r_on_right_return_r_state_cxc_lxl_rxrr);
}
