#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{  
    struct treeset_array_test_remove_compare_with_stdtreeset : public treeset_array_test_case
    {
	elem_t step = (std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min())/15;
	std::vector<elem_t> data;
	test_result run()
	    {
		using It = std::vector<elem_t>::iterator;
		test_result result = data.size();
		auto failed_list = std::make_shared<single_failed_list<std::pair<elem_t,elem_t>>>();
		result.set_failed( failed_list );
		compare_test_range<It>( result,
					data.begin(),
					data.end()-1,
					[this,&failed_list](It it) -> bool {
					    constexpr elem_t min = std::numeric_limits<elem_t>::min();
					    constexpr elem_t max = std::numeric_limits<elem_t>::max();
					    const elem_t el = *it;
					    auto rem_it = testtreeset.find(el);
					    if(rem_it != testtreeset.end())
						this->testtreeset.erase(rem_it);
					    this->container.remove(el);
					    for(elem_t j = min; j < max; ++j)
					    {
						bool contains = this->container.contains(j);
						bool cmp_contains = this->testtreeset.count(j) != 0;
						if ( cmp_contains ^ contains )
						{
						    failed_list->add_failed(std::make_pair(el,j));
						    return false;
						}
					    }
					    bool contains = this->container.contains(max);
					    bool cmp_contains = this->testtreeset.count(max) != 0;
					    if ( cmp_contains ^ contains )
					    {
						failed_list->add_failed(std::make_pair(el,max));
						return false;
					    }
					    return true;
					});
		return result;
	    }
    };
    
    struct populated_inorder_remove_inorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step)
		{
		    testtreeset.insert(i);
		    container.insert(i);
		    data.push_back(i);
		}
		testtreeset.insert(std::numeric_limits<elem_t>::max());
		container.insert(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_inorder_compare_with_stdtreeset);
    
    struct populated_inorder_remove_revorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step)
		{
		    container.insert(i);
		    testtreeset.insert(i);
		    data.push_back(i);
		}
		testtreeset.insert(std::numeric_limits<elem_t>::max());
		container.insert(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());

		std::reverse(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_revorder_compare_with_stdtreeset);

    struct populated_inorder_remove_noorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step )
		{
		    container.insert(i);
		    testtreeset.insert(i);
		    data.push_back(i);
		}
		testtreeset.insert(std::numeric_limits<elem_t>::max());
		container.insert(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
		
		std::random_shuffle(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_noorder_compare_with_stdtreeset);

    struct populated_revorder_remove_inorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); i -=step )
		{
		    data.push_back(i);
		    container.insert(i);
		    testtreeset.insert(i);
		}
		testtreeset.insert(std::numeric_limits<elem_t>::min());
		container.insert(std::numeric_limits<elem_t>::min());
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_inorder_compare_with_stdtreeset);

    struct populated_revorder_remove_revorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); i -=step )
		{
		    data.push_back(i);
		    container.insert(i);
		    testtreeset.insert(i);
		}
		testtreeset.insert(std::numeric_limits<elem_t>::min());
		container.insert(std::numeric_limits<elem_t>::min());
		data.push_back(std::numeric_limits<elem_t>::min());

		std::reverse(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_revorder_compare_with_stdtreeset);

    struct populated_revorder_remove_noorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); i -=step )
		{
		    container.insert(i);
		    testtreeset.insert(i);
		    data.push_back(i);
		}
		testtreeset.insert(std::numeric_limits<elem_t>::min());
		container.insert(std::numeric_limits<elem_t>::min());
		data.push_back(std::numeric_limits<elem_t>::min());

		std::random_shuffle(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_noorder_compare_with_stdtreeset);

    struct populated_noorder_remove_inorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testtreeset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_inorder_compare_with_stdtreeset);

    struct populated_noorder_remove_revorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testtreeset.insert(x);
		}
		std::reverse(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_revorder_compare_with_stdtreeset);

    struct populated_noorder_remove_noorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step )
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
				
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testtreeset.insert(x);
		}
		std::random_shuffle(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_noorder_compare_with_stdtreeset);

    struct populated_doubled_inorder_remove_inorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
		
		for(auto x : data )
		{
		    container.insert(x);
		    testtreeset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_doubled_inorder_remove_inorder_compare_with_stdtreeset);

    struct populated_doubled_shuffled_remove_inorder_compare_with_stdtreeset : public treeset_array_test_remove_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step )
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());

		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testtreeset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_doubled_shuffled_remove_inorder_compare_with_stdtreeset);
}
