#include "list_array_enchanced_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_enchanced
{
    struct list_array_enchanced_test_contains_compare_with_stdlist : public list_array_enchanced_test_case
    {
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()+1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
				    std::numeric_limits<elem_t>::min(),
				    std::numeric_limits<elem_t>::max(),
				    [this,&failed_list](elem_t el) -> bool {
					auto cmp_end = this->testlist.end();
					auto cmp_res = find(this->testlist.begin(), cmp_end, el);
					bool cmp_contains = cmp_res != cmp_end;
					if( cmp_contains ^ this->container.contains(el) )
					{
					    failed_list->add_failed(el);
					    return false;
					}
					return true;
				    });
		return result;
	    }
    };
    
    struct empty_contains_all_vals_return_end : public list_array_enchanced_test_case
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()+1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    std::numeric_limits<elem_t>::min(),
					    std::numeric_limits<elem_t>::max(),
					    [this,&failed_list](elem_t el) -> bool {
						bool result =  !this->container.contains(el);
						if( !result )
						    failed_list->add_failed(el);
						return result;
					    });
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),empty_contains_all_vals_return_end);

    struct populated_inorder_contains_compare_with_stdlist
	: public list_array_enchanced_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		std::vector<int> next =     { 1,13, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		std::vector<int> prev =     { 2, 0, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 1 };

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);
		
		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_contains_compare_with_stdlist);

    struct populated_noorder_contains_compare_with_stdlist
	: public list_array_enchanced_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
		// next_string: head,10,12,8,6,4,2,1,3,5,7,9,11,tail
		std::vector<int> next =     { 1,11, 4, 2, 6, 3, 8, 5,10, 7,12,13, 0, 9};
		// prev_string: tail,11,9,7,5,3,1,2,4,6,8,12,10,head
		std::vector<int> prev =     {12, 0, 3, 5, 2, 7, 4, 9, 6,13, 8, 1,10,11};

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);
		
		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_contains_compare_with_stdlist);

    struct populated_revorder_contains_compare_with_stdlist
	: public list_array_enchanced_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		std::vector<int> next =     { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 0 };
		std::vector<int> prev =     {13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);

		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_contains_compare_with_stdlist);

    struct populated_singleelem_contains_compare_with_stdlist
	: public list_array_enchanced_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { 0, 0, 1 };
		std::vector<int> next = { 1, 2, 0 };
		std::vector<int> prev = { 2, 0, 1 };

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);
		
		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_contains_compare_with_stdlist);
}

