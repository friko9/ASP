#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_case
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
						bool cmp_contains = this->testtreeset.count(el) != 0;
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
		setup_data();
		for( auto x : data )
		{
		    container.insert(x);
		    testtreeset.insert(x);
		}
	    }
    };
    
    struct empty_contains_all_vals_return_empty
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data(){}
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_contains_all_vals_return_empty);

    struct populated_inorder_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_contains_compare_with_stdtreeset);

    struct populated_inorder_all_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( int i = std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_all_contains_compare_with_stdtreeset);

    struct populated_noorder_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( int i = std::numeric_limits<elem_t>::max(); i > 0; i-=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_contains_compare_with_stdtreeset);

    struct populated_noorder_all_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::random_shuffle(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_all_contains_compare_with_stdtreeset);

    struct populated_revorder_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < 0; i+=3)
		    data.push_back(i);
		for( int i = 1; i < std::numeric_limits<elem_t>::max(); i+=7)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::reverse(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_contains_compare_with_stdtreeset);

    struct populated_revorder_all_contains_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for( int i = std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::reverse(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_all_contains_compare_with_stdtreeset);
}
