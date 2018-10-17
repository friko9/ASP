 #include "list_array_sorted_warden_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_sorted_warden
{  
    struct list_array_sorted_warden_test_remove_compare_with_stdlist
	: public list_array_sorted_warden_test_case
    {
	test_result test()
	    {
		using It = std::vector<elem_t>::iterator;
		test_result result = data.size();
		auto failed_list = std::make_shared<single_failed_list<std::pair<elem_t,elem_t>>>();
		result.set_failed( failed_list );
		compare_test_range<It>( result,
				    data.begin(),
				    data.end()-1,
				    [this,&failed_list](It it) -> bool {
					constexpr elem_t min = std::numeric_limits<elem_t>::min()+1;
					constexpr elem_t max = std::numeric_limits<elem_t>::max()-1;
					const elem_t el = *it;
					auto rem_it = std::find(testlist.begin(),testlist.end(),*it);
					if(rem_it != testlist.end())
					    this->testlist.erase(rem_it);
					this->container.remove(el);
					auto cmp_end = this->testlist.end();
					for(elem_t j = min; j < max; ++j)
					{
					    auto cmp_res = std::find(this->testlist.begin(), cmp_end, j);
					    bool contains = this->container.contains(j);
					    bool cmp_contains = cmp_res != cmp_end;
					    if ( cmp_contains ^ contains )
					    {
						failed_list->add_failed(std::make_pair(el,j));
						return false;
					    }
					}
					auto cmp_res = std::find(this->testlist.begin(), cmp_end, max);
					bool contains = this->container.contains(max);
					bool cmp_contains = cmp_res != cmp_end;
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
    
    struct populated_inorder_remove_inorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    testlist.push_back(i);
		    container.insert(i);
		    data.push_back(i);
		}
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_inorder_compare_with_stdlist);
    
    struct populated_inorder_remove_revorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    container.insert(i);
		    testlist.push_back(i);
		    data.push_back(i);
		}
		std::reverse(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_revorder_compare_with_stdlist);

    struct populated_inorder_remove_noorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    container.insert(i);
		    testlist.push_back(i);
		    data.push_back(i);
		}
		std::random_shuffle(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_noorder_compare_with_stdlist);

    struct populated_revorder_remove_inorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::max()-1; i > std::numeric_limits<elem_t>::min(); --i)
		{
		    data.push_back(i);
		    container.insert(i);
		    testlist.push_back(i);
		}
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_inorder_compare_with_stdlist);

    struct populated_revorder_remove_revorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::max()-1; i > std::numeric_limits<elem_t>::min(); --i)
		{
		    data.push_back(i);
		    container.insert(i);
		    testlist.push_back(i);
		}
		std::reverse(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_revorder_compare_with_stdlist);

    struct populated_revorder_remove_noorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::max()-1; i > std::numeric_limits<elem_t>::min(); --i)
		{
		    container.insert(i);
		    testlist.push_back(i);
		    data.push_back(i);
		}
		std::random_shuffle(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_noorder_compare_with_stdlist);

    struct populated_noorder_remove_inorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testlist.push_back(x);
		}
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_inorder_compare_with_stdlist);

    struct populated_noorder_remove_revorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testlist.push_back(x);
		}
		std::reverse(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_revorder_compare_with_stdlist);

    struct populated_noorder_remove_noorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
				
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testlist.push_back(x);
		}
		std::random_shuffle(data.begin(), data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_noorder_compare_with_stdlist);

    struct populated_doubled_inorder_remove_inorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		
		for(auto x : data )
		{
		    container.insert(x);
		    testlist.push_back(x);
		}
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_doubled_inorder_remove_inorder_compare_with_stdlist);

    struct populated_doubled_shuffled_remove_inorder_compare_with_stdlist
	: public list_array_sorted_warden_test_remove_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min()+1; i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    data.push_back(i);
		    data.push_back(i);
		}

		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testlist.push_back(x);
		}
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),populated_doubled_shuffled_remove_inorder_compare_with_stdlist);
}
