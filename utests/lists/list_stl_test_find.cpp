#include "list_stl_test.h"

#include <algorithm>
#include <limits>

namespace test_list_stl
{
    struct list_stl_test_find_compare_with_stdlist
	: public list_stl_test_case
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
					auto find_end = this->test_plug.getL(container).end();
					auto find_res = this->test_plug.find(container, el);
					bool cmp_contains = cmp_res != cmp_end;
					bool contains = find_res != find_end && *find_res == el;
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
	: public list_stl_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure(){}
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_inorder_find_compare_with_stdlist : public list_stl_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		testlist.push_back(std::numeric_limits<elem_t>::min());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testlist.push_back(i);
		testlist.push_back(0);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testlist.push_back(i);
		testlist.push_back(std::numeric_limits<elem_t>::max());	    
		auto& list = test_plug.getL(container);
		list = testlist;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_find_compare_with_stdlist);

    struct populated_noorder_find_compare_with_stdlist : public list_stl_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    testlist.push_back(i);
		testlist.push_back(std::numeric_limits<elem_t>::min());
		testlist.push_back(0);
		testlist.push_back(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::min()+1; i < 0; i+=3)
		    testlist.push_back(i);
		auto& list = test_plug.getL(container);
		list = testlist;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_find_compare_with_stdlist);

    struct populated_revorder_find_compare_with_stdlist : public list_stl_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		testlist.push_back(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::max()-1; i > 0; i-=7)
		    testlist.push_back(i);
		testlist.push_back(0);
		for( int i = -1; i > std::numeric_limits<elem_t>::min(); i-=3)
		    testlist.push_back(i);
		testlist.push_back(std::numeric_limits<elem_t>::min());
		auto& list = test_plug.getL(container);
		list = testlist;
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_find_compare_with_stdlist);
}
