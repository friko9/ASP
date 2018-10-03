#include "treeset_dynamic_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic
{
    struct populated_1elem_exclude_node_singleelem_left_return_root_state_empty: public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { data[0], nullptr, nullptr };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node( container, node, nullptr, &node_t::left );
		bool is_state_ok = test_plug.get_root(container) == nullptr;
		bool is_ret_ok = res == node;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_1elem_exclude_node_singleelem_left_return_root_state_empty);

    struct populated_1elem_exclude_node_singleelem_right_return_root_state_empty : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { data[0], nullptr, nullptr };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node(container, node, nullptr, &node_t::right );
		bool is_state_ok = test_plug.get_root(container) == nullptr;
		bool is_ret_ok = res == node;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_1elem_exclude_node_singleelem_right_return_root_state_empty);

    struct populated_2elem_exclude_leaf_right_return_right_state_root_only : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], nullptr, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node(container, node_r, node, &node_t::right );
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
		bool root_left_ok = root_ok && root->left == nullptr;
		bool root_right_ok = root_ok && root->right == nullptr;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok;
		bool is_ret_ok = res == node_r;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_2elem_exclude_leaf_right_return_right_state_root_only);

    struct populated_2elem_exclude_leaf_left_return_left_state_root_only : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, nullptr };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node(container, node_l, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
		bool root_left_ok = root_ok && root->left == nullptr;
		bool root_right_ok = root_ok && root->right == nullptr;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok;
		bool is_ret_ok = res == node_l;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_2elem_exclude_leaf_left_return_left_state_root_only);

    struct populated_2elem_right_exclude_root_return_root_state_right_is_root : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, 1 };
		node_r = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], nullptr, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node(container, node, nullptr, &node_t::right );
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[1];
		bool root_left_ok = root_ok && root->left == nullptr;
		bool root_right_ok = root_ok && root->right == nullptr;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok;
		bool is_ret_ok = res == node;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_2elem_right_exclude_root_return_root_state_right_is_root);

    struct populated_2elem_left_exclude_root_return_root_state_left_is_root : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		data = { 0, -1 };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, nullptr };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node(container, node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[1];
		bool root_left_ok = root_ok && root->left == nullptr;
		bool root_right_ok = root_ok && root->right == nullptr;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok;
		bool is_ret_ok = res == node;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_2elem_left_exclude_root_return_root_state_left_is_root);

    struct populated_3elem_lr_exclude_leaf_left_return_left_state_root_and_right_not_changed : public treeset_dynamic_test_case
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
		node_t* res = test_plug.exclude_single_node(container, node_l, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
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
    ENABLE_TEST(access_test_set(),populated_3elem_lr_exclude_leaf_left_return_left_state_root_and_right_not_changed);

    struct populated_3elem_lr_exclude_leaf_right_return_right_state_root_and_right_not_changed : public treeset_dynamic_test_case
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
		node_t* res = test_plug.exclude_single_node(container, node_r, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
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
    ENABLE_TEST(access_test_set(),populated_3elem_lr_exclude_leaf_right_return_right_state_root_and_right_not_changed);

    struct populated_4elem_lrll_exclude_left_return_left_state_left_is_ll : public treeset_dynamic_test_case
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
		node_t* res = test_plug.exclude_single_node(container, node_l, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
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
    ENABLE_TEST(access_test_set(),populated_4elem_lrll_exclude_left_return_left_state_left_is_ll);

    struct populated_4elem_lrlr_exclude_left_return_left_state_left_is_lr : public treeset_dynamic_test_case
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
		node_t* res = test_plug.exclude_single_node(container, node_l, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
		bool root_left_ok = root_ok && root->left == node_lr;
		bool root_right_ok = root_ok && root->right == node_r;
		bool node_r_val_ok = root_right_ok && node_r->val == data[2];
		bool node_r_left_ok = root_right_ok && node_r->left == nullptr;
		bool node_r_right_ok = root_right_ok && node_r->right == nullptr;
		bool node_lr_val_ok = root_left_ok && node_lr->val == data[3];
		bool node_lr_left_ok = root_left_ok && node_lr->left == nullptr;
		bool node_lr_right_ok = root_left_ok && node_lr->right == nullptr;
		bool is_ret_ok = res == node_l;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_r_val_ok && node_r_left_ok && node_r_right_ok
		    && node_lr_val_ok && node_lr_left_ok && node_lr_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_lrlr_exclude_left_return_left_state_left_is_lr);

    struct populated_4elem_lrrl_exclude_right_return_right_state_right_is_rl : public treeset_dynamic_test_case
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
		node_t* res = test_plug.exclude_single_node(container, node_r, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
		bool root_left_ok = root_ok && root->left == node_l;
		bool root_right_ok = root_ok && root->right == node_rl;
		bool node_l_val_ok = root_left_ok && node_l->val == data[1];
		bool node_l_left_ok = root_left_ok && node_l->left == nullptr;
		bool node_l_right_ok = root_left_ok && node_l->right == nullptr;
		bool node_rl_val_ok = root_right_ok && node_rl->val == data[3];
		bool node_rl_left_ok = root_right_ok && node_rl->left == nullptr;
		bool node_rl_right_ok = root_right_ok && node_rl->right == nullptr;
		bool is_ret_ok = res == node_r;
		bool is_state_ok = root_val_ok && root_left_ok && root_right_ok
		    && node_l_val_ok && node_l_left_ok && node_l_right_ok
		    && node_rl_val_ok && node_rl_left_ok && node_rl_right_ok;
		if( is_ret_ok && is_state_ok )
		    ++result;
		delete res;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_4elem_lrrl_exclude_right_return_right_state_right_is_rl);

    struct populated_4elem_lrrr_exclude_right_return_right_state_right_is_rr : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_r,*node_rr;
	void configure()
	    {
		data = { 0, -2, 1, -1 };
		node_rr = new node_t { data[3], nullptr, nullptr };
		node_r = new node_t { data[2], nullptr, node_rr };
		node_l = new node_t { data[1], nullptr, nullptr };
		node = new node_t { data[0], node_l, node_r };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_result result = 1;
		node_t* res = test_plug.exclude_single_node(container, node_r, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root != nullptr;
		bool root_val_ok = root_ok && root->val == data[0];
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
    ENABLE_TEST(access_test_set(),populated_4elem_lrrr_exclude_right_return_right_state_right_is_rr);
}
