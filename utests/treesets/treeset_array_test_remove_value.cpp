#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct treeset_array_test_remove_value
	: public treeset_array_test_case
    {
	size_t del_index;
	std::vector<node_t> cmp_values;
	std::vector<size_t> cmp_indexes;
	test_result run()
	    {
		test_plug.remove_value(container, del_index);
		score_t values_ok = compare(cmp_values, test_plug.get_values(container));
		score_t indexes_ok = compare(cmp_indexes, test_plug.get_indexes(container));
		return values_ok + indexes_ok;
	    }
    };
	
    struct populated_c1_l2_null0_remove_value_0_return_c1_l0
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,null}, {0,1}, {-1,2}};
		std::vector<size_t> indexes{ null, 1, 2, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 0;
		cmp_values = { {-1,2}, {0,1} };
		cmp_indexes = { null, 1, 0, null, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c1_l2_null0_remove_value_0_return_c1_l0);

    struct populated_c2_l0_null1_remove_value_1_return_c1_l0
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {-1,2}, {1,null}, {0,1}};
		std::vector<size_t> indexes{ null, 2, 0, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 1;
		cmp_values = { {-1,2}, {0,1}};
		cmp_indexes = { null, 1, 0, null, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c2_l0_null1_remove_value_1_return_c1_l0);

    struct populated_c1_l0_null2_remove_value_2_return_c1_l0
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {-1,2}, {0,1}, {1,null}};
		std::vector<size_t> indexes{ null, 1, 0, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = { {-1,2}, {0,1}};
		cmp_indexes = { null, 1, 0, null, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c1_l0_null2_remove_value_2_return_c1_l0);

    struct populated_null0_remove_value_0_return_empty
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values {{1,null}};
		std::vector<size_t> indexes{ null, null, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 0;
		cmp_values = {};
		cmp_indexes = { null, null, null, null, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_null0_remove_value_0_return_empty);
    
    struct populated_c1_l2_r0_remove_value_0_return_c1_l0_r0
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,3}, {0,1}, {-1,2}};
		std::vector<size_t> indexes{ null, 1, 2, 0, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 0;
		cmp_values = { {-1,2}, {0,1}};
		cmp_indexes = { null, 1, 0, 0, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c1_l2_r0_remove_value_0_return_c1_l0_r0);

    struct populated_c2_l0_r1_remove_value_1_return_c1_l0_r1
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {-1,2}, {1,3}, {0,1}};
		std::vector<size_t> indexes{ null, 2, 0, 1, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 1;
		cmp_values = { {-1,2}, {0,1}};
		cmp_indexes = { null, 1, 0, 1, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c2_l0_r1_remove_value_1_return_c1_l0_r1);

    struct populated_c1_l0_r2_remove_value_2_return_c1_l0_r2
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {-1,2}, {0,1}, {1,3}};
		std::vector<size_t> indexes{ null, 1, 0, 2, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = { {-1,2}, {0,1}};
		cmp_indexes = { null, 1, 0, 2, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c1_l0_r2_remove_value_2_return_c1_l0_r2);

    struct populated_c0_remove_value_0_return_c0
	: public treeset_array_test_remove_value
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values {{1,1}};
		std::vector<size_t> indexes{ null, 0, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 0;
		cmp_values = {};
		cmp_indexes = { null, 0, null, null, null, null, null, null};
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c0_remove_value_0_return_c0);
}
