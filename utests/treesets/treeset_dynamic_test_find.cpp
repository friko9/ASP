#include "treeset_dynamic_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic
{
    struct treeset_dynamic_test_find_compare_with_stdtreeset : public treeset_dynamic_test_case
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
						auto find_res = test_plug.find(container, el, root, nullptr);
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
    
    struct empty_find_all_vals_return_end : public treeset_dynamic_test_case
    {
	TEST_INSERTER;
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
						auto find_res = test_plug.find(container, el, root, nullptr);
						bool result = find_res.first == nullptr;
						if( !result )
						    failed_list->add_failed(el);
						return result;
					    });
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_singleelem_zero_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0 };
		node_t* node = new node_t { data[0], nullptr, nullptr };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_zero_find_compare_with_stdtreeset);

    struct populated_singleelem_min_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { std::numeric_limits<elem_t>::min() };
		node_t* node = new node_t { data[0], nullptr, nullptr };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_min_find_compare_with_stdtreeset);

    struct populated_singleelem_max_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { std::numeric_limits<elem_t>::max() };
		node_t* node = new node_t { data[0], nullptr, nullptr };
		testtreeset.insert(data[0]);
		test_plug.get_root(container) = node;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_max_find_compare_with_stdtreeset);

    struct populated_right_only_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( elem_t i=std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-1; i+=2 )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		node_t** node = &(test_plug.get_root(container));
		for( elem_t x : data )
		{
		    testtreeset.insert(x);
		    *node = new node_t { x, nullptr, nullptr };
		    node = &((*node)->right);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_right_only_find_compare_with_stdtreeset);

    struct populated_left_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for( elem_t i=std::numeric_limits<elem_t>::max(); i < std::numeric_limits<elem_t>::min()+1; i+=2 )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
		
		node_t** node = &(test_plug.get_root(container));
		for( elem_t x : data )
		{
		    testtreeset.insert(x);
		    *node = new node_t { x, nullptr, nullptr };
		    node = &((*node)->left);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_left_find_compare_with_stdtreeset);

    struct populated_leftrightchain_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 120, 100, 0, 50, 70 };
		node_t* n_llrr = new node_t { data[4], nullptr, nullptr };
		node_t* n_llr = new node_t { data[3], nullptr, n_llrr };
		node_t* n_ll = new node_t { data[2], nullptr, n_llr };
		node_t* n_l = new node_t { data[1], n_ll, nullptr };
		node_t* n = new node_t { data[0], n_l, nullptr };

		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_leftrightchain_find_compare_with_stdtreeset);

    struct populated_rightleftchain_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { -120, -100, 0, -50, -70 };
		node_t* n_rrll = new node_t { data[4], nullptr, nullptr };
		node_t* n_rrl = new node_t { data[3], n_rrll, nullptr };
		node_t* n_rr = new node_t { data[2], n_rrl, nullptr };
		node_t* n_r = new node_t { data[1], nullptr, n_rr };
		node_t* n = new node_t { data[0], nullptr, n_r };

		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_rightleftchain_find_compare_with_stdtreeset);

    struct populated_left_chain_with_leafs_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 100, 110, 70, 90, 0, 50, -50, -25, -70 };
		node_t* n_llll = new node_t { data[8], nullptr, nullptr };
		node_t* n_lllr = new node_t { data[7], nullptr, nullptr };
		node_t* n_lll = new node_t { data[6], n_llll, n_lllr };
		node_t* n_llr = new node_t { data[5], nullptr, nullptr };
		node_t* n_ll = new node_t { data[4], n_lll, n_llr };
		node_t* n_lr = new node_t { data[3], nullptr, nullptr };
		node_t* n_l = new node_t { data[2], n_ll, n_lr };
		node_t* n_r = new node_t { data[1], nullptr, nullptr };
		node_t* n = new node_t { data[0], n_l, n_r };

		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_left_chain_with_leafs_find_compare_with_stdtreeset);

    struct populated_right_chain_with_leafs_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { -100, -110, -70, -90, 0, -50, 50, 25, 70 };
		node_t* n_rrrr = new node_t { data[8], nullptr, nullptr };
		node_t* n_rrrl = new node_t { data[7], nullptr, nullptr };
		node_t* n_rrr = new node_t { data[6], n_rrrl, n_rrrr };
		node_t* n_rrl = new node_t { data[5], nullptr, nullptr };
		node_t* n_rr = new node_t { data[4], n_rrl, n_rrr };
		node_t* n_rl = new node_t { data[3], nullptr, nullptr };
		node_t* n_r = new node_t { data[2], n_rl, n_rr };
		node_t* n_l = new node_t { data[1], nullptr, nullptr };
		node_t* n = new node_t { data[0], n_l, n_r };

		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_right_chain_with_leafs_find_compare_with_stdtreeset);


    struct populated_balanced_find_compare_with_stdtreeset
	: public treeset_dynamic_test_find_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, -100, 100, -120, -50, 50, 120 };
		node_t* n_rr = new node_t { data[6], nullptr, nullptr };
		node_t* n_rl = new node_t { data[5], nullptr, nullptr };
		node_t* n_lr = new node_t { data[4], nullptr, nullptr };
		node_t* n_ll = new node_t { data[3], nullptr, nullptr };
		node_t* n_r = new node_t { data[2], n_rl, n_rr };
		node_t* n_l = new node_t { data[1], n_ll, n_lr };
		node_t* n = new node_t { data[0], n_l, n_r };

		test_plug.get_root(container) = n;
		for( elem_t x : data )
		    testtreeset.insert(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_balanced_find_compare_with_stdtreeset);
}
