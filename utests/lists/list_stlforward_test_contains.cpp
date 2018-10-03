#include "list_stlforward_test.h"

#include <algorithm>
#include <limits>

namespace test_list_stlforward
{

    struct list_stlforward_test_contains_compare_with_stdlist : public list_stlforward_test_case
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
    
    struct empty_contains_all_vals_return_end : public list_stlforward_test_case
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
	: public list_stlforward_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		testlist.push_front(std::numeric_limits<elem_t>::min());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testlist.push_front(i);
		testlist.push_front(0);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testlist.push_front(i);
		testlist.push_front(std::numeric_limits<elem_t>::max());	    
		auto& list = test_plug.getL(container);
		for( auto x : testlist )
		    list.push_front(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_contains_compare_with_stdlist);

    struct populated_noorder_contains_compare_with_stdlist
	: public list_stlforward_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testlist.push_front(i);
		testlist.push_front(std::numeric_limits<elem_t>::min());
		testlist.push_front(0);
		testlist.push_front(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testlist.push_front(i);
		auto& list = test_plug.getL(container);
		for( auto x : testlist )
		    list.push_front(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_contains_compare_with_stdlist);

    struct populated_revorder_contains_compare_with_stdlist
	: public list_stlforward_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		testlist.push_front(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::max()-1; i > 0; i-=7)
		    testlist.push_front(i);
		testlist.push_front(0);
		for( int i = -1; i > std::numeric_limits<elem_t>::min(); i-=3)
		    testlist.push_front(i);
		testlist.push_front(std::numeric_limits<elem_t>::min());
		auto& list = test_plug.getL(container);
		for( auto x : testlist )
		    list.push_front(x);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_contains_compare_with_stdlist);

}
