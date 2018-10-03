#include "treeset_stl_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_stl
{
    struct treeset_stl_test_insert_compare_with_stdtreeset
	: public treeset_stl_test_case
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
					    constexpr elem_t min = std::numeric_limits<elem_t>::min();
					    constexpr elem_t max = std::numeric_limits<elem_t>::max();
					    const elem_t el = *it;
					    this->container.insert(el);
					    this->testtreeset.insert(el);
					    for(elem_t j = min; j < max; ++j)
					    {
						bool contains = test_plug.getS(container).count(j) != 0;
						bool cmp_contains = testtreeset.count(j) != 0;
						if ( cmp_contains ^ contains )
						{
						    failed_list->add_failed(std::make_pair(el,j));
						    return false;
						}
					    }
					    bool contains = test_plug.getS(container).count(max) != 0;
					    bool cmp_contains = testtreeset.count(max) != 0;
					    if ( cmp_contains ^ contains )
					    {
						failed_list->add_failed(std::make_pair(el,max));
						return false;
					    }
					    return true;
					});
		return result;
	    }
	void configure()
	    { setup_data(); }
    };
    
    struct empty_insert_unique_elems_inorder_compare_with_stdtreeset
	: public treeset_stl_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_inorder_compare_with_stdtreeset);
    
    struct empty_insert_unique_elems_revorder_compare_with_stdtreeset
	: public treeset_stl_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(int i =std::numeric_limits<elem_t>::max(); i > std::numeric_limits<elem_t>::min(); --i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::min());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_revorder_compare_with_stdtreeset);

    struct empty_insert_unique_elems_noorder_compare_with_stdtreeset
	: public treeset_stl_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
		std::random_shuffle(data.begin(),data.end());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_insert_unique_elems_noorder_compare_with_stdtreeset);

    struct empty_insert_doubled_sticked_elems_inorder_compare_with_stdtreeset
	: public treeset_stl_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
	    {
		for(int i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_insert_doubled_sticked_elems_inorder_compare_with_stdtreeset);

    struct empty_insert_doubled_shuffled_elems_noorder_compare_with_stdtreeset
	: public treeset_stl_test_insert_compare_with_stdtreeset
    {
	TEST_INSERTER;
	void setup_data()
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
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),empty_insert_doubled_shuffled_elems_noorder_compare_with_stdtreeset);
}
