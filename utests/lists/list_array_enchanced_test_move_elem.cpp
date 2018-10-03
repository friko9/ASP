#include "list_array_enchanced_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_enchanced
{
    struct list_array_enchanced_test_populate_3elems_inorder_1_excluded : public list_array_enchanced_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1, 2, 3, 99 };
		next =  { 1, 2, 3, 4, 0, 99 };
		prev =  { 4, 0, 1, 2, 3, 99 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
	    }
    };

    struct list_array_enchanced_test_populate_3elems_revorder_1_excluded : public list_array_enchanced_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1, 2, 3, 99 };
		next =  { 1, 4, 0, 2, 3, 99 };
		prev =  { 2, 0, 3, 4, 1, 99 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
	    }
    };

    struct list_array_enchanced_test_populate_3elems_noorder_1_excluded : public list_array_enchanced_test_case
    {
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1, 2, 3, 99 };
		next =  { 1, 3, 4, 2, 0, 99 };
		prev =  { 4, 0, 3, 1, 2, 99 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
	    }
    };
    
    struct populated_singleelem_move_elem_return_not_changed : public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		elems = { 0, 0, 1 };
		next =  { 1, 2, 0 };
		prev =  { 2, 0, 1 };

		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_nexts = test_plug.get_Nexts(container);
		auto prev_prevs = test_plug.get_Prevs(container);
		auto prev_elems = test_plug.get_Elems(container);

		test_plug.move_elem(container, 2, 2);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = prev_nexts.at(head) == nexts.at(head);

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prev_prevs.at(tail) == prevs.at(tail);

		bool elem_val_ok = prev_elems[2] == elems[2];
		bool elem_prev_ok = prev_prevs[2] == head;
		bool elem_next_ok = prev_nexts[2] == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && elem_val_ok && elem_prev_ok && elem_next_ok;
		
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_move_elem_return_not_changed);

    struct populated_3elems_inorder_move_elem_inplace_return_not_changed
	: public list_array_enchanced_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 3;
		int first = 2;
		int second = 3;
		int last = 4;

		for( int i =2; i < 5; ++i )
		{
		    this->configure();
		    
		    int prev_head = test_plug.get_Head(container);
		    int prev_tail = test_plug.get_Tail(container);
		    auto prev_nexts = test_plug.get_Nexts(container);
		    auto prev_prevs = test_plug.get_Prevs(container);
		    auto prev_elems = test_plug.get_Elems(container);

		    test_plug.move_elem(container, i, i);

		    int head = test_plug.get_Head(container);
		    int tail = test_plug.get_Tail(container);
		    auto nexts = test_plug.get_Nexts(container);
		    auto prevs = test_plug.get_Prevs(container);
		    auto elems = test_plug.get_Elems(container);
		
		    bool head_ok = prev_head == head;
		    bool head_next_ok = prev_nexts.at(head) == nexts.at(head);

		    bool tail_ok = prev_tail == tail;
		    bool tail_prev_ok = prev_prevs.at(tail) == prevs.at(tail);

		    bool first_val_ok = prev_elems.at(first) == elems.at(first);
		    bool first_prev_ok = prev_prevs.at(first) == prevs.at(first);
		    bool first_next_ok = prev_nexts.at(first) == nexts.at(first);

		    bool second_val_ok = prev_elems.at(second) == elems.at(second);
		    bool second_prev_ok = prev_prevs.at(second) == prevs.at(second);
		    bool second_next_ok = prev_nexts.at(second) == nexts.at(second);

		    bool last_val_ok = prev_elems.at(last) == elems.at(last);
		    bool last_prev_ok = prev_prevs.at(last) == prevs.at(last);
		    bool last_next_ok = prev_nexts.at(last) == nexts.at(last);

		    bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
			&& first_val_ok && first_prev_ok && first_next_ok
			&& second_val_ok && second_prev_ok && second_next_ok
			&& last_val_ok && last_prev_ok && last_next_ok;

		    if( test )
			++result;
		}
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_inplace_return_not_changed);

    struct populated_3elems_inorder_move_elem_first_return_consistent
	: public list_array_enchanced_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 2;
		int second = 3;
		int last = 4;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, first, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == dest;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == last;

		bool first_val_ok = elems.at(dest) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(dest) == head;
		bool first_next_ok = nexts.at(dest) == second;

		bool second_val_ok = elems.at(second) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(second) == dest;
		bool second_next_ok = nexts.at(second) == last;

		bool last_val_ok = elems.at(last) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(last) == second;
		bool last_next_ok = nexts.at(last) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_first_return_consistent);

    struct populated_3elems_inorder_move_elem_middle_return_consistent
	: public list_array_enchanced_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 2;
		int second = 3;
		int last = 4;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, second, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == first;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == last;

		bool first_val_ok = elems.at(first) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(first) == head;
		bool first_next_ok = nexts.at(first) == dest;

		bool second_val_ok = elems.at(dest) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(dest) == first;
		bool second_next_ok = nexts.at(dest) == last;

		bool last_val_ok = elems.at(last) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(last) == dest;
		bool last_next_ok = nexts.at(last) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_middle_return_consistent);

    struct populated_3elems_inorder_move_elem_last_return_consistent
	: public list_array_enchanced_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 2;
		int second = 3;
		int last = 4;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, last, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == first;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == dest;

		bool first_val_ok = elems.at(first) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(first) == head;
		bool first_next_ok = nexts.at(first) == second;

		bool second_val_ok = elems.at(second) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(second) == first;
		bool second_next_ok = nexts.at(second) == dest;

		bool last_val_ok = elems.at(dest) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(dest) == second;
		bool last_next_ok = nexts.at(dest) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_last_return_consistent);

    struct populated_3elems_revorder_move_elem_first_return_consistent
	: public list_array_enchanced_test_populate_3elems_revorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 4;
		int second = 3;
		int last = 2;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, first, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == dest;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == last;

		bool first_val_ok = elems.at(dest) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(dest) == head;
		bool first_next_ok = nexts.at(dest) == second;

		bool second_val_ok = elems.at(second) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(second) == dest;
		bool second_next_ok = nexts.at(second) == last;

		bool last_val_ok = elems.at(last) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(last) == second;
		bool last_next_ok = nexts.at(last) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_first_return_consistent);

    struct populated_3elems_revorder_move_elem_middle_return_consistent
	: public list_array_enchanced_test_populate_3elems_revorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 4;
		int second = 3;
		int last = 2;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, second, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == first;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == last;

		bool first_val_ok = elems.at(first) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(first) == head;
		bool first_next_ok = nexts.at(first) == dest;

		bool second_val_ok = elems.at(dest) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(dest) == first;
		bool second_next_ok = nexts.at(dest) == last;

		bool last_val_ok = elems.at(last) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(last) == dest;
		bool last_next_ok = nexts.at(last) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_middle_return_consistent);

    struct populated_3elems_revorder_move_elem_last_return_consistent
    	: public list_array_enchanced_test_populate_3elems_revorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 4;
		int second = 3;
		int last = 2;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, last, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == first;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == dest;

		bool first_val_ok = elems.at(first) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(first) == head;
		bool first_next_ok = nexts.at(first) == second;

		bool second_val_ok = elems.at(second) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(second) == first;
		bool second_next_ok = nexts.at(second) == dest;

		bool last_val_ok = elems.at(dest) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(dest) == second;
		bool last_next_ok = nexts.at(dest) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_last_return_consistent);

    struct populated_3elems_noorder_move_elem_first_return_consistent
	: public list_array_enchanced_test_populate_3elems_noorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 3;
		int second = 2;
		int last = 4;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, first, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == dest;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == last;

		bool first_val_ok = elems.at(dest) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(dest) == head;
		bool first_next_ok = nexts.at(dest) == second;

		bool second_val_ok = elems.at(second) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(second) == dest;
		bool second_next_ok = nexts.at(second) == last;

		bool last_val_ok = elems.at(last) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(last) == second;
		bool last_next_ok = nexts.at(last) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_first_return_consistent);

    struct populated_3elems_noorder_move_elem_middle_return_consistent
	: public list_array_enchanced_test_populate_3elems_noorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 3;
		int second = 2;
		int last = 4;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, second, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == first;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == last;

		bool first_val_ok = elems.at(first) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(first) == head;
		bool first_next_ok = nexts.at(first) == dest;

		bool second_val_ok = elems.at(dest) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(dest) == first;
		bool second_next_ok = nexts.at(dest) == last;

		bool last_val_ok = elems.at(last) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(last) == dest;
		bool last_next_ok = nexts.at(last) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_middle_return_consistent);

    struct populated_3elems_noorder_move_elem_last_return_consistent
    	: public list_array_enchanced_test_populate_3elems_noorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		int first = 3;
		int second = 2;
		int last = 4;
		int dest = 5;
		
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		auto prev_elems = test_plug.get_Elems(container);
		
		test_plug.move_elem(container, last, dest);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		auto nexts = test_plug.get_Nexts(container);
		auto prevs = test_plug.get_Prevs(container);
		auto elems = test_plug.get_Elems(container);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = nexts.at(head) == first;

		bool tail_ok = prev_tail == tail;
		bool tail_prev_ok = prevs.at(tail) == dest;

		bool first_val_ok = elems.at(first) == prev_elems.at(first);
		bool first_prev_ok = prevs.at(first) == head;
		bool first_next_ok = nexts.at(first) == second;

		bool second_val_ok = elems.at(second) == prev_elems.at(second);
		bool second_prev_ok = prevs.at(second) == first;
		bool second_next_ok = nexts.at(second) == dest;

		bool last_val_ok = elems.at(dest) == prev_elems.at(last);
		bool last_prev_ok = prevs.at(dest) == second;
		bool last_next_ok = nexts.at(dest) == tail;

		bool test = head_ok && head_next_ok && tail_ok && tail_prev_ok
		    && first_val_ok && first_prev_ok && first_next_ok
		    && second_val_ok && second_prev_ok && second_next_ok
		    && last_val_ok && last_prev_ok && last_next_ok;

		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_last_return_consistent);
}
