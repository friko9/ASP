#include "treeset_array_test.h"

#include <algorithm>
#include <limits>

namespace test_treeset_array
{
    struct populated_c_traverse_last_c_on_left_return_c
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0}};
	    }
	test_result run()
	    {
		auto root = TestPlug_t::root;
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == root);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_left_return_c);

    struct populated_c_traverse_last_c_on_right_return_c
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0}};
	    }
	test_result run()
	    {
		auto root = TestPlug_t::root;
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == root);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_traverse_last_c_on_right_return_c);

    struct populated_c_l_traverse_last_c_on_left_return_l
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == 2);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_left_return_l);

    struct populated_c_l_traverse_last_c_on_right_return_c
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == 1);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_traverse_last_c_on_right_return_c);
    
    struct populated_c_r_traverse_last_c_on_left_return_c
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{3,1}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == 1);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_left_return_c);
    
    struct populated_c_r_traverse_last_c_on_right_return_r
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{3,1}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == 3);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_r_traverse_last_c_on_right_return_r);

    struct populated_c_l_r_traverse_last_c_on_left_return_l
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1},{3,1}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == 2);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_left_return_l);

    struct populated_c_l_r_traverse_last_c_on_right_return_r
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 32;
		data = {{1,0},{2,-1},{3,1}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == 3);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_c_l_r_traverse_last_c_on_right_return_r);

    struct populated_lml_traverse_last_c_on_left_return_last_l
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2048;
		data = {{1,-10},{2,-20},{4,-30},{8,-40},{16,-50},{32,-60},{64,-70},{128,-80},{256,-90},{512,-100}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == 512);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lml_traverse_last_c_on_left_return_last_l);

    struct populated_rmr_traverse_last_c_on_right_return_last_r
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 2048;
		data = {{1,10},{3,20},{7,30},{15,40},{31,50},{63,60},{127,70},{255,80},{511,90},{1023,100}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == 1023);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_traverse_last_c_on_right_return_last_r);
    
    struct populated_lml_lmlr_traverse_last_c_on_left_return_last_l
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,-10},{2,-20},{4,-30},{8,-40},{16,-50},{32,-60},{64,-70},{128,-80},{256,-90},{512,-100},{1025,-95}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == 512);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lml_lmlr_traverse_last_c_on_left_return_last_l);

    struct populated_rmr_rmrl_traverse_last_c_on_right_return_last_r
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,10},{3,20},{7,30},{15,40},{31,50},{63,60},{127,70},{255,80},{511,90},{1023,100},{2046,95}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == 1023);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_rmr_rmrl_traverse_last_c_on_right_return_last_r);

    struct populated_lrml_traverse_last_c_on_left_return_last_l
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,0},{2,-10},{3,10},{4,-20},{5,-5},{8,-30},{9,-15},{16,-40},{17,-25},{32,-50},{33,-35}
			,{64,-60},{63,-45},{128,-70},{129,-55},{256,-80},{257,-65},{512,-90},{513,-75},{1025,-85}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::left);
		return score_t(ret == 512);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lrml_traverse_last_c_on_left_return_last_l);

    struct populated_lrmr_traverse_last_c_on_right_return_last_r
	: public treeset_array_test_case
    {
	TEST_INSERTER;
	void setup_data()
	    {
		tree_size = 4096;
		data = {{1,0},{2,-10},{3,10},{6,5},{7,20},{14,15},{15,30},{30,25},{31,40},{62,35},{63,50},{126,45}
			,{127,60},{254,55},{255,70},{510,65},{511,80},{1022,75},{1023,90},{2046,85}};
	    }
	test_result run()
	    {
		auto ret = test_plug.traverse_last(container, root, side_t::right);
		return score_t(ret == 1023);
	    }
    };
    ENABLE_TEST(access_test_set(),populated_lrmr_traverse_last_c_on_right_return_last_r);
}
