#include "sorting.h"
#include "includes/asp_sorting/insertion_sort.h"

#include <algorithm>

namespace sorting
{
    struct populated_inorder_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_allvals_inorder();
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_test_insertion_sort_index_bitand_state_sorted);

    struct populated_revorder_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_allvals_inorder();
		std::reverse( data.begin(), data.end() );
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_test_insertion_sort_index_bitand_state_sorted);

    struct populated_noorder_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_allvals_inorder();
		std::random_shuffle( data.begin(), data.end() );
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_test_insertion_sort_index_bitand_state_sorted);

    struct populated_double_inorder_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_doublevals_inorder();
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_inorder_test_insertion_sort_index_bitand_state_sorted);

    struct populated_double_revorder_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_doublevals_inorder();
		std::reverse( data.begin(), data.end() );
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_revorder_test_insertion_sort_index_bitand_state_sorted);

    struct populated_double_noorder_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		populate_data_doublevals_inorder();
		std::random_shuffle( data.begin(), data.end() );
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_noorder_test_insertion_sort_index_bitand_state_sorted);

    struct populated_multiple_same_elem_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		for( int i=0; i < 100; ++i)
		    data.push_back(10);
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data,std::less_equal<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_multiple_same_elem_test_insertion_sort_index_bitand_state_sorted);

    struct populated_two_inorder_elem_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = {9,10};
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data,std::less<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_two_inorder_elem_test_insertion_sort_index_bitand_state_sorted);

    struct populated_two_revorder_elem_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = {10,9};
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return test_sorted(data,std::less<elem_t>());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_two_revorder_elem_test_insertion_sort_index_bitand_state_sorted);

    struct populated_single_elem_test_insertion_sort_index_bitand_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = {10};
		data.reserve(data.size()+1);
	    }
	test_result run()
	    {
		insertion_sort_index_bitand(data);
		return {1,1};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_single_elem_test_insertion_sort_index_bitand_state_sorted);
}
