#include "treeset_dynamic_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic
{
    struct populated_c_l_r_exclude_double_node_c_on_left_return_c_state_cxl_rxr
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
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_l;
		node_cmp_t node_cmp = test_node(root_ok, node_l, {nullptr,node_r,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_exclude_double_node_c_on_left_return_c_state_cxl_rxr);

    struct populated_c_l_r_exclude_double_node_c_on_right_return_c_state_cxr_lxl
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
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_r;
		node_cmp_t node_cmp = test_node(root_ok, node_r, {node_l,nullptr,data[2]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_l_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_exclude_double_node_c_on_right_return_c_state_cxr_lxl);

    struct populated_c_l_r_ll_exclude_double_node_c_on_left_return_c_state_cxl_rxr_lxll
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
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_l;
		node_cmp_t node_cmp = test_node(root_ok, node_l, {node_ll,node_r,data[1]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_ll, {nullptr,nullptr,data[3]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_exclude_double_node_c_on_left_return_c_state_cxl_rxr_lxll);

    struct populated_c_l_r_rr_exclude_double_node_c_on_right_return_c_state_cxr_lxl_rxrr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -1, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, node_rr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_r;
		node_cmp_t node_cmp = test_node(root_ok, node_r, {node_l,node_rr,data[2]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rr, {nullptr,nullptr,data[3]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rr_exclude_double_node_c_on_right_return_c_state_cxr_lxl_rxrr);

    struct populated_c_l_r_lr_exclude_double_node_c_on_left_return_c_state_cxlr_lxl_rxr
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
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_lr;
		node_cmp_t node_cmp = test_node(root_ok, node_lr, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_lr_exclude_double_node_c_on_left_return_c_state_cxlr_lxl_rxr);

    struct populated_c_l_r_rl_exclude_double_node_c_on_right_return_c_state_cxrl_lxl_rxr
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
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_rl;
		node_cmp_t node_cmp = test_node(root_ok, node_rl, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_exclude_double_node_c_on_right_return_c_state_cxrl_lxl_rxr);

    struct populated_c_l_r_lr_lrl_exclude_double_node_c_on_left_return_c_state_cxlr_lxl_rxr_lrxlrl
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr,*node_lrl;
	void configure()
	    {
		data = { 0, -3, 1, -1, -2 };
		node_lrl = new node_t { nullptr, nullptr, data[4] };
		node_lr = new node_t { node_lrl, nullptr, data[3] };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, node_lr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_lr;
		node_cmp_t node_cmp = test_node(root_ok, node_lr, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,node_lrl,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		node_cmp_t node_lr_cmp = test_node(node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,data[4]});
		score_t score = score_t(del_node_ok) + score_t(root_ok)
		    + node_cmp + node_l_cmp + node_r_cmp + node_lr_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_lr_lrl_exclude_double_node_c_on_left_return_c_state_cxlr_lxl_rxr_lrxlrl);

    struct populated_c_l_r_rl_rlr_exclude_double_node_c_on_right_return_c_state_cxrl_lxl_rxr_rlxrlr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl,*node_rlr;
	void configure()
	    {
		data = { 0, -1, 3, 1, 2 };
		node_rlr = new node_t { nullptr, nullptr, data[4] };
		node_rl = new node_t { nullptr, node_rlr, data[3] };
		node_r = new node_t { node_rl, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool root_ok = new_root == node_rl;
		node_cmp_t node_cmp = test_node(root_ok, node_rl, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {node_rlr,nullptr,data[2]});
		node_cmp_t node_rl_cmp = test_node(node_r_cmp.left_ok, node_rlr, {nullptr,nullptr,data[4]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + node_cmp + node_l_cmp + node_r_cmp + node_rl_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rlr_exclude_double_node_c_on_right_return_c_state_cxrl_lxl_rxr_rlxrlr);

    struct populated_c_l_ll_lr_exclude_double_node_l_on_left_return_l_state_cxc_lxll_lrxlr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_l,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_l, {nullptr,node_r,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_exclude_double_node_l_on_left_return_l_state_cxc_lxll_lrxlr);

    struct populated_c_l_ll_lr_exclude_double_node_l_on_right_return_l_state_cxc_lxlr_llxll
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_r,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_r, {node_l,nullptr,data[2]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_exclude_double_node_l_on_right_return_l_state_cxc_lxlr_llxll);

    struct populated_c_l_ll_lr_lll_exclude_double_node_l_on_left_return_l_state_cxc_lxll_lrxlr_llxlll
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { node_ll, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_l,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_l, {node_ll,node_r,data[1]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_ll, {nullptr,nullptr,data[3]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lll_exclude_double_node_l_on_left_return_l_state_cxc_lxll_lrxlr_llxlll);

    struct populated_c_l_ll_lr_lrr_exclude_double_node_l_on_right_return_l_state_cxc_lxlr_llxll_lrxlrr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -1, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, node_rr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_r,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_r, {node_l,node_rr,data[2]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rr, {nullptr,nullptr,data[3]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrr_exclude_double_node_l_on_right_return_l_state_cxc_lxlr_llxll_lrxlrr);
    struct populated_c_l_ll_lr_llr_exclude_double_node_l_on_left_return_l_state_cxc_lxllr_llxll_lrxlr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, node_lr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_lr,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_lr, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_llr_exclude_double_node_l_on_left_return_l_state_cxc_lxllr_llxll_lrxlr);

    struct populated_c_l_ll_lr_lrl_exclude_double_node_l_on_right_return_l_state_cxc_lxlrl_llxll_lrxlr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, data[3] };
		node_r = new node_t { node_rl, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_rl,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_rl, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		score_t score = score_t(del_node_ok) + score_t(root_ok) + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_exclude_double_node_l_on_right_return_l_state_cxc_lxlrl_llxll_lrxlr);

    struct populated_c_l_ll_lr_llr_llrl_exclude_double_node_l_on_left_return_l_state_cxc_lxllr_llxll_lrxlr_llrxllrl
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr,*node_lrl;
	void configure()
	    {
		data = { 0, -3, 1, -1, -2 };
		node_lrl = new node_t { nullptr, nullptr, data[4] };
		node_lr = new node_t { node_lrl, nullptr, data[3] };
		node_r = new node_t { nullptr, nullptr, data[2] };
		node_l = new node_t { nullptr, node_lr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_lr,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_lr, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,node_lrl,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,data[2]});
		node_cmp_t node_lr_cmp = test_node(node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,data[4]});
		score_t score = score_t(del_node_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp + node_lr_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_llr_llrl_exclude_double_node_l_on_left_return_l_state_cxc_lxllr_llxll_lrxlr_llrxllrl);

    struct populated_c_l_ll_lr_lrl_lrlr_exclude_double_node_l_on_right_return_l_state_cxc_lxlrl_llxll_lrxlr_lrlxlrlr
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl,*node_rlr;
	void configure()
	    {
		data = { 0, -1, 3, 1, 2 };
		node_rlr = new node_t { nullptr, nullptr, data[4] };
		node_rl = new node_t { nullptr, node_rlr, data[3] };
		node_r = new node_t { node_rl, nullptr, data[2] };
		node_l = new node_t { nullptr, nullptr, data[1] };
		node = new node_t { node_l, node_r, data[0] };
		root = new node_t { node, nullptr, 99 };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_rl,nullptr,99});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_rl, {node_l,node_r,data[3]});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,data[1]});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {node_rlr,nullptr,data[2]});
		node_cmp_t node_rl_cmp = test_node(node_r_cmp.left_ok, node_rlr, {nullptr,nullptr,data[4]});
		score_t score = score_t(del_node_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp + node_rl_cmp;
		delete del_node;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_lrlr_exclude_double_node_l_on_right_return_l_state_cxc_lxlrl_llxll_lrxlr_lrlxlrlr);
}
