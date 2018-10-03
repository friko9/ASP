#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct populated_c_traverse_last_c_on_left_return_c
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
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_left_return_c);

    struct populated_c_traverse_last_c_on_right_return_c
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
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_right_return_c);

    struct populated_c_l_traverse_last_c_on_left_return_l
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
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == node_l);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_left_return_l);

    struct populated_c_l_traverse_last_c_on_right_return_c
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
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_right_return_c);
    
    struct populated_c_r_traverse_last_c_on_left_return_c
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
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_left_return_c);
    
    struct populated_c_r_traverse_last_c_on_right_return_r
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r;
	void configure()
	    {
		data = { 0, -1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { nullptr, node_r, nullptr, data[0], 2 };
		node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == node_r);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_right_return_r);

    struct populated_c_l_r_traverse_last_c_on_left_return_l
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r,*node_l;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 2 };
		node_r->up = node_l->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == node_l);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_left_return_l);

    struct populated_c_l_r_traverse_last_c_on_right_return_r
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_r,*node_l;
	void configure()
	    {
		data = { 0, -1, 1 };
		node_r = new node_t { nullptr, nullptr, nullptr, data[2], 1 };
		node_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node = new node_t { node_l, node_r, nullptr, data[0], 2 };
		node_r->up = node_l->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == node_r);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_right_return_r);

    struct populated_left_only_traverse_last_c_on_left_return_left_last
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *last_node;
	void configure()
	    {
		node_t* node = last_node = new node_t { nullptr, nullptr, nullptr, -101, 1 };
		for(elem_t i=-100;i<=0;++i)
		{
		    int_fast8_t h = node->height;
		    node_t* new_node = new node_t { node, nullptr, nullptr, i, ++h };
		    node->up = new_node;
		    node = new_node;
		}
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == last_node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_left_only_traverse_last_c_on_left_return_left_last);

    struct populated_right_only_traverse_last_c_on_right_return_right_last
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *last_node;
	void configure()
	    {
		node_t* node = last_node = new node_t { nullptr, nullptr, nullptr, 101, 1 };
		for(elem_t i=100;i>=0;--i)
		{
		    int_fast8_t h = node->height;
		    node_t* new_node = new node_t { nullptr, node, nullptr, i, ++h };
		    node->up = new_node;
		    node = new_node;
		}
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == last_node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_right_only_traverse_last_c_on_right_return_right_last);
    
    struct populated_lml_lmlr_traverse_last_c_on_left_return_left_last
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *last_node;
	void configure()
	    {
		node_t* node_r = new node_t { nullptr, nullptr, nullptr, -101, 1 };
		node_t* node = last_node = new node_t { nullptr, node_r, nullptr, -102, 2 };
		node_r->up = node;
		
		for(elem_t i=-100;i<=0;++i)
		{
		    int_fast8_t h = node->height;
		    node_t* new_node = new node_t { node, nullptr, nullptr, i, ++h};
		    node->up = new_node;
		    node = new_node;
		}
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == last_node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lml_lmlr_traverse_last_c_on_left_return_left_last);

    struct populated_rmr_rmrl_traverse_last_c_on_right_return_right_last
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *last_node;
	void configure()
	    {
		node_t* node_l = new node_t { nullptr, nullptr, nullptr, 101, 1 };
		node_t* node = last_node = new node_t { node_l,nullptr, nullptr, 102, 2 };
		node_l->up = node;
		for(elem_t i=100;i>=0;--i)
		{
		    int_fast8_t h = node->height;
		    node_t* new_node = new node_t { nullptr, node, nullptr, i, ++h };
		    node->up = new_node;
		    node = new_node;
		}
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == last_node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_rmrl_traverse_last_c_on_right_return_right_last);

    struct populated_lrml_traverse_last_c_on_left_return_left_last
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *last_node;
	void configure()
	    {
		node_t* node_r = new node_t { nullptr, nullptr, nullptr, -101, 1 };
		node_t* node = last_node = new node_t { nullptr, node_r, nullptr, -102, 2 };
		node_r->up = node;
		for(elem_t i=-100;i<=0;i+=2)
		{
		    elem_t i_1 = i+1;
		    int_fast8_t h = node->height;
		    ++h;
		    node_t* new_r = new node_t { node, nullptr, nullptr, i_1, h};
		    node_t* new_node = new node_t { node, new_r, nullptr, i, h};
		    new_r->up = node->up = new_node;
		    node = new_node;
		}
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::left);
		return score_t(ret == last_node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lrml_traverse_last_c_on_left_return_left_last);

    struct populated_lrmr_traverse_last_c_on_right_return_right_last
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *last_node;
	void configure()
	    {
		node_t* node_l = new node_t { nullptr, nullptr, nullptr, 101, 1 };
		node_t* node = last_node = new node_t { node_l,nullptr, nullptr, 102, 2 };
		node_l->up = node;
		for(elem_t i=100;i>=0;i-=2)
		{
		    elem_t i_1 = i-1;
		    int_fast8_t h = node->height;
		    ++h;
		    node_t* new_l = new node_t { node, nullptr, nullptr, i_1, h};
		    node_t* new_node = new node_t { new_l, node, nullptr, i, ++h };
		    node->up = new_l->up = new_node;
		    node = new_node;
		}
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		node_t* root = test_plug.get_root(container);
		auto *ret = test_plug.traverse_last(container, root, &node_t::right);
		return score_t(ret == last_node);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lrmr_traverse_last_c_on_right_return_right_last);
}
