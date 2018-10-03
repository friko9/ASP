#include "list_array_enchanced_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_enchanced
{
    struct list_array_enchanced_test_insert_compare_with_stdlist : public list_array_enchanced_test_case
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
					    this->container.insert(el);
					    this->testlist.push_back(el);
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
    
    struct empty_insert_unique_elems_inorder_compare_with_stdlist
	: public list_array_enchanced_test_insert_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_inorder_compare_with_stdlist);
    
    struct empty_insert_unique_elems_revorder_compare_with_stdlist
	: public list_array_enchanced_test_insert_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_revorder_compare_with_stdlist);

    struct empty_insert_unique_elems_noorder_compare_with_stdlist
	: public list_array_enchanced_test_insert_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::random_shuffle(data.begin(),data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_noorder_compare_with_stdlist);

    struct empty_insert_doubled_sticked_elems_inorder_compare_with_stdlist
	: public list_array_enchanced_test_insert_compare_with_stdlist
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
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_doubled_sticked_elems_inorder_compare_with_stdlist);

    struct empty_insert_doubled_shuffled_elems_noorder_compare_with_stdlist
	: public list_array_enchanced_test_insert_compare_with_stdlist
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
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_doubled_shuffled_elems_noorder_compare_with_stdlist);
}
