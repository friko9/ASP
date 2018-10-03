#include "list_array_enchanced_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_enchanced
{
    struct populated_singleelem_move_elem_return_not_changed
	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 0 };
		test_plug.get_Prevs(container) = { 2, 0, 1 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 2);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 2, {1,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {2,1,data[0]});
		score_t score = head_cmp + hn1_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_move_elem_return_not_changed);

    struct populated_3elems_inorder_move_elem_2_to_2_return_not_changed
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 2);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 2, {1,3,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {2,4,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_2_to_2_return_not_changed);

    struct populated_3elems_inorder_move_elem_3_to_3_return_not_changed
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 3, 3);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 2, {1,3,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {2,4,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_3_to_3_return_not_changed);

    struct populated_3elems_inorder_move_elem_4_to_4_return_not_changed
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 4, 4);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 2, {1,3,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {2,4,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_4_to_4_return_not_changed);

    struct populated_3elems_inorder_move_elem_first_return_consistent
	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,5,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 5, {1,3,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {5,4,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_first_return_consistent);

    struct populated_3elems_inorder_move_elem_middle_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 3, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 2, {1,5,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 5, {2,4,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {5,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_middle_return_consistent);

    struct populated_3elems_inorder_move_elem_last_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 1, 2, 3, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 4, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,2,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 2, {1,3,data[2]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {2,5,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 5, {3,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {5,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_last_return_consistent);

    struct populated_3elems_revorder_move_elem_first_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 4, 0, 2, 3, 99 };
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 1, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 4, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,5,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 5, {1,3,data[4]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {5,2,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {3,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {2,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_first_return_consistent);

    struct populated_3elems_revorder_move_elem_middle_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 4, 0, 2, 3, 99 };
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 1, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 3, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,4,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 4, {1,5,data[4]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 5, {4,2,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 2, {5,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {2,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_middle_return_consistent);

    struct populated_3elems_revorder_move_elem_last_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 4, 0, 2, 3, 99 };
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 1, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,4,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 4, {1,3,data[4]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 3, {4,5,data[3]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 5, {3,0,data[2]});
		node_cmp_t tail_cmp = test_node(true, 0, {5,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_last_return_consistent);

    struct populated_3elems_noorder_move_elem_first_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 3, 4, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 3, 1, 2, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 3, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,5,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 5, {1,2,data[3]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {5,4,data[2]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {2,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_first_return_consistent);

    struct populated_3elems_noorder_move_elem_middle_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 3, 4, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 3, 1, 2, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 2, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,3,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 3, {1,5,data[3]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 5, {3,4,data[2]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 4, {5,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {4,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_middle_return_consistent);

    struct populated_3elems_noorder_move_elem_last_return_consistent
    	: public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 99 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 3, 4, 2, 0, 99 };
		test_plug.get_Prevs(container) = { 4, 0, 3, 1, 2, 99 };
	    }
	test_result run()
	    {
		test_plug.move_elem(container, 4, 5);
		node_cmp_t head_cmp = test_node(true, 1, {0,3,data[1]});
		node_cmp_t hn1_cmp = test_node(head_cmp.next_ok, 3, {1,2,data[3]});
		node_cmp_t hn2_cmp = test_node(hn1_cmp.next_ok, 2, {3,5,data[2]});
		node_cmp_t hn3_cmp = test_node(hn2_cmp.next_ok, 5, {2,0,data[4]});
		node_cmp_t tail_cmp = test_node(true, 0, {5,1,data[0]});
		score_t score = head_cmp + hn1_cmp + hn2_cmp + hn3_cmp + tail_cmp;
		return score;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_last_return_consistent);
}
