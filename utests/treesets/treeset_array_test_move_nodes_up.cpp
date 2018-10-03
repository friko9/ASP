#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct treeset_array_test_move_nodes_up
	: public treeset_array_test_case
    {
	size_t del_index;
	std::vector<node_t> cmp_values;
	std::vector<size_t> cmp_indexes;
	test_result test()
	    {
		test_plug.move_nodes_up(container, del_index);
		score_t values_ok = compare(cmp_values, test_plug.get_values(container));
		score_t indexes_ok = compare(cmp_indexes, test_plug.get_indexes(container));
		return values_ok + indexes_ok;
	    }
    };
	
    struct treesize2_c_move_nodes_up_2_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,1}};
		std::vector<size_t> indexes{ null, 0};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = values;
		cmp_indexes = { null, null };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize2_c_move_nodes_up_2_state_null);

    struct treesize2_c_move_nodes_up_3_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,1}};
		std::vector<size_t> indexes{ null, 0};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 3;
		cmp_values = values;
		cmp_indexes = { null, null };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize2_c_move_nodes_up_3_state_null);

    struct treesize8_c_move_nodes_up_2_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,1}};
		std::vector<size_t> indexes { null, 0, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = values;
		cmp_indexes = { null, null, null, null, null, null, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_move_nodes_up_2_state_null);

    struct treesize8_c_move_nodes_up_3_state_null
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,1}};
		std::vector<size_t> indexes { null, 0, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 3;
		cmp_values = values;
		cmp_indexes = { null, null, null, null, null, null, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c_move_nodes_up_3_state_null);

    struct treesize4_c_l_move_nodes_up_2_state_cxl
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,1},{-1,2}};
		std::vector<size_t> indexes { null, 0, 1, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = { {1,1},{-1,1}};
		cmp_indexes = { null, 1, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_move_nodes_up_2_state_cxl);

    struct treesize16_c_l_move_nodes_up_2_state_cxl
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {1,1},{-1,2}};
		std::vector<size_t> indexes { null, 0, 1, null, null, null, null, null
			, null, null, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = { {1,1},{-1,1}};
		cmp_indexes = { null, 1, null, null, null, null, null, null
				,null, null, null, null, null, null, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_move_nodes_up_2_state_cxl);

    struct treesize4_c_r_move_nodes_up_3_state_cxr
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{1,3}};
		std::vector<size_t> indexes { null, 0, null, 1};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 3;
		cmp_values = { {0,1},{1,1}};
		cmp_indexes = { null, 1, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_r_move_nodes_up_3_state_cxr);

    struct treesize16_c_r_move_nodes_up_3_state_cxr
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{1,3}};
		std::vector<size_t> indexes { null, 0, null, 1, null, null, null, null
			, null, null, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 3;
		cmp_values = { {0,1},{1,1}};
		cmp_indexes = { null, 1, null, null, null, null, null, null
				,null, null, null, null, null, null, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_r_move_nodes_up_3_state_cxr);

    struct treesize4_c_l_r_move_nodes_up_2_state_cxl
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-1,2},{1,3}};
		std::vector<size_t> indexes { null, 0, 1, 2};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = { {0,1},{-1,1},{1,3}};
		cmp_indexes = { null, 1, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_up_2_state_cxl);

    struct treesize16_c_l_r_move_nodes_up_2_state_cxl
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-1,2},{1,3}};
		std::vector<size_t> indexes { null, 0, 1, 2, null, null, null, null
			, null, null, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 2;
		cmp_values = { {0,1},{-1,1},{1,3}};
		cmp_indexes = { null, 1, null, null, null, null, null, null
				,null, null, null, null, null, null, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_move_nodes_up_2_state_cxl);

    struct treesize4_c_l_r_move_nodes_up_3_state_cxr
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-1,2},{1,3}};
		std::vector<size_t> indexes { null, 0, 1, 2};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 3;
		cmp_values = { {0,1},{-1,2},{1,1}};
		cmp_indexes = { null, 2, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c_l_r_move_nodes_up_3_state_cxr);

    struct treesize16_c_l_r_move_nodes_up_3_state_cxr
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-1,2},{1,3}};
		std::vector<size_t> indexes { null, 0, 1, 2, null, null, null, null
			, null, null, null, null, null, null, null, null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 3;
		cmp_values = { {0,1},{-1,2},{1,1}};
		cmp_indexes = { null, 2, null, null, null, null, null, null
				,null, null, null, null, null, null, null, null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_c_l_r_move_nodes_up_3_state_cxr);

    struct treesize16_full16_move_nodes_up_4_state_lxll_llxlll_llrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 4;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,2},{-2,5},{2,6},{6,7}
			       ,{-7,4},{-5,5},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		cmp_indexes = { null, 0, 3, 2, 7, 8, 5, 6, null, null, null, null, 11, 12, 13, 14 };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_4_state_lxll_llxlll_llrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize32_full16_move_nodes_up_4_state_lxll_llxlll_llrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
			null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 4;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,2},{-2,5},{2,6},{6,7}
			       ,{-7,4},{-5,5},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		cmp_indexes = { null, 0, 3, 2, 7, 8, 5, 6, null, null, null, null, 11, 12, 13, 14,
				null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_4_state_lxll_llxlll_llrxllr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize16_full16_move_nodes_up_5_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 5;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,4},{-2,2},{2,6},{6,7}
			       ,{-7,8},{-5,9},{-3,4},{-1,5},{1,12},{3,13},{5,14},{7,15}};
		cmp_indexes = { null, 0, 4, 2, 9, 10, 5, 6, null, null, null, null, 11, 12, 13, 14 };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_5_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize32_full16_move_nodes_up_5_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
			null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 5;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,4},{-2,2},{2,6},{6,7}
			       ,{-7,8},{-5,9},{-3,4},{-1,5},{1,12},{3,13},{5,14},{7,15}};
		cmp_indexes = { null, 0, 4, 2, 9, 10, 5, 6, null, null, null, null, 11, 12, 13, 14,
				null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_5_state_lxlr_llxlrl_lrxlrr_lllxnull_llrxnull_lrlxnull_lrrxnull);

    struct treesize16_full16_move_nodes_up_6_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 6;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,3},{6,7}
			       ,{-7,8},{-5,9},{-3,10},{-1,11},{1,6},{3,7},{5,14},{7,15}};
		cmp_indexes = { null, 0, 1, 5, 3, 4, 11, 12, 7, 8, 9, 10, null, null, null, null };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_6_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull);

    struct treesize32_full16_move_nodes_up_6_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
			null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 6;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,3},{6,7}
			       ,{-7,8},{-5,9},{-3,10},{-1,11},{1,6},{3,7},{5,14},{7,15}};
		cmp_indexes = { null, 0, 1, 5, 3, 4, 11, 12, 7, 8, 9, 10, null, null, null, null,
				null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_6_state_rxrl_rlxrll_rrxrlr_rllxnull_rlrxnull_rrlxnull_rrrxnull);

    struct treesize16_full16_move_nodes_up_7_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 7;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,3}
			       ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,6},{7,7}};
		cmp_indexes = { null, 0, 1, 6, 3, 4, 13, 14, 7, 8, 9, 10, null, null, null, null };
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_full16_move_nodes_up_7_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull);

    struct treesize32_full16_move_nodes_up_7_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull
	: public treeset_array_test_move_nodes_up
    {
	TEST_INSERTER;
	void configure()
	    {
		std::vector<node_t> values { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,7}
		    ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,14},{7,15}};
		std::vector<size_t> indexes { null, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
			null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
		test_plug.get_values(container) = values;
		test_plug.get_indexes(container) = indexes;
		del_index = 7;
		cmp_values = { {0,1},{-4,2},{4,3},{-6,4},{-2,5},{2,6},{6,3}
			       ,{-7,8},{-5,9},{-3,10},{-1,11},{1,12},{3,13},{5,6},{7,7}};
		cmp_indexes = { null, 0, 1, 6, 3, 4, 13, 14, 7, 8, 9, 10, null, null, null, null,
				null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null};
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_full16_move_nodes_up_7_state_rxrr_rlxrrl_rrxrrr_rllxnull_rlrxnull_rrlxnull_rrrxnull);
}
