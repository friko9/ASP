 #include "hashset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_hashset_array
{  
    struct hashset_array_test_remove_compare_with_stdhashset : public hashset_array_test_case
    {
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
					    auto rem_it = testhashset.find(el);
					    if(rem_it != testhashset.end())
						this->testhashset.erase(rem_it);
					    this->container.remove(el);
					    for(elem_t j = min; j < max; ++j)
					    {
						bool contains = this->container.contains(j);
						bool cmp_contains = this->testhashset.count(j) != 0;
						if ( cmp_contains ^ contains )
						{
						    failed_list->add_failed(std::make_pair(el,j));
						    return false;
						}
					    }
					    bool contains = this->container.contains(max);
					    bool cmp_contains = this->testhashset.count(max) != 0;
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
    
    struct populated_inorder_remove_inorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    testhashset.insert(i);
		    container.insert(i);
		    data.push_back(i);
		}
		testhashset.insert(std::numeric_limits<elem_t>::max());
		container.insert(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_inorder_compare_with_stdhashset);
    
    struct populated_inorder_remove_revorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    container.insert(i);
		    testhashset.insert(i);
		    data.push_back(i);
		}
		testhashset.insert(std::numeric_limits<elem_t>::max());
		container.insert(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());

		std::reverse(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_revorder_compare_with_stdhashset);

    struct populated_inorder_remove_noorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    container.insert(i);
		    testhashset.insert(i);
		    data.push_back(i);
		}
		testhashset.insert(std::numeric_limits<elem_t>::max());
		container.insert(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
		
		std::random_shuffle(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_remove_noorder_compare_with_stdhashset);

    struct populated_revorder_remove_inorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		{
		    data.push_back(i);
		    container.insert(i);
		    testhashset.insert(i);
		}
		testhashset.insert(std::numeric_limits<elem_t>::min());
		container.insert(std::numeric_limits<elem_t>::min());
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_inorder_compare_with_stdhashset);

    struct populated_revorder_remove_revorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		{
		    data.push_back(i);
		    container.insert(i);
		    testhashset.insert(i);
		}
		testhashset.insert(std::numeric_limits<elem_t>::min());
		container.insert(std::numeric_limits<elem_t>::min());
		data.push_back(std::numeric_limits<elem_t>::min());

		std::reverse(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_revorder_compare_with_stdhashset);

    struct populated_revorder_remove_noorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		{
		    container.insert(i);
		    testhashset.insert(i);
		    data.push_back(i);
		}
		testhashset.insert(std::numeric_limits<elem_t>::min());
		container.insert(std::numeric_limits<elem_t>::min());
		data.push_back(std::numeric_limits<elem_t>::min());

		std::random_shuffle(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_remove_noorder_compare_with_stdhashset);

    struct populated_noorder_remove_inorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_inorder_compare_with_stdhashset);

    struct populated_noorder_remove_revorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
		std::reverse(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_revorder_compare_with_stdhashset);

    struct populated_noorder_remove_noorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
				
		std::random_shuffle(data.begin(),data.end());
		for(auto x : data )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
		std::random_shuffle(data.begin(), data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_remove_noorder_compare_with_stdhashset);

    struct populated_doubled_inorder_remove_inorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
		
		for(auto x : data )
		{
		    container.insert(x);
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_doubled_inorder_remove_inorder_compare_with_stdhashset);

    struct populated_doubled_shuffled_remove_inorder_compare_with_stdhashset : public hashset_array_test_remove_compare_with_stdhashset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
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
		    testhashset.insert(x);
		}
	    }
    };
    ENABLE_TEST(access_test_set(),populated_doubled_shuffled_remove_inorder_compare_with_stdhashset);
}
