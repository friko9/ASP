#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct populated_c_l_ll_lr_exclude_double_node_l_on_left_return_l_ll_left_state_cxc_lxll_lrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t {  node_l, node_r, nullptr, data[0], 2 };
		root = new node_t {  node, nullptr, nullptr, 99, 3 };
		node->up = root;
		node_r->up = node_l->up = node;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::left);
		auto new_root = test_plug.get_root(container);

		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_l;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_l,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_l, {nullptr,node_r,root,data[1],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node_l,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_r_cmp;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_exclude_double_node_l_on_left_return_l_ll_left_state_cxc_lxll_lrxlr);

    struct populated_c_l_ll_lr_exclude_double_node_l_on_right_return_l_lr_right_state_cxc_lxlr_llxll
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 2 };
		root = new node_t {  node, nullptr, nullptr, 99, 3 };
		node->up = root;
		node_r->up = node_l->up = node;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_r;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_r,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_r, {node_l,nullptr,root,data[2],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node_r,data[1],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_exclude_double_node_l_on_right_return_l_lr_right_state_cxc_lxlr_llxll);

    struct populated_c_l_ll_lr_lll_exclude_double_node_l_on_left_return_l_ll_left_state_cxc_lxll_llxlll_lrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { node_ll, nullptr, nullptr, data[1], 2 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		root = new node_t {  node, nullptr, nullptr, 99, 4 };
		node->up = root;
		node_r->up = node_l->up = node;
		node_ll->up = node_l;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_l;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_l,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_l, {node_ll,node_r,root,data[1],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_ll, {nullptr,nullptr,node_l,data[3],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node_l,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lll_exclude_double_node_l_on_left_return_l_ll_left_state_cxc_lxll_llxlll_lrxlr);

    struct populated_c_l_ll_lr_lrr_exclude_double_node_l_on_right_return_l_lr_left_state_cxc_lxlr_llxll_lrxlrr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -1, 1, 2 };
		node_rr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, node_rr, nullptr, data[2], 2 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		root = new node_t {  node, nullptr, nullptr, 99, 4 };
		node->up = root;
		node_r->up = node_l->up = node;
		node_rr->up = node_r;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_r;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_r,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_r, {node_l,node_rr,root,data[2],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node_r,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_rr, {nullptr,nullptr,node_r,data[3],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrr_exclude_double_node_l_on_right_return_l_lr_left_state_cxc_lxlr_llxll_lrxlrr);

    struct populated_c_l_ll_lr_llr_exclude_double_node_l_on_left_return_l_ll_right_state_cxc_lxllr_llxll_lrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 2 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		root = new node_t {  node, nullptr, nullptr, 99, 4 };
		node->up = root;
		node_r->up = node_l->up = node;
		node_lr->up = node_l;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_l;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_lr,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_lr, {node_l,node_r,root,data[3],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node_lr,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node_lr,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_llr_exclude_double_node_l_on_left_return_l_ll_right_state_cxc_lxllr_llxll_lrxlr);

    struct populated_c_l_ll_lr_lrl_exclude_double_node_l_on_right_return_l_lr_left_state_cxc_lxlrl_llxll_lrxlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_r = new node_t { node_rl, nullptr, nullptr, data[2], 2 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 3 };
		root = new node_t {  node, nullptr, nullptr, 99, 4 };
		node->up = root;
		node_r->up = node_l->up = node;
		node_rl->up = node_r;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_r;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_rl,nullptr,nullptr,99, root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_rl, {node_l,node_r,root,data[3],2});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node_rl,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node_rl,data[2],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_exclude_double_node_l_on_right_return_l_lr_left_state_cxc_lxlrl_llxll_lrxlr);

    struct populated_c_l_ll_lr_llr_llrl_exclude_double_node_l_on_left_return_l_ll_right_state_cxc_lxllr_llxll_lrxlr_llrxllrl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr,*node_lrl;
	void configure()
	    {
		data = { 0, -3, 1, -1, -2 };
		node_lrl = new node_t { nullptr, nullptr, nullptr, data[4], 1 };
		node_lr = new node_t { node_lrl, nullptr, nullptr, data[3], 2 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, node_lr, nullptr, data[1], 3 };
		node = new node_t { node_l, node_r, nullptr, data[0], 4 };
		root = new node_t {  node, nullptr, nullptr, 99, 5 };
		node->up = root;
		node_r->up = node_l->up = node;
		node_lr->up = node_l;
		node_lrl->up = node_lr;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::left);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_l;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_lr,nullptr,nullptr,99,root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_lr, {node_l,node_r,root,data[3],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,node_lrl,node_lr,data[1],2});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {nullptr,nullptr,node_lr,data[2],1});
		node_cmp_t node_lr_cmp = test_node(node_l_cmp.right_ok, node_lrl, {nullptr,nullptr,node_l,data[4],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp + node_lrl;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_llr_llrl_exclude_double_node_l_on_left_return_l_ll_right_state_cxc_lxllr_llxll_lrxlr_llrxllrl);

    struct populated_c_l_ll_lr_lrl_lrlr_exclude_double_node_l_on_right_return_l_lr_left_state_cxc_lxlrl_llxll_lrxlr_lrlxlrlr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl,*node_rlr;
	void configure()
	    {
		data = { 0, -1, 3, 1, 2 };
		node_rlr = new node_t { nullptr, nullptr, nullptr, data[4], 1 };
		node_rl = new node_t { nullptr, node_rlr, nullptr, data[3], 2 };
		node_r = new node_t { node_rl, nullptr, nullptr, data[2], 3 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 4 };
		root = new node_t {  node, nullptr, nullptr, 99, 5 };
		node->up = root;
		node_r->up = node_l->up = node;
		node_rl->up = node_r;
		node_rlr->up = node_rl;
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		node_t *del_node, *rebalance;
		std::tie(del_node,rebalance) = test_plug.exclude_double_node(container, node, &node_t::right);
		auto new_root = test_plug.get_root(container);
		
		bool del_node_ok = del_node == node;
		bool rebalance_ok = rebalance == node_r;
		bool root_ok = new_root == root;
		node_cmp_t root_cmp = test_node(root_ok, root, {node_rl,nullptr,nullptr,99,root->height});
		node_cmp_t node_cmp = test_node(root_cmp.left_ok, node_rl, {node_l,node_r,root,data[3],3});
		node_cmp_t node_l_cmp = test_node(node_cmp.left_ok, node_l, {nullptr,nullptr,node_rl,data[1],1});
		node_cmp_t node_r_cmp = test_node(node_cmp.right_ok, node_r, {node_rlr,nullptr,node_rl,data[2],2});
		node_cmp_t node_rl_cmp = test_node(node_r_cmp.right_ok, node_rlr, {nullptr,nullptr,node_r,data[4],1});
		score_t score = score_t(del_node_ok) + score_t(rebalance_ok) + score_t(root_ok)
		    + root_cmp + node_cmp + node_l_cmp + node_r_cmp + node_rlr;
		delete del_node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_lr_lrl_lrlr_exclude_double_node_l_on_right_return_l_lr_left_state_cxc_lxlrl_llxll_lrxlr_lrlxlrlr);

}
