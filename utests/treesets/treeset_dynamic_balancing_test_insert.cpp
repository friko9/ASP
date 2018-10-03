#include "treeset_dynamic_balancing_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_dynamic_balancing
{
    struct treeset_dynamic_balancing_test_insert_compare_with_stdtreeset : public treeset_dynamic_balancing_test_case
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
					container.insert(el);
					testtreeset.insert(el);
					auto cmp_end = testtreeset.end();
					auto root = test_plug.get_root(container);
					for(elem_t j = min; j < max; ++j)
					{
					    auto find_res = test_plug.find(container, j, root);
					    bool cmp_contains = testtreeset.count(j) != 0;
					    bool contains = find_res.first != nullptr && find_res.first->val == j ;
					    if ( cmp_contains ^ contains )
					    {
						failed_list->add_failed(std::make_pair(el,j));
						return false;
					    }
					}
					auto find_res = test_plug.find(container, max, root);
					bool cmp_contains = testtreeset.count(max) != 0;
					bool contains = find_res.first != nullptr && find_res.first->val == max ;
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
	: public treeset_dynamic_balancing_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_inorder_compare_with_stdtreeset);
    
    struct empty_insert_unique_elems_revorder_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void configure()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_revorder_compare_with_stdtreeset);

    struct empty_insert_unique_elems_noorder_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_insert_compare_with_stdtreeset
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
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_noorder_compare_with_stdtreeset);

    struct empty_insert_doubled_sticked_elems_inorder_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_insert_compare_with_stdtreeset
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
    ENABLE_TEST(access_test_set(),empty_insert_doubled_sticked_elems_inorder_compare_with_stdtreeset);

    struct empty_insert_doubled_shuffled_elems_noorder_compare_with_stdtreeset
	: public treeset_dynamic_balancing_test_insert_compare_with_stdtreeset
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
    ENABLE_TEST(access_test_set(),empty_insert_doubled_shuffled_elems_noorder_compare_with_stdtreeset);
}
