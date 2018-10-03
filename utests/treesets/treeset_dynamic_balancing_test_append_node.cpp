#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct empty_append_node_null_root_left_state_empty
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	void configure(){}
	test_result run()
	    {
		auto root = test_plug.get_root(container);
		test_plug.append_node(container, nullptr, root, &node_t::left);

		score_t score = score_t(root == nullptr);
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),empty_append_node_null_root_left_state_empty);

    struct empty_append_node_newc_root_left_state_c
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		node = new node_t {nullptr,nullptr,nullptr,0,1};
	    }
	test_result run()
	    {
		test_plug.append_node(container, node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,0,1});
		score_t score = score_t(root_ok) + root_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),empty_append_node_newc_root_left_state_c);

    struct populated_c_append_node_null_root_left_state_empty
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node;
	void configure()
	    {
		data = { 0 };
		node = new node_t { nullptr, nullptr, nullptr, data[0], 1 };
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, nullptr, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == nullptr;
		score_t score = score_t(root_ok);
		delete node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_append_node_null_root_left_state_empty);

    struct populated_c_append_node_newc_root_left_state_c
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*new_node;
	void configure()
	    {
		node = new node_t {nullptr,nullptr,nullptr,0,1};
		new_node = new node_t {nullptr,nullptr,nullptr,2,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, nullptr, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == new_node;
		node_cmp_t root_cmp = test_node(root_ok, new_node, {nullptr,nullptr,nullptr,2,1});
		score_t score = score_t(root_ok) + root_cmp;
		delete node;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_append_node_newc_root_left_state_c);

    struct populated_c_append_node_null_c_left_state_c
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		node = new node_t {nullptr,nullptr,nullptr,0,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, nullptr, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,0,1});
		score_t score = score_t(root_ok) + root_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_append_node_null_c_left_state_c);

    struct populated_c_append_node_null_c_right_state_c
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node;
	void configure()
	    {
		node = new node_t {nullptr,nullptr,nullptr,0,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, nullptr, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,0,1});
		score_t score = score_t(root_ok) + root_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_append_node_null_c_right_state_c);

    struct populated_c_append_node_newc_c_left_state_c_lxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*new_node;
	void configure()
	    {
		node = new node_t {nullptr,nullptr,nullptr,0,1};
		new_node = new node_t {nullptr,nullptr,nullptr,-2,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {new_node,nullptr,nullptr,0,2});
		node_cmp_t node_l_cmp = test_node(root_cmp.left_ok, new_node, {nullptr,nullptr,node,-2,1});
		score_t score = score_t(root_ok) + root_cmp + node_l_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_append_node_newc_c_left_state_c_lxnewc);

    struct populated_c_append_node_newc_c_right_state_c_rxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*new_node;
	void configure()
	    {
		node = new node_t {nullptr,nullptr,nullptr,0,1};
		new_node = new node_t {nullptr,nullptr,nullptr,2,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,new_node,nullptr,0,2});
		node_cmp_t node_r_cmp = test_node(root_cmp.left_ok, new_node, {nullptr,nullptr,node,2,1});
		score_t score = score_t(root_ok) + root_cmp + node_r_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_append_node_newc_c_right_state_c_rxnewc);
    
    struct populated_c_l_append_node_null_c_left_state_c
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l;
	void configure()
	    {
		node_l = new node_t {nullptr,nullptr,nullptr,-1,1};
		node = new node_t {node_l,nullptr,nullptr,0,2};
		node_l->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, nullptr, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,0,1});
		score_t score = score_t(root_ok) + root_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_append_node_null_c_left_state_c);

    struct populated_c_r_append_node_null_c_right_state_c
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r;
	void configure()
	    {
		node_r = new node_t {nullptr,nullptr,nullptr,1,1};
		node = new node_t {nullptr,node_r,nullptr,0,2};
		node_r->up = node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, nullptr, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,nullptr,nullptr,0,1});
		score_t score = score_t(root_ok) + root_cmp;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_append_node_null_c_right_state_c);

    struct populated_c_l_append_node_newc_c_left_state_c_lxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*new_node;
	void configure()
	    {
		node_l = new node_t {nullptr,nullptr,nullptr,-1,1};
		node = new node_t {node_l,nullptr,nullptr,0,2};
		node_l->up = node;
		new_node = new node_t {nullptr,nullptr,nullptr,-2,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {new_node,nullptr,nullptr,0,2});
		node_cmp_t node_l_cmp = test_node(root_ok, new_node, {nullptr,nullptr,node,-2,1});
		score_t score = score_t(root_ok) + root_cmp + node_l_cmp;
		delete node_l;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_append_node_newc_c_left_state_c_lxnewc);

    struct populated_c_r_append_node_newc_c_right_state_c_rxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*new_node;
	void configure()
	    {
		node_r = new node_t {nullptr,nullptr,nullptr,1,1};
		node = new node_t {nullptr,node_r,nullptr,0,2};
		node_r->up = node;
		new_node = new node_t {nullptr,nullptr,nullptr,2,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,new_node,nullptr,0,2});
		node_cmp_t node_r_cmp = test_node(root_ok, new_node, {nullptr,nullptr,node,2,1});
		score_t score = score_t(root_ok) + root_cmp + node_r_cmp;
		delete node_r;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_append_node_newc_c_right_state_c_rxnewc);

    struct populated_c_l_append_node_newc_l_c_left_state_c_lxnewc_llxnewl
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*new_node,*new_node_l;
	void configure()
	    {
		node_l = new node_t {nullptr,nullptr,nullptr,-1,1};
		node = new node_t {node_l,nullptr,nullptr,0,2};
		node_l->up = node;
		new_node_l = new node_t {nullptr,nullptr,nullptr,-3,1};
		new_node = new node_t {new_node_l,nullptr,nullptr,-2,2};
		new_node_l->up = new_node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {new_node,nullptr,nullptr,0,3});
		node_cmp_t node_l_cmp = test_node(root_ok, new_node, {new_node_l,nullptr,node,-2,2});
		node_cmp_t node_ll_cmp = test_node(root_ok, new_node_l, {nullptr,nullptr,new_node,-3,1});
		score_t score = score_t(root_ok) + root_cmp + node_l_cmp + node_ll_cmp;
		delete node_l;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_append_node_newc_l_c_left_state_c_lxnewc_llxnewl);

    struct populated_c_r_append_node_newc_r_c_right_state_c_rxnewc_rrxnewr
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*new_node,*new_node_r;;
	void configure()
	    {
		node_r = new node_t {nullptr,nullptr,nullptr,1,1};
		node = new node_t {nullptr,node_r,nullptr,0,2};
		node_r->up = node;
		new_node_r = new node_t {nullptr,nullptr,nullptr,3,1};
		new_node = new node_t {nullptr,new_node_r,nullptr,2,2};
		new_node_r->up = new_node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,new_node,nullptr,0,3});
		node_cmp_t node_r_cmp = test_node(root_ok, new_node, {nullptr,new_node_r,node,2,2});
		node_cmp_t node_rr_cmp = test_node(root_ok, new_node_r, {nullptr,nullptr,new_node,3,1});
		score_t score = score_t(root_ok) + root_cmp + node_r_cmp + node_rr_cmp;
		delete node_r;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_append_node_newc_r_c_right_state_c_rxnewc_rrxnewr);

    struct populated_c_l_ll_append_node_newc_c_left_state_c_lxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_ll,*new_node;
	void configure()
	    {
		node_ll = new node_t {nullptr,nullptr,nullptr,-2,1};
		node_l = new node_t {node_l,nullptr,nullptr,-1,2};
		node = new node_t {node_l,nullptr,nullptr,0,3};
		node_ll->up = node_l;
		node_l->up = node;
		new_node = new node_t {nullptr,nullptr,nullptr,-3,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {new_node,nullptr,nullptr,0,2});
		node_cmp_t node_l_cmp = test_node(root_ok, new_node, {nullptr,nullptr,node,-3,1});
		score_t score = score_t(root_ok) + root_cmp + node_l_cmp;
		delete node_l;
		delete node_ll;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_append_node_newc_c_left_state_c_lxnewc);

    struct populated_c_r_rr_append_node_newc_c_right_state_c_rxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*node_rr,*new_node;
	void configure()
	    {
		node_rr = new node_t {nullptr,nullptr,nullptr,2,1};
		node_r = new node_t {nullptr,node_rr,nullptr,1,2};
		node = new node_t {nullptr,node_r,nullptr,0,3};
		node_rr->up = node_r;
		node_r->up = node;
		new_node = new node_t {nullptr,nullptr,nullptr,3,1};
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,new_node,nullptr,0,2});
		node_cmp_t node_r_cmp = test_node(root_ok, new_node, {nullptr,nullptr,node,3,1});
		score_t score = score_t(root_ok) + root_cmp + node_r_cmp;
		delete node_r;
		delete node_rr;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rr_append_node_newc_c_right_state_c_rxnewc);

        struct populated_c_l_ll_append_node_newl_c_left_state_c_lxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t *node,*node_l,*node_ll,*new_node,*new_node_l;
	void configure()
	    {
		node_ll = new node_t {nullptr,nullptr,nullptr,-2,1};
		node_l = new node_t {node_l,nullptr,nullptr,-1,2};
		node = new node_t {node_l,nullptr,nullptr,0,3};
		node_ll->up = node_l;
		node_l->up = node;
		new_node = new node_t {nullptr,nullptr,nullptr,-3,2};
		new_node_l = new node_t {nullptr,nullptr,new_node,-4,1};
		new_node_l->up = new_node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node_l, node, &node_t::left);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {new_node_l,nullptr,nullptr,0,2});
		node_cmp_t node_l_cmp = test_node(root_ok, new_node_l, {nullptr,nullptr,node,-4,1});
		score_t score = score_t(root_ok) + root_cmp + node_l_cmp;
		delete node_l;
		delete node_ll;
		delete new_node_l;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_append_node_newl_c_left_state_c_lxnewc);

    struct populated_c_r_rr_append_node_newr_c_right_state_c_rxnewc
	: public treeset_dynamic_balancing_test_case
    {
	TEST_INSERTER;
	node_t* node,*node_r,*node_rr,*new_node,*new_node_r;
	void configure()
	    {
		node_rr = new node_t {nullptr,nullptr,nullptr,2,1};
		node_r = new node_t {nullptr,node_rr,nullptr,1,2};
		node = new node_t {nullptr,node_r,nullptr,0,3};
		node_rr->up = node_r;
		node_r->up = node;
		new_node = new node_t {nullptr,nullptr,nullptr,3,1};
		new_node_r = new node_t {nullptr,nullptr,new_node,4,1};
		new_node_r->up = new_node;
		test_plug.get_root(container) = node;
	    }
	test_result run()
	    {
		test_plug.append_node(container, new_node_r, node, &node_t::right);
		auto root = test_plug.get_root(container);
		bool root_ok = root == node;
		node_cmp_t root_cmp = test_node(root_ok, node, {nullptr,new_node_r,nullptr,0,2});
		node_cmp_t node_r_cmp = test_node(root_ok, new_node_r, {nullptr,nullptr,node,4,1});
		score_t score = score_t(root_ok) + root_cmp + node_r_cmp;
		delete node_r;
		delete node_rr;
		delete new_node_r;
		return score.to_test_result();
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rr_append_node_newr_c_right_state_c_rxnewc);
}
