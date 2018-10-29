#include "sorting.h"
#include "includes/asp_sorting/selection_sort.h"

#include <algorithm>

namespace sorting
{
    struct populated_inorder_test_selection_sort_iter_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    { populate_data_allvals_inorder(); }
	test_result run()
	    {
		selection_sort_iter(data);
		return test_sorted(data);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_test_selection_sort_iter_state_sorted);

    struct populated_revorder_test_selection_sort_iter_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_allvals_inorder();
		std::reverse( data.begin(), data.end() );
	    }
	test_result run()
	    {
		selection_sort_iter(data);
		return test_sorted(data);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_test_selection_sort_iter_state_sorted);

    struct populated_noorder_test_selection_sort_iter_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_allvals_inorder();
		std::random_shuffle( data.begin(), data.end() );
	    }
	test_result run()
	    {
		selection_sort_iter(data);
		return test_sorted(data);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_test_selection_sort_iter_state_sorted);

    struct populated_double_inorder_test_selection_sort_iter_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    { populate_data_doublevals_inorder(); }
	test_result run()
	    {
		selection_sort_iter(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_inorder_test_selection_sort_iter_state_sorted);

    struct populated_double_revorder_test_selection_sort_iter_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_doublevals_inorder();
		std::reverse( data.begin(), data.end() );
	    }
	test_result run()
	    {
		selection_sort_iter(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_revorder_test_selection_sort_iter_state_sorted);

    struct populated_double_noorder_test_selection_sort_iter_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_doublevals_inorder();
		std::random_shuffle( data.begin(), data.end() );
	    }
	test_result run()
	    {
		selection_sort_iter(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_noorder_test_selection_sort_iter_state_sorted);
}
