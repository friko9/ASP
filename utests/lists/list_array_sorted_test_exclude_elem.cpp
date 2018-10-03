#include "list_array_sorted_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_sorted
{
    struct list_array_sorted_test_populate_3elems_inorder : public list_array_sorted_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		head = 0;
		tail = 2;
		elems = { 1, 2, 3 };
		next = { 1, 2, null };
		prev = { null, 0, 1 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
    };

    struct list_array_sorted_test_populate_3elems_revorder : public list_array_sorted_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		head = 2;
		tail = 0;
		elems = { 1, 2, 3 };
		next = { null, 0, 1 };
		prev = { 1, 2, null };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
    };

    struct list_array_sorted_test_populate_3elems_noorder : public list_array_sorted_test_case
    {
	int head,tail;
	std::vector<elem_t> elems;
	std::vector<int> next,prev;
	void configure()
	    {
		head = 1;
		tail = 0;
		elems =   { 1,    2, 3 };
		next = { null,    2, 0 };
		prev =    { 2, null, 1 };

		test_plug.get_Elems(container) = elems;
		test_plug.get_Nexts(container) = next;
		test_plug.get_Prevs(container) = prev;
		test_plug.get_Head(container) = head;
		test_plug.get_Tail(container) = tail;
	    }
    };

    struct populated_singleelem_exclude_elem_return_head_null_tail_null : public list_array_sorted_test_case
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

		test_plug.exclude_elem(container, 0);

		bool head_null = test_plug.get_Head(container) == null;
		bool tail_null = test_plug.get_Tail(container) == null;
		bool test = head_null && tail_null;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_exclude_elem_return_head_null_tail_null);

    struct populated_3elems_inorder_exclude_elem_head_return_2elems
	: public list_array_sorted_test_populate_3elems_inorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, head);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 1;
		bool head_val_ok = head_val == elems[1];
		bool head_next_ok = head_next == 2;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 2;
		bool tail_val_ok = tail_val = elems[2];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 1;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_head_return_2elems);

    struct populated_3elems_inorder_exclude_elem_tail_return_2elems
	: public list_array_sorted_test_populate_3elems_inorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, tail);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 0;
		bool head_val_ok = head_val == elems[0];
		bool head_next_ok = head_next == 1;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 1;
		bool tail_val_ok = tail_val = elems[1];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 0;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_tail_return_2elems);

    struct populated_3elems_inorder_exclude_elem_middle_return_2elems
	: public list_array_sorted_test_populate_3elems_inorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 1);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 0;
		bool head_val_ok = head_val == elems[0];
		bool head_next_ok = head_next == 2;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 2;
		bool tail_val_ok = tail_val = elems[2];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 0;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_inorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_revorder_exclude_elem_head_return_2elems
    	: public list_array_sorted_test_populate_3elems_revorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, head);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 1;
		bool head_val_ok = head_val == elems[1];
		bool head_next_ok = head_next == 0;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 0;
		bool tail_val_ok = tail_val = elems[0];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 1;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_head_return_2elems);

    struct populated_3elems_revorder_exclude_elem_tail_return_2elems
    	: public list_array_sorted_test_populate_3elems_revorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, tail);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 2;
		bool head_val_ok = head_val == elems[2];
		bool head_next_ok = head_next == 1;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 1;
		bool tail_val_ok = tail_val = elems[1];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 2;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_tail_return_2elems);

    struct populated_3elems_revorder_exclude_elem_middle_return_2elems
	: public list_array_sorted_test_populate_3elems_revorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 1);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 2;
		bool head_val_ok = head_val == elems[2];
		bool head_next_ok = head_next == 0;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 0;
		bool tail_val_ok = tail_val = elems[0];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 2;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_revorder_exclude_elem_middle_return_2elems);

    struct populated_3elems_noorder_exclude_elem_head_return_2elems
    	: public list_array_sorted_test_populate_3elems_noorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, head);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 2;
		bool head_val_ok = head_val == elems[2];
		bool head_next_ok = head_next == 0;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 0;
		bool tail_val_ok = tail_val = elems[0];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 2;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_head_return_2elems);

    struct populated_3elems_noorder_exclude_elem_tail_return_2elems
    	: public list_array_sorted_test_populate_3elems_noorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, tail);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 1;
		bool head_val_ok = head_val == elems[1];
		bool head_next_ok = head_next == 2;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 2;
		bool tail_val_ok = tail_val = elems[2];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 1;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_tail_return_2elems);

    struct populated_3elems_noorder_exclude_elem_middle_return_2elems
	: public list_array_sorted_test_populate_3elems_noorder
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = 1;
		
		test_plug.exclude_elem(container, 2);

		int head = test_plug.get_Head(container);
		int head_next = test_plug.get_Nexts(container).at(head);
		int head_prev = test_plug.get_Prevs(container).at(head);
		elem_t head_val = test_plug.get_Elems(container).at(head);

		int tail = test_plug.get_Tail(container);
		int tail_next = test_plug.get_Nexts(container).at(tail);
		int tail_prev = test_plug.get_Prevs(container).at(tail);
		elem_t tail_val = test_plug.get_Elems(container).at(tail);

		bool head_ok = head == 1;
		bool head_val_ok = head_val == elems[1];
		bool head_next_ok = head_next == 0;
		bool head_prev_ok = head_prev == null;

		bool tail_ok = tail == 0;
		bool tail_val_ok = tail_val = elems[0];
		bool tail_next_ok = tail_next == null;
		bool tail_prev_ok = tail_prev == 1;
		
		bool test = head_ok && head_val_ok && head_next_ok && head_prev_ok
		    && tail_ok && tail_val_ok && tail_next_ok && tail_prev_ok;
		if( test )
		    ++result;
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_3elems_noorder_exclude_elem_middle_return_2elems);
}

