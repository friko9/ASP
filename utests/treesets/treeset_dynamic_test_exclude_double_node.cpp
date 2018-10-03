#include "treeset_dynamic_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic
{
    struct populated_3elem_root_lr_exclude_double_root_on_left_return_left_state_root_val_is_left_val_and_right_not_changed
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[1];
		bool root_left_ok = root_ok && root->left == nullptr;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool is_ret_ok = res == node_l;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elem_root_lr_exclude_double_root_on_left_return_left_state_root_val_is_left_val_and_right_not_changed);

    struct populated_3elem_root_lr_exclude_double_root_on_right_return_right_state_root_val_is_right_val_and_left_not_changed
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[2];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == nullptr;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == nullptr;
		bool is_ret_ok = res == node_r;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elem_root_lr_exclude_double_root_on_right_return_right_state_root_val_is_right_val_and_left_not_changed);

    struct populated_4elem_root_lrll_exclude_double_root_on_left_return_left_state_root_val_is_left_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], node_ll, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[1];
		bool root_left_ok = root_ok && root->left == node_ll;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool node_ll_val_ok = root_left_ok && node_ll->val == data[3];
		bool node_ll_left_ok = root_left_ok && node_ll->left == nullptr;
		bool node_ll_right_ok = root_left_ok && node_ll->right == nullptr;
		bool is_ret_ok = res == node_l;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_ll_val_ok && node_ll_left_ok && node_ll_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_root_lrll_exclude_double_root_on_left_return_left_state_root_val_is_left_val);

    struct populated_4elem_root_lrrr_exclude_double_root_on_right_return_right_state_root_val_is_right_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -1, 1, 2 };
		node_rr = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, node_rr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[2];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == node_rr;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == nullptr;
		bool node_rr_val_ok = root_right_ok && node_rr->val == data[3];
		bool node_rr_left_ok = root_right_ok && node_rr->left == nullptr;
		bool node_rr_right_ok = root_right_ok && node_rr->right == nullptr;
		bool is_ret_ok = res == node_r;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_rr_val_ok && node_rr_left_ok && node_rr_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_root_lrrr_exclude_double_root_on_right_return_right_state_root_val_is_right_val);

    struct populated_4elem_root_lrlr_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, node_lr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[3];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == nullptr;
		bool is_ret_ok = res == node_lr;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_root_lrlr_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val);

    struct populated_4elem_root_lrrl_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], node_rl, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[3];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == nullptr;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool is_ret_ok = res == node_rl;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_root_lrrl_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val);

    struct populated_4elem_root_lrlrlrl_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_lr,*node_lrl;
	void configure()
	    {
		data = { 0, -3, 1, -1, -2 };
		node_lrl = new node_t { data[4], nullptr, nullptr };
		node_lr = new node_t { data[3], node_lrl, nullptr };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, node_lr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[3];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == node_lrl;
		bool node_lr_val_ok = node_l_right_ok && node_lrl->val == data[4];
		bool node_lr_left_ok = node_l_right_ok && node_lrl->left == nullptr;
		bool node_lr_right_ok = node_l_right_ok && node_lrl->right == nullptr;
		bool is_ret_ok = res == node_lr;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_lr_val_ok && node_lr_left_ok && node_lr_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_root_lrlrlrl_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val);

    struct populated_4elem_root_lrrlrlr_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rl,*node_rlr;
	void configure()
	    {
		data = { 0, -1, 3, 1, 2 };
		node_rlr = new node_t { data[4], nullptr, nullptr };
		node_rl = new node_t { data[3], nullptr, node_rlr };
		node_r = new node_t { data[2], node_rl, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, nullptr, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		bool root_val_ok = root_ok && root->val == data[3];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == nullptr;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == node_rlr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool node_rl_val_ok = node_r_left_ok && node_rlr->val == data[4];
		bool node_rl_left_ok = node_r_left_ok && node_rlr->left == nullptr;
		bool node_rl_right_ok = node_r_left_ok && node_rlr->right == nullptr;
		bool is_ret_ok = res == node_rl;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_rl_val_ok && node_rl_left_ok && node_rl_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_root_lrrlrlr_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val);

    struct populated_3elem_node_lr_exclude_double_root_on_left_return_left_state_root_val_is_left_val_and_right_not_changed
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[1];
		bool node_left_ok = root_left_ok && node->left == nullptr;
		bool node_right_ok = root_left_ok && node->right == node_r;
		
		bool node_r_val_ok = node_right_ok && node_r->val == data[2];
		bool node_r_left_ok = node_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = node_right_ok && node_r->right == nullptr;
		bool is_ret_ok = res == node_l;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elem_node_lr_exclude_double_root_on_left_return_left_state_root_val_is_left_val_and_right_not_changed);

    struct populated_3elem_node_lr_exclude_double_root_on_right_return_right_state_root_val_is_right_val_and_left_not_changed
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[2];
		bool node_left_ok = root_left_ok && node->left == node_l;
		bool node_right_ok = root_left_ok && node->right == nullptr;
		
		bool node_l_val_ok = node_left_ok && node_l->val == data[1];
		bool node_l_left_ok = node_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = node_left_ok && node_l->right == nullptr;
		bool is_ret_ok = res == node_r;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elem_node_lr_exclude_double_root_on_right_return_right_state_root_val_is_right_val_and_left_not_changed);

    struct populated_4elem_node_lrll_exclude_double_root_on_left_return_left_state_root_val_is_left_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_ll;
	void configure()
	    {
		data = { 0, -1, 1, -2 };
		node_ll = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], node_ll, nullptr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[1];
		bool node_left_ok = root_left_ok && node->left == node_ll;
		bool node_right_ok = root_left_ok && node->right == node_r;
		
		bool node_r_val_ok = node_right_ok && node_r->val == data[2];
		bool node_r_left_ok = node_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = node_right_ok && node_r->right == nullptr;
		bool node_ll_val_ok = node_left_ok && node_ll->val == data[3];
		bool node_ll_left_ok = node_left_ok && node_ll->left == nullptr;
		bool node_ll_right_ok = node_left_ok && node_ll->right == nullptr;
		bool is_ret_ok = res == node_l;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_ll_val_ok && node_ll_left_ok && node_ll_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_node_lrll_exclude_double_root_on_left_return_left_state_root_val_is_left_val);

    struct populated_4elem_node_lrrr_exclude_double_root_on_right_return_right_state_root_val_is_right_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -1, 1, 2 };
		node_rr = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, node_rr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[2];
		bool node_left_ok = root_left_ok && node->left == node_l;
		bool node_right_ok = root_left_ok && node->right == node_rr;

		bool node_l_val_ok = node_left_ok && node_l->val == data[1];
		bool node_l_left_ok = node_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = node_left_ok && node_l->right == nullptr;
		bool node_rr_val_ok = node_right_ok && node_rr->val == data[3];
		bool node_rr_left_ok = node_right_ok && node_rr->left == nullptr;
		bool node_rr_right_ok = node_right_ok && node_rr->right == nullptr;
		bool is_ret_ok = res == node_r;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_rr_val_ok && node_rr_left_ok && node_rr_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_node_lrrr_exclude_double_root_on_right_return_right_state_root_val_is_right_val);

    struct populated_4elem_node_lrlr_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_lr = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, node_lr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[3];
		bool node_left_ok = root_left_ok && node->left == node_l;
		bool node_right_ok = root_left_ok && node->right == node_r;
		
		bool node_r_val_ok = node_right_ok && node_r->val == data[2];
		bool node_r_left_ok = node_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = node_right_ok && node_r->right == nullptr;
		
		bool node_l_val_ok = node_left_ok && node_l->val == data[1];
		bool node_l_left_ok = node_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = node_left_ok && node_l->right == nullptr;
		bool is_ret_ok = res == node_lr;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_node_lrlr_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val);

    struct populated_4elem_node_lrrl_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl;
	void configure()
	    {
		data = { 0, -1, 2, 1 };
		node_rl = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], node_rl, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[3];
		bool node_left_ok = root_left_ok && node->left == node_l;
		bool node_right_ok = root_left_ok && node->right == node_r;

		bool node_l_val_ok = node_left_ok && node_l->val == data[1];
		bool node_l_left_ok = node_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = node_left_ok && node_l->right == nullptr;
		bool node_r_val_ok = node_right_ok && node_r->val == data[2];
		bool node_r_left_ok = node_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = node_right_ok && node_r->right == nullptr;
		bool is_ret_ok = res == node_rl;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_node_lrrl_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val);

    struct populated_4elem_node_lrlrlrl_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_lr,*node_lrl;
	void configure()
	    {
		data = { 0, -3, 1, -1, -2 };
		node_lrl = new node_t { data[4], nullptr, nullptr };
		node_lr = new node_t { data[3], node_lrl, nullptr };
		node_r = new node_t { data[2], nullptr, nullptr };
		node_l = new node_t { data[1], nullptr, node_lr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::left);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[3];
		bool node_left_ok = root_left_ok && node->left == node_l;
		bool node_right_ok = root_left_ok && node->right == node_r;
		
		bool node_r_val_ok = node_right_ok && node_r->val == data[2];
		bool node_r_left_ok = node_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = node_right_ok && node_r->right == nullptr;
		
		bool node_l_val_ok = node_left_ok && node_l->val == data[1];
		bool node_l_left_ok = node_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = node_left_ok && node_l->right == node_lrl;
		
		bool node_lr_val_ok = node_l_right_ok && node_lrl->val == data[4];
		bool node_lr_left_ok = node_l_right_ok && node_lrl->left == nullptr;
		bool node_lr_right_ok = node_l_right_ok && node_lrl->right == nullptr;
		bool is_ret_ok = res == node_lr;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_lr_val_ok && node_lr_left_ok && node_lr_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_node_lrlrlrl_exclude_double_root_on_left_return_lr_state_root_val_is_lr_val);

    struct populated_4elem_node_lrrlrlr_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val
	: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *root,*node,*node_l,*node_r,*node_rl,*node_rlr;
	void configure()
	    {
		data = { 0, -1, 3, 1, 2 };
		node_rlr = new node_t { data[4], nullptr, nullptr };
		node_rl = new node_t { data[3], nullptr, node_rlr };
		node_r = new node_t { data[2], node_rl, nullptr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		root = new node_t { 99, node, nullptr };
		test_plug.get_root(container) = root;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_double_node(container, node, root, &node_t::right);
		auto root = test_plug.get_root(container);

		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == 99;
		bool root_left_ok = root_ok && root->left == node;
		bool root_right_ok = root_ok && root->right == nullptr;

		bool node_val_ok = root_left_ok && node->val == data[3];
		bool node_left_ok = root_left_ok && node->left == node_l;
		bool node_right_ok = root_left_ok && node->right == node_r;

		bool node_l_val_ok = node_left_ok && node_l->val == data[1];
		bool node_l_left_ok = node_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = node_left_ok && node_l->right == nullptr;
		
		bool node_r_val_ok = node_right_ok && node_r->val == data[2];
		bool node_r_left_ok = node_right_ok && node_r->left == node_rlr;
		bool node_r_right_ok = node_right_ok && node_r->right == nullptr;
		
		bool node_rl_val_ok = node_r_left_ok && node_rlr->val == data[4];
		bool node_rl_left_ok = node_r_left_ok && node_rlr->left == nullptr;
		bool node_rl_right_ok = node_r_left_ok && node_rlr->right == nullptr;
		bool is_ret_ok = res == node_rl;
		bool is_state_ok = node_val_ok && node_left_ok && node_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_rl_val_ok && node_rl_left_ok && node_rl_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_node_lrrlrlr_exclude_double_root_on_right_return_rl_state_root_val_is_rl_val);
}
