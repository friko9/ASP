#include "list_array_selforganizing_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_selforganizing
{
    struct list_array_selforganizing_test_contains_compare_with_stdlist
	: public list_array_selforganizing_test_case
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
    
    struct empty_contains_all_vals_return_end
	: public list_array_selforganizing_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_contains_all_vals_return_end);

    struct populated_inorder_contains_compare_with_stdlist
	: public list_array_selforganizing_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12 };		
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,null};
		test_plug.get_Prevs(container) = {null, 0, 1, 2, 3, 4, 5, 6, 7,  8,  9, 10 };
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 11;
		for( auto x : data )
		    testlist.push_back(x);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_contains_compare_with_stdlist);

    struct populated_noorder_contains_compare_with_stdlist
	: public list_array_selforganizing_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
		test_plug.get_Elems(container) = data;
		// next_string: head,3,5,7,9,11,12,10,8,6,4,2,1,tail
		test_plug.get_Nexts(container) = {null, 0,   4, 1, 6, 3, 8, 5,10, 7,11, 9};
		// prev_string: tail,1,2,4,6,8,10,12,11,9,7,5,3,head
		test_plug.get_Prevs(container) = {   1, 3,null, 5, 2, 7, 4, 9, 6,11, 8,10};
		test_plug.get_Head(container) = 2;
		test_plug.get_Tail(container) = 0;
		for( auto x : data )
		    testlist.push_back(x);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_contains_compare_with_stdlist);

    struct populated_revorder_contains_compare_with_stdlist
	: public list_array_selforganizing_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {null, 0, 1, 2, 3, 4, 5, 6, 7,  8,  9,  10};
		test_plug.get_Prevs(container) = {   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,null};
		test_plug.get_Head(container) = 11;
		test_plug.get_Tail(container) = 0;
		for( auto x : data )
		    testlist.push_back(x);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_contains_compare_with_stdlist);

    struct populated_singleelem_contains_compare_with_stdlist
	: public list_array_selforganizing_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		data = { 1 };
		test_plug.get_Elems(container) = data;
		test_plug.get_Nexts(container) = {null};
		test_plug.get_Prevs(container) = {null};
		test_plug.get_Head(container) = 0;
		test_plug.get_Tail(container) = 0;
		for( auto x : data )
		    testlist.push_back(x);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_contains_compare_with_stdlist);
}

