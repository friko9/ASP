#include "list_array_sorted_warden_test.h"

#include <algorithm>
#include <limits>

namespace test_list_array_sorted_warden
{
    struct list_array_sorted_warden_test_find_compare_with_stdlist : public list_array_sorted_warden_test_case
    {
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()-1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
				    std::numeric_limits<elem_t>::min()+1,
				    std::numeric_limits<elem_t>::max()-1,
				    [this,&failed_list](elem_t el) -> bool {
					auto cmp_end = this->testlist.end();
					auto cmp_res = find(this->testlist.begin(), cmp_end, el);
					auto find_res = this->test_plug.find(container, el);
					auto find_end = this->test_plug.get_Tail(container);
					bool cmp_contains = cmp_res != cmp_end;
					bool contains = find_res != find_end && this->test_plug.get_Elems(container)[find_res] == el;
					if( cmp_contains ^ contains )
					{
					    failed_list->add_failed(el);
					    return false;
					}
					return true;
				    });
		return result;
	    }
    };
    
    struct empty_find_all_vals_return_end : public list_array_sorted_warden_test_case
    {
	TEST_INSERTER;
	test_result run()
	    {
		test_result result = std::numeric_limits<elem_t>::max() - std::numeric_limits<elem_t>::min()-1;
		auto failed_list = std::make_shared<single_failed_list<elem_t>>();
		result.set_failed( failed_list );
		compare_test_range<elem_t>( result,
					    std::numeric_limits<elem_t>::min()+1,
					    std::numeric_limits<elem_t>::max()-1,
					    [this,&failed_list](elem_t el) -> bool {
						auto find_end = this->test_plug.get_Tail(container);
						auto find_res = this->test_plug.find(container,el);
						bool result = find_res == find_end;
						if( !result )
						    failed_list->add_failed(el);
						return result;
					    });
		return result;
	    }
    };
    ENABLE_TEST(access_test_set(),empty_find_all_vals_return_end);

    struct populated_inorder_find_compare_with_stdlist
	: public list_array_sorted_warden_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { max, min,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
		std::vector<int> next =     {null,  13, 0, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
		std::vector<int> prev =     {   2,null, 3, 4, 5, 6, 7, 8, 9,10,11,12,13, 1};

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);
		
		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_find_compare_with_stdlist);

    struct populated_noorder_find_compare_with_stdlist
	: public list_array_sorted_warden_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
		void configure()
	    {
		std::vector<elem_t> elems = { max, min, 7, 6, 8, 5, 9, 4,10, 3,11, 1,12, 2};
		// next_string: head,1,2,3,4,5,6,7,8,9,10,11,12,tail
		std::vector<int> next =     {null,  11, 4, 2, 6, 3, 8, 5,10, 7,12,13, 0, 9};
		// prev_string: tail,12,11,10,9,8,7,6,5,4,3,2,1,head
		std::vector<int> prev =     {  12,null, 3, 5, 2, 7, 4, 9, 6,13, 8, 1,10,11};

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);
		
		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_find_compare_with_stdlist);

    struct populated_revorder_find_compare_with_stdlist
	: public list_array_sorted_warden_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { max, min, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
		std::vector<int> next =     {null, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 0 };
		std::vector<int> prev =     {  13,null, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);

		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_find_compare_with_stdlist);

    struct populated_singleelem_find_compare_with_stdlist
	: public list_array_sorted_warden_test_find_compare_with_stdlist
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<elem_t> elems = { max, min, 1 };
		std::vector<int> next =     {null,   2, 0 };
		std::vector<int> prev =     {   2,null, 1 };

		for( int i=2; i<elems.size(); ++i )
		    testlist.push_back(elems[i]);
		
		test_plug.get_Elems(container) = std::move(elems);
		test_plug.get_Nexts(container) = std::move(next);
		test_plug.get_Prevs(container) = std::move(prev);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_singleelem_find_compare_with_stdlist);
}
