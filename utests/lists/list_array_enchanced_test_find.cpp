#include "list_array_enchanced_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_enchanced
{
    struct list_array_enchanced_test_find_compare_with_stdlist
	: public list_array_enchanced_test_case
    {
	test_result test()
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
					auto find_res = this->test_plug.find(container, el);
					int tail = this->test_plug.get_Tail(container);
					bool cmp_contains = cmp_res != cmp_end;
					bool contains = find_res != tail && this->test_plug.get_Elems(container)[find_res] == el;
					if( cmp_contains ^ contains )
					{
					    failed_list->add_failed(el);
					    return false;
					}
					return true;
				    });
		return result;
	    }
    };
    
    struct empty_find_all_vals_return_end
	: public list_array_enchanced_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_inorder_find_compare_with_stdlist
	: public list_array_enchanced_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1,13, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		test_plug.get_Prevs(container) = { 2, 0, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 1 };
		for( int i=2; i<data.size(); ++i )
		    testlist.push_back(data[i]);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_find_compare_with_stdlist);

    struct populated_noorder_find_compare_with_stdlist
	: public list_array_enchanced_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
		test_plug.get_Elems(container) = data;
		// next_string: head,10,12,8,6,4,2,1,3,5,7,9,11,tail
		test_plug.get_Nexts(container) = { 1,11, 4, 2, 6, 3, 8, 5,10, 7,12,13, 0, 9};
		// prev_string: tail,11,9,7,5,3,1,2,4,6,8,12,10,head
		test_plug.get_Prevs(container) = {12, 0, 3, 5, 2, 7, 4, 9, 6,13, 8, 1,10,11};
		for( int i=2; i<data.size(); ++i )
		    testlist.push_back(data[i]);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_find_compare_with_stdlist);

    struct populated_revorder_find_compare_with_stdlist
	: public list_array_enchanced_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 0 };
		test_plug.get_Prevs(container) = {13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		for( int i=2; i<data.size(); ++i )
		    testlist.push_back(data[i]);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_find_compare_with_stdlist);

    struct populated_singleelem_find_compare_with_stdlist
	: public list_array_enchanced_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 0, 0, 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = { 1, 2, 0 };
		test_plug.get_Prevs(container) = { 2, 0, 1 };
		for( int i=2; i<data.size(); ++i )
		    testlist.push_back(data[i]);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_find_compare_with_stdlist);
}
