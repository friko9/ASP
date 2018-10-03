#include "list_array_enchanced_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_enchanced
{
    struct list_array_enchanced_test_populate_3elems_inorder : public list_array_enchanced_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1, 2, 3 };
		next =  { 1, 2, 3, 4, 0 };
		prev =  { 4, 0, 1, 2, 3 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
	    }
    };

    struct list_array_enchanced_test_populate_3elems_revorder : public list_array_enchanced_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1, 2, 3 };
		next =  { 1, 4, 0, 2, 3 };
		prev =  { 2, 0, 3, 4, 1 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
	    }
    };

    struct list_array_enchanced_test_populate_3elems_noorder : public list_array_enchanced_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1, 2, 3 };
		next =  { 1, 3, 4, 2, 0 };
		prev =  { 4, 0, 3, 1, 2 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
	    }
    };

    struct populated_singleelem_exclude_elem_return_head_tail_only : public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { 0, 0, 1 };
		std::vector<int> next = { 1, 2, 0 };
		std::vector<int> prev = { 2, 0, 1 };

		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
	test_result run()
	    {
		test_result result = 1;

		test_plug.exclude_elem(container, 2);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);

		bool head_ok = test_plug.get_Head(container) == 1;
		bool tail_ok = test_plug.get_Tail(container) == 0;
		bool head_next_ok = nexts.at(1) == 0;
		bool head_prev_ok = prevs.at(1) == 0;
		bool tail_next_ok = nexts.at(0) == 1;
		bool tail_prev_ok = prevs.at(0) == 1;
		
		bool test = head_ok && head_next_ok && head_next_ok
		    && tail_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_exclude_elem_return_head_tail_only);

    struct populated_3elems_inorder_exclude_elem_first_return_2elems
	: public list_array_enchanced_test_populate_3elems_inorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 2);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 3;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 4;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 2;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 3;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_first_return_2elems);

    struct populated_3elems_inorder_exclude_elem_last_return_2elems
	: public list_array_enchanced_test_populate_3elems_inorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 4);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 2;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 3;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 1;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 2;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_last_return_2elems);

    struct populated_3elems_inorder_exclude_elem_middle_return_2elems
	: public list_array_enchanced_test_populate_3elems_inorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 3);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 2;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 4;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 1;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 3;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_revorder_exclude_elem_first_return_2elems
    	: public list_array_enchanced_test_populate_3elems_revorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 2);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 4;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 3;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 3;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 2;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_first_return_2elems);

    struct populated_3elems_revorder_exclude_elem_last_return_2elems
    	: public list_array_enchanced_test_populate_3elems_revorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 4);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 3;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 2;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 2;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 1;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_last_return_2elems);

    struct populated_3elems_revorder_exclude_elem_middle_return_2elems
	: public list_array_enchanced_test_populate_3elems_revorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 3);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 4;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 2;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 3;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 1;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_noorder_exclude_elem_first_return_2elems
    	: public list_array_enchanced_test_populate_3elems_noorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 2);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 3;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 4;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 2;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 3;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_first_return_2elems);

    struct populated_3elems_noorder_exclude_elem_last_return_2elems
    	: public list_array_enchanced_test_populate_3elems_noorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 4);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 3;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 2;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 2;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 1;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_last_return_2elems);

    struct populated_3elems_noorder_exclude_elem_middle_return_2elems
	: public list_array_enchanced_test_populate_3elems_noorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 3);

		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		int head = test_plug.get_Head(container);
		int head_next = nexts.at(head);

		int first = 2;
		int first_next = nexts.at(first);
		int first_prev = prevs.at(first);
		elem_t first_val = elems.at(first);

		int second = 4;
		int second_next = nexts.at(second);
		int second_prev = prevs.at(second);
		elem_t second_val = elems.at(second);

		int tail = test_plug.get_Tail(container);
		int tail_prev = prevs.at(tail);

		bool head_ok = head == 1;
		bool head_next_ok = head_next == first;
		bool tail_ok = tail == 0;
		bool tail_prev_ok = tail_prev == second;
		bool first_next_ok = first_next == second;
		bool first_prev_ok = first_prev == head;
		bool first_val_ok = elems[first] == 1;
		bool second_next_ok = second_next == tail;
		bool second_prev_ok = second_prev == first;
		bool second_val_ok = elems[second] == 3;
		
		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_next_ok && first_prev_ok && first_val_ok
		    && second_next_ok && second_prev_ok && second_val_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_middle_return_2elems);
}

