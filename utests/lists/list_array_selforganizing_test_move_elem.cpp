#include "list_array_selforganizing_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_selforganizing
{
    struct list_array_selforganizing_test_populate_3elems_inorder_1_excluded : public list_array_selforganizing_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		head = 0;
		tail = 2;
		elems =   { 1, 2,    3, 99 };
		next =    { 1, 2, null, 99 };
		prev = { null, 0,    1, 99 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
    };

    struct list_array_selforganizing_test_populate_3elems_revorder_1_excluded : public list_array_selforganizing_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		head = 2;
		tail = 0;
		elems =   { 1, 2,    3, 99 };
		next = { null, 0,    1, 99 };
		prev =    { 1, 2, null, 99 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
    };

    struct list_array_selforganizing_test_populate_3elems_noorder_1_excluded : public list_array_selforganizing_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		head = 1;
		tail = 0;
		elems =   { 1,    2, 3, 99 };
		next = { null,    2, 0, 99 };
		prev =    { 2, null, 1, 99 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
    };
    
    struct populated_singleelem_move_elem_return_not_changed : public list_array_selforganizing_test_case
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { 1 };
		std::vector<int> next = { null };
		std::vector<int> prev = { null };
		int head = 0;
		int tail = 0;

		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_head_next = test_plug.get_Nexts(container).at(0);
		int prev_head_prev = test_plug.get_Prevs(container).at(0);
		elem_t prev_head_val = test_plug.get_Elems(container).at(0);

		int prev_tail = test_plug.get_Tail(container);
		int prev_tail_next = test_plug.get_Nexts(container).at(0);
		int prev_tail_prev = test_plug.get_Prevs(container).at(0);
		elem_t prev_tail_val = test_plug.get_Elems(container).at(0);

		test_plug.move_elem(container, 0,0);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(0);
		int head_prev = test_plug.get_Prevs(container).at(0);
		elem_t head_val = test_plug.get_Elems(container).at(0);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(0);
		int tail_prev = test_plug.get_Prevs(container).at(0);
		elem_t tail_val = test_plug.get_Elems(container).at(0);
		
		bool head_ok = prev_head == head;
		bool head_next_ok = prev_head_next == head_next;
		bool head_prev_ok = prev_head_prev == head_prev;
		bool head_val_ok = prev_head_val == head_val;

		bool tail_ok = prev_tail == tail;
		bool tail_next_ok = prev_tail_next == tail_next;
		bool tail_prev_ok = prev_tail_prev == tail_prev;
		bool tail_val_ok = prev_tail_val == tail_val;

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;
		
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_move_elem_return_not_changed);

    struct populated_3elems_inorder_move_elem_inplace_return_not_changed
	: public list_array_selforganizing_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 3;

		for( int i =0; i < 3; ++i )
		{
		    this->configure();

		    int prev_head = test_plug.get_Head(container);
		    int prev_head_next = test_plug.get_Nexts(container).at(head);
		    int prev_head_prev = test_plug.get_Prevs(container).at(head);
		    elem_t prev_head_val = test_plug.get_Elems(container).at(head);

		    int prev_tail = test_plug.get_Tail(container);
		    int prev_tail_next = test_plug.get_Nexts(container).at(tail);
		    int prev_tail_prev = test_plug.get_Prevs(container).at(tail);
		    elem_t prev_tail_val = test_plug.get_Elems(container).at(tail);

		    test_plug.move_elem(container, i, i);

		    int head = test_plug.get_Head(container);
		    int head_next = test_plug.get_Nexts(container).at(head);
		    int head_prev = test_plug.get_Prevs(container).at(head);
		    elem_t head_val = test_plug.get_Elems(container).at(head);

		    int tail = test_plug.get_Tail(container);
		    int tail_next = test_plug.get_Nexts(container).at(tail);
		    int tail_prev = test_plug.get_Prevs(container).at(tail);
		    elem_t tail_val = test_plug.get_Elems(container).at(tail);
		
		    bool head_ok = prev_head == head;
		    bool head_next_ok = prev_head_next == head_next;
		    bool head_prev_ok = prev_head_prev == head_prev;
		    bool head_val_ok = prev_head_val == head_val;

		    bool tail_ok = prev_tail == tail;
		    bool tail_next_ok = prev_tail_next == tail_next;
		    bool tail_prev_ok = prev_tail_prev == tail_prev;
		    bool tail_val_ok = prev_tail_val == tail_val;

		    bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
			&& tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		    if( test )
			++result;
		}
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_inplace_return_not_changed);

    struct populated_3elems_inorder_move_elem_head_return_consistent
	: public list_array_selforganizing_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 0, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == 3;
		bool head_next_ok = next.at(3) == prev_next.at(0);
		bool head_prev_ok = prev.at(3) == prev_prev.at(0);
		bool head_val_ok = elems.at(3) == prev_elems.at(0);

		bool mid_next_ok = next.at(1) == prev_next.at(1);
		bool mid_prev_ok = prev.at(1) == 3;
		bool mid_val_ok = elems.at(1) == prev_elems.at(1);

		bool tail_ok = prev_tail == tail;
		bool tail_next_ok = next.at(2) == prev_next.at(2);
		bool tail_prev_ok = prev.at(2) == prev_prev.at(2);
		bool tail_val_ok = elems.at(2) == prev_elems.at(2);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_head_return_consistent);

    struct populated_3elems_inorder_move_elem_middle_return_consistent
	: public list_array_selforganizing_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 1, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == prev_head;
		bool head_next_ok = next.at(0) == 3;
		bool head_prev_ok = prev.at(0) == prev_prev.at(0);
		bool head_val_ok = elems.at(0) == prev_elems.at(0);

		bool mid_next_ok = next.at(3) == prev_next.at(1);
		bool mid_prev_ok = prev.at(3) == prev_prev.at(1);
		bool mid_val_ok = elems.at(3) == prev_elems.at(1);

		bool tail_ok = tail == prev_tail;
		bool tail_next_ok = next.at(2) == prev_next.at(2);
		bool tail_prev_ok = prev.at(2) == 3;
		bool tail_val_ok = elems.at(2) == prev_elems.at(2);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_middle_return_consistent);

    struct populated_3elems_inorder_move_elem_tail_return_consistent
	: public list_array_selforganizing_test_populate_3elems_inorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 2, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == prev_head;
		bool head_next_ok = next.at(0) == prev_next.at(0);
		bool head_prev_ok = prev.at(0) == prev_prev.at(0);
		bool head_val_ok = elems.at(0) == prev_elems.at(0);

		bool mid_next_ok = next.at(1) == 3;
		bool mid_prev_ok = prev.at(1) == prev_prev.at(1);
		bool mid_val_ok = elems.at(1) == prev_elems.at(1);

		bool tail_ok = tail == 3;
		bool tail_next_ok = next.at(3) == prev_next.at(2);
		bool tail_prev_ok = prev.at(3) == prev_prev.at(2);
		bool tail_val_ok = elems.at(3) == prev_elems.at(2);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_move_elem_tail_return_consistent);

    struct populated_3elems_revorder_move_elem_head_return_consistent
	: public list_array_selforganizing_test_populate_3elems_revorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 2, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == 3;
		bool head_next_ok = next.at(3) == prev_next.at(2);
		bool head_prev_ok = prev.at(3) == prev_prev.at(2);
		bool head_val_ok = elems.at(3) == prev_elems.at(2);

		bool mid_next_ok = next.at(1) == prev_next.at(1);
		bool mid_prev_ok = prev.at(1) == 3;
		bool mid_val_ok = elems.at(1) == prev_elems.at(1);

		bool tail_ok = prev_tail == tail;
		bool tail_next_ok = next.at(0) == prev_next.at(0);
		bool tail_prev_ok = prev.at(0) == prev_prev.at(0);
		bool tail_val_ok = elems.at(0) == prev_elems.at(0);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_head_return_consistent);

    struct populated_3elems_revorder_move_elem_middle_return_consistent
	: public list_array_selforganizing_test_populate_3elems_revorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 1, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == prev_head;
		bool head_next_ok = next.at(2) == 3;
		bool head_prev_ok = prev.at(2) == prev_prev.at(2);
		bool head_val_ok = elems.at(2) == prev_elems.at(2);

		bool mid_next_ok = next.at(3) == prev_next.at(1);
		bool mid_prev_ok = prev.at(3) == prev_prev.at(1);
		bool mid_val_ok = elems.at(3) == prev_elems.at(1);

		bool tail_ok = tail == prev_tail;
		bool tail_next_ok = next.at(0) == prev_next.at(0);
		bool tail_prev_ok = prev.at(0) == 3;
		bool tail_val_ok = elems.at(0) == prev_elems.at(0);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_middle_return_consistent);

    struct populated_3elems_revorder_move_elem_tail_return_consistent
    	: public list_array_selforganizing_test_populate_3elems_revorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 0, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == prev_head;
		bool head_next_ok = next.at(2) == prev_next.at(2);
		bool head_prev_ok = prev.at(2) == prev_prev.at(2);
		bool head_val_ok = elems.at(2) == prev_elems.at(2);

		bool mid_next_ok = next.at(1) == 3;
		bool mid_prev_ok = prev.at(1) == prev_prev.at(1);
		bool mid_val_ok = elems.at(1) == prev_elems.at(1);

		bool tail_ok = tail == 3;
		bool tail_next_ok = next.at(3) == prev_next.at(0);
		bool tail_prev_ok = prev.at(3) == prev_prev.at(0);
		bool tail_val_ok = elems.at(3) == prev_elems.at(0);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_move_elem_tail_return_consistent);

    struct populated_3elems_noorder_move_elem_head_return_consistent
	: public list_array_selforganizing_test_populate_3elems_noorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 1, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == 3;
		bool head_next_ok = next.at(3) == prev_next.at(1);
		bool head_prev_ok = prev.at(3) == prev_prev.at(1);
		bool head_val_ok = elems.at(3) == prev_elems.at(1);

		bool mid_next_ok = next.at(2) == prev_next.at(2);
		bool mid_prev_ok = prev.at(2) == 3;
		bool mid_val_ok = elems.at(2) == prev_elems.at(2);

		bool tail_ok = prev_tail == tail;
		bool tail_next_ok = next.at(0) == prev_next.at(0);
		bool tail_prev_ok = prev.at(0) == prev_prev.at(0);
		bool tail_val_ok = elems.at(0) == prev_elems.at(0);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_head_return_consistent);

    struct populated_3elems_noorder_move_elem_middle_return_consistent
	: public list_array_selforganizing_test_populate_3elems_noorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 2, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == prev_head;
		bool head_next_ok = next.at(1) == 3;
		bool head_prev_ok = prev.at(1) == prev_prev.at(1);
		bool head_val_ok = elems.at(1) == prev_elems.at(1);

		bool mid_next_ok = next.at(3) == prev_next.at(2);
		bool mid_prev_ok = prev.at(3) == prev_prev.at(2);
		bool mid_val_ok = elems.at(3) == prev_elems.at(2);

		bool tail_ok = tail == prev_tail;
		bool tail_next_ok = next.at(0) == prev_next.at(0);
		bool tail_prev_ok = prev.at(0) == 3;
		bool tail_val_ok = elems.at(0) == prev_elems.at(0);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_middle_return_consistent);

    struct populated_3elems_noorder_move_elem_tail_return_consistent
    	: public list_array_selforganizing_test_populate_3elems_noorder_1_excluded
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;

		int prev_head = test_plug.get_Head(container);
		int prev_tail = test_plug.get_Tail(container);
		std::vector<elem_t> prev_elems = test_plug.get_Elems(container);
		std::vector<int> prev_next = test_plug.get_Nexts(container);
		std::vector<int> prev_prev = test_plug.get_Prevs(container);

		test_plug.move_elem(container, 0, 3);

		int head = test_plug.get_Head(container);
		int tail = test_plug.get_Tail(container);
		std::vector<elem_t> elems = test_plug.get_Elems(container);
		std::vector<int> next = test_plug.get_Nexts(container);
		std::vector<int> prev = test_plug.get_Prevs(container);
		
		bool head_ok = head == prev_head;
		bool head_next_ok = next.at(1) == prev_next.at(1);
		bool head_prev_ok = prev.at(1) == prev_prev.at(1);
		bool head_val_ok = elems.at(1) == prev_elems.at(1);

		bool mid_next_ok = next.at(2) == 3;
		bool mid_prev_ok = prev.at(2) == prev_prev.at(2);
		bool mid_val_ok = elems.at(2) == prev_elems.at(2);

		bool tail_ok = tail == 3;
		bool tail_next_ok = next.at(3) == prev_next.at(0);
		bool tail_prev_ok = prev.at(3) == prev_prev.at(0);
		bool tail_val_ok = elems.at(3) == prev_elems.at(0);

		bool test = head_ok && head_next_ok && head_prev_ok && head_val_ok
		    && mid_next_ok && mid_prev_ok && mid_val_ok
		    && tail_ok && tail_next_ok && tail_prev_ok && tail_val_ok;

		if( test )
		    ++result;

		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_move_elem_tail_return_consistent);
}
