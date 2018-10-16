#include "list_array_selforganizing_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_selforganizing
{
    struct list_array_selforganizing_test_populate_3elems_noorder
	: public list_array_selforganizing_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;

    };

    struct populated_singleelem_exclude_elem_return_head_null_tail_null
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null };
		test_plug.get_Prevs(container) = { null };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 0);
		bool head_ok = test_plug.get_Head(container) == null;
		bool tail_ok = test_plug.get_Tail(container) == null;
		score_t score = score_t(head_ok) + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_exclude_elem_return_head_null_tail_null);

    struct populated_3elems_inorder_exclude_elem_head_return_2elems
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null };
		test_plug.get_Prevs(container) = { null, 0, 1 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 0);
		bool head_ok = test_plug.get_Head(container) == 1;
		node_cmp_t hn1_cmp = test_node(head_ok, 1, {null,2,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_head_return_2elems);

    struct populated_3elems_inorder_exclude_elem_middle_return_2elems
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null };
		test_plug.get_Prevs(container) = { null, 0, 1 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 1);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,2,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {0,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_inorder_exclude_elem_tail_return_2elems
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null };
		test_plug.get_Prevs(container) = { null, 0, 1 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {0,null,data[1]});
		bool tail_ok = test_plug.get_Tail(container) == 1;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_tail_return_2elems);

    struct populated_3elems_revorder_exclude_elem_head_return_2elems
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0, 1 };
		test_plug.get_Prevs(container) = { 1, 2, null };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		bool head_ok = test_plug.get_Head(container) == 1;
		node_cmp_t hn1_cmp = test_node(head_ok, 1, {null,0,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 0, {1,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_head_return_2elems);

    struct populated_3elems_revorder_exclude_elem_middle_return_2elems
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0, 1 };
		test_plug.get_Prevs(container) = { 1, 2, null };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 1);
		bool head_ok = test_plug.get_Head(container) == 2;
		node_cmp_t hn1_cmp = test_node(head_ok, 2, {null,0,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 0, {2,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_revorder_exclude_elem_tail_return_2elems
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0, 1 };
		test_plug.get_Prevs(container) = { 1, 2, null };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 0);
		bool head_ok = test_plug.get_Head(container) == 2;
		node_cmp_t hn1_cmp = test_node(head_ok, 2, {null,1,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {2,null,data[1]});
		bool tail_ok = test_plug.get_Tail(container) == 1;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_tail_return_2elems);

    struct populated_3elems_noorder_exclude_elem_head_return_2elems
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {null,   2, 0};
		test_plug.get_Prevs(container) = {   2,null, 1};
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 1);
		bool head_ok = test_plug.get_Head(container) == 2;
		node_cmp_t hn1_cmp = test_node(head_ok, 2, {null,0,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 0, {2,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_head_return_2elems);

    struct populated_3elems_noorder_exclude_elem_middle_return_2elems
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {null,   2, 0};
		test_plug.get_Prevs(container) = {   2,null, 1};
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 2);
		bool head_ok = test_plug.get_Head(container) == 1;
		node_cmp_t hn1_cmp = test_node(head_ok, 1, {null,0,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 0, {1,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_noorder_exclude_elem_tail_return_2elems
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {null,   2, 0};
		test_plug.get_Prevs(container) = {   2,null, 1};
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.exclude_elem(container, 0);
		bool head_ok = test_plug.get_Head(container) == 1;
		node_cmp_t hn1_cmp = test_node(head_ok, 1, {null,2,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = score_t(head_ok) + hn1_cmp + hn2_cmp + score_t(tail_ok);
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_tail_return_2elems);
}

