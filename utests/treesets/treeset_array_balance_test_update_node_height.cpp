#include "treeset_array_balance_test.h"

namespace test_treeset_array_balance
{
    struct treeset_array_test_update_node_height
	: public treeset_array_balance_test_case
    {
	index_t index;
	std::vector<node_t> expected_values;
	std::vector<index_t> expected_indexes;
	std::vector<height_t> expected_heights;
	score_t compare(std::vector<node_t>& vals1,std::vector<index_t> &indexes1,std::vector<height_t> &heights1,
			std::vector<node_t>& vals2,std::vector<index_t> &indexes2,std::vector<height_t> &heights2)
	    {
		score_t score = indexes1.size() == indexes2.size();
		for(int i=0; i<indexes1.size(); ++i)
		{
		    bool indexes_null = indexes1[i] == null && indexes2[i] == null;
		    bool index1_ok = indexes1[i] < vals1.size();
		    bool index2_ok = indexes2[i] < vals2.size();
		    bool vals_equal = index1_ok && index2_ok && vals1[indexes1[i]] == vals2[indexes2[i]];
		    score += indexes_null || vals_equal;
		}
		for(int i=0; i<heights1.size(); ++i)
		    score += heights1[i] == heights2[i];
		return score;
	    }
	test_result test()
	    {
		test_plug.update_node_height(container, index);
		bool index_size_match = test_plug.get_indexes(container).size() == expected_indexes.size();
		bool heights_size_match = test_plug.get_indexes(container).size() == expected_indexes.size();
		if( index_size_match && heights_size_match )
		    return compare(expected_values,
				   expected_indexes,
				   expected_heights,
				   test_plug.get_values(container),
				   test_plug.get_indexes(container),
				   test_plug.get_heights(container));
		else
		    return score_t(false);
	    }
    };
    
    struct treesize2_c99_update_node_height_c_state_c1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2;
		data = {{1,0,99}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize2_c99_update_node_height_c_state_c1);

    struct treesize8_c99_update_node_height_c_state_c1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_update_node_height_c_state_c1);

    struct treesize4_c99_l1_update_node_height_c_state_c2_l1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{2,-1,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{2,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c99_l1_update_node_height_c_state_c2_l1);

    struct treesize8_c99_l1_update_node_height_c_state_c2_l1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-1,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{2,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_l1_update_node_height_c_state_c2_l1);

    struct treesize4_c99_l10_update_node_height_c_state_c11_l10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{2,-1,10}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,11},{2,-1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c99_l10_update_node_height_c_state_c11_l10);

    struct treesize8_c99_l10_update_node_height_c_state_c11_l10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-1,10}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,11},{2,-1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_l10_update_node_height_c_state_c11_l10);

    struct treesize4_c99_r1_update_node_height_c_state_c2_r1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{3,1,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{3,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c99_r1_update_node_height_c_state_c2_r1);

    struct treesize8_c99_r1_update_node_height_c_state_c2_r1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{3,1,1}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,2},{3,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_r1_update_node_height_c_state_c2_r1);

    struct treesize4_c99_r12_update_node_height_c_state_c13_r12
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{3,1,12}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,13},{3,1,12}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c99_r12_update_node_height_c_state_c13_r12);

    struct treesize8_c99_r12_update_node_height_c_state_c13_r12
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{3,1,12}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,13},{3,1,12}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_r12_update_node_height_c_state_c13_r12);

    struct treesize4_c99_l10_r20_update_node_height_c_state_c21_l10_r20
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{2,-1,10},{3,1,20}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,21},{2,-1,10},{3,1,20}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c99_l10_r20_update_node_height_c_state_c21_l10_r20);

    struct treesize8_c99_l10_r20_update_node_height_c_state_c21_l10_r20
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-1,10},{3,1,20}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,21},{2,-1,10},{3,1,20}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_l10_r20_update_node_height_c_state_c21_l10_r20);

    struct treesize4_c99_l20_r10_update_node_height_c_state_c21_l20_r10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4;
		data = {{1,0,99},{2,-1,20},{3,1,10}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,21},{2,-1,20},{3,1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize4_c99_l20_r10_update_node_height_c_state_c21_l20_r10);

    struct treesize8_c99_l20_r10_update_node_height_c_state_c21_l20_r10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{1,0,99},{2,-1,20},{3,1,10}};
		index = 1;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{1,0,21},{2,-1,20},{3,1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_c99_l20_r10_update_node_height_c_state_c21_l20_r10);

    struct treesize8_lr99_update_node_height_lr_state_lr1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{5,0,99}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize8_lr99_update_node_height_lr_state_lr1);

    struct treesize16_lr99_update_node_height_lr_state_lr1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 8;
		data = {{5,0,99}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_update_node_height_lr_state_lr1);

    struct treesize16_lr99_lrl1_update_node_height_lr_state_lr2_lrl1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{5,0,99},{10,-1,1}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,2},{10,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_lrl1_update_node_height_lr_state_lr2_lrl1);

    struct treesize32_lr99_lrl1_update_node_height_lr_state_lr2_lrl1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{5,0,99},{10,-1,1}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,2},{10,-1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_lr99_lrl1_update_node_height_lr_state_lr2_lrl1);

    struct treesize16_lr99_lrl10_update_node_height_lr_state_lr11_lrl10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{5,0,99},{10,-1,10}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,11},{10,-1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_lrl10_update_node_height_lr_state_lr11_lrl10);

    struct treesize32_lr99_lrl10_update_node_height_lr_state_lr11_lrl10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{5,0,99},{10,-1,10}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,11},{10,-1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_lr99_lrl10_update_node_height_lr_state_lr11_lrl10);

    struct treesize16_lr99_lrr1_update_node_height_lr_state_lr2_lrr1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{5,0,99},{11,1,1}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,2},{11,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_lrr1_update_node_height_lr_state_lr2_lrr1);

    struct treesize32_lr99_lrr1_update_node_height_lr_state_lr2_lrr1
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{5,0,99},{11,1,1}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,2},{11,1,1}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_lr99_lrr1_update_node_height_lr_state_lr2_lrr1);

    struct treesize16_lr99_lrr10_update_node_height_lr_state_lr11_lrr10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{5,0,99},{11,1,10}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,11},{11,1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_lrr10_update_node_height_lr_state_lr11_lrr10);

    struct treesize32_lr99_lrr10_update_node_height_lr_state_lr11_lrr10
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{5,0,99},{11,1,10}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,11},{11,1,10}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_lr99_lrr10_update_node_height_lr_state_lr11_lrr10);
    
    struct treesize16_lr99_lrl19_lrr20_update_node_height_lr_state_lr21_lrl19_lrr20
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{5,0,99},{10,-1,19},{11,1,20}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,21},{10,-1,19},{11,1,20}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_lrl19_lrr20_update_node_height_lr_state_lr21_lrl19_lrr20);

    struct treesize32_lr99_lrl19_lrr20_update_node_height_lr_state_lr21_lrl19_lrr20
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{5,0,99},{10,-1,19},{11,1,20}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,21},{10,-1,19},{11,1,20}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_lr99_lrl19_lrr20_update_node_height_lr_state_lr21_lrl19_lrr20);

    struct treesize16_lr99_lrl20_lrr19_update_node_height_lr_state_lr21_lrl20_lrr19
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 16;
		data = {{5,0,99},{10,-1,20},{11,1,19}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,21},{10,-1,20},{11,1,19}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize16_lr99_lrl20_lrr19_update_node_height_lr_state_lr21_lrl20_lrr19);

    struct treesize32_lr99_lrl20_lrr19_update_node_height_lr_state_lr21_lrl20_lrr19
	: public treeset_array_test_update_node_height
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{5,0,99},{10,-1,20},{11,1,19}};
		index = 5;
		std::tie(expected_values,expected_indexes,expected_heights)
		    = make_data(tree_size,{{5,0,21},{10,-1,20},{11,1,19}});
	    }
	test_result run(){ return test(); }
    };
    ENABLE_TEST(access_test_set(),treesize32_lr99_lrl20_lrr19_update_node_height_lr_state_lr21_lrl20_lrr19);

}
