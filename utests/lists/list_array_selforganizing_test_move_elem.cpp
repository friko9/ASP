#include "list_array_selforganizing_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_selforganizing
{
    
    struct list_array_selforganizing_test_populate_3elems_revorder_1_excluded
	: public list_array_selforganizing_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;

    };

    
    struct populated_singleelem_move_elem_return_not_changed
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
		test_plug.move_elem(container, 0, 0);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = head_ok + hn1_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_move_elem_return_not_changed);

    struct populated_3elems_inorder_move_elem_0_to_0_return_not_changed
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data  = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0, 1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 0);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {0,2,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_0_to_0_return_not_changed);

    struct populated_3elems_inorder_move_elem_1_to_1_return_not_changed
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data  = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0, 1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 1);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {0,2,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_1_to_1_return_not_changed);

    struct populated_3elems_inorder_move_elem_2_to_2_return_not_changed
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data  = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0, 1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 2);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {0,2,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_2_to_2_return_not_changed);

    struct populated_3elems_inorder_move_elem_head_return_consistent
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	
	void configure()
	    {
		data  = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0, 1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 3);
		bool head_ok = test_plug.get_Head(container) == 3;
		node_cmp_t hn1_cmp = test_node(head_ok, 3, {null,1,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {3,2,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_head_return_consistent);

    struct populated_3elems_inorder_move_elem_middle_return_consistent
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data  = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0, 1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 3);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,3,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {0,2,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {3,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 2;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_middle_return_consistent);

    struct populated_3elems_inorder_move_elem_tail_return_consistent
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data  = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0, 1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 3);
		bool head_ok = test_plug.get_Head(container) == 0;
		node_cmp_t hn1_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {0,3,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 3, {1,null,data[2]});
		bool tail_ok = test_plug.get_Tail(container) == 3;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_tail_return_consistent);

    struct populated_3elems_revorder_move_elem_head_return_consistent
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data =   { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0,    1, 99 };
		test_plug.get_Prevs(container) = {    1, 2, null, 99 };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 3);
		bool head_ok = test_plug.get_Head(container) == 3;
		node_cmp_t hn1_cmp = test_node(head_ok, 3, {null,1,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {3,0,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 0, {1,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_head_return_consistent);

    struct populated_3elems_revorder_move_elem_middle_return_consistent
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data =   { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0,    1, 99 };
		test_plug.get_Prevs(container) = {    1, 2, null, 99 };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 3);
		bool head_ok = test_plug.get_Head(container) == 2;
		node_cmp_t hn1_cmp = test_node(head_ok, 2, {null,3,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {2,0,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 0, {3,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_middle_return_consistent);

    struct populated_3elems_revorder_move_elem_tail_return_consistent
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
		void configure()
	    {
		data =   { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0,    1, 99 };
		test_plug.get_Prevs(container) = {    1, 2, null, 99 };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 3);
		bool head_ok = test_plug.get_Head(container) == 2;
		node_cmp_t hn1_cmp = test_node(head_ok, 2, {null,1,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 1, {2,3,data[1]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 3, {1,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 3;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_tail_return_consistent);

    struct populated_3elems_noorder_move_elem_head_return_consistent
	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data =   { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null,   2, 0, 99 };
		test_plug.get_Prevs(container) = {    2,null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 3);
		bool head_ok = test_plug.get_Head(container) == 3;
		node_cmp_t hn1_cmp = test_node(head_ok, 3, {null,2,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {3,0,data[2]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 0, {2,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_head_return_consistent);

    struct populated_3elems_noorder_move_elem_middle_return_consistent
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data =   { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 2, 0, 99 };
		test_plug.get_Prevs(container) = {    2, null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 3);
		bool head_ok = test_plug.get_Head(container) == 1;
		node_cmp_t hn1_cmp = test_node(head_ok, 1, {null,3,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {1,0,data[2]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 0, {3,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 0;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_middle_return_consistent);

    struct populated_3elems_noorder_move_elem_tail_return_consistent
    	: public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data =   { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 2, 0, 99 };
		test_plug.get_Prevs(container) = {    2, null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 3);
		bool head_ok = test_plug.get_Head(container) == 1;
		node_cmp_t hn1_cmp = test_node(head_ok, 1, {null,2,data[1]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {1,3,data[2]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 3, {2,null,data[0]});
		bool tail_ok = test_plug.get_Tail(container) == 3;
		score_t score = head_ok + hn1_cmp + hn2_cmp + hn3_cmp + tail_ok;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_tail_return_consistent);
}
