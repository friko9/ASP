#include "list_dynamic_test.h"

#include <algorithm>
#include <limits>

namespace test_list_dynamic
{
    struct list_dynamic_test_contains_compare_with_stdlist
	: public list_dynamic_test_case
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
	void configure()
	    {
		auto& head = test_plug.getHead(container);
		for( auto x : data)
		{
		    testlist.push_back(x);
		    node_t* n = new node_t {x,head.next};
		    head.next = n;
		}
	    }
    };

    struct empty_contains_all_vals_return_end
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_contains_all_vals_return_end);

    struct populated_single_min_contains_compare_with_stdlist
    	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data = { std::numeric_limits<elem_t>::min() };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_single_min_contains_compare_with_stdlist);

    struct populated_single_0_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data = { 0 };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_single_0_contains_compare_with_stdlist);

    struct populated_single_max_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data = { std::numeric_limits<elem_t>::max() };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_single_max_contains_compare_with_stdlist);

    struct populated_inorder_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data = { -100,-10,-9,-8,-6,-3,-1,0,1,4,9,100 };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_contains_compare_with_stdlist);

    struct populated_inorder_all_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back( std::numeric_limits<elem_t>::max() );
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_all_contains_compare_with_stdlist);

    struct populated_revorder_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		data = { 100,99,98,96,93,89,80,60,1,0,-1,-10,-30,-99};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_contains_compare_with_stdlist);

    struct populated_revorder_all_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		    data.push_back(i);
		data.push_back( std::numeric_limits<elem_t>::min() );
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_all_contains_compare_with_stdlist);

    struct populated_noorder_all_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back( std::numeric_limits<elem_t>::max() );
		std::random_shuffle(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_all_contains_compare_with_stdlist);

    struct populated_inorder_doubled_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		constexpr elem_t step = 7;
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-step; i +=step)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back( std::numeric_limits<elem_t>::max() );
		data.push_back( std::numeric_limits<elem_t>::max() );
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_doubled_contains_compare_with_stdlist);

    struct populated_noorder_doubled_contains_compare_with_stdlist
	: public list_dynamic_test_contains_compare_with_stdlist
    {
	TEST_INSERTER;
	void setup_data()
	    {
		constexpr elem_t step = 7;
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-step; i +=step)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back( std::numeric_limits<elem_t>::max() );
		data.push_back( std::numeric_limits<elem_t>::max() );
		std::random_shuffle(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_doubled_contains_compare_with_stdlist);
}
