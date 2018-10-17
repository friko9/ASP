#include "list_array_sorted_warden_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_sorted_warden
{
    struct list_array_sorted_warden_test_populate_3elems_noorder : public list_array_sorted_warden_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
    };

    struct populated_singleelem_exclude_elem_return_head_tail_only
	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = {max, min, 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 0 };
		test_plug.get_Prevs(container) = { 2, 0, 1 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		node_cmp_t head_cmp = test_node(true, 1, {0, 0,data[1]});
		node_cmp_t tail_cmp = test_node(true, 0, {1, 1,data[0]});
		score_t score = head_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_exclude_elem_return_head_tail_only);

    struct populated_3elems_inorder_exclude_elem_first_return_2elems
    	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		node_cmp_t head_cmp = test_node(true, 1, {0,3,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 3, {1,4,data[3]});
		node_cmp_t hn2_cmp = test_node(true, 4, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_first_return_2elems);

    struct populated_3elems_inorder_exclude_elem_middle_return_2elems
    	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 3);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 2, {1,4,data[2]});
		node_cmp_t hn2_cmp = test_node(true, 4, {2,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_inorder_exclude_elem_tail_return_2elems
	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 4);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 2, {1,3,data[2]});
		node_cmp_t hn2_cmp = test_node(true, 3, {2,0,data[3]});
		node_cmp_t tail_cmp = test_node(true, 0, {3,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_tail_return_2elems);

    struct populated_3elems_revorder_exclude_elem_first_return_2elems
    	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 3, 2, 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 4, 0, 2, 3 };
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 1 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 4);
		node_cmp_t head_cmp = test_node(true, 1, {0,3,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 3, {1,2,data[3]});
		node_cmp_t hn2_cmp = test_node(true, 2, {3,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {2,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_first_return_2elems);

    struct populated_3elems_revorder_exclude_elem_middle_return_2elems
	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 3, 2, 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 4, 0, 2, 3 };
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 1 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 3);
		node_cmp_t head_cmp = test_node(true, 1, {0,4,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 4, {1,2,data[4]});
		node_cmp_t hn2_cmp = test_node(true, 2, {4,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {2,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_revorder_exclude_elem_last_return_2elems
    	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 3, 2, 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 4, 0, 2, 3 };
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 1 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		node_cmp_t head_cmp = test_node(true, 1, {0,4,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 4, {1,3,data[4]});
		node_cmp_t hn2_cmp = test_node(true, 3, {4,0,data[3]});
		node_cmp_t tail_cmp = test_node(true, 0, {3,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_last_return_2elems);

    struct populated_3elems_noorder_exclude_elem_first_return_2elems
	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 2, 1, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 3, 4, 2, 0 };
		test_plug.get_Prevs(container) = { 4, 0, 3, 1, 2 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 3);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 2, {1,4,data[2]});
		node_cmp_t hn2_cmp = test_node(true, 4, {2,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_first_return_2elems);

    struct populated_3elems_noorder_exclude_elem_middle_return_2elems
    	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 2, 1, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 3, 4, 2, 0 };
		test_plug.get_Prevs(container) = { 4, 0, 3, 1, 2 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		node_cmp_t head_cmp = test_node(true, 1, {0,3,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 3, {1,4,data[3]});
		node_cmp_t hn2_cmp = test_node(true, 4, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_noorder_exclude_elem_tail_return_2elems
    	: public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { max, min, 2, 1, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 3, 4, 2, 0 };
		test_plug.get_Prevs(container) = { 4, 0, 3, 1, 2 };
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 4);
		node_cmp_t head_cmp = test_node(true, 1, {0,3,data[1]});
		node_cmp_t hn1_cmp = test_node(true, 3, {1,2,data[3]});
		node_cmp_t hn2_cmp = test_node(true, 2, {3,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {2,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_tail_return_2elems);
}

