#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct treeset_dynamic_balancing_test_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_case
    {
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()+1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    std::numeric_limits<elem_t>::min(),
					    std::numeric_limits<elem_t>::max(),
					    [this,&failed_list](elem_t el) -> bool {
						auto root = test_plug.get_root(container);
						auto find_res = test_plug.find(container, el, root);
						bool cmp_contains = this->testtreeset.count(el) != 0;
						bool contains = find_res.first != nullptr && find_res.first->val == el ;
						if( cmp_contains ^ contains )
						{
						    failed_list->add_failed(el);
						    return false;
						}
						return true;
					    });
		return result;
	    }
    };
    
    struct empty_find_all_vals_return_end
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure(){}
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_c_v0_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0 };
		node_t* node = new node_t { nullptr, nullptr, nullptr, data[0], 1 };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_v0_find_compare_with_stdtreeset);

    struct populated_c_vmin_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { std::numeric_limits<elem_t>::min() };
		node_t* node = new node_t { nullptr, nullptr, nullptr, data[0], 1 };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_vmin_find_compare_with_stdtreeset);

    struct populated_c_vmax_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { std::numeric_limits<elem_t>::max() };
		node_t* node = new node_t { nullptr, nullptr, nullptr, data[0], 1 };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_vmax_find_compare_with_stdtreeset);

    struct populated_rmr_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( elem_t i=std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-1; i+=3 )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		node_t** node = &(test_plug.get_root(container));
		node_t* prev_node = nullptr;
		int_fast8_t i = data.size();
		for( elem_t x : data )
		{
		    testtreeset.insert(x);
		    auto n = new node_t { nullptr, nullptr, prev_node, x, i-- };
		    *node = prev_node = n;
		    node = &((*node)->right);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_find_compare_with_stdtreeset);

    struct populated_lml_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( elem_t i=std::numeric_limits<elem_t>::max(); i < std::numeric_limits<elem_t>::min()+1; i+=3 )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
		
		node_t** node = &(test_plug.get_root(container));
		node_t* prev_node = nullptr;
		int_fast8_t i = data.size();
		for( elem_t x : data )
		{
		    testtreeset.insert(x);
		    auto n = new node_t { nullptr, nullptr, prev_node, x, i-- };
		    *node = prev_node = n;
		    node = &((*node)->left);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lml_find_compare_with_stdtreeset);

    struct populated_c_l_ll_llr_llrr_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 120, 100, 0, 50, 70 };
		node_t* n_llrr = new node_t { nullptr, nullptr, nullptr, data[4], 1 };
		node_t* n_llr = new node_t { nullptr, n_llrr, nullptr, data[3], 2 };
		node_t* n_ll = new node_t { nullptr, n_llr, nullptr, data[2], 3 };
		node_t* n_l = new node_t { n_ll, nullptr, nullptr, data[1], 4 };
		node_t* n = new node_t { n_l, nullptr, nullptr, data[0], 5 };
		n_llrr->up = n_llr;
		n_llr->up = n_ll;
		n_ll->up = n_l;
		n_l->up = n;
		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_ll_llr_llrr_find_compare_with_stdtreeset);

    struct populated_c_r_rr_rrl_rrll_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { -120, -100, 0, -50, -70 };
		node_t* n_rrll = new node_t { nullptr, nullptr, nullptr, data[4], 1 };
		node_t* n_rrl = new node_t { n_rrll, nullptr, nullptr, data[3], 2 };
		node_t* n_rr = new node_t { n_rrl, nullptr, nullptr, data[2], 3 };
		node_t* n_r = new node_t { nullptr, n_rr, nullptr, data[1], 4 };
		node_t* n = new node_t { nullptr, n_r, nullptr, data[0], 5 };
		n_rrll->up = n_rrl;
		n_rrl->up = n_rr;
		n_rr->up = n_r;
		n_r->up = n;
		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_rr_rrl_rrll_find_compare_with_stdtreeset);

    struct populated_c_l_r_ll_lr_lr_lll_llr_llll_lllr_with_leafs_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 100, 110, 70, 90, 0, 50, -50, -25, -70 };
		node_t* n_llll = new node_t { nullptr, nullptr, nullptr, data[8], 1 };
		node_t* n_lllr = new node_t { nullptr, nullptr, nullptr, data[7], 1 };
		node_t* n_lll = new node_t { n_llll, n_lllr, nullptr, data[6], 2 };
		node_t* n_llr = new node_t { nullptr, nullptr, nullptr, data[5], 1 };
		node_t* n_ll = new node_t { n_lll, n_llr, nullptr, data[4], 3 };
		node_t* n_lr = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_t* n_l = new node_t { n_ll, n_lr, nullptr, data[2], 4 };
		node_t* n_r = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node_t* n = new node_t { n_l, n_r, nullptr, data[0], 5 };
		n_llll->up = n_lllr->up = n_lll;
		n_lll->up = n_llr->up = n_ll;
		n_ll->up = n_lr->up = n_l;
		n_l->up = n_r->up = n;
		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_lr_lll_llr_llll_lllr_with_leafs_find_compare_with_stdtreeset);

    struct populated_c_l_r_rl_rr_rrl_rrr_rrrl_rrrr_with_leafs_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { -100, -110, -70, -90, 0, -50, 50, 25, 70 };
		node_t* n_rrrr = new node_t { nullptr, nullptr, nullptr, data[8], 1 };
		node_t* n_rrrl = new node_t { nullptr, nullptr, nullptr, data[7], 1 };
		node_t* n_rrr = new node_t { n_rrrl, n_rrrr, nullptr, data[6], 2 };
		node_t* n_rrl = new node_t { nullptr, nullptr, nullptr, data[5], 1 };
		node_t* n_rr = new node_t { n_rrl, n_rrr, nullptr, data[4], 3 };
		node_t* n_rl = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_t* n_r = new node_t { n_rl, n_rr, nullptr, data[2], 4 };
		node_t* n_l = new node_t { nullptr, nullptr, nullptr, data[1], 1 };
		node_t* n = new node_t { n_l, n_r, nullptr, data[0], 5 };
		n_rrrr->up = n_rrrl->up = n_rrr;
		n_rrr->up = n_rrl->up = n_rr;
		n_rr->up = n_rl->up = n_r;
		n_l->up = n_r->up = n;
		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_rl_rr_rrl_rrr_rrrl_rrrr_with_leafs_find_compare_with_stdtreeset);


    struct populated_c_l_r_ll_lr_rl_rr_find_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, -100, 100, -120, -50, 50, 120 };
		node_t* n_rr = new node_t { nullptr, nullptr, nullptr, data[6], 1 };
		node_t* n_rl = new node_t { nullptr, nullptr, nullptr, data[5], 1 };
		node_t* n_lr = new node_t { nullptr, nullptr, nullptr, data[4], 1 };
		node_t* n_ll = new node_t { nullptr, nullptr, nullptr, data[3], 1 };
		node_t* n_r = new node_t { n_rl, n_rr, nullptr, data[2], 2 };
		node_t* n_l = new node_t { n_ll, n_lr, nullptr, data[1], 2 };
		node_t* n = new node_t { n_l, n_r, nullptr, data[0], 3 };
		n_rr->up = n_rl->up = n_r;
		n_ll->up = n_lr->up = n_l;
		n_l->up = n_r->up = n;
		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_ll_lr_rl_rr_find_compare_with_stdtreeset);
}
