#include "treeset_array_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array_balancing
{
    struct treeset_array_balancing_test_insert_compare_with_stdtreeset : public treeset_array_balancing_test_case
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
					container.insert(el);
					testtreeset.insert(el);
					auto cmp_end = testtreeset.end();
					for(elem_t j = min; j < max; ++j)
					{
					    auto find_res = test_plug.find(container, j);
					    auto vals = test_plug.get_values(container);
					    auto indexes = test_plug.get_indexes(container);
					    bool cmp_contains = this->testtreeset.count(j) != 0;
					    bool found = find_res < indexes.size() && indexes[find_res] != null;
					    bool contains =  found && vals[indexes[find_res]].first == j;
					    if ( cmp_contains ^ contains )
					    {
						failed_list->add_failed(std::make_pair(el,j));
						return false;
					    }
					}
					auto find_res = test_plug.find(container, max);
					auto vals = test_plug.get_values(container);
					auto indexes = test_plug.get_indexes(container);
					bool cmp_contains = this->testtreeset.count(max) != 0;
					bool found = find_res < indexes.size() && indexes[find_res] != null;
					bool contains =  found && vals[indexes[find_res]].first == max;
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

    struct empty_insert_unique_elems_inorder_compare_with_stdtreeset
	: public treeset_array_balancing_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_inorder_compare_with_stdtreeset);
    
    struct empty_insert_unique_elems_revorder_compare_with_stdtreeset
	: public treeset_array_balancing_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); i -=step)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_revorder_compare_with_stdtreeset);

    struct empty_insert_unique_elems_noorder_compare_with_stdtreeset
	: public treeset_array_balancing_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); i +=step)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::random_shuffle(data.begin(),data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_noorder_compare_with_stdtreeset);

    struct empty_insert_doubled_sticked_elems_inorder_compare_with_stdtreeset
	: public treeset_array_balancing_test_insert_compare_with_stdtreeset
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
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_doubled_sticked_elems_inorder_compare_with_stdtreeset);

    struct empty_insert_doubled_shuffled_elems_noorder_compare_with_stdtreeset
	: public treeset_array_balancing_test_insert_compare_with_stdtreeset
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
		std::random_shuffle(data.begin(),data.end());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_doubled_shuffled_elems_noorder_compare_with_stdtreeset);
}
