#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct treeset_array_test_contains_compare_with_stdtreeset
	: public treeset_array_test_case
    {
	elem_t step = (std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min())/15;
	std::vector<elem_t> data;
	test_result run()
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
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void configure(){}
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
    ENABLE_TEST(access_test_set(),empty_contains_all_vals_return_empty);

    struct populated_inorder_contains_compare_with_stdtreeset
	: public treeset_array_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_contains_compare_with_stdtreeset);

    struct populated_revorder_contains_compare_with_stdtreeset
    	: public treeset_array_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min()+step; i -=step)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_contains_compare_with_stdtreeset);
    
    struct populated_noorder_contains_compare_with_stdtreeset
	: public treeset_array_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-step; i +=step)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::random_shuffle(data.begin(),data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_contains_compare_with_stdtreeset);

    struct populated_inorder_doubled_sticked_contains_compare_with_stdtreeset
    	: public treeset_array_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-step; i +=step)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_doubled_sticked_contains_compare_with_stdtreeset);

    struct populated_inorder_doubled_shuffled_contains_compare_with_stdtreeset
	: public treeset_array_test_contains_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max()-step; i +=step)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
		std::random_shuffle(data.begin(),data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_doubled_shuffled_contains_compare_with_stdtreeset);
}
