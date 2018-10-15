#include "list_array_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array
{
    struct list_array_test_populate_3elems_noorder_1_excluded
	: public list_array_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = { null, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 2, null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
    };
    
    struct populated1_inorder_move_h_to_0_state_h0_t0
	: public list_array_test_case
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
		bool tail_ok = test_plug.get_Tail(container) == 0;
		node_cmp_t head_cmp = test_node(tail_ok, 0, {null,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated1_inorder_move_h_to_0_state_h0_t0);

    struct populated3_inorder_move_h_to_0_state_h0_hn1_t2
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {    1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0,    1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 0);
		bool head_ok = test_plug.get_Head(container) == 0;
		bool tail_ok = test_plug.get_Tail(container) == 2;
		node_cmp_t head_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1,{0,2,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 2, {1,null,data[2]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_inorder_move_h_to_0_state_h0_hn1_t2);

    struct populated3_inorder_move_hn_to_1_state_h0_hn1_t2
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {    1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0,    1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 1);
		bool head_ok = test_plug.get_Head(container) == 0;
		bool tail_ok = test_plug.get_Tail(container) == 2;
		node_cmp_t head_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1,{0,2,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 2, {1,null,data[2]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_inorder_move_hn_to_1_state_h0_hn1_t2);

    struct populated3_inorder_move_t_to_2_state_h0_hn1_t2
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {    1, 2, null, 99 };
		test_plug.get_Prevs(container) = { null, 0,    1, 99 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 2);
		bool head_ok = test_plug.get_Head(container) == 0;
		bool tail_ok = test_plug.get_Tail(container) == 2;
		node_cmp_t head_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1, {0,2,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 2, {1,null,data[2]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_inorder_move_t_to_2_state_h0_hn1_t2);

    struct populated3_inorder_move_elem_h_to_3_state_h3_hn1_t2
    	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {   1, 2,null, 99};
		test_plug.get_Prevs(container) = {null, 0,   1, 99};
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 3);
		bool head_ok = test_plug.get_Head(container) == 3;
		bool tail_ok = test_plug.get_Tail(container) == 2;
		node_cmp_t head_cmp = test_node(head_ok, 3, {null,1,data[0]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1, {3,2,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 2, {1,null,data[2]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_inorder_move_elem_h_to_3_state_h3_hn1_t2);

    struct populated3_inorder_move_elem_hn_to_3_state_h0_hn3_t2
    	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {   1, 2,null, 99};
		test_plug.get_Prevs(container) = {null, 0,   1, 99};
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 3);
		bool head_ok = test_plug.get_Head(container) == 0;
		bool tail_ok = test_plug.get_Tail(container) == 2;
		node_cmp_t head_cmp = test_node(head_ok, 0, {null,3,data[0]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 3, {0,2,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 2, {3,null,data[2]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_inorder_move_elem_hn_to_3_state_h0_hn3_t2);

    struct populated3_inorder_move_elem_t_to_3_state_h0_hn1_t3
    	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {   1, 2,null, 99};
		test_plug.get_Prevs(container) = {null, 0,   1, 99};
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 2;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 3);
		bool head_ok = test_plug.get_Head(container) == 0;
		bool tail_ok = test_plug.get_Tail(container) == 3;
		node_cmp_t head_cmp = test_node(head_ok, 0, {null,1,data[0]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1, {0,3,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 3, {1,null,data[2]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_inorder_move_elem_t_to_3_state_h0_hn1_t3);

    struct populated3_revorder_move_elem_h_to_3_state_h3_hn1_t0
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0, 1, 99 };
		test_plug.get_Prevs(container) = { 1, 2, null, 99 };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 3);
		bool head_ok = test_plug.get_Head(container) == 3;
		bool tail_ok = test_plug.get_Tail(container) == 0;
		node_cmp_t head_cmp = test_node(head_ok, 3, {null,1,data[2]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1, {3,0,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 0, {1,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_revorder_move_elem_h_to_3_state_h3_hn1_t0);

    struct populated3_revorder_move_elem_hn_to_3_state_h2_hn3_t0
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0, 1, 99 };
		test_plug.get_Prevs(container) = { 1, 2, null, 99 };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 3);
		bool head_ok = test_plug.get_Head(container) == 2;
		bool tail_ok = test_plug.get_Tail(container) == 0;
		node_cmp_t head_cmp = test_node(head_ok, 2, {null,3,data[2]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 3, {2,0,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 0, {3,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_revorder_move_elem_hn_to_3_state_h2_hn3_t0);

    struct populated3_revorder_move_elem_t_to_3_state_h2_hn1_t3
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 0, 1, 99 };
		test_plug.get_Prevs(container) = { 1, 2, null, 99 };
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 3);
		bool head_ok = test_plug.get_Head(container) == 2;
		bool tail_ok = test_plug.get_Tail(container) == 3;
		node_cmp_t head_cmp = test_node(head_ok, 2, {null,1,data[2]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 1, {2,3,data[1]});
		node_cmp_t tail_cmp = test_node(tail_ok, 3, {1,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_revorder_move_elem_t_to_3_state_h2_hn1_t3);

    struct populated3_noorder_move_elem_h_to_3_state_h3_hn2_t0
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 2, null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 1, 3);
		bool head_ok = test_plug.get_Head(container) == 3;
		bool tail_ok = test_plug.get_Tail(container) == 0;
		node_cmp_t head_cmp = test_node(head_ok, 3, {null,2,data[1]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 2, {3,0,data[2]});
		node_cmp_t tail_cmp = test_node(tail_ok, 0, {2,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_noorder_move_elem_h_to_3_state_h3_hn2_t0);

    struct populated3_noorder_move_elem_hn_to_3_state_h1_hn3_t0
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 2, null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 3);
		bool head_ok = test_plug.get_Head(container) == 1;
		bool tail_ok = test_plug.get_Tail(container) == 0;
		node_cmp_t head_cmp = test_node(head_ok, 1, {null,3,data[1]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 3, {1,0,data[2]});
		node_cmp_t tail_cmp = test_node(tail_ok, 0, {3,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_noorder_move_elem_hn_to_3_state_h1_hn3_t0);

    struct populated3_noorder_move_elem_t_to_3_state_h1_hn2_t3
	: public list_array_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { null, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 2, null, 1, 99 };
		test_plug.get_Head(container) = 1;
		test_plug.get_Tail(container) = 0;
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 0, 3);
		bool head_ok = test_plug.get_Head(container) == 1;
		bool tail_ok = test_plug.get_Tail(container) == 3;
		node_cmp_t head_cmp = test_node(head_ok, 1, {null,2,data[1]});
		node_cmp_t mid_cmp = test_node(head_cmp.next_ok, 2, {1,3,data[2]});
		node_cmp_t tail_cmp = test_node(tail_ok, 3, {2,null,data[0]});
		score_t score = score_t(head_ok) + score_t(tail_ok) + head_cmp + mid_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated3_noorder_move_elem_t_to_3_state_h1_hn2_t3);
}
